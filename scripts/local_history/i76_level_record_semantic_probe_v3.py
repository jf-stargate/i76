#!/usr/bin/env python3
"""
Interstate '76 level record semantic probe v3.

Corpus-side decoder to correlate with cgpt_i76exe_export_level_record_handler_deeptrace_v17.
It keeps the broad v2 outputs but adds:
  * ODEF/OBJ tail dword offset histograms and type-byte classification.
  * ODEF/OBJ likely object class from payload +0x5c.
  * RDEF/RSEG records decoded as six float32s plus raw hex.
  * RDEF/RSEG kind/count histograms.
  * LDEF/OBJ size/name histograms and raw payload samples.
  * FSM token histogram.

This remains a probe, not a final semantic decoder.
"""

from __future__ import annotations
import argparse, csv, dataclasses, json, math, os, re, struct, subprocess
from pathlib import Path
from collections import Counter, defaultdict
from typing import List, Tuple, Dict, Iterable, Optional

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

WRLD_FIELDS = [
    (30, 13, "palette_act"),
    (43, 13, "luma_lum"),
    (56, 13, "translucency_tbl"),
    (69, 13, "objective_npt"),
    (82, 13, "sky_texture"),
    (95, 13, "scrounge_or_screen_sdf"),
    (108, 13, "surface_texture"),
    (121, 13, "level_map_texture"),
    (134, 13, "hazard_hzd"),
]

@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""
    @property
    def end(self) -> int: return self.offset + self.size

def u32(data: bytes, off: int) -> int: return struct.unpack_from("<I", data, off)[0]
def f32(data: bytes, off: int) -> float: return struct.unpack_from("<f", data, off)[0]
def fourcc(data: bytes, off: int) -> str: return data[off:off+4].decode("ascii", errors="replace")
def clean_cstr(b: bytes) -> str:
    return b.split(b"\0",1)[0].decode("latin1", errors="replace").strip()
def printable(b: bytes) -> str:
    return re.sub(r"[^ -~]", ".", b.decode("latin1", errors="replace"))
def hexbytes(b: bytes) -> str:
    return " ".join(f"{x:02x}" for x in b)
def sane_float(x: float) -> str:
    if not math.isfinite(x): return "nan"
    return f"{x:.9g}"

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out=[]; off=start
    while off+8 <= end:
        tag=fourcc(data, off); size=u32(data, off+4)
        if size < 8 or off+size > end: break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots=parse_flat(data,0,len(data),"")
    def rec(chs):
        out=[]
        for c in chs:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                out.extend(rec(parse_flat(data,c.payload_offset,c.end,c.tag)))
        return out
    return rec(roots)

def nested(chunks, parent, tag):
    return [c for c in chunks if c.parent == parent and c.tag == tag]

def mission_files(root: Path):
    if root.is_file(): return [root]
    return sorted(p for p in root.rglob("*") if p.is_file() and p.suffix.lower() in {".msn",".spc",".lvl"})

def write_tsv(path: Path, fields: List[str], rows: Iterable[dict]) -> int:
    path.parent.mkdir(parents=True, exist_ok=True)
    n=0
    with path.open("w", newline="", encoding="utf-8") as f:
        w=csv.DictWriter(f, fields, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r); n+=1
    return n

def decode_wrld(corpus, msn, data, chunks):
    rows=[]
    for c in nested(chunks,"WDEF","WRLD"):
        p=data[c.payload_offset:c.end]
        rev = u32(p,0) if len(p)>=4 else ""
        for off,w,name in WRLD_FIELDS:
            val=clean_cstr(p[off:off+w]) if off+w <= len(p) else ""
            rows.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(),
                             chunk_offset=f"0x{c.offset:08x}", field=name, offset=off, width=w, value=val,
                             wrld_revision_or_flags=rev))
    return rows

def decode_odef(corpus, msn, data, chunks):
    obj_rows=[]; tail_rows=[]
    for idx,c in enumerate(nested(chunks,"ODEF","OBJ\0")):
        p=data[c.payload_offset:c.end]
        if len(p) < 100: continue
        tail=p[56:100]
        dwords=[u32(tail,i) for i in range(0,44,4)]
        class_byte = p[92] if len(p)>92 else 0
        name=clean_cstr(p[:8])
        row=dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(), index=idx,
                 chunk_offset=f"0x{c.offset:08x}", payload_size=len(p),
                 name8=name, class_byte=class_byte, class_chr=chr(class_byte) if 32 <= class_byte <= 126 else "",
                 basis00=sane_float(f32(p,8)), basis01=sane_float(f32(p,12)), basis02=sane_float(f32(p,16)),
                 basis10=sane_float(f32(p,20)), basis11=sane_float(f32(p,24)), basis12=sane_float(f32(p,28)),
                 basis20=sane_float(f32(p,32)), basis21=sane_float(f32(p,36)), basis22=sane_float(f32(p,40)),
                 pos_x=sane_float(f32(p,44)), pos_y=sane_float(f32(p,48)), pos_z=sane_float(f32(p,52)),
                 tail_u32_hex=" ".join(f"{x:08x}" for x in dwords), tail_ascii=printable(tail))
        obj_rows.append(row)
        for j,val in enumerate(dwords):
            tail_rows.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(), index=idx,
                                  name8=name, tail_offset=56+j*4, tail_dword_index=j,
                                  value_u32=val, value_hex=f"0x{val:08x}"))
    return obj_rows, tail_rows

def decode_rseg(corpus, msn, data, chunks):
    hdr=[]; pts=[]
    for si,c in enumerate(nested(chunks,"RDEF","RSEG")):
        p=data[c.payload_offset:c.end]
        if len(p)<8: continue
        kind=u32(p,0); count=u32(p,4); rem=len(p)-8
        hdr.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(),
                        segment_index=si, chunk_offset=f"0x{c.offset:08x}", payload_size=len(p),
                        kind_u32=kind, count_u32=count, remaining_bytes=rem,
                        stride24_ok=(rem==count*24), stride16_ok=(rem==count*16)))
        if rem == count*24:
            for i in range(count):
                off=8+i*24
                raw=p[off:off+24]
                vals=[f32(raw,j*4) for j in range(6)]
                pts.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(),
                                segment_index=si, point_index=i, chunk_offset=f"0x{c.offset:08x}",
                                raw_hex=hexbytes(raw),
                                f0=sane_float(vals[0]), f1=sane_float(vals[1]), f2=sane_float(vals[2]),
                                f3=sane_float(vals[3]), f4=sane_float(vals[4]), f5=sane_float(vals[5])))
    return hdr, pts

def decode_ldef(corpus, msn, data, chunks):
    rows=[]
    for idx,c in enumerate(nested(chunks,"LDEF","OBJ\0")):
        p=data[c.payload_offset:c.end]
        rows.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(), index=idx,
                         chunk_offset=f"0x{c.offset:08x}", payload_size=len(p),
                         name_guess=clean_cstr(p[:16]), first64_hex=hexbytes(p[:64]),
                         ascii_preview=printable(p[:128])))
    return rows

def decode_fsm(corpus, msn, data, chunks):
    rows=[]
    for c in nested(chunks,"ADEF","FSM\0"):
        p=data[c.payload_offset:c.end]
        for m in re.finditer(rb"[A-Za-z_][A-Za-z0-9_]{1,31}", p):
            rows.append(dict(corpus=corpus, mission=msn.name, stem=msn.stem.lower(),
                             chunk_offset=f"0x{c.offset:08x}", payload_size=len(p),
                             string_offset=m.start(), string=m.group(0).decode("ascii","replace")))
    return rows

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("input", nargs="?", type=Path)
    ap.add_argument("--miss8", type=Path)
    ap.add_argument("--miss16", type=Path)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--make-tar", action="store_true")
    args=ap.parse_args()
    inputs=[]
    if args.miss8: inputs.append(("miss8", args.miss8))
    if args.miss16: inputs.append(("miss16", args.miss16))
    if not inputs and args.input: inputs.append(("input", args.input))
    if not inputs: raise SystemExit("provide input or --miss8/--miss16")
    out=args.out_dir; out.mkdir(parents=True, exist_ok=True)

    wrld=[]; odef=[]; otail=[]; rhdr=[]; rpts=[]; ldef=[]; fsm=[]; warnings=[]; missions=0
    for corpus,root in inputs:
        for msn in mission_files(root):
            if args.mission_filter and args.mission_filter.lower() not in msn.name.lower() and args.mission_filter.lower() not in msn.stem.lower():
                continue
            missions += 1
            try:
                data=msn.read_bytes(); chunks=parse_tree(data)
                wrld.extend(decode_wrld(corpus,msn,data,chunks))
                a,b=decode_odef(corpus,msn,data,chunks); odef.extend(a); otail.extend(b)
                a,b=decode_rseg(corpus,msn,data,chunks); rhdr.extend(a); rpts.extend(b)
                ldef.extend(decode_ldef(corpus,msn,data,chunks))
                fsm.extend(decode_fsm(corpus,msn,data,chunks))
            except Exception as e:
                warnings.append(f"{corpus}:{msn}: {type(e).__name__}: {e}")

    # Histograms
    hist_rows=[]
    for name, counter in [
        ("odef_class_byte", Counter((r["class_byte"], r["class_chr"]) for r in odef)),
        ("rseg_kind", Counter(r["kind_u32"] for r in rhdr)),
        ("ldef_payload_size", Counter(r["payload_size"] for r in ldef)),
        ("fsm_token", Counter(r["string"] for r in fsm)),
    ]:
        for key,count in counter.most_common(300):
            if isinstance(key, tuple): kval="|".join(str(x) for x in key)
            else: kval=str(key)
            hist_rows.append(dict(histogram=name, key=kval, count=count))

    outputs={}
    outputs["wrld_fixed_fields_v3.tsv"]=write_tsv(out/"wrld_fixed_fields_v3.tsv", ["corpus","mission","stem","chunk_offset","wrld_revision_or_flags","field","offset","width","value"], wrld)
    outputs["odef_obj_records_v3.tsv"]=write_tsv(out/"odef_obj_records_v3.tsv", ["corpus","mission","stem","index","chunk_offset","payload_size","name8","class_byte","class_chr","basis00","basis01","basis02","basis10","basis11","basis12","basis20","basis21","basis22","pos_x","pos_y","pos_z","tail_u32_hex","tail_ascii"], odef)
    outputs["odef_obj_tail_dwords_v3.tsv"]=write_tsv(out/"odef_obj_tail_dwords_v3.tsv", ["corpus","mission","stem","index","name8","tail_offset","tail_dword_index","value_u32","value_hex"], otail)
    outputs["rdef_rseg_headers_v3.tsv"]=write_tsv(out/"rdef_rseg_headers_v3.tsv", ["corpus","mission","stem","segment_index","chunk_offset","payload_size","kind_u32","count_u32","remaining_bytes","stride24_ok","stride16_ok"], rhdr)
    outputs["rdef_rseg_points_v3.tsv"]=write_tsv(out/"rdef_rseg_points_v3.tsv", ["corpus","mission","stem","segment_index","point_index","chunk_offset","raw_hex","f0","f1","f2","f3","f4","f5"], rpts)
    outputs["ldef_obj_records_v3.tsv"]=write_tsv(out/"ldef_obj_records_v3.tsv", ["corpus","mission","stem","index","chunk_offset","payload_size","name_guess","first64_hex","ascii_preview"], ldef)
    outputs["adef_fsm_tokens_v3.tsv"]=write_tsv(out/"adef_fsm_tokens_v3.tsv", ["corpus","mission","stem","chunk_offset","payload_size","string_offset","string"], fsm)
    outputs["corpus_histograms_v3.tsv"]=write_tsv(out/"corpus_histograms_v3.tsv", ["histogram","key","count"], hist_rows)

    manifest=dict(format="i76_level_record_semantic_probe", version=3, mission_count=missions,
                  inputs=[str(p) for _,p in inputs], mission_filter=args.mission_filter,
                  outputs=outputs, warnings=warnings,
                  notes=["ODEF class_byte is payload +0x5c, matching handler comparisons against 0x50/0x52/0x53.",
                         "RSEG points are still emitted as six f32 values; raw_hex is included for alternate integer/fixed-point decoding."])
    (out/"manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    if args.make_tar:
        subprocess.run(["tar","-cf",str(out.with_suffix(".tar")),"-C",str(out.parent),out.name], check=False)
    print(json.dumps({"out_dir":str(out), "missions":missions, "warnings":len(warnings), "outputs":outputs}, indent=2))

if __name__ == "__main__":
    main()
