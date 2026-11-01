#!/usr/bin/env python3
"""Check private bounded captures; emit metrics/hashes only, never decompiler text."""
import argparse, hashlib, json, re, struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--private',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--gzf',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def parse(p):
 s=p.read_text();out={}
 for m in re.finditer(r'^FUNCTION ([0-9a-f]{8}) (.*?) BODY (.*?)\n(.*?)(?=^FUNCTION |\Z)',s,re.M|re.S):
  body=m[4];ins=re.findall(r'^[0-9a-f]{8} .+$',body,re.M);c=body.split('\n\n',1)[1];c=re.split(r'^004[0-9a-f]{5} ',c,flags=re.M)[0]
  out[m[1]]={'sig':m[2],'body':m[3],'params':re.findall(r'^PARAM .+$',body,re.M),'ret':re.search(r'^RETURN (.*)',body,re.M)[1],'ins':ins,'c':c}
 return s,out
b,bf=parse(a.private/'final_before.txt');e,ef=parse(a.private/'final_after.txt');checks=[]
def check(name,ok):
 checks.append({'check':name,'passed':bool(ok)})
 if not ok:raise AssertionError(name)
check('retail PE SHA256',digest(a.exe)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3')
check('private GZF SHA256',digest(a.gzf)=='d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd')
check('dry-run capture unchanged',(a.private/'final_before.txt').read_bytes()==(a.private/'after_dry.txt').read_bytes())
check('function count preserved',re.search(r'FUNCTION_COUNT (\d+)',b)[1]==re.search(r'FUNCTION_COUNT (\d+)',e)[1]=='2337')
targets=['00493080','00493160','004931c0','00493550','004927b0'];rows=['address\tbefore_c_lines\tafter_c_lines\tbefore_grid_accesses\tafter_grid_accesses\tbefore_named_normal_fields\tafter_named_normal_fields\tchanged']
for va in targets:
 x,y=bf[va],ef[va];check(va+' instructions and body unchanged',x['ins']==y['ins'] and x['body']==y['body'])
 rows.append('\t'.join(map(str,[va,len(x['c'].splitlines()),len(y['c'].splitlines()),x['c'].count('g_runtime_terrain_page_pointer_grid['),y['c'].count('g_runtime_terrain_page_pointer_grid['),len(re.findall(r'out_normal->\w+',x['c'])),len(re.findall(r'out_normal->\w+',y['c'])),x['c']!=y['c']])))
check('height has only two 8-byte stack parameters',len(ef['00493550']['params'])==2 and 'Stack[0x4]:8' in ef['00493550']['params'][0] and 'Stack[0xc]:8' in ef['00493550']['params'][1])
check('height return in ST0 without hidden pointer',ef['00493550']['ret']=='ST0:10' and ef['00493550']['sig'].startswith('double '))
check('height full four-corner calculation visible',ef['00493550']['c'].count('g_runtime_terrain_page_pointer_grid[')==4 and 'return (((double)' in ef['00493550']['c'])
check('normal packed stack offsets preserved',len(ef['004931c0']['params'])==3 and all(t in v for t,v in zip(['Stack[0x4]:4','Stack[0x8]:8','Stack[0x10]:8'],ef['004931c0']['params'])))
check('normal no invented alignment gap','in_stack_' not in ef['004931c0']['c'] and 'CONCAT44' not in ef['004931c0']['c'])
check('normal named fields visible',all('out_normal->'+f in ef['004931c0']['c'] for f in ['x','y','z']))
check('page size 32768','TYPE /I76_TerrainPilotA/TER_Page 32768' in e)
check('pointer grid has 16384 uint16 pointers','GLOBAL 00644380 ushort *[16384]' in e)
check('existing user global names retained',re.findall(r'^SYMBOL (.*?) USER_DEFINED$',b,re.M)==re.findall(r'^SYMBOL (.*?) USER_DEFINED$',e,re.M))
# Independently resolve PE section offsets and compare all five database guard hashes.
raw=a.exe.read_bytes();pe=struct.unpack_from('<I',raw,0x3c)[0];count=struct.unpack_from('<H',raw,pe+6)[0];optlen=struct.unpack_from('<H',raw,pe+20)[0]
sections=[struct.unpack_from('<IIII',raw,pe+24+optlen+40*n+8) for n in range(count)]
guards=Path(__file__).with_name('TerrainSemantic.java').read_text().split('CODE_HASHES={',1)[1]
code_rows=['start_va\tbytes\tsha256']
for va,length,expected in re.findall(r'\{"([0-9a-f]{8})","(\d+)","([0-9a-f]{64})"\}',guards):
 rva=int(va,16)-0x400000;l=int(length)
 section=next(row for row in sections if row[1]<=rva<row[1]+row[2]);offset=section[3]+rva-section[1]
 check(va+' guard equals original PE',hashlib.sha256(raw[offset:offset+l]).hexdigest()==expected)
 code_rows.append(f'{va}\t{length}\t{expected}')
a.out.mkdir(parents=True,exist_ok=True);(a.out/'code_ranges.tsv').write_text('\n'.join(code_rows)+'\n')
a.out.mkdir(parents=True,exist_ok=True);(a.out/'readability_metrics.tsv').write_text('\n'.join(rows)+'\n')
(a.out/'capture_checks.json').write_text(json.dumps({'checks':checks,'passed':len(checks),'total':len(checks),'private_capture_sha256':{n:digest(a.private/n) for n in ['final_before.txt','after_dry.txt','final_after.txt']}},indent=2)+'\n')
print(f'{len(checks)}/{len(checks)} capture/identity checks passed')
