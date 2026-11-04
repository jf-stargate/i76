"""Read-only aggregate inspector; never emits a full proprietary inventory.
ZFS authentication uses pinned historical extraction as comparison evidence,
including its system liblzo2 dependency; the PIX/PAK reader has no dependency.
"""
import argparse
from collections import Counter, defaultdict
from dataclasses import asdict
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
from pix_reader import parse_index, validate_ranges, FormatError

def sha(data):
    return hashlib.sha256(data).hexdigest()

def load_module(path):
    spec = importlib.util.spec_from_file_location("historical_pix_comparison", path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mod
    spec.loader.exec_module(mod)
    return mod

def inspect(root, archive, historical, private_details=None):
    baseline = load_module(historical)
    header, records = baseline.parse_zfs_records(archive)
    lzo = baseline.Lzo()
    disk = {p.name.lower(): p for p in root.iterdir() if p.is_file()}
    auth, flags, failures = {}, Counter(), Counter()
    identities = []
    # Only archive PIX/PAK records are decoded; no writes or asset exports.
    with archive.open("rb") as stream:
        for r in records:
            if not r.active or r.extension not in ("pix", "pak"):
                continue
            flags[str(r.compression)] += 1
            stream.seek(r.file_offset)
            packed = stream.read(r.stored_size)
            if len(packed) != r.stored_size:
                raise ValueError("truncated ZFS specimen")
            blob = lzo.decompress(packed, r.logical_size, r.compression)
            if len(blob) != (r.logical_size if r.compression else r.stored_size):
                raise ValueError("ZFS decode size mismatch")
            target = disk.get(r.name.lower())
            ok = target is not None and sha(target.read_bytes()) == sha(blob)
            auth[r.name.lower()] = ok
            if not ok:
                failures["archive_vs_extracted"] += 1
            identities.append([r.name.lower(), len(blob), sha(blob), ok])
    pairs, all_entries, ranges = [], defaultdict(list), []
    counts, exts = Counter(), Counter()
    samples, details, comparison = {}, [], Counter({"index_mismatches":0,"entry_mismatches":0})
    counts.update({k:0 for k in ("unsupported_indexes","missing_pak","invalid_range_indexes")})
    for path in sorted(root.iterdir(), key=lambda p: p.name.lower()):
        if path.suffix.lower() != ".pix":
            continue
        raw = path.read_bytes()
        counts["pix_files"] += 1
        counts["crlf_indexes"] += b"\r\n" in raw
        try:
            index = parse_index(raw)
        except FormatError:
            counts["unsupported_indexes"] += 1
            continue
        counts["valid_indexes"] += 1
        pak_name = path.name.split(".", 1)[0].lower() + ".pak"
        pak = disk.get(pak_name)
        if pak is None:
            counts["missing_pak"] += 1
            continue
        data = pak.read_bytes()
        try:
            validate_ranges(index, len(data))
        except FormatError:
            counts["invalid_range_indexes"] += 1
            continue
        pairs.append(pak_name)
        legacy_count, legacy_rows, legacy_err = baseline.parse_pix_index(raw)
        comparison["indexes"] += 1
        if legacy_err or legacy_count != len(index.entries):
            comparison["index_mismatches"] += 1
        intervals = []
        previous = None
        backward = 0
        for e, old in zip(index.entries, legacy_rows):
            counts["valid_entries"] += 1
            ext = Path(e.name).suffix.lower()
            exts[ext] += 1
            counts["zero_length_entries"] += e.size == 0
            payload = data[e.offset:e.offset + e.size]
            digest = sha(payload)
            comparison["entries"] += 1
            old_name, old_offset, old_size = old
            if (e.name, e.offset, e.size) != old or digest != sha(data[old_offset:old_offset+old_size]):
                comparison["entry_mismatches"] += 1
            all_entries[e.key].append((pak_name, e.offset, e.size, digest))
            if e.size:
                intervals.append((e.offset, e.offset + e.size))
            if previous is not None and e.offset < previous:
                backward += 1
            previous = e.offset
            sample_key = ext if ext not in samples else ext + "_nonzero"
            if ext in (".geo", ".tmt", ".map", ".m16", ".vqm", ".cbk") and sample_key not in samples and (sample_key == ext or e.offset > 0):
                samples[sample_key] = {"pix": path.name, "pix_bytes": len(raw), "pix_sha256": sha(raw),
                                "pak": pak.name, "pak_bytes": len(data), "pak_sha256": sha(data),
                                "archive_authenticated": bool(auth.get(path.name.lower()) and auth.get(pak_name)),
                                **asdict(e), "payload_sha256": digest,
                                "loose_name_present": e.name.lower() in disk}
        counts["indexes_with_descending_offsets"] += backward != 0
        # Union lengths count alias/overlap bytes only once. Count overlap pairs separately.
        intervals.sort()
        union = end = overlap_pairs = 0
        active_ends = []
        import heapq
        for start, stop in intervals:
            while active_ends and active_ends[0] <= start:
                heapq.heappop(active_ends)
            overlap_pairs += len(active_ends)
            heapq.heappush(active_ends, stop)
            union += max(0, stop - max(start, end))
            end = max(end, stop)
        row = {"pak": pak_name, "bytes": len(data), "entries": len(index.entries),
               "union_bytes": union, "unused_bytes": len(data)-union,
               "overlap_pairs": overlap_pairs, "min_start": intervals[0][0] if intervals else None,
               "max_end": end, "sha256": sha(data)}
        details.append(row)
        counts["pak_bytes"] += len(data)
        counts["referenced_union_bytes"] += union
        counts["unused_bytes"] += len(data)-union
        counts["overlap_pairs"] += overlap_pairs
        counts["paks_with_unused_bytes"] += len(data) != union
        counts["paks_with_overlaps"] += overlap_pairs != 0
        counts["nonzero_first_offset"] += bool(intervals and intervals[0][0] != 0)
    counts["pak_files"] = sum(p.suffix.lower()==".pak" for p in root.iterdir())
    counts["paired_pak_files"] = len(set(pairs))
    counts["unreferenced_pak_files"] = counts["pak_files"]-counts["paired_pak_files"]
    counts["unique_names"] = len(all_entries)
    duplicates = [v for v in all_entries.values() if len(v)>1]
    counts["duplicate_keys"] = len(duplicates)
    counts["duplicate_extra_entries"] = sum(len(v)-1 for v in duplicates)
    counts["duplicate_keys_distinct_locations"] = sum(len(set(x[:3] for x in v))>1 for v in duplicates)
    counts["duplicate_keys_distinct_payloads"] = sum(len(set(x[3] for x in v))>1 for v in duplicates)
    counts["within_pak_duplicate_keys"] = sum(any(n>1 for n in Counter(x[0] for x in v).values()) for v in duplicates)
    def digest_json(value):
        return sha(json.dumps(value,sort_keys=True,separators=(",", ":")).encode())
    if private_details:
        private_details.write_text(json.dumps({"identities":identities,"ranges":details},sort_keys=True,indent=2)+"\n")
    return {"archive": {"name":archive.name,"bytes":archive.stat().st_size,"sha256":sha(archive.read_bytes()),
                         "directory_records":len(records),"pix_pak_records":len(identities),
                         "authenticated_extracted_files":sum(auth.values()),"compression_flags":dict(flags),
                         "failures":dict(failures),"identity_digest":digest_json(identities)},
            "counts":dict(sorted(counts.items())),"extensions":dict(sorted(exts.items())),
            "samples":samples,"historical_comparison":dict(comparison),
            "duplicate_examples": [{"name": k.rstrip(b"\0").decode(), "occurrences": len(v),
                                     "distinct_payload_hashes":len(set(x[3] for x in v))}
                                    for k,v in list((k,v) for k,v in sorted(all_entries.items()) if len(v)>1)[:3]],
            "backing_ranges_digest":digest_json(details),
            "historical_script_sha256":sha(historical.read_bytes()),
            "limits":"One base-game ZFS and its extracted resource root; excludes Nitro Pack. No retail execution."}

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root",type=Path,required=True)
    ap.add_argument("--archive",type=Path,required=True)
    ap.add_argument("--historical",type=Path,required=True)
    ap.add_argument("--private-details",type=Path)
    args=ap.parse_args()
    print(json.dumps(inspect(args.root,args.archive,args.historical,args.private_details),sort_keys=True,indent=2))
if __name__ == "__main__":
    main()
