"""Independent rational IEEE arithmetic. No Python float/pow in LUM calculation.
Finite normal range only: this is the measured palette domain, not a full FPU.
CW selects PC and RC; conversion service is explicitly truncation toward zero.
"""
from fractions import Fraction as F
from hashlib import sha256

def binary(bits, frac, bias):
    sign=-1 if bits>>(frac+(bias*2+1).bit_length()) else 1
    ebits=(bias*2+1).bit_length()
    exp=(bits>>frac)&((1<<ebits)-1)
    mant=bits&((1<<frac)-1)
    if exp==(1<<ebits)-1: raise ValueError('nonfinite')
    if exp: mant|=1<<frac
    e=(exp or 1)-bias-frac
    return sign*F(mant)*(F(2)**e)

def f32(bits): return binary(bits,23,127)
def f64(bits): return binary(bits,52,1023)
def ext80(raw):
    b=int.from_bytes(raw,'little');exp=(b>>64)&32767
    if exp==32767: raise ValueError('nonfinite')
    return (-1 if b>>79 else 1)*F(b&((1<<64)-1))*F(2)**((exp or 1)-16383-63)

def rounded(x,p,rc=0):
    x=F(x)
    if not x:return x
    n,d=abs(x.numerator),x.denominator
    e=n.bit_length()-d.bit_length()
    if F(2)**e>abs(x):e-=1
    unit=F(2)**(e-p+1)
    q=abs(x)/unit
    floor=q.numerator//q.denominator
    tail=q-floor
    up=(tail>F(1,2) or (tail==F(1,2) and floor%2)) if rc==0 else bool(tail and ((rc==1 and x<0) or (rc==2 and x>0)))
    return (-1 if x<0 else 1)*(floor+int(up))*unit

class Arithmetic:
    def __init__(self,cw=0x37f):
        self.p={0:24,2:53,3:64}[(cw>>8)&3]
        self.rc=(cw>>10)&3
    def op(self,x):return rounded(x,self.p,self.rc)
    def spill(self,x,p=24):return rounded(x,p,self.rc)
    def channels(self,value,early=False):
        start=f32(0x3c23d70a);norm=f32(0x3b808081)
        t=self.op(self.op(value*norm)-start)
        if early:t=self.spill(t)
        step=self.spill(self.op(t*f32(0x3d25294a)))
        state=start;out=[];history=[]
        for row in range(31,-1,-1):
            v=self.op(state*255)
            out.append(max(0,min(255,int(v))))
            history.append((row,state,step,v))
            state=self.spill(self.op(state+step))
            if row==8:
                t=self.op(1-state)
                if early:t=self.spill(t)
                step=self.spill(self.op(t*f32(0x3d6e23b9)))
        return out,history

class Nearest:
    def __init__(self,palette):
        if len(palette)!=768:raise ValueError('palette length')
        self.p=[tuple(palette[i:i+3]) for i in range(0,768,3)]
        self.cache={}
    def lookup(self,q,cache=True,tie_last=False):
        key=tuple(v>>3 for v in q)
        if cache and key in self.cache:return self.cache[key]
        d=[sum((a-b)**2 for a,b in zip(q,p)) for p in self.p[:255]]
        best=min(range(255),key=lambda i:(d[i],-i if tie_last else i))
        if cache:self.cache[key]=best
        return best

def lum(palette,cw=0x37f,early=False,cache=True,tie_last=False,row_major=False):
    a=Arithmetic(cw);channels=[a.channels(i,early)[0] for i in range(256)]
    n=Nearest(palette);out=bytearray(65536)
    pairs=((c,r) for c in range(256) for r in range(32))
    if row_major:pairs=((c,r) for r in range(32) for c in range(256))
    for col,r in pairs:
        q=[channels[palette[3*col+k]][r] for k in range(3)]
        out[(31-r)*256+col]=n.lookup(q,cache,tie_last)
    for r in range(32,144):out[r*256:(r+1)*256]=out[31*256:32*256]
    for r in range(144,256):out[r*256:(r+1)*256]=out[:256]
    return bytes(out)

def digest(b):return sha256(b).hexdigest()

def synthetic():
    # Deterministic RGB8 palettes; payloads authored here, not retail resources.
    return {
      'gray':bytes(v for i in range(256) for v in (i,i,i)),
      'permuted':bytes(v for i in range(256) for v in (i,(73*i+19)&255,(151*i+7)&255)),
      'ties':bytes([0,0,0,4,0,0,4,0,0]+[255,255,255]*252+[2,0,0]),
    }
