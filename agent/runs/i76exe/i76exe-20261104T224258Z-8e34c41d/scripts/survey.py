"""Read-only full corpus comparison. Full inventory output must remain private."""
import argparse
from collections import Counter
from dataclasses import asdict
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
from zfs_reader import Archive, SafeLzo, DecodeError

def sha(b): return hashlib.sha256(b).hexdigest()
def canonical(x): return json.dumps(x, sort_keys=True, separators=(',', ':')).encode()
def module(path):
    spec=importlib.util.spec_from_file_location('historical_zfs_comparator', path)
    mod=importlib.util.module_from_spec(spec);sys.modules[spec.name]=mod;spec.loader.exec_module(mod)
    return mod

def survey(archive, extracted, historical, private):
    raw=archive.read_bytes(); reader=Archive(raw); old=module(historical)
    old_header=old.parse_header(raw);old_rows,old_tables=old.parse_records(raw,old_header)
    old_lzo=old.LzoDecompressor(required=True)
    backend=SafeLzo(); rows=[]; errors=[]; ext={}; disagreements=Counter(); wrong=Counter()
    if len(old_rows)!=len(reader.entries): disagreements['count']+=1
    if [(t['offset'],t['next_offset']) for t in old_tables]!=list(reader.tables): disagreements['tables']+=1
    for entry in reader.entries:
        family=Path(entry.key).suffix
        bucket=ext.setdefault(family,Counter())
        bucket['records']+=1;bucket['mode_'+str(entry.mode)]+=1
        row=asdict(entry);row['raw_name']=entry.raw_name.hex();row['active']=entry.active
        row['mode']=entry.mode;row['expected_size']=entry.expected_size
        row['stored_sha256']=sha(raw[entry.offset:entry.offset+entry.stored_size])
        prior=old_rows[entry.ordinal]
        if (prior.name,prior.file_offset,prior.record_id,prior.stored_size,prior.unix_timestamp,prior.flags_size,prior.inactive)!=(entry.name,entry.offset,entry.identifier,entry.stored_size,entry.time_word,entry.flags_size,not entry.active): disagreements['metadata']+=1
        if not entry.active:
            row['result']='inactive';rows.append(row);continue
        try:
            decoded=reader.read(entry.key);digest=sha(decoded)
            assert reader.lookup(entry.name.upper()) is entry
            row.update(result='decoded',logical_sha256=digest,decoded_size=len(decoded))
            bucket['decoded']+=1;bucket['decoded_bytes']+=len(decoded);bucket['stored_bytes']+=entry.stored_size
            path=extracted/entry.key
            if not path.is_file():disagreements['extracted_missing']+=1
            elif sha(path.read_bytes())!=digest:disagreements['extracted_hash']+=1
            else:bucket['extracted_equal']+=1
            old_payload,_=old.decode_payload(raw,prior,old_lzo)
            if old_payload!=decoded:disagreements['historical_decoded']+=1
            else:bucket['historical_equal']+=1
            if entry.mode:
                try:
                    other=backend.decode(4 if entry.mode==2 else 2,raw[entry.offset:entry.offset+entry.stored_size],entry.expected_size)
                    wrong[f'{entry.mode}:same' if other==decoded else f'{entry.mode}:different']+=1
                except DecodeError:wrong[f'{entry.mode}:rejected']+=1
        except Exception as exc:
            errors.append({'ordinal':entry.ordinal,'error':str(exc)});row['result']='error';bucket['errors']+=1
        rows.append(row)
    private.write_bytes(canonical(rows)+b'\n')
    # Commit only compact aggregates. Complete names/offsets/hashes stay private.
    out={'archive_sha256':sha(raw),'archive_bytes':len(raw),'header':asdict_header(reader,old_header),
         'entries':len(rows),'active':sum(e.active for e in reader.entries),'inactive':sum(not e.active for e in reader.entries),
         'tables':len(reader.tables),'empty_slots':len(reader.tables)*100-len(rows),
         'decoded':sum(r['result']=='decoded' for r in rows),'errors':errors,
         'flags':dict(sorted(Counter(str(e.flags) for e in reader.entries).items())),
         'duplicate_normalized_keys':len(reader.duplicate_keys),'exact_storage_alias_pairs':len(reader.aliases),
         'partial_overlaps':0,'by_extension':{k:dict(sorted(v.items())) for k,v in sorted(ext.items())},
         'disagreements':dict(sorted(disagreements.items())), 'wrong_mode_crosscheck':dict(sorted(wrong.items())),
         'inventory_digest':sha(canonical(rows)), 'inventory_encoding':'directory order, canonical JSON list: sort_keys=True,separators=(comma,colon); raw_name hex; no final newline in digest',
         'historical_script_sha256':sha(historical.read_bytes()),'historical_rows':len(old_rows),
         'extracted_file_count':sum(p.is_file() for p in extracted.iterdir()),
         'backend_version':backend.version,
         'raw_size_upper_bits_nonzero':sum(bool(e.flags_size>>8) for e in reader.entries if e.mode==0),
         'identifier_equals_ordinal':sum(e.identifier==e.ordinal for e in reader.entries),
         'identifiers_unique':len({e.identifier for e in reader.entries}),
         'raw_name_postnul_nonzero':sum(any(e.raw_name.split(b'\0',1)[1]) for e in reader.entries),
         'time_word_range':[min(e.time_word for e in reader.entries),max(e.time_word for e in reader.entries)]}
    return out

def asdict_header(reader,h): return h.to_dict()
if __name__=='__main__':
    ap=argparse.ArgumentParser(description=__doc__)
    for name in ('archive','extracted','historical','private','summary'):ap.add_argument('--'+name,type=Path,required=True)
    a=ap.parse_args()
    run=Path(__file__).resolve().parents[1]
    for p in (a.private,a.summary):
        if p.resolve().is_relative_to(run.parents[3]):raise ValueError('survey outputs must be outside public checkout')
    report=survey(a.archive,a.extracted,a.historical,a.private)
    a.summary.write_text(json.dumps(report,indent=2,sort_keys=True)+'\n')
    print(json.dumps({k:report[k] for k in ('entries','decoded','disagreements','inventory_digest')}))
    if report['errors'] or report['disagreements']:sys.exit(1)
