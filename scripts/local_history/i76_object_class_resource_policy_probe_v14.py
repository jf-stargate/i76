#!/usr/bin/env python3
"""
Interstate '76 object class/resource policy probe, v14.

Purpose:
  Reconcile binary-truth ODEF class handling against the actual extracted resource
  inventory. Earlier probes correctly found recursive .vcf inventory, but treated all
  dispatch-valid ODEF rows as label.vcf. The full-corpus class distribution shows a
  stronger class-specific split:
    - class 0x01 / 0x08 / 0x09 commonly resolve to .vcf
    - classes 0x02 / 0x03 / 0x04 / 0x50 / 0x52 commonly have same-stem .sdf
      alternatives and no .vcf

This probe does not assert final runtime semantics. It produces class-by-class
evidence tables so the next Ghidra pass can validate class-case bodies.
"""

from __future__ import annotations

import argparse, csv, json, struct, tarfile, time
from pathlib import Path
from collections import Counter, defaultdict

CONTAINERS = {"BWD2","WDEF","TDEF","RDEF","ODEF","LDEF","ADEF"}
ODEF_OBJ_PAYLOAD = 100

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode("ascii", errors="replace")

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]

def parse_flat(data: bytes, start: int, end: int, parent: str):
    off=start
    while off+8 <= end:
        tag=fourcc(data, off)
        size=u32(data, off+4)
        if size < 8 or off+size > end:
            break
        yield {"tag":tag, "offset":off, "size":size, "payload_offset":off+8, "payload_size":size-8, "parent":parent}
        off += size

def parse_tree(data: bytes):
    roots=list(parse_flat(data, 0, len(data), ""))
    out=[]
    def rec(chunks):
        for c in chunks:
            out.append(c)
            if c["tag"] in CONTAINERS and c["payload_size"] >= 8:
                rec(list(parse_flat(data, c["payload_offset"], c["offset"]+c["size"], c["tag"])))
    rec(roots)
    return out

def decode_label(raw8: bytes):
    chars=[]
    high=0
    for i,b in enumerate(raw8):
        if b & 0x80:
            high |= (1<<i)
        c=b & 0x7f
        if c == 0:
            break
        chars.append(chr(c))
    return "".join(chars), high

def iter_files(root: Path):
    if root.is_file():
        yield root
    else:
        for p in root.rglob("*"):
            if p.is_file():
                yield p

def index_assets(roots):
    by_name={}
    by_stem=defaultdict(list)
    ext_counts=Counter()
    for root in roots:
        if not root.exists():
            continue
        for p in iter_files(root):
            name=p.name.lower()
            ext=p.suffix.lower()
            ext_counts[ext]+=1
            by_name.setdefault(name, p)
            by_stem[p.stem.lower()].append(p)
    return by_name, by_stem, ext_counts

def find_missions(root: Path):
    return sorted([p for p in iter_files(root) if p.suffix.lower() in {".msn",".spc",".lvl"}])

def row_writer(path, fields):
    f=open(path, "w", newline="", encoding="utf-8")
    w=csv.DictWriter(f, fieldnames=fields, delimiter="\t", extrasaction="ignore")
    w.writeheader()
    return f,w

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--asset-root", type=Path, action="append", required=True)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--make-tar", action="store_true")
    args=ap.parse_args()

    run_dir=args.out_dir
    run_dir.mkdir(parents=True, exist_ok=True)

    by_name, by_stem, ext_counts = index_assets(args.asset_root)

    rec_fields=[
        "corpus","mission","chunk_offset_hex","label","raw_name_hex","label_highbits",
        "class_hex","pos_x","pos_y","pos_z","vcf_candidate","vcf_match",
        "sdf_candidate","sdf_match","same_stem_exts","policy_hint"
    ]
    rec_f, rec_w = row_writer(run_dir/"odef_class_resource_records.tsv", rec_fields)

    summary=defaultdict(lambda: Counter())
    examples=defaultdict(list)

    roots=[("miss8", args.miss8), ("miss16", args.miss16)]
    for corpus, root in roots:
        for msn in find_missions(root):
            if args.mission_filter and args.mission_filter.lower() not in msn.name.lower() and args.mission_filter.lower() not in msn.stem.lower():
                continue
            data=msn.read_bytes()
            chunks=parse_tree(data)
            for c in chunks:
                if c["parent"] != "ODEF" or c["tag"] != "OBJ\x00" or c["payload_size"] < ODEF_OBJ_PAYLOAD:
                    continue
                po=c["payload_offset"]
                raw8=data[po:po+8]
                label, high=decode_label(raw8)
                cls=u32(data, po+0x5c) & 0xff
                class_hex=f"0x{cls:02x}"
                px,py,pz=f32(data, po+0x2c), f32(data, po+0x30), f32(data, po+0x34)
                if not label or cls == 0:
                    hint="blank_or_class0_special"
                    vcf=sdf=""
                    vcf_match=sdf_match=False
                elif cls == 1 and label.lower() in {"spawn","regen"}:
                    hint="spawn_regen_special"
                    vcf=sdf=""
                    vcf_match=sdf_match=False
                else:
                    vcf=f"{label.lower()}.vcf"
                    sdf=f"{label.lower()}.sdf"
                    vcf_match=vcf in by_name
                    sdf_match=sdf in by_name
                    # Evidence-oriented hint, not final runtime truth.
                    if vcf_match and not sdf_match:
                        hint="vcf_only"
                    elif sdf_match and not vcf_match:
                        hint="sdf_only_same_stem"
                    elif vcf_match and sdf_match:
                        hint="both_vcf_and_sdf"
                    else:
                        hint="neither_vcf_nor_sdf"

                stem_exts=""
                if label:
                    stem_exts=",".join(sorted({p.suffix.lower() for p in by_stem.get(label.lower(), []) if p.suffix}))

                rec={
                    "corpus":corpus,"mission":msn.name,"chunk_offset_hex":f"0x{c['offset']:08x}",
                    "label":label,"raw_name_hex":raw8.hex(),"label_highbits":high,
                    "class_hex":class_hex,"pos_x":f"{px:.6f}","pos_y":f"{py:.6f}","pos_z":f"{pz:.6f}",
                    "vcf_candidate":vcf,"vcf_match":int(bool(vcf_match)),
                    "sdf_candidate":sdf,"sdf_match":int(bool(sdf_match)),
                    "same_stem_exts":stem_exts,"policy_hint":hint
                }
                rec_w.writerow(rec)
                summary[class_hex]["records"] += 1
                summary[class_hex][hint] += 1
                if vcf_match: summary[class_hex]["vcf_match"] += 1
                if sdf_match: summary[class_hex]["sdf_match"] += 1
                if len(examples[class_hex]) < 12:
                    examples[class_hex].append(rec)

    rec_f.close()

    sum_fields=["class_hex","records","vcf_match","sdf_match","vcf_only","sdf_only_same_stem","both_vcf_and_sdf","neither_vcf_nor_sdf","spawn_regen_special","blank_or_class0_special"]
    sum_f,sum_w=row_writer(run_dir/"odef_class_resource_summary.tsv", sum_fields)
    for cls in sorted(summary.keys()):
        c=summary[cls]
        row={"class_hex":cls}
        for k in sum_fields[1:]:
            row[k]=c.get(k,0)
        sum_w.writerow(row)
    sum_f.close()

    ex_fields=rec_fields
    ex_f,ex_w=row_writer(run_dir/"odef_class_resource_examples.tsv", ex_fields)
    for cls in sorted(examples.keys()):
        for r in examples[cls]:
            ex_w.writerow(r)
    ex_f.close()

    ext_f,ext_w=row_writer(run_dir/"asset_extension_inventory.tsv", ["ext","count"])
    for ext,count in ext_counts.most_common():
        ext_w.writerow({"ext":ext, "count":count})
    ext_f.close()

    manifest={
        "format":"i76_object_class_resource_policy_probe",
        "version":14,
        "asset_roots":[str(p) for p in args.asset_root],
        "asset_file_count":sum(ext_counts.values()),
        "vcf_count":ext_counts.get(".vcf",0),
        "sdf_count":ext_counts.get(".sdf",0),
        "mission_filter":args.mission_filter,
        "outputs":["odef_class_resource_records.tsv","odef_class_resource_summary.tsv","odef_class_resource_examples.tsv","asset_extension_inventory.tsv"],
        "note":"Class-specific evidence only. Runtime semantics should be validated in Ghidra case bodies."
    }
    (run_dir/"manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path=run_dir.with_suffix(".tar")
        with tarfile.open(tar_path, "w") as tf:
            tf.add(run_dir, arcname=run_dir.name)
        manifest["tar_path"]=str(tar_path)
        (run_dir/"manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({"out_dir":str(run_dir),"vcf_count":ext_counts.get(".vcf",0),"sdf_count":ext_counts.get(".sdf",0)}, indent=2))
if __name__=="__main__":
    main()
