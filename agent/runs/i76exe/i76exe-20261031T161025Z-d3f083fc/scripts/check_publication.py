import hashlib,json,pathlib,sys
r=pathlib.Path(sys.argv[1]);d=pathlib.Path(sys.argv[2]);m=json.loads((r/'manifest.json').read_text());v=json.loads((r/'validation.json').read_text());assert v==m['validation']==json.loads((d/'validation.json').read_text())
for name in ['results.json','opcodes.json']:assert (r/'evidence'/name).read_bytes()==(d/name).read_bytes()
listed=set()
for i in m['artifacts']:
 b=(r/i['path']).read_bytes();assert len(b)==i['bytes'] and hashlib.sha256(b).hexdigest()==i['sha256'];listed.add(i['path'])
assert listed=={str(p.relative_to(r)) for p in r.rglob('*') if p.is_file()}-{'manifest.json','findings.json','validation.json'}
print('Standalone equality and complete inventory passed.')
