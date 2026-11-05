"""Compare the authenticated installed ZIX specimen; not a general ZIX parser."""
from collections import Counter
import hashlib
from pathlib import Path
from zfs_reader import Archive, normalize

def check(path,archive):
 raw=path.read_bytes();lines=raw.decode('ascii').splitlines()
 assert lines[2].startswith('-') and lines[4].startswith('-')
 assert lines[3]=='DIR: i76.zfs'
 records=[line.split() for line in lines[5:] if line.strip()]
 assert all(len(row)==2 for row in records)
 keys=[normalize(row[1]) for row in records]
 sources=Counter(row[0] for row in records)
 reader=Archive.open(archive)
 assert int(lines[0])==len(records)==len(reader.entries)
 assert Counter(keys)==Counter(e.key for e in reader.entries if e.active)
 return {'zix_sha256':hashlib.sha256(raw).hexdigest(),'zix_bytes':len(raw),'declared_records':int(lines[0]),
         'records':len(records),'archive_key_multiset_equal':True,'source_ordinals':dict(sources),
         'configured_path':'i76.zfs','configured_path_mode':'DIR:','scope':'supplied installed specimen only; not runtime enumeration or media callback execution'}
