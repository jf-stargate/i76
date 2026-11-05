"""Use accepted outer resource readers; authenticate bytes in memory only."""
import sys,json,hashlib,struct,importlib.util
from pathlib import Path
from decoder import decode
EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
ZFS='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'
def sha(b):return hashlib.sha256(b).hexdigest()
def load(n,p):
    s=importlib.util.spec_from_file_location(n,p);m=importlib.util.module_from_spec(s);sys.modules[n]=m;s.loader.exec_module(m);return m
class Corpus:
    def __init__(self,repo,root):
        self.repo,self.root=repo,root
        z=load('accepted_zfs',repo/'agent/runs/i76exe/i76exe-20261104T224258Z-8e34c41d/scripts/zfs_reader.py')
        self.arc=z.Archive.open(root/'orig/I76.ZFS');assert sha((root/'orig/I76.ZFS').read_bytes())==ZFS
        p=load('accepted_pix',repo/'agent/runs/i76exe/i76exe-20261104T195642Z-eaccd134/scripts/pix_reader.py')
        self.members={};self.cache={}
        for ent in self.arc.entries:
            if ent.active and ent.name.lower().endswith('.pix'):
                ix=p.parse_index(self.arc.read_entry(ent));pn=ent.name.lower()[:-4]+'.pak'
                for e in ix.entries:self.members.setdefault(e.name.lower(),[]).append((pn,e.offset,e.size,ent.name.lower(),e.ordinal))
    def top(self,n):
        if n not in self.cache:self.cache[n]=self.arc.read(n)
        return self.cache[n]
    def get(self,n):
        n=n.lower()
        if n in self.members:
            choices=self.members[n];bs=[self.top(p)[o:o+s] for p,o,s,_,_ in choices]
            assert len({sha(b) for b in bs})==1
            return bs[0]
        return self.top(n)
    def identity(self,n):
        b=self.get(n);sources=[]
        for p,o,s,ix,ordinal in self.members.get(n,[]):
            ent=self.arc.lookup(p);sources.append(dict(pak=p,pak_sha256=sha(self.top(p)),offset=o,length=s,pix=ix,pix_sha256=sha(self.top(ix)),pix_row=ordinal,zfs_directory_offset=ent.directory_offset,zfs_stored_offset=ent.offset,zfs_stored_size=ent.stored_size,zfs_flags=ent.flags))
        if not sources:
            e=self.arc.lookup(n);sources=[dict(zfs_directory_offset=e.directory_offset,zfs_stored_offset=e.offset,zfs_stored_size=e.stored_size,zfs_flags=e.flags)]
        return dict(name=n,sha256=sha(b),length=len(b),sources=sources)
    def survey(self):
        rows=[];dims={};flags={};solid=0;tile=0;counts={};trailing=0
        for n in sorted(self.members):
            if not n.endswith('.vqm'):continue
            b=self.get(n);w,h=struct.unpack_from('<II',b);dep=b[8:24].split(b'\0')[0].decode().lower();cb=self.get(dep);out=decode(b,cb)
            ts=struct.unpack('<'+'H'*((len(b)-24)//2),b[24:]);solid+=sum(bool(t&32768) for t in ts);tile+=sum(not t&32768 for t in ts)
            dims[str((w,h))]=dims.get(str((w,h)),0)+1;flags[str(h>>29)]=flags.get(str(h>>29),0)+1
            rows.append([n,sha(b),dep,sha(cb),sha(out)])
        return dict(unique_vqm=len(rows),dimensions=dims,height_flags=flags,solid_tokens=solid,codebook_tokens=tile,comparison_rows_sha256=sha(json.dumps(rows,separators=(',',':')).encode()),note='Independent decoder corpus; original instruction comparisons reported separately')
