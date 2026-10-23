#!/usr/bin/env python3
"""Validate published renderer evidence against the user's private retail executable.
No game payloads are generated, uploaded, or modified.
"""
import argparse,csv,hashlib,json,struct
from pathlib import Path

def getrows(path):
    with open(path,newline='') as f:return list(csv.DictReader(f,delimiter='\t'))

def pe_offset(binary, va):
    pe=struct.unpack_from('<I',binary,0x3c)[0]
    assert binary[pe:pe+4]==b'PE\0\0'
    sections=struct.unpack_from('<H',binary,pe+6)[0]
    optional=struct.unpack_from('<H',binary,pe+20)[0]
    base=struct.unpack_from('<I',binary,pe+24+28)[0]
    rva=va-base
    start=pe+24+optional
    for i in range(sections):
        hdr=start+i*40
        vsize,vaddr,rsize,roff=struct.unpack_from('<IIII',binary,hdr+8)
        if vaddr<=rva<vaddr+max(vsize,rsize):return roff+rva-vaddr
    raise ValueError(f'unmapped VA: 0x{va:08x}')

def validate(base,exe):
    b=Path(exe).read_bytes()
    assert hashlib.md5(b).hexdigest()=='a640ea0097dbb62e0c77b7f2847c7161','wrong retail binary'
    assert hashlib.sha256(b).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','wrong executable SHA256'
    checks=0
    anchors=getrows(base/'evidence/retail_x86_anchors.tsv')
    assert len(anchors)==45
    for a in anchors:
        observed=bytes.fromhex(a['original_x86_bytes'])
        off=pe_offset(b,int(a['va'],16))
        assert b[off:off+len(observed)]==observed,('opcode',a['va'])
        checks+=1
    cases=getrows(base/'evidence/render_boundary_native.tsv')
    assert [r['scenario'] for r in cases]==['NO_OWNER','EMPTY_BINDINGS','MIXED_FLAGS','REPEAT_REFRESH','HASH_COLLISION']
    assert [(int(r['eax']),int(r['vqm_intercepts']),int(r['m16_intercepts'])) for r in cases]==[(0,0,0),(1,0,0),(1,1,3),(1,0,3),(0,0,0)]
    assert 's1_cache=0;s1_flags=2;s2_flags=1;s3_flags=2' in cases[2]['asserted_state']
    checks+=len(cases)
    depth=getrows(base/'evidence/render_depth_native.tsv')
    assert len(depth)==2
    assert depth[0]['scenario']=='POSITIVE' and depth[1]['scenario']=='NEGATIVE'
    assert depth[0]['root_left_40']!='00000000' and depth[0]['root_right_44']=='00000000'
    assert depth[1]['root_left_40']=='00000000' and depth[1]['root_right_44']!='00000000'
    assert [int(d['steps']) for d in depth]==[24,24]
    checks+=len(depth)
    lazy=getrows(base/'evidence/render_lazy_native.tsv')
    assert [x['phase'] for x in lazy]==['HIT_BEFORE_REFRESH','AFTER_REFRESH','LAZY_RELOAD','REUSE_AFTER_RELOAD']
    assert [int(x['vqm_load_stubs']) for x in lazy]==[0,0,1,1]
    assert [int(x['slot_flags']) for x in lazy]==[0,2,0,0]
    assert [int(x['slot_vqm_cache']) for x in lazy]==[0x12345678,0,0x2900beef,0x2900beef]
    assert len(set(x['tmt_record_ptr'] for x in lazy))==1
    checks+=len(lazy)
    return {'status':'passed','opcode_anchors':len(anchors),'original_code_trace_rows':len(cases)+len(depth)+len(lazy),'checks':checks,'executable_md5':hashlib.md5(b).hexdigest(),'executable_sha256':hashlib.sha256(b).hexdigest(),'limitations':'Original Ghidra emulator stubs CRT/VQM loader/release helpers; x87 depth test warned about uninitialized ST registers; no pixel or GPU execution.'}

if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('run',type=Path);parser.add_argument('--pe',required=True,type=Path);args=parser.parse_args()
    print(json.dumps(validate(args.run,args.pe),indent=2))
