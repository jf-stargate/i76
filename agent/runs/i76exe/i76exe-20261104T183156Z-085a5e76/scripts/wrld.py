#!/usr/bin/env python3
"""Read-only retail BWD2/WRLD survey; outputs metadata, never resource payloads.
All offsets are payload-relative. Unknown bytes remain in Wrld.raw.
"""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import struct

SIZE = 331
NAMES = {'slot_04': (4,13), 'slot_11': (17,13), 'palette': (30,13),
         'luminance': (43,13), 'blend_table': (56,13), 'notepad': (69,13),
         'sky': (82,13), 'scrounge': (95,13), 'terrain_default': (108,13),
         'map_name': (121,13), 'horizon_manifest': (134,13)}
CONTAINERS = {b'WDEF', b'TDEF', b'RDEF', b'ODEF', b'LDEF', b'ADEF'}

class FormatError(ValueError):
    pass

def chunks(data, start, end, depth=0, budget=None):
    if budget is None: budget = [16384]
    if depth > 16: raise FormatError('depth limit')
    while start < end:
        if end-start < 8: raise FormatError(f'truncated header at {start}')
        tag, size = struct.unpack_from('<4sI', data, start)
        if size < 8 or size > end-start: raise FormatError(f'invalid size at {start}')
        if any(x < 32 or x > 126 for x in tag.rstrip(b'\0')): raise FormatError('invalid tag')
        budget[0] -= 1
        if budget[0] < 0: raise FormatError('chunk limit')
        children = list(chunks(data,start+8,start+size,depth+1,budget)) if tag in CONTAINERS else []
        yield {'tag':tag.decode('ascii'), 'offset':start, 'size':size, 'children':children}
        start += size

class Wrld:
    def __init__(self, payload, revision):
        if revision != 9: raise FormatError(f'unsupported WREV {revision}')
        if len(payload) != SIZE: raise FormatError(f'unsupported WRLD length {len(payload)}')
        self.raw = bytes(payload)
        self.names = {}
        for key,(offset,width) in NAMES.items():
            raw = self.raw[offset:offset+width]
            if b'\0' not in raw: raise FormatError(f'unterminated {key}')
            try: self.names[key] = raw.split(b'\0',1)[0].decode('ascii')
            except UnicodeDecodeError as exc: raise FormatError(f'non-ASCII {key}') from exc
        self.audio_word = struct.unpack_from('<I',self.raw,0)[0]
        self.environment_selector_word = struct.unpack_from('<i',self.raw,147)[0]
        self.distance_word = struct.unpack_from('<i',self.raw,311)[0]

    def serialize(self):
        """Lossless original bytes, including padding and untyped regions."""
        return self.raw

def inspect(data):
    if len(data)>16*1024*1024: raise FormatError('resource limit')
    if len(data)<8 or data[:8] != b'BWD2\x08\x00\x00\x00': raise FormatError('expected 8-byte BWD2 marker')
    top=list(chunks(data,8,len(data)))
    records=[]
    for section in top:
        if section['tag']!='WDEF': continue
        revs=[c for c in section['children'] if c['tag']=='WREV']
        if len(revs)!=1 or revs[0]['size']!=12: raise FormatError('expected one 4-byte WREV')
        revision=struct.unpack_from('<I',data,revs[0]['offset']+8)[0]
        for c in section['children']:
            if c['tag']!='WRLD': continue
            p=data[c['offset']+8:c['offset']+c['size']]
            w=Wrld(p,revision)
            records.append((section,c,revision,w))
    if not records: raise FormatError('missing WRLD')
    return records

def spans(indices):
    result=[]
    for i in indices:
        if result and result[-1][1]==i: result[-1][1]=i+1
        else: result.append([i,i+1])
    return result

def survey(root):
    rows=[]; payloads={}
    for directory in ('miss8','miss16'):
        for path in sorted((root/directory).glob('*')):
            if path.suffix.lower()!='.msn': continue
            data=path.read_bytes()
            for section,c,rev,w in inspect(data):
                key=path.relative_to(root).as_posix(); payloads[key]=w.raw
                root_revs=[c for c in chunks(data,8,len(data)) if c['tag']=='REV\0']
                if len(root_revs)!=1 or root_revs[0]['size']!=12: raise FormatError('bad root REV')
                root_revision=struct.unpack_from('<I',data,root_revs[0]['offset']+8)[0]
                rows.append(dict(specimen=key,root_revision=root_revision,wdef_children=[c['tag'] for c in section['children']],bytes=len(data),sha256=hashlib.sha256(data).hexdigest(),
                    md5=hashlib.md5(data).hexdigest(),wdef_chunk_length=section['size'],wrld_offset=c['offset'],
                    wrld_chunk_length=c['size'],payload_length=len(w.raw),wrev=rev,
                    audio_word=w.audio_word,environment_selector_word=w.environment_selector_word,distance_word=w.distance_word,names=w.names))
    if not rows: raise FormatError('empty corpus')
    values=[set(p[i] for p in payloads.values()) for i in range(SIZE)]
    pairs=[]
    for key,p in payloads.items():
        if not key.startswith('miss8/'): continue
        other='miss16/'+key.split('/',1)[1]
        if other not in payloads: continue
        q=payloads[other]
        pairs.append(dict(mission=key.split('/',1)[1],different_spans=spans(i for i in range(SIZE) if p[i]!=q[i]),
            differing_fields=[name for name,(o,n) in NAMES.items() if p[o:o+n]!=q[o:o+n]]))
    return dict(records=rows,pairs=pairs,byte_span_convention='[start,end) payload-relative decimal',
        zero_spans=spans(i for i,v in enumerate(values) if v=={0}),
        stable_nonzero_spans=spans(i for i,v in enumerate(values) if len(v)==1 and v!={0}),
        variable_spans=spans(i for i,v in enumerate(values) if len(v)>1))

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('root',type=Path);parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();args.output.write_text(json.dumps(survey(args.root),indent=2)+'\n')
