#!/usr/bin/env python3
"""Verify published field spans and all private specimens, without writing assets."""
import argparse
import hashlib
import json
from pathlib import Path
import wrld

def check(root):
    run=Path(__file__).resolve().parents[1]
    fields=json.loads((run/'artifacts/fields.json').read_text())['fields']
    coverage=[i for f in fields for i in range(f['offset'],f['offset']+f['width'])]
    assert sorted(coverage)==list(range(wrld.SIZE)), 'gap or overlapping field'
    assert [f['offset'] for f in fields if f['encoding'].startswith('char[13]')]==[o for o,n in wrld.NAMES.values()]
    metadata=json.loads((run/'evidence/corpus.json').read_text())
    checked=0
    for entry in metadata['records']:
        data=(root/entry['specimen']).read_bytes()
        assert hashlib.sha256(data).hexdigest()==entry['sha256'],entry['specimen']
        records=wrld.inspect(data);assert len(records)==1
        section,c,rev,w=records[0]
        assert c['size']==339 and rev==9 and section['size']==367
        assert w.names==entry['names']
        assert w.serialize()==data[c['offset']+8:c['offset']+c['size']]
        assert b''.join(w.raw[f['offset']:f['offset']+f['width']] for f in fields)==w.raw
        checked+=1
    return dict(checked_specimens=checked,layout_bytes=wrld.SIZE,field_spans=len(fields),status='passed')

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('root',type=Path);args=p.parse_args()
    print(json.dumps(check(args.root),indent=2))
