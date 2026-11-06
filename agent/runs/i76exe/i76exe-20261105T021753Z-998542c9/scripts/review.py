"""Authenticate private Ghidra instruction exports; publish bounded excerpts/hashes."""
import json
from corpus import sha,EXE,GZF
from retail import Machine
WINDOWS=[
 ('selection cache before preference',0x44755b,0x447644),
 ('runtime allocation and decoder invocation',0x4476bf,0x447747),
 ('resource releases / MAP fallback',0x447839,0x4478a7),
 ('TMT / owner slot / M16 switch',0x44a5d7,0x44a61f),
 ('decoder header / capacity',0x44b430,0x44b48a),
 ('decoder token and tile row address',0x44b4ba,0x44b504),
 ('decoder right edge',0x44b529,0x44b5bb),
 ('M16 acquire',0x471a09,0x471a45),
 ('M16 FULLRES flags',0x471adf,0x471b19),
 ('row-cache key and header',0x48513d,0x485172),
 ('row-cache stride and masks',0x4851c8,0x485213),
 ('span packing',0x485229,0x485243),
 ('shade conversion',0x4852b1,0x4852ef),
 ('perspective segment delta',0x485315,0x485359),
 ('scalar sample shade store',0x4853d3,0x485421),
 ('compose sample/store',0x482b10,0x482b90),
 ('producer callback selection',0x485a3d,0x485a50),
 ('composition callback selection',0x48303b,0x483050)]

def review(exe,gzf,private,out):
    assert sha(exe.read_bytes())==EXE and sha(gzf.read_bytes())==GZF
    m=Machine(exe);functions=[];selected={};total=0;calls=[]
    for pn in range(1,5):
        d=json.loads((private/f'pass{pn}.json').read_text());assert d['executable_sha256']==EXE and d['ghidra']=='12.1.4' and d['modification_before']==d['modification_after']
        for f in d['functions']:
            for r in f.get('ranges',[]):assert sha(m.pe_read(int(r['start'],16),r['length']))==r['sha256']
            functions.append(dict(requested_address=f['entry'],ranges=f.get('ranges',[]),instruction_count=len(f['instructions'])))
            for i in f['instructions']:
                p=int(i['va'],16);b=bytes.fromhex(i['bytes']);assert m.pe_read(p,len(b))==b;total+=1
                tags=[name for name,a,z in WINDOWS if a<=p<=z]
                if tags:selected[i['va']]=dict(va=i['va'],asm=i['asm'],length=len(b),sha256=sha(b),annotation=tags)
                if 'CALL' in i['asm'] and f['entry'] in ['004474b0','0044a290','0044ab90','0044ac80','00471980','004859e0','00482fe0','00487ea0','00472ee0']:
                    calls.append(dict(caller=f['entry'],va=i['va'],asm=i['asm']))
    cov=json.loads((out/'executed_instructions.json').read_text())
    for r in cov:assert sha(m.pe_read(int(r['va'],16),r['length']))==r['sha256']
    refs=json.loads((private/'pass4.json.refs.json').read_text())
    ref_ins=0
    for ref in refs:
        code=ref.pop('bytes',None)
        if code is not None:
            b=bytes.fromhex(code);assert m.pe_read(int(ref['from'],16),len(b))==b;ref_ins+=1
            ref['length']=len(b);ref['sha256']=sha(b)
    assert ref_ins>0,'missing authenticated reference instructions'
    result=dict(reference_instructions_verified=ref_ins,exe_sha256=EXE,gzf_sha256=GZF,ghidra='12.1.4',program='i76.exe',domain_file='i76exe_v100',static_instructions_verified=total,unique_executed_instructions=len(cov),retired_instructions=sum(r['count'] for r in cov),functions=functions,annotation_mutation=False,publication='No opcode bytes, full decompilation, proprietary payloads or database included')
    for name,obj in [('instruction_validation.json',result),('reviewed_instructions.json',sorted(selected.values(),key=lambda r:r['va'])),('callgraph.json',calls),('texture_references.json',refs)]:
        (out/name).write_text(json.dumps(obj,indent=2,sort_keys=True)+'\n')
    return result
