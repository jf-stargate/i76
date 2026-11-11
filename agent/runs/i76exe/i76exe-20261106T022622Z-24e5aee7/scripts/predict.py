"""Independent camera -> terrain footprint/root/hull/planes. No observation reader.

Inputs: 472-byte view, viewport width, independent terrain height provider.
Numerics selects emulated float64 arithmetic or native x87 extended arithmetic.
Neither original root, plane, threshold nor hull fields are accepted as inputs.
"""
import math, struct
import numpy as np
from coordinate_model import f32
if np.finfo(np.longdouble).nmant!=63:
    raise RuntimeError("This measured model requires x86 64-significand-bit longdouble")

R=f32(.2)
def bits(v):return f'{struct.unpack("<I",struct.pack("<f",v))[0]:08X}'
def dbits(v):return struct.pack('<d',v).hex()
def bias(v,T=float):
    b=struct.pack('<d',float(T(v)+T(6755399441055744.)))
    return struct.unpack('<i',b[:4])[0]

def seed_table():
    table=[]
    for i in range(256):
        d=struct.unpack('<d',struct.pack('<II',0,((i|0x1ff00)<<13)&0xffffffff))[0]
        high=struct.unpack('<II',struct.pack('<d',1/math.sqrt(d)))[1]
        table.append(((high+0x400)>>12)&255)
    table[128]=255
    return bytes(table)

TABLE=seed_table()
def invsqrt(d,T):
    hi=struct.unpack('<II',struct.pack('<d',d))[1]
    index=(hi>>13)&255
    # AND EAX,0xff precedes MOV AL and SHL.
    a=TABLE[index]<<12
    hi2=((((0xbfc-(hi>>20))&0xffffffff)>>1)<<20)|(a&0xffffffff)
    y=T(struct.unpack('<d',struct.pack('<II',0,hi2&0xffffffff))[0])
    return ((T(3)-T(d)*(y*y))*(y*T(.5)))*T(1.00001)

def predict(view,width,height,T=float,quality=0):
    d=lambda o:struct.unpack_from('<d',view,o)[0]
    f=lambda o:struct.unpack_from('<f',view,o)[0]
    c=[d(0x160+8*k) for k in range(3)]
    corners=[[d(0x178+24*j+8*k) for k in range(3)] for j in range(4)]
    qx,qz={0:(6.4,1/256),2:(40,struct.unpack("<f",bytes.fromhex("f853e33a"))[0])}.get(quality,(16,1/384))
    tx=f32(T(abs(f(8)))*T(f32(qx))/T(width>>1))
    tz=f32(abs(T(f(0x2c))*T(f(0x2c))*T(4))*T(f32(qz))*T(5)*T(10))
    out={'threshold_bits':[bits(tx),bits(tz)],'camera_lattice_bits':[bits(T(c[0])*T(R)),bits(T(c[2])*T(R))]}
    if T(c[1])-T(height(c[0],c[2]))<T(.01):
        return out|{'accepted':False,'reason':'camera_height'}
    pts=[[float(T(c[0])*T(R)),0.,float(T(c[2])*T(R))]]
    pts += [[float(T(p[0])*T(R)),0.,float(T(p[2])*T(R))] for p in corners]
    initial=[p[:] for p in pts]
    ground=all(p[1]<=0 for p in corners)
    if ground:
        for p,q in zip(pts[1:],corners):
            t=T(R)*T(q[1])/(T(c[1])-T(q[1]))
            p[0]=float((T(q[0])-T(c[0]))*t+T(p[0]))
            p[2]=float((T(q[2])-T(c[2]))*t+T(p[2]))
    ints=[[bias(v,T) for v in (p[0],p[2])] for p in pts]
    # Initial camera extrema retain the extended products across FST. The
    # all-ground branch resets them from the stored double camera point.
    if not ground:ints[0]=[bias(T(c[k])*T(R),T) for k in [0,2]]
    mins=[min([0x3400]+[p[k] for p in ints]) for k in range(2)]
    maxs=[max([-0xc00]+[p[k] for p in ints]) for k in range(2)]
    roots=[(v&~31)-32 for v in mins]
    extent=max(maxs[k]-roots[k] for k in range(2))
    if extent<0:raise ValueError('negative extent causes original nonterminating SAR loop')
    root=roots+[extent.bit_length()]
    kept=[];keep=[]
    for j,p in enumerate(pts):
        retain=True
        for q in pts[j+1:]:
            dx=T(p[0])-T(q[0]);dz=T(p[2])-T(q[2])
            # Original spills dx and retains dz across the squared-distance test.
            if dx*T(float(dx))+dz*dz<T(.25):retain=False;break
        keep.append(retain)
        if retain:kept.append(p[:])
    out|={'ground':ground,'initial':initial,'points':pts,'root':root,'keep':keep,'filtered':kept}
    if len(kept)<3:return out|{'accepted':False,'reason':'distinct_points'}
    n=len(kept)
    start=min(range(n),key=lambda j:(kept[j][2],-j))
    work=[p[:] for p in kept]+[kept[start][:]]
    lower=T(0);selected=start;i=0;scores=[]
    while True:
        work[i],work[selected]=work[selected],work[i]
        best=T(125663706.14359173);selected=n
        for j in range(i+1,n+1):
            dx=T(work[j][0])-T(work[i][0]);dz=T(work[j][2])-T(work[i][2])
            angle=T(np.arctan2(np.longdouble(dz),np.longdouble(dx)))
            if angle<0:angle-=T(-6.283185307179586)
            dx=T(float(dx));dz=T(float(dz))
            score=float((dz*dz+dx*dx)-angle*T(-10000000.))
            scores.append({'step':i,'slot':j,'score':score,'lower':float(lower)})
            if lower<T(score)<best:selected=j;best=T(score)
        lower=best;i+=1
        if selected==n:break
        if i>=n:raise ValueError('hull did not close')
    hull=work[:i]
    sx=T(0);sz=T(0)
    for p in hull:sx+=T(p[0]);sz+=T(p[2])
    cx=float(sx*(T(1)/T(i)));cz=float(sz*(T(1)/T(i)))
    planes=[];flips=[]
    for k,p in enumerate(hull):
        q=hull[k-1]
        dx=float(T(q[0])-T(p[0]));dz=float(T(q[2])-T(p[2]))
        # Cross((q-p),(p+(0,10,0)-p)), with each cross result stored f64.
        ny=float(T(0)*T(dz)-T(0)*T(dx))
        nx=float(T(0)*T(0)-T(10)*T(dz));nz=float(T(10)*T(dx)-T(0)*T(0))
        d2=float(T(nz)*T(nz)+T(nx)*T(nx))
        inv=invsqrt(d2,T)
        ex=T(nx)*inv;ez=T(nz)*inv
        offset=float((-ex*T(p[0]))-ez*T(p[2]))
        fx,fz=f32(ex),f32(ez)
        flip=T(fx)*T(cx)+T(fz)*T(cz)+T(offset)<0
        if flip:fx=-fx;fz=-fz;offset=-offset
        planes.append({'nx_bits':bits(fx),'ny_bits':bits(T(ny)*inv),'nz_bits':bits(fz),'padding_bits':'00000000','offset_le':dbits(offset),'nx':fx,'nz':fz,'offset':offset})
        flips.append(bool(flip))
    return out|{'accepted':True,'hull':hull,'scores':scores,'centroid':[cx,cz],'planes':planes,'flips':flips}
