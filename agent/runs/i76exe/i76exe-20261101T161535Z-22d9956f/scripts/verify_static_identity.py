"""Compare audited Ghidra function-body hashes to verified PE bytes; no execution."""
import argparse, csv, hashlib, json, struct
from pathlib import Path

def verify(exe, audit):
    raw = Path(exe).read_bytes()
    digest = hashlib.sha256(raw).hexdigest()
    if digest != 'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3':
        raise ValueError('wrong executable SHA-256')
    pe = struct.unpack_from('<I', raw, 0x3c)[0]
    assert raw[pe:pe+4] == b'PE\0\0'
    machine, count = struct.unpack_from('<HH', raw, pe+4)
    assert machine == 0x14c
    optsize = struct.unpack_from('<H', raw, pe+20)[0]
    opt = pe+24
    assert struct.unpack_from('<H', raw, opt)[0] == 0x10b
    base = struct.unpack_from('<I', raw, opt+28)[0]
    sections = []
    for i in range(count):
        off = opt+optsize+i*40
        vsize, va, size, pos = struct.unpack_from('<IIII', raw, off+8)
        sections.append((base+va, size, pos))
    passed = 0
    for row in csv.DictReader(Path(audit).open(), delimiter='\t'):
        if row['kind'] != 'range':
            continue
        va, length = int(row['address'],16), int(row['detail'])
        candidates = [(start,size,pos) for start,size,pos in sections if start <= va and va+length <= start+size]
        assert len(candidates) == 1, hex(va)
        start,size,pos = candidates[0]
        payload = raw[pos+va-start:pos+va-start+length]
        assert hashlib.sha256(payload).hexdigest() == row['value'], hex(va)
        passed += 1
    assert passed >= 23, 'incomplete audit'
    return {'executable_sha256':digest,'matched_function_ranges':passed,'method':'static byte comparison; no original execution'}

if __name__ == '__main__':
    p=argparse.ArgumentParser();p.add_argument('--exe',required=True);p.add_argument('--audit',required=True)
    a=p.parse_args(); print(json.dumps(verify(a.exe,a.audit),indent=2))
