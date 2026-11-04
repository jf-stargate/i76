"""Independent seek/read checks plus bounded top-level CBK authentication."""
import argparse
import hashlib
import json
from pathlib import Path
from inspect_corpus import load_module
from pix_reader import Reader

def sha(data):return hashlib.sha256(data).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root",type=Path,required=True)
    ap.add_argument("--archive",type=Path,required=True)
    ap.add_argument("--historical",type=Path,required=True)
    ap.add_argument("--corpus",type=Path,required=True)
    args=ap.parse_args()
    corpus=json.loads(args.corpus.read_text())
    verified=[]
    full_count=0
    full_digest=hashlib.sha256()
    for pix in sorted(args.root.glob("*.pix")):
        reader=Reader(pix)
        pak=next(p for p in args.root.iterdir() if p.name.lower()==pix.stem.lower()+".pak")
        with pak.open("rb") as stream:
            for e in reader.index.entries:
                view=reader.acquire(e.name,ordinal=e.ordinal)
                stream.seek(e.offset); bounded=stream.read(e.size)
                assert len(view)==len(bounded)==e.size and bytes(view)==bounded
                full_digest.update(json.dumps([pix.name,e.ordinal,e.name,e.offset,e.size,sha(view)],separators=(",", ":")).encode()+b"\n")
                full_count+=1
        reader.close()
    for tag,s in sorted(corpus["samples"].items()):
        reader=Reader(args.root/s["pix"])
        payload=reader.acquire(s["name"],ordinal=s["ordinal"])
        with (args.root/s["pak"]).open("rb") as stream:
            stream.seek(s["offset"]);independent=stream.read(s["size"])
        assert len(payload)==len(independent)==s["size"]
        assert bytes(payload)==independent
        assert sha(payload)==s["payload_sha256"]
        verified.append({"sample":tag,"payload_sha256":sha(payload),"bytes":len(payload)})
    old=load_module(args.historical)
    _,records=old.parse_zfs_records(args.archive)
    cbks=[r for r in records if r.active and r.extension=="cbk"]
    r=sorted(cbks,key=lambda r:r.name.lower())[0]
    with args.archive.open("rb") as stream:
        stream.seek(r.file_offset);packed=stream.read(r.stored_size)
    payload=old.Lzo().decompress(packed,r.logical_size,r.compression)
    extracted=next(p for p in args.root.iterdir() if p.name.lower()==r.name.lower()).read_bytes()
    assert extracted==payload
    vehicle_path=args.historical.with_name("i76_vehicle_texture_slot_resolver_v5.py")
    vehicle=load_module(vehicle_path)
    wanted={s[k].lower() for s in corpus["samples"].values() for k in ("pix","pak")}
    selected=[r for r in records if r.name.lower() in wanted]
    filemap={p.name.lower():p for p in args.root.iterdir() if p.is_file()}
    index,warnings=vehicle.build_asset_index(selected,{r.index:filemap[r.name.lower()].read_bytes() for r in selected},None)
    assert not warnings
    vehicle_checks=0
    for s in corpus["samples"].values():
        asset=index.resolve(s["name"])
        assert asset is not None
        assert asset.pak_name.lower()==s["pak"].lower() and asset.pix_name.lower()==s["pix"].lower()
        assert asset.size==s["size"] and asset.sha256==s["payload_sha256"]
        rows,error=vehicle.parse_pix_index(filemap[s["pix"].lower()].read_bytes())
        assert not error and rows[s["ordinal"]]==(s["name"],s["offset"],s["size"])
        vehicle_checks+=1
    # This decimal spelling is accepted by original %d, but int(token,0) rejects it.
    _,_,err=old.parse_pix_index(b"1\nA.GEO 0010 2\n")
    assert err
    print(json.dumps({"vehicle_resolver_samples":vehicle_checks,"vehicle_resolver_sha256":sha(vehicle_path.read_bytes()),"full_reader_entries":full_count,"full_reader_digest":full_digest.hexdigest(),"seek_and_reader_samples":verified,"cbk_top_level_count":len(cbks),
                      "cbk_example":{"name":r.name,"zfs_stored_offset":r.file_offset,
                                     "zfs_stored_size":r.stored_size,"zfs_compression_flag":r.compression,
                                     "payload_bytes":len(payload),"payload_sha256":sha(payload)},
                      "historical_decimal_mismatch":"int(token,0) rejects 0010; original %d reads decimal 10",
                      "indexed_cbk_count":corpus["extensions"].get(".cbk",0)},sort_keys=True,indent=2))
if __name__=="__main__":main()
