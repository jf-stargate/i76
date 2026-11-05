"""Authenticated decoder and connected diagnostic raster experiments; metadata only."""
import argparse,json,struct,sys,collections
from pathlib import Path
sys.dont_write_bytecode=True
from corpus import Corpus,sha,EXE,GZF
from decoder import decode,InvalidTexture
from retail import Machine

def fixture(w,h,tokens=None):
    cb=struct.pack('<I',3)+bytes((t*61+y*7+x*3)&255 for t in range(3) for y in range(4) for x in range(4))
    ts=tokens or [([0,1,2,0x81fe,0x80ff,0x8000][i%6]) for i in range(((w+3)//4)*((h+3)//4))]
    return struct.pack('<II16s',w,h,b'synthetic.cbk')+struct.pack('<'+'H'*len(ts),*ts),cb

def original_decode(exe,v,cb,capacity=None):
    m=Machine(exe);vptr=m.add_resource('v',v);cptr=m.add_resource('c',cb);w,h=struct.unpack_from('<II',v);size=8+w*(h&0x1fffffff);out=m.alloc(size)
    result=m.call(0x44b430,[vptr,cptr,out,w*h+24 if capacity is None else capacity]);b=bytes(m.u.mem_read(out,size))
    assert m.guards()
    return m,result,b

def raster(m,texture,w,h,lum,tbl,operation,length,u0=-2,v0=-1,du=0.5,dv=0.25):
    cmd,desc,spans,fb=0x20400000,0x20401000,0x20402000,0x20500000
    m.u.mem_write(cmd,bytes(256));m.u.mem_write(desc,bytes(128));m.u.mem_write(spans,bytes(64));m.u.mem_write(fb,b'\xa5'*4096)
    m.u.mem_write(0x61b2a0,lum);m.u.mem_write(0x60afa0,tbl)
    m.w32(cmd,texture);m.f32(cmd+12,u0*65536);m.f32(cmd+16,v0*65536);m.f32(cmd+20,1.0);m.f32(cmd+24,15*256)
    m.f32(cmd+0x40,du*65536);m.f32(cmd+0x48,dv*65536)
    m.w32(cmd+0x28,(2<<21)|(length<<10)|1);m.w32(cmd+0x2c,spans);m.w32(cmd+0x30,spans+4)
    x,y=2,1;m.w32(spans+4,(x<<21)|(length<<10)|y)
    m.w32(desc,64);m.w32(desc+0x14,fb)
    before=len(m.stores);read_start=len(m.reads);m.watch_texture=(texture+8,w*h);sampler_before=m.u32(0x6439c0)
    m.call(0x485120 if operation=='shade' else 0x4828e0,[cmd,desc]);stores=m.stores[before:]
    # Fractional negatives require arithmetic >> of rounded signed 16.16.
    coords=[((round((u0+du*(x+i))*65536)>>16)&(w-1),(round((v0+dv*(x+i))*65536)>>16)&(h-1)) for i in range(length)]
    pixels=bytes(m.u.mem_read(texture+8,w*h));texels=[pixels[yy*w+xx] for xx,yy in coords]
    expected=bytes(lum[15*256+t] if operation=='shade' else tbl[t*256+165] for t in texels)
    got=bytes(m.u.mem_read(fb+64*y+x,length));assert got==expected,(operation,length,list(got),list(expected),coords)
    reads=m.reads[read_start:];actual=[r for r in reads if r['kind']=='texel'];assert [r['index'] for r in actual]==texels
    assert [int(r['address'],16) for r in actual]==[texture+8+yy*w+xx for xx,yy in coords]
    lookups=[r for r in reads if r['kind']==('lum' if operation=='shade' else 'tbl')]
    assert [int(r['address'],16) for r in lookups]==[(0x61b2a0+15*256+t) if operation=='shade' else (0x60afa0+t*256+165) for t in texels]
    assert [r['index'] for r in lookups]==list(expected)
    assert len(stores)==length and all(s['size']==1 for s in stores)
    fbbytes=bytes(m.u.mem_read(fb,4096));assert fbbytes[:66]==b'\xa5'*66 and fbbytes[66+length:]==b'\xa5'*(4096-66-length)
    rows=[m.u32(0x6439d8+i*4) for i in range(h)];assert rows==[texture+8+i*w for i in range(h)]
    return dict(operation=operation,length=length,command='20400000',descriptor='20401000',texture=f'{texture:08x}',framebuffer='20500000',span_x=x,span_y=y,span_word=f'{((x<<21)|(length<<10)|y):08x}',u0=u0,v0=v0,du_dx=du,dv_dx=dv,q=1,shade_row=15 if operation=='shade' else None,destination_before=165,coordinates=coords,sampled_indices=texels,result_indices=list(got),stores=stores,original_memory_reads=reads,row_cache_previous=f'{sampler_before:08x}',row_cache_current=f'{m.u32(0x6439c0):08x}',row_cache_sha256=sha(b''.join(struct.pack('<I',p) for p in rows)))

def run(repo,root,out):
    exe=root/'orig/i76.exe';assert sha(exe.read_bytes())==EXE and sha((root/'scratch_data/i76exe_v100.gzf').read_bytes())==GZF
    c=Corpus(repo,root);out.mkdir(parents=True,exist_ok=False);coverage=collections.Counter()
    def cover(m):
        previous=getattr(m,"coverage_reported",collections.Counter())
        coverage.update(m.seen-previous);m.coverage_reported=m.seen.copy()
    report=c.survey();(out/'corpus.json').write_text(json.dumps(report,indent=2)+'\n')
    comparisons=[];names=['xb11mdu1.vqm','al11mdu1.vqm','3abrtms1.vqm']
    # Additional specimen per distinct shape, private name inventory omitted from publication.
    shape_seen=set()
    for name in sorted(c.members):
        if name.endswith('.vqm'):
            shape=struct.unpack_from('<II',c.get(name))
            if shape not in shape_seen:shape_seen.add(shape);names.append(name)
    names=list(dict.fromkeys(names))
    for name in names:
        v=c.get(name);dep=v[8:24].split(b'\0')[0].decode().lower();cb=c.get(dep);m,ret,b=original_decode(exe,v,cb);assert ret==1 and b==decode(v,cb);cover(m)
        comparisons.append(dict(source=c.identity(name),codebook=c.identity(dep),dimensions=list(struct.unpack_from('<II',v)),runtime_length=len(b),runtime_sha256=sha(b),texel_sha256=sha(b[8:]),original_return=ret,independent_equal=True,instructions=sum(m.seen.values())))
    synthetic=[]
    for w,h in [(1,1),(3,2),(4,4),(5,7),(7,5),(8,8),(9,1),(1,9)]:
        v,cb=fixture(w,h);m,r,b=original_decode(exe,v,cb);assert r==1 and b==decode(v,cb);cover(m)
        synthetic.append(dict(width=w,height=h,result=r,independent_equal=True,runtime_sha256=sha(b)))
    v,cb=fixture(5,7)
    for cap in [0,8+35,24+35-1,24+35,24+35+1]:
        m,r,b=original_decode(exe,v,cb,cap);assert r==int(cap>=59);cover(m);synthetic.append(dict(test='capacity',capacity=cap,result=r,output_untouched=(b==b'\xa5'*43)))
    # CBK count does not bound retail access; full backing retained for safe execution.
    altered=struct.pack('<I',0)+cb[4:];m,r,b=original_decode(exe,v,altered);assert b==decode(v,cb);cover(m);synthetic.append(dict(test='cbk_count_zero_full_backing',result=r,same_bytes=True))
    rejects=[]
    for label,vv,cc in [('short_header',v[:7],cb),('short_tokens',v[:-1],cb),('bad_index',fixture(4,4,[3])[0],cb),('short_cbk',v,cb[:-1]),('zero_width',struct.pack('<I',0)+v[4:],cb),('height_flags',v[:4]+struct.pack('<I',0x40000007)+v[8:],cb)]:
        try:decode(vv,cc)
        except InvalidTexture:rejects.append(label)
        else:raise AssertionError(label)
    connected=[];lum=c.get('m02.lum');tbl=bytearray(c.get('m02.tbl'));tbl[255*256:]=bytes(range(256));tbl=bytes(tbl)
    for name in ['xb11mdu1.vqm','al11mdu1.vqm']:
        v=c.get(name);dep=v[8:24].split(b'\0')[0].decode().lower();m=Machine(exe);m.add_resource(name,v);m.add_resource(dep,c.get(dep));m.w32(0x609564,0);m.w32(0x5dd2a8,0)
        mapname=name[:-4]+'.map';m.u.mem_write(0x20010000,mapname.encode()+b'\0')
        tmtname='1xb1mdun.tmt' if name.startswith('xb') else '4al1mdun.tmt'
        tmtptr=m.add_resource(tmtname,c.get(tmtname));descriptor=m.alloc(0x34)
        assert m.call(0x44ab90,[tmtptr,descriptor])==1
        frame=m.cstr(m.u32(descriptor+0x2c));assert frame==mapname
        m.u.mem_write(0x20011000,b'V1 MD UN.MAP\0');owner=0x20012000
        slot=m.call(0x44ac80,[owner,0x20011000,0x20011000,descriptor]);assert slot
        p=m.call(0x44a290,[owner,0x20011000,0]);assert p and bytes(m.u.mem_read(p,4104))==decode(v,c.get(dep));assert m.guards()
        assert m.u32(slot+0x34)==p and m.u32(slot+0x3c)==0
        owner_layout=dict(owner=f'{owner:08x}',slot=f'{slot:08x}',logical_material='V1 MD UN.MAP',tmt=c.identity(tmtname),descriptor=f'{descriptor:08x}',first_frame=frame,dimension_count=m.u32(descriptor+0x1c),dimension_product=m.u32(descriptor+0x20),slot_words=[m.u32(slot+4*i) for i in range(18)])
        p2=m.call(0x4474b0,[0x20010000]);assert p2==p
        acquisitions=list(m.events);draws=[]
        for op in ['shade','compose']:
            for length in [1,2,5,16,17,33]:draws.append(raster(m,p,64,64,lum,tbl,op,length))
        m16name=name[:-4]+'.m16';m16=c.get(m16name);m16ptr=m.add_resource(m16name,m16)
        m.w32(0x58da14,1) # externally supplied initialized empty FULLRES hash bitset
        m.w32(0x20013000+0x3c,0x20014000);m.w32(0x20014000+8,1)
        m16result=m.call(0x44a290,[owner,0x20011000,0x20013000]);assert m16result==m16ptr and m.u32(slot+0x38)==m16ptr
        m16obs=dict(source=c.identity(m16name),result=f'{m16result:08x}',before_header=list(struct.unpack_from('<II',m16)),after_header=[m.u32(m16ptr),m.u32(m16ptr+4)],services=m.events[len(acquisitions):],context='supplied context+3c -> descriptor with +8==1; initialized empty FULLRES bitmap')
        assert m.guards();cover(m)
        connected.append(dict(source=name,m16_observation=m16obs,owner_layout=owner_layout,logical_request=mapname,runtime_pointer=f'{p:08x}',runtime_sha256=sha(bytes(m.u.mem_read(p,4104))),allocations=[dict(pointer=f'{a:08x}',bytes=n) for a,n in m.allocations],acquisition_services=acquisitions,draws=draws,guards_intact=True,cache_hit_same_pointer=True))
    selection=[]
    sv,sc=fixture(8,8);sm=struct.pack('<II',8,8)+bytes(range(64))
    for label,prefer,have_vqm,have_cbk,have_map in [('vqm_first',0,1,1,1),('map_first',1,1,1,1),('map_fallback',0,0,0,1),('vqm_fallback',1,1,1,0),('missing_cbk',0,1,0,1),('all_missing',0,0,0,0)]:
        m=Machine(exe);m.w32(0x609564,prefer);m.w32(0x5dd2a8,0)
        if have_vqm:m.add_resource('choice.vqm',sv)
        if have_cbk:m.add_resource('synthetic.cbk',sc)
        mp=m.add_resource('choice.map',sm) if have_map else 0
        m.u.mem_write(0x20010000,b'choice.map\0');p=m.call(0x4474b0,[0x20010000]);cover(m)
        expected=sm if label in ('map_first','map_fallback') else decode(sv,sc) if label in ('vqm_first','vqm_fallback') else None
        assert (p==0) if expected is None else (bytes(m.u.mem_read(p,len(expected)))==expected)
        selection.append(dict(test=label,prefer=prefer,result=f'{p:08x}',services=list(m.events)))
        if label=='vqm_first':
            m.w32(0x609564,1);events=len(m.events);p2=m.call(0x4474b0,[0x20010000]);assert p2==p and len(m.events)==events;cover(m)
            selection.append(dict(test='cached_vqm_overrides_changed_preference',same_pointer=True,no_resource_calls=True))
    name='mcalt101.map';b=c.get(name);m=Machine(exe);mp=m.add_resource(name,b);m.w32(0x609564,0);m.w32(0x5dd2a8,0);m.u.mem_write(0x20010000,name.encode()+b'\0');p=m.call(0x4474b0,[0x20010000]);assert p==mp;cover(m)
    selection.append(dict(test='authentic_direct_map',source=c.identity(name),result=f'{p:08x}',resource_pointer_returned=True,runtime_sha256=sha(bytes(m.u.mem_read(p,len(b)))),dimensions=list(struct.unpack_from('<II',b)),services=m.events))
    sv,sc=fixture(8,8,[0x8000,0x80ff,0x80fe,0x8001]);m,r,b=original_decode(exe,sv,sc);ptr=m.alloc(len(b));m.u.mem_write(ptr,b)
    # This synthetic transparency test injects an already original-decoded copy;
    # authentic connected fixtures never copy/reconstruct their decoded textures.
    reserved=[raster(m,ptr,8,8,lum,tbl,op,5,-2,0,1,0) for op in ['shade','compose']];cover(m)
    (out/'reserved_indices.json').write_text(json.dumps(reserved,indent=2)+'\n')
    (out/'selection.json').write_text(json.dumps(selection,indent=2)+'\n')
    (out/'execution.json').write_text(json.dumps(dict(decoder_comparisons=comparisons,synthetic_original=synthetic,strict_host_rejections=rejects,connected=connected,color_resources=[c.identity('m02.lum'),c.identity('m02.tbl')],runtime_tbl_sha256=sha(tbl)),indent=2)+'\n')
    (out/'executed_instructions.json').write_text(json.dumps([dict(va=f'{p:08x}',length=s,sha256=h,count=n) for (p,s,h),n in sorted(coverage.items())],indent=2)+'\n')
    print('passed',len(comparisons),'retail decodes',len(synthetic),'synthetic original cases',len(rejects),'host rejects',sum(len(d['stores']) for c in connected for d in c['draws']),'connected pixel stores')
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--repo',type=Path,required=True);p.add_argument('--root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();run(a.repo,a.root,a.out)
