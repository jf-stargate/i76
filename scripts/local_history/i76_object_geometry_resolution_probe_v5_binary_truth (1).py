#!/usr/bin/env python3
"""
Interstate '76 object geometry/resource resolution probe, v5 binary-truth.

Purpose:
  Keep the retail-binary-backed ODEF policy as the baseline:
    ODEF dispatch-valid object labels -> <label>.vcf
    ODEF spawn/regen -> special markers
    ODEF blank/class 0 -> special/invalid diagnostics
    LDEF labels -> <label>.sdf

  Additionally report basename alternatives, e.g. <label>.sdf exists while
  <label>.vcf does not. These are diagnostic only and must not be used as the
  reconstruction baseline unless later binary evidence justifies them.

This script intentionally does not parse embedded PAK/PIX containers. It indexes
loose files under --asset-root and emits enough data to show which candidates
must be resolved through another resource index/container layer.
"""
from __future__ import annotations

import argparse, csv, dataclasses, json, math, os, struct, tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

PAGE_W = 128
PATCH_SIZE_WORLD = 640.0

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('ascii', errors='replace')

@dataclasses.dataclass
class Chunk:
    tag: str
    off: int
    size: int
    payload_off: int
    payload_size: int
    parent: str = ''
    @property
    def end(self) -> int: return self.off + self.size

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out=[]; off=start
    while off+8 <= end:
        tag=fourcc(data, off); size=u32(data, off+4)
        if size < 8 or off+size > end: break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots=parse_flat(data,0,len(data),'')
    out=[]
    def rec(chs):
        for c in chs:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                rec(parse_flat(data,c.payload_off,c.end,c.tag))
    rec(roots)
    return out

def clean_label(raw8: bytes) -> Tuple[str, int]:
    hi=0; bs=[]
    for i,b in enumerate(raw8):
        if b & 0x80: hi |= (1 << i)
        c=b & 0x7f
        if c == 0: break
        bs.append(c)
    return bytes(bs).decode('ascii', errors='ignore'), hi

def hexbytes(b: bytes) -> str: return b.hex()

def tail_words(payload: bytes) -> str:
    ws=[]
    for off in range(0x38, min(len(payload),0x64),4):
        if off+4 <= len(payload): ws.append(f"0x{u32(payload,off):08x}")
    return ','.join(ws)

def f32(payload: bytes, off: int) -> float:
    if off+4 > len(payload): return float('nan')
    return struct.unpack_from('<f', payload, off)[0]

@dataclasses.dataclass
class ObjRec:
    mission_set: str
    mission: str
    section: str
    record_index: int
    chunk_offset_hex: str
    name: str
    raw_label_hex: str
    label_hi_mask_hex: str
    class_hex: str
    pos_x: float
    pos_y: float
    pos_z: float
    payload_size: int
    tail_words: str

    def row(self):
        return dataclasses.asdict(self)


def decode_obj_records(root: Path, mission_set: str, filt: str) -> List[ObjRec]:
    recs=[]
    files=[p for p in root.rglob('*') if p.is_file() and p.suffix.lower() in {'.msn','.lvl','.spc'}]
    if filt:
        files=[p for p in files if filt.lower() in p.stem.lower() or filt.lower() in p.name.lower()]
    for msn in sorted(files):
        data=msn.read_bytes(); chunks=parse_tree(data)
        idx=0
        for c in chunks:
            if c.parent == 'ODEF' and c.tag == 'OBJ\x00' and c.payload_size >= 0x64:
                p=data[c.payload_off:c.end]
                label,hi=clean_label(p[:8])
                cls=u32(p,0x5c) if len(p)>=0x60 else 0
                recs.append(ObjRec(mission_set, msn.name, 'ODEF', idx, f"0x{c.off:08x}", label, hexbytes(p[:8]), f"0x{hi:02x}", f"0x{cls:02x}", f32(p,0x2c), f32(p,0x30), f32(p,0x34), c.payload_size, tail_words(p)))
                idx += 1
            elif c.parent == 'LDEF' and c.tag == 'OBJ\x00':
                p=data[c.payload_off:c.end]
                label,hi=clean_label(p[:8]) if len(p)>=8 else ('',0)
                recs.append(ObjRec(mission_set, msn.name, 'LDEF', idx, f"0x{c.off:08x}", label, hexbytes(p[:8]), f"0x{hi:02x}", '', float('nan'), float('nan'), float('nan'), c.payload_size, ''))
                idx += 1
    return recs


def index_assets(roots: List[Path]):
    by_name: Dict[str,List[Path]]={}
    by_stem: Dict[str,List[Path]]={}
    warnings=[]
    for root in roots:
        if not root.exists():
            warnings.append(f"asset root does not exist: {root}")
            continue
        for p in root.rglob('*'):
            if not p.is_file(): continue
            by_name.setdefault(p.name.lower(),[]).append(p)
            by_stem.setdefault(p.stem.lower(),[]).append(p)
    return by_name, by_stem, warnings


def match_name(by_name, candidate: str) -> List[str]:
    return [str(p) for p in by_name.get(candidate.lower(), [])]

def stem_alts(by_stem, stem: str) -> List[Path]:
    return by_stem.get(stem.lower(), [])


def write_tsv(path: Path, rows: List[dict], fields: List[str]):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w', newline='', encoding='utf-8') as f:
        w=csv.DictWriter(f, fieldnames=fields, delimiter='\t', extrasaction='ignore')
        w.writeheader(); w.writerows(rows)


def make_tar(out_dir: Path):
    tar_path=out_dir.with_suffix('.tar')
    with tarfile.open(tar_path,'w') as tf:
        tf.add(out_dir, arcname=out_dir.name)
    return tar_path


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path, required=True)
    ap.add_argument('--miss16', type=Path, required=True)
    ap.add_argument('--asset-root', type=Path, action='append', required=True)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--make-tar', action='store_true')
    args=ap.parse_args()

    out=args.out_dir; out.mkdir(parents=True, exist_ok=True)
    by_name, by_stem, warnings=index_assets(args.asset_root)
    records=decode_obj_records(args.miss8,'miss8',args.mission_filter)+decode_obj_records(args.miss16,'miss16',args.mission_filter)

    object_rows=[r.row() for r in records]
    binary_matches=[]; binary_unresolved=[]; open76_matches=[]; open76_unresolved=[]; basename_alt_rows=[]; attempt_rows=[]

    for r in records:
        base=r.row()
        name=(r.name or '').strip()
        cls=r.class_hex.lower()
        if r.section == 'ODEF':
            if not name or cls in {'0x00','0x0'}:
                pol='special_or_invalid'; cand=''; reason='blank_or_class0_no_resource'
                binary_unresolved.append({**base,'policy':pol,'candidate_name':cand,'policy_reason':reason,'unresolved_reason':reason})
                open76_unresolved.append({**base,'policy':'open76_special_or_invalid','candidate_name':'','policy_reason':reason,'unresolved_reason':reason})
                continue
            if cls == '0x01' and name.lower() in {'spawn','regen'}:
                reason='spawn_or_regen_no_file'
                binary_unresolved.append({**base,'policy':'special_marker','candidate_name':'','policy_reason':reason,'unresolved_reason':reason})
                open76_unresolved.append({**base,'policy':'open76_special_marker','candidate_name':'','policy_reason':reason,'unresolved_reason':reason})
                continue
            # binary-backed
            cand=f'{name}.vcf'
            ms=match_name(by_name,cand)
            attempt_rows.append({**base,'policy':'binary_odef_vcf','candidate_name':cand,'candidate_kind':'binary','match_count':len(ms)})
            if ms:
                for p in ms: binary_matches.append({**base,'policy':'binary_odef_vcf','candidate_name':cand,'matched_ext':Path(p).suffix.lower(),'path':p})
            else:
                binary_unresolved.append({**base,'policy':'binary_odef_vcf','candidate_name':cand,'policy_reason':'binary_validated_odef_label_plus_vcf','unresolved_reason':'binary_candidate_not_found_in_indexed_asset_roots'})
            # basename alternatives, diagnostic only
            alts=stem_alts(by_stem,name)
            for p in sorted(alts, key=lambda x: x.name.lower()):
                basename_alt_rows.append({**base,'binary_candidate':cand,'alt_name':p.name,'alt_ext':p.suffix.lower(),'alt_path':str(p),'diagnostic_note':'same_basename_alternative_not_binary_truth'})
            # Open76 compat comparison
            oc=f'{name}.sdf'
            oms=match_name(by_name,oc)
            attempt_rows.append({**base,'policy':'open76_compat_odef_sdf','candidate_name':oc,'candidate_kind':'open76_compat','match_count':len(oms)})
            if oms:
                for p in oms: open76_matches.append({**base,'policy':'open76_compat_odef_sdf','candidate_name':oc,'matched_ext':Path(p).suffix.lower(),'path':p})
            else:
                open76_unresolved.append({**base,'policy':'open76_compat_odef_sdf','candidate_name':oc,'policy_reason':'comparison_only_open76_noncar_label_plus_sdf','unresolved_reason':'open76_candidate_not_found'})
        elif r.section == 'LDEF':
            if not name:
                binary_unresolved.append({**base,'policy':'special_or_invalid','candidate_name':'','policy_reason':'blank_ldef','unresolved_reason':'blank_ldef'})
                continue
            cand=f'{name}.sdf'
            ms=match_name(by_name,cand)
            attempt_rows.append({**base,'policy':'binary_ldef_sdf','candidate_name':cand,'candidate_kind':'binary','match_count':len(ms)})
            if ms:
                for p in ms: binary_matches.append({**base,'policy':'binary_ldef_sdf','candidate_name':cand,'matched_ext':Path(p).suffix.lower(),'path':p})
            else:
                binary_unresolved.append({**base,'policy':'binary_ldef_sdf','candidate_name':cand,'policy_reason':'binary_validated_ldef_label_plus_sdf','unresolved_reason':'candidate_not_found'})

    fields=list(object_rows[0].keys()) if object_rows else ['mission_set','mission','section','record_index','name']
    write_tsv(out/'object_records_binarytruth.tsv', object_rows, fields)
    common=fields+['policy','candidate_name','policy_reason','unresolved_reason']
    write_tsv(out/'binary_resource_unresolved.tsv', binary_unresolved, common)
    write_tsv(out/'open76_compat_resource_unresolved.tsv', open76_unresolved, common)
    mf=fields+['policy','candidate_name','matched_ext','path']
    write_tsv(out/'binary_resource_matches.tsv', binary_matches, mf)
    write_tsv(out/'open76_compat_resource_matches.tsv', open76_matches, mf)
    write_tsv(out/'resource_candidate_attempts.tsv', attempt_rows, fields+['policy','candidate_name','candidate_kind','match_count'])
    write_tsv(out/'basename_alternative_matches.tsv', basename_alt_rows, fields+['binary_candidate','alt_name','alt_ext','alt_path','diagnostic_note'])

    # summaries
    from collections import Counter
    summary=[]
    for bucket,rows in [('binary_matches',binary_matches),('binary_unresolved',binary_unresolved),('open76_compat_matches',open76_matches),('open76_compat_unresolved',open76_unresolved),('basename_alternatives',basename_alt_rows)]:
        c=Counter(r.get('policy', r.get('alt_ext','')) for r in rows)
        if not c and bucket=='basename_alternatives': c=Counter(r.get('alt_ext','') for r in rows)
        for k,v in c.items(): summary.append({'bucket':bucket,'policy_or_ext':k,'count':v})
    write_tsv(out/'resource_policy_summary.tsv', summary, ['bucket','policy_or_ext','count'])
    cls=Counter((r.section,r.class_hex) for r in records)
    write_tsv(out/'object_class_summary.tsv', [{'section':k[0],'class_hex':k[1],'count':v} for k,v in sorted(cls.items())], ['section','class_hex','count'])

    manifest={'format':'i76_object_geometry_resolution_probe_binarytruth','version':5,'asset_roots':[str(p) for p in args.asset_root],'asset_index_file_count':sum(len(v) for v in by_name.values()),'mission_filter':args.mission_filter,'object_records':len(records),'binary_matches':len(binary_matches),'binary_unresolved':len(binary_unresolved),'open76_compat_matches':len(open76_matches),'open76_compat_unresolved':len(open76_unresolved),'basename_alternative_rows':len(basename_alt_rows),'warnings':warnings,'policy':{'source_of_truth':'retail i76.exe v31/v32 validation','odef':'spawn/regen special; otherwise label + .vcf','ldef':'label + .sdf','basename_alternatives':'diagnostic only; not reconstruction baseline'}}
    if args.make_tar: manifest['tar_path']=str(make_tar(out))
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
    print(json.dumps({'out_dir':str(out), 'object_records':len(records), 'binary_matches':len(binary_matches), 'binary_unresolved':len(binary_unresolved), 'basename_alternatives':len(basename_alt_rows), 'warnings':len(warnings)}, indent=2))
if __name__=='__main__': main()
