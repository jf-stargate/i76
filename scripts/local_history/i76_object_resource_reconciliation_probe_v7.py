#!/usr/bin/env python3
"""
Interstate '76 object resource reconciliation probe v7.

Purpose:
  Keep binary-truth policy (ODEF -> .vcf, LDEF -> .sdf), but produce a
  reconstruction-oriented reconciliation table showing:
    - exact binary matches
    - exact Open76-compatible .sdf alternatives for unresolved ODEF .vcf
    - whether the unresolved .vcf candidate text appears anywhere in indexed roots
    - whether same basename appears with other extensions

This does NOT treat same-basename .sdf as runtime truth.
"""

from __future__ import annotations
import argparse, csv, json, os, struct, tarfile, time
from pathlib import Path
from typing import Dict, List, Tuple, Optional

CONTAINERS = {"BWD2","WDEF","TDEF","RDEF","ODEF","LDEF","ADEF"}
OBJ_TAG = "OBJ\x00"

def u32(b,o): return struct.unpack_from("<I", b, o)[0]
def f32(b,o): return struct.unpack_from("<f", b, o)[0]
def fourcc(b,o): return b[o:o+4].decode("ascii", "replace")

def parse_flat(data, start, end, parent=""):
    out=[]; off=start
    while off+8<=end:
        tag=fourcc(data,off); sz=u32(data,off+4)
        if sz<8 or off+sz>end: break
        out.append((tag, off, sz, off+8, sz-8, parent))
        off += sz
    return out

def parse_tree(data):
    roots=parse_flat(data,0,len(data),"")
    out=[]
    def rec(chs):
        for c in chs:
            out.append(c)
            tag,off,sz,po,ps,parent=c
            if tag in CONTAINERS and ps>=8:
                rec(parse_flat(data, po, off+sz, tag))
    rec(roots)
    return out

def decode_label(raw: bytes):
    chars=[]; mask=0
    for i,b in enumerate(raw[:8]):
        if b & 0x80: mask |= (1<<i)
        c=b & 0x7f
        if c==0: break
        if 32 <= c <= 126: chars.append(chr(c))
    return "".join(chars).strip(), mask

def iter_files(root: Path):
    if root.is_file():
        yield root
    elif root.exists():
        for p in root.rglob("*"):
            if p.is_file(): yield p

def build_index(roots):
    by_name: Dict[str,List[Path]]={}
    by_base: Dict[str,List[Path]]={}
    for r in roots:
        for p in iter_files(r):
            n=p.name.lower()
            by_name.setdefault(n,[]).append(p)
            by_base.setdefault(p.stem.lower(),[]).append(p)
    return by_name, by_base

def find_files(root: Path):
    return [p for p in iter_files(root) if p.suffix.lower() in (".msn",".spc",".lvl")]

def read_odef_ldef(mission_path: Path, mission_set: str):
    data=mission_path.read_bytes()
    chunks=parse_tree(data)
    rows=[]
    for tag,off,sz,po,ps,parent in chunks:
        if tag==OBJ_TAG and parent in ("ODEF","LDEF"):
            payload=data[po:po+ps]
            if parent=="ODEF" and ps>=100:
                name,himask=decode_label(payload[:8])
                cls=u32(payload,0x5c)
                pos=(f32(payload,0x2c), f32(payload,0x30), f32(payload,0x34))
                rows.append({
                    "mission_set":mission_set, "mission":mission_path.name, "section":parent,
                    "offset_hex":f"0x{off:08x}", "name":name, "hi_mask_hex":f"0x{himask:02x}",
                    "class_hex":f"0x{cls:02x}", "pos_x":pos[0], "pos_y":pos[1], "pos_z":pos[2],
                    "payload_size":ps
                })
            elif parent=="LDEF" and ps>=8:
                name,himask=decode_label(payload[:8])
                rows.append({
                    "mission_set":mission_set, "mission":mission_path.name, "section":parent,
                    "offset_hex":f"0x{off:08x}", "name":name, "hi_mask_hex":f"0x{himask:02x}",
                    "class_hex":"", "pos_x":"", "pos_y":"", "pos_z":"", "payload_size":ps
                })
    return rows

def write_tsv(path: Path, rows: List[dict], fields: List[str]):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w=csv.DictWriter(f, fields, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows: w.writerow(r)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--asset-root", action="append", type=Path, required=True)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--make-tar", action="store_true")
    args=ap.parse_args()
    out=args.out_dir; out.mkdir(parents=True, exist_ok=True)
    by_name, by_base = build_index(args.asset_root)

    records=[]
    for root,setname in [(args.miss8,"miss8"),(args.miss16,"miss16")]:
        for m in sorted(find_files(root)):
            if args.mission_filter and args.mission_filter.lower() not in m.name.lower() and args.mission_filter.lower() not in m.stem.lower():
                continue
            records.extend(read_odef_ldef(m,setname))

    recon=[]; unresolved=[]; alternatives=[]; exact=[]
    for r in records:
        name=(r["name"] or "").lower()
        cls=int(r["class_hex"],16) if r["class_hex"] else None
        policy=""; cand=""; note=""
        if r["section"]=="ODEF":
            if not name or cls==0:
                policy="invalid_or_special"; note="blank_or_class0"
            elif name in ("spawn","regen"):
                policy="spawn_regen_marker"; note="special_marker_not_resource"
            else:
                policy="binary_odef_vcf"; cand=f"{name}.vcf"; note="binary_validated_odef_vcf"
        elif r["section"]=="LDEF":
            if name: policy="binary_ldef_sdf"; cand=f"{name}.sdf"; note="binary_validated_ldef_sdf"
            else: policy="invalid_or_special"; note="blank_ldef"

        rr=dict(r); rr.update({"policy":policy,"binary_candidate":cand,"note":note})
        matches=by_name.get(cand.lower(),[]) if cand else []
        rr["binary_match_count"]=len(matches)
        rr["binary_match_paths"]=";".join(str(p) for p in matches[:8])
        open76=f"{name}.sdf" if (r["section"]=="ODEF" and name and name not in ("spawn","regen")) else ""
        rr["open76_compat_candidate"]=open76
        om=by_name.get(open76.lower(),[]) if open76 else []
        rr["open76_compat_match_count"]=len(om)
        rr["open76_compat_paths"]=";".join(str(p) for p in om[:8])
        same=by_base.get(name,[]) if name else []
        rr["same_basename_count"]=len(same)
        rr["same_basename_exts"]=";".join(sorted(set(p.suffix.lower() for p in same)))
        rr["same_basename_paths"]=";".join(str(p) for p in same[:16])
        recon.append(rr)
        if matches: exact.append(rr)
        elif policy.startswith("binary_"): unresolved.append(rr)
        if same and not matches: alternatives.append(rr)

    fields=list(recon[0].keys()) if recon else ["mission_set","mission","section","name"]
    write_tsv(out/"object_resource_reconciliation.tsv", recon, fields)
    write_tsv(out/"binary_exact_matches.tsv", exact, fields)
    write_tsv(out/"binary_unresolved_with_alternatives.tsv", alternatives, fields)
    write_tsv(out/"binary_unresolved.tsv", unresolved, fields)

    summary={
        "format":"i76_object_resource_reconciliation",
        "version":7,
        "policy":{"ODEF":"label.vcf except spawn/regen/blank/class0","LDEF":"label.sdf","Open76_ODEF_SDF":"comparison only"},
        "asset_roots":[str(x) for x in args.asset_root],
        "asset_index_file_count":sum(len(v) for v in by_name.values()),
        "object_records":len(records),
        "binary_exact_matches":len(exact),
        "binary_unresolved":len(unresolved),
        "binary_unresolved_with_same_basename_alternatives":len(alternatives),
    }
    (out/"manifest.json").write_text(json.dumps(summary,indent=2),encoding="utf-8")
    with (out/"summary.tsv").open("w",encoding="utf-8") as f:
        for k,v in summary.items():
            if not isinstance(v, (dict,list)):
                f.write(f"{k}\t{v}\n")
    if args.make_tar:
        tar_path=out.with_suffix(".tar")
        with tarfile.open(tar_path,"w") as t:
            t.add(out, arcname=out.name)
        print(tar_path)
    print(json.dumps(summary,indent=2))
if __name__=="__main__":
    main()
