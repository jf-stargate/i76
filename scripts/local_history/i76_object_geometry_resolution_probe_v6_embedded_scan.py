#!/usr/bin/env python3
"""
Interstate '76 object resource embedded lookup probe, v6.

Purpose:
  Keep the binary-backed policy from v31/v32/v33:
    ODEF dispatch-valid object -> label.vcf
    LDEF object -> label.sdf
    SOBJ child -> part.geo
  but look for missing binary candidates inside container-like files rather than
  treating same-basename .sdf files as runtime truth.

This probe does three things:
  1. Re-parses mission ODEF/LDEF records and produces binary candidate names.
  2. Indexes loose files under asset roots by filename.
  3. Scans container-like files for candidate ASCII names and basename mentions.

It does NOT claim an embedded-name hit is a decoded resource; it is only evidence
for where to inspect next.
"""

from __future__ import annotations

import argparse, csv, dataclasses, json, os, re, struct, tarfile, time
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
CONTAINER_EXTS = {".pak", ".pix", ".zfs", ".zix", ".dat", ".mw2", ".res", ".rsc", ".bin"}
MISSION_EXTS = {".msn", ".lvl", ".spc"}

@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""
    @property
    def end(self) -> int:
        return self.offset + self.size

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode("ascii", errors="replace")

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out=[]
    off=start
    while off+8 <= end:
        tag=fourcc(data,off)
        size=u32(data,off+4)
        if size < 8 or off+size > end:
            break
        out.append(Chunk(tag,off,size,off+8,size-8,parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots=parse_flat(data,0,len(data),"")
    allc=[]
    def rec(chs):
        for c in chs:
            allc.append(c)
            if c.tag in CONTAINERS and c.payload_size>=8:
                rec(parse_flat(data,c.payload_offset,c.end,c.tag))
    rec(roots)
    return allc

def decode_label(raw: bytes) -> Tuple[str,int]:
    chars=[]
    mask=0
    for i,b in enumerate(raw[:8]):
        if b & 0x80:
            mask |= (1 << i)
        v=b & 0x7f
        if v == 0:
            break
        chars.append(chr(v) if 32 <= v < 127 else "?")
    return "".join(chars).strip(), mask

def parse_odef_obj(data: bytes, c: Chunk, mission_set: str, mission: str, idx: int) -> dict:
    p=c.payload_offset
    raw=data[p:p+8]
    name,himask=decode_label(raw)
    cls = u32(data,p+0x5c) if c.payload_size >= 0x60 else None
    rec={
        "mission_set":mission_set, "mission":mission, "section":"ODEF", "record_index":idx,
        "chunk_offset_hex":f"0x{c.offset:08x}", "name":name, "raw_label_hex":raw.hex(),
        "label_hi_mask_hex":f"0x{himask:02x}", "class_hex":("" if cls is None else f"0x{cls:02x}"),
        "pos_x":("" if c.payload_size<0x38 else f"{f32(data,p+0x2c):.6f}"),
        "pos_y":("" if c.payload_size<0x38 else f"{f32(data,p+0x30):.6f}"),
        "pos_z":("" if c.payload_size<0x38 else f"{f32(data,p+0x34):.6f}"),
        "payload_size":c.payload_size,
    }
    if not name or cls == 0 or cls is None:
        rec["policy"]="special_or_invalid"; rec["candidate_name"]=""; rec["reason"]="blank_or_class0_no_resource"
    elif name.lower() in {"spawn","regen"} and cls == 1:
        rec["policy"]="special_marker"; rec["candidate_name"]=""; rec["reason"]="spawn_or_regen_no_file"
    else:
        rec["policy"]="binary_odef_vcf"; rec["candidate_name"]=name.lower()+".vcf"; rec["reason"]="binary_validated_odef_label_plus_vcf"
    rec["open76_candidate_name"] = "" if rec["policy"] != "binary_odef_vcf" else name.lower()+".sdf"
    return rec

def parse_ldef_obj(data: bytes, c: Chunk, mission_set: str, mission: str, idx: int) -> dict:
    p=c.payload_offset
    raw=data[p:p+8]
    name,himask=decode_label(raw)
    return {
        "mission_set":mission_set, "mission":mission, "section":"LDEF", "record_index":idx,
        "chunk_offset_hex":f"0x{c.offset:08x}", "name":name, "raw_label_hex":raw.hex(),
        "label_hi_mask_hex":f"0x{himask:02x}", "class_hex":"",
        "pos_x":"", "pos_y":"", "pos_z":"", "payload_size":c.payload_size,
        "policy":"binary_ldef_sdf" if name else "special_or_invalid",
        "candidate_name":(name.lower()+".sdf") if name else "",
        "reason":"binary_validated_ldef_label_plus_sdf" if name else "blank_ldef_name",
        "open76_candidate_name":(name.lower()+".sdf") if name else "",
    }

def find_files(root: Path) -> List[Path]:
    if root.is_file(): return [root]
    return [p for p in root.rglob("*") if p.is_file()]

def iter_missions(root: Path, mission_filter: str) -> List[Path]:
    files=find_files(root)
    out=[]
    mf=mission_filter.lower()
    for p in files:
        if p.suffix.lower() in MISSION_EXTS:
            if not mf or mf in p.stem.lower() or mf in p.name.lower():
                out.append(p)
    return sorted(out)

def parse_missions(miss_dirs: List[Tuple[str,Path]], mission_filter: str) -> List[dict]:
    rows=[]
    for setname, root in miss_dirs:
        for m in iter_missions(root, mission_filter):
            data=m.read_bytes()
            chunks=parse_tree(data)
            oidx=lidx=0
            for c in chunks:
                if c.parent=="ODEF" and c.tag.startswith("OBJ") and c.payload_size>=0x64:
                    rows.append(parse_odef_obj(data,c,setname,m.name,oidx)); oidx+=1
                elif c.parent=="LDEF" and c.tag.startswith("OBJ"):
                    rows.append(parse_ldef_obj(data,c,setname,m.name,lidx)); lidx+=1
    return rows

def index_assets(roots: List[Path]) -> Tuple[Dict[str,List[Path]], List[Path]]:
    byname: Dict[str,List[Path]]={}
    containers=[]
    for root in roots:
        if not root.exists():
            continue
        for p in find_files(root):
            byname.setdefault(p.name.lower(),[]).append(p)
            if p.suffix.lower() in CONTAINER_EXTS:
                containers.append(p)
    return byname, containers

def write_tsv(path: Path, rows: List[dict], fieldnames: List[str]):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w=csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)

def byte_search_container(path: Path, needles: List[bytes], max_size: int) -> List[Tuple[int,bytes]]:
    try:
        size=path.stat().st_size
        if max_size and size > max_size:
            return []
        data=path.read_bytes()
    except Exception:
        return []
    hits=[]
    low=data.lower()
    for n in needles:
        if not n: continue
        pos=low.find(n.lower())
        if pos >= 0:
            hits.append((pos,n))
    return hits

def main() -> int:
    ap=argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--asset-root", type=Path, action="append", required=True)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--scan-containers", action="store_true", help="Scan container-like files for missing candidate names")
    ap.add_argument("--max-container-size", type=int, default=256*1024*1024)
    ap.add_argument("--make-tar", action="store_true")
    args=ap.parse_args()

    out=args.out_dir
    out.mkdir(parents=True, exist_ok=True)
    rows=parse_missions([("miss8",args.miss8),("miss16",args.miss16)], args.mission_filter)
    byname, containers=index_assets(args.asset_root)

    loose_matches=[]
    unresolved=[]
    alt=[]
    for r in rows:
        cand=r.get("candidate_name","")
        if cand and cand in byname:
            for p in byname[cand]:
                rr=dict(r); rr.update({"matched_name":cand, "matched_ext":Path(cand).suffix.lower(), "path":str(p)})
                loose_matches.append(rr)
        elif cand:
            unresolved.append(dict(r))
            base=Path(cand).stem
            for ext in [".sdf",".vcf",".vdf",".pak",".pix",".geo"]:
                an=base+ext
                if an in byname and an != cand:
                    for p in byname[an]:
                        rr=dict(r); rr.update({"binary_candidate":cand,"alt_name":an,"alt_ext":ext,"alt_path":str(p),"diagnostic_note":"same_basename_alternative_not_binary_truth"})
                        alt.append(rr)

    # container scan only for unresolved binary candidates
    container_hits=[]
    if args.scan_containers:
        missing=sorted({r["candidate_name"].lower() for r in unresolved if r.get("candidate_name")})
        # include basename-only and extension candidate
        needles=[]
        for c in missing:
            needles.append(c.encode("ascii","ignore"))
            needles.append(Path(c).stem.encode("ascii","ignore"))
        # de-dup preserving order
        seen=set(); nd=[]
        for n in needles:
            if n and n not in seen:
                seen.add(n); nd.append(n)
        for ci,p in enumerate(containers):
            hits=byte_search_container(p, nd, args.max_container_size)
            for pos,n in hits:
                container_hits.append({
                    "container_path":str(p), "container_name":p.name, "container_ext":p.suffix.lower(),
                    "offset_hex":f"0x{pos:x}", "needle":n.decode("ascii","ignore"),
                    "note":"raw_ascii_hit_not_decoded_resource"
                })

    common=["mission_set","mission","section","record_index","chunk_offset_hex","name","raw_label_hex","label_hi_mask_hex","class_hex","pos_x","pos_y","pos_z","payload_size","policy","candidate_name","reason","open76_candidate_name"]
    write_tsv(out/"object_records_binary_policy.tsv", rows, common)
    write_tsv(out/"loose_binary_resource_matches.tsv", loose_matches, common+["matched_name","matched_ext","path"])
    write_tsv(out/"loose_binary_resource_unresolved.tsv", unresolved, common)
    write_tsv(out/"same_basename_alternatives.tsv", alt, common+["binary_candidate","alt_name","alt_ext","alt_path","diagnostic_note"])
    write_tsv(out/"container_name_hits.tsv", container_hits, ["container_path","container_name","container_ext","offset_hex","needle","note"])

    # candidate list
    cand_rows=[]
    for c in sorted({r["candidate_name"] for r in rows if r.get("candidate_name")}):
        cand_rows.append({"candidate_name":c,"loose_match_count":len(byname.get(c,[])),"basename":Path(c).stem,"ext":Path(c).suffix.lower()})
    write_tsv(out/"binary_candidate_names.tsv", cand_rows, ["candidate_name","basename","ext","loose_match_count"])

    summary=[]
    def add(k,v): summary.append({"key":k,"value":v})
    add("object_records",len(rows)); add("loose_binary_matches",len(loose_matches)); add("loose_binary_unresolved",len(unresolved))
    add("same_basename_alternatives",len(alt)); add("asset_index_file_count",sum(len(v) for v in byname.values()))
    add("container_file_count",len(containers)); add("container_name_hits",len(container_hits))
    write_tsv(out/"summary.tsv", summary, ["key","value"])

    manifest={
        "format":"i76_object_geometry_resolution_embedded_probe",
        "version":6,
        "asset_roots":[str(p) for p in args.asset_root],
        "mission_filter":args.mission_filter,
        "scan_containers":args.scan_containers,
        "max_container_size":args.max_container_size,
        "object_records":len(rows),
        "loose_binary_matches":len(loose_matches),
        "loose_binary_unresolved":len(unresolved),
        "same_basename_alternatives":len(alt),
        "container_file_count":len(containers),
        "container_name_hits":len(container_hits),
        "policy":{"odef":"label.vcf after binary validation","ldef":"label.sdf","alternatives":"diagnostic only"}
    }
    (out/"manifest.json").write_text(json.dumps(manifest,indent=2),encoding="utf-8")
    print(json.dumps(manifest,indent=2))

    if args.make_tar:
        tar_path=out.with_suffix(".tar")
        with tarfile.open(tar_path,"w") as tf:
            tf.add(out, arcname=out.name)
        print(f"tar={tar_path}")
    return 0

if __name__=="__main__":
    raise SystemExit(main())
