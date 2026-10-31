#!/usr/bin/env python3
"""Publication consistency only; separate from scientific assertion counts."""
import hashlib,json,pathlib,sys
run,derived=map(pathlib.Path,sys.argv[1:])
manifest=json.loads((run/'manifest.json').read_text());validation=json.loads((run/'validation.json').read_text())
assert validation==manifest['validation']==json.loads((derived/'validation.json').read_text()),'exact validation equality'
assert json.loads((run/'evidence/results.json').read_text())==json.loads((derived/'results.json').read_text()),'exact regenerated scientific evidence'
listed={a['path'] for a in manifest['artifacts']}
actual={p.relative_to(run).as_posix() for p in run.rglob('*') if p.is_file()}-{'manifest.json','validation.json','findings.json'}
assert listed==actual,'complete artifact inventory'
for item in manifest['artifacts']:
 data=(run/item['path']).read_bytes()
 assert len(data)==item['bytes'] and hashlib.sha256(data).hexdigest()==item['sha256'],item['path']
print('Publication equality, complete inventory, lengths and SHA-256 passed')
