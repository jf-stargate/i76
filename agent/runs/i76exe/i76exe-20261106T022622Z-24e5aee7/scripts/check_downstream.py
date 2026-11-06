#!/usr/bin/env python3
"""#140 source graph consumer, now supplied exclusively predicted camera geometry."""
import argparse,json,struct,hashlib
from pathlib import Path
import numpy as np
from compare import predictions,dump,RUN
from verify_topology import Model,original_predicate

p=argparse.ArgumentParser()
for k in ['cases','msn','ter']:p.add_argument('--'+k,type=Path,required=True)
p.add_argument('--fixtures',type=Path,default=RUN/'evidence/camera_fixtures.json');p.add_argument('--emit',type=Path,default=RUN/'evidence/downstream.json');a=p.parse_args();msn=a.msn.read_bytes();ter=a.ter.read_bytes()
assert hashlib.sha256(msn).hexdigest()=='923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'
assert hashlib.sha256(ter).hexdigest()=='fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'
zm=msn[msn.index(b'ZMAP')+9:msn.index(b'ZMAP')+6409]
def sample(x,z):
    assert 0<=x<10240 and 0<=z<10240
    page=zm[(z//128)*80+x//128];assert page!=255
    return struct.unpack_from('<H',ter,page*32768+2*((z&127)*128+(x&127)))[0]
def special(x,z,size):
    if min(x,z)<0 or max(x,z)>10240:return False
    page=zm[(z//128)*80+x//128];assert page!=255
    start=page*32768+2*((z&127)*128+(x&127))
    for i in range(size-1,-1,-1):
        for off in [i,(size-1)*128+i,i*128,(size-1)+i*128]:
            w=struct.unpack_from('<H',ter,start+2*off)[0]
            if w>=0x4000 and w&0xe000!=0xa000:return True
    return False
def f(s):return struct.unpack('<f',bytes.fromhex(s)[::-1])[0]
result={}
for fixture in json.loads(a.fixtures.read_text()):
    case=fixture['case'];p=predictions(fixture,np.longdouble)
    trace=a.cases/(case+'.tsv')
    if not p['accepted']:
        result[case]={'rejected':True,'no_source_graph':not Path(str(trace)+'.pre.bin').exists()};continue
    if not fixture['emulated']['accepted']:
        result[case]={'native_prediction_accepted':True,'emulated_rejected':True,'source_comparison':'unavailable; emulator sampler boundary mismatch'};continue
    x,z,e=p['root'];s=1<<e
    seeds=[(float(i),float(sample(i,j)&4095),float(j)) for i,j in [(x,z),(x+s,z),(x+s,z+s),(x,z+s)]]
    m=Model(seeds,sample);edges=[m.edge(3,2),m.edge(0,1),m.edge(1,2),m.edge(0,3)]
    cam=[f(p['camera_lattice_bits'][0]),0.,f(p['camera_lattice_bits'][1])]
    planes=[(q['nx'],0.,q['nz'],0.,q['offset']) for q in p['planes']]
    thresholds=list(map(f,p['threshold_bits']))
    m.quad((edges[3],edges[2],edges[1],edges[0]),lambda model,es:original_predicate(model,es,thresholds,cam,planes,special)[0])
    source=b''.join(struct.pack('<3f',*v) for v in m.v);arena=m.binary()
    expected_source=Path(str(trace)+'.pre.bin').read_bytes();expected_arena=Path(str(trace)+'.source-arena.bin').read_bytes()
    assert source==expected_source,case+' source bytes'
    assert arena==expected_arena,case+' arena bytes'
    result[case]={'vertices':len(m.v),'edges':len(m.edges),'leaves':len(m.leaves),'source_sha256':hashlib.sha256(source).hexdigest(),'arena_sha256':hashlib.sha256(arena).hexdigest(),'source_exact':True,'arena_exact':True}
dump(a.emit,result)
print('Predicted camera inputs reproduce source graphs:',len(result))
