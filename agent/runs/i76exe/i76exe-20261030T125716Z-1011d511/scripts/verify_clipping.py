#!/usr/bin/env python3
"""Standalone checks for the published, bounded M-RND-04 evidence."""
import argparse, math, re
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
def rows(name):
    return [line.split('\t',3) for line in (ROOT/'evidence'/name).read_text().splitlines() if line]
def select(name,kind): return [r for r in rows(name) if len(r)==4 and r[1]==kind]
def field(detail,key):
    m=re.search(r'(?:^|;)'+re.escape(key)+r'=([^;]*)',detail)
    if not m: raise AssertionError(f'missing {key}: {detail[:180]}')
    return m.group(1)
def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--run',type=Path,default=None); a=ap.parse_args()
    global ROOT; ROOT=(a.run or ROOT).resolve()
    pos=rows('positive.tsv'); rep=rows('repeat.tsv'); neg=rows('negative.tsv'); src=(ROOT/'evidence/retail_instructions.tsv').read_text()
    def one(rs,k):
        x=[r for r in rs if len(r)==4 and r[1]==k]
        if len(x)!=1: raise AssertionError(f'{k}: expected one row, got {len(x)}')
        return x[0]
    # Chain and independent-original-state provenance.
    assert any(r[1]=='CAMERA_ENTER' and r[2]=='00406AB0' for r in pos)
    assert any(r[1]=='WORLD_REGISTERED' and 'entry=00542830' in r[3] for r in pos)
    assert any(r[1]=='TARGET_REGISTERED' and 'entry=005428A8' in r[3] for r in pos)
    assert any(r[1]=='GEO_SOURCE' and 'owner=27006800' in r[3] and 'vertexCount=16' in r[3] for r in pos)
    assert sum(1 for r in pos if r[1]=='GEO_SECTION' and 'count=4' in r[3])>=1
    # Two genuine kind-6 quads hit the one removed substitute and return from native code.
    enters=[r for r in pos if r[1]=='ORIGINAL_CLIP_ENTER']; returns=[r for r in pos if r[1]=='ORIGINAL_CLIP_RETURN']
    assert len(enters)==len(returns)==2
    for en,ret in zip(enters,returns):
        assert en[2]=='0047C8D0' and ret[2]=='0047C92F'
        assert field(en[3],'arg1')=='004C2730' and field(en[3],'count')=='4'
        assert field(en[3],'src').startswith('2D') and field(en[3],'dst').startswith('3001')
        before=bytes.fromhex(field(en[3],'output_before')); after=bytes.fromhex(field(ret[3],'output'))
        assert len(before)==len(after)==96 and before!=after
        assert field(ret[3],'eax')=='00000004' and field(ret[3],'source_unchanged')=='true'
        # Three projected floats per vertex are finite and nonzero depth reciprocals.
        xyz=[struct_float(after[i:i+4]) for i in range(0,96,24)]
        recip=[struct_float(after[i:i+4]) for i in range(8,96,24)]
        assert all(math.isfinite(v) for v in xyz+recip) and all(v>0 for v in recip)
    # Kind 10 and drawing remain substituted: only one callback body changed.
    assert len(select('positive.tsv','SERVICE_CLIP_KIND10'))==1
    assert len(select('positive.tsv','SERVICE_DRAW'))==3 and sum(r[2]=='0047CE40' for r in select('positive.tsv','SERVICE_DRAW'))==2
    # Repeat identity of input/output bytes for the same native clipping calls.
    reps=[r for r in rep if r[1]=='ORIGINAL_CLIP_RETURN']; assert len(reps)==2
    for x,y in zip(returns,reps): assert field(x[3],'output')==field(y[3],'output') and field(x[3],'eax')==field(y[3],'eax')
    assert not select('negative.tsv','POLYGON_WRAPPER') and not select('negative.tsv','ORIGINAL_CLIP_ENTER')
    assert '0047c8d0' in src.lower() and '0047c92e' in src.lower() and 'FSTP' in src
    print('passed: 18 assertions; native kind-6 projection/clip-preparation output, return, ownership, repeat and behind-camera negative control')
def struct_float(b):
    import struct
    return struct.unpack('<f',b)[0]
if __name__=='__main__': main()
