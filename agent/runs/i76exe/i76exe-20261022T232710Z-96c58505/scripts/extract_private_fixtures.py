#!/usr/bin/env python3
"""Focused independent ZFSF VCF dependency census and replay-input extraction.

Original retail game resources are NOT distributed with the research checkpoint.
Needs an authorized retail I76.ZFS, liblzo2, and a separate scratch --out.
"""
import argparse, ctypes, ctypes.util, hashlib, json, pathlib, struct, collections

def read_records(buf):
    magic, version, name_bytes, per_table, total, xor_key, cursor = struct.unpack_from('<4sIIIIII',buf,0)
    assert (magic,version,name_bytes,per_table,xor_key) == (b'ZFSF',1,16,100,0)
    records=[]
    while cursor:
        next_cursor,=struct.unpack_from('<I',buf,cursor)
        for i in range(per_table):
            raw, off, ident, stored, mtime, flags=struct.unpack_from('<16sIIIII',buf,cursor+4+i*36)
            name=raw.partition(b'\0')[0].decode('latin1')
            if name: records.append(dict(name=name,off=off,stored=stored,mode=flags&255,logical=flags>>8))
        cursor=next_cursor
    assert len(records)==total
    return records

class Reader:
    def __init__(self,buf):
        self.buf=buf
        self.lib=ctypes.CDLL(ctypes.util.find_library('lzo2'))
        for name in ['lzo1x_decompress_safe','lzo1y_decompress_safe']:
            fn=getattr(self.lib,name);fn.argtypes=[ctypes.c_void_p,ctypes.c_size_t,ctypes.c_void_p,ctypes.POINTER(ctypes.c_size_t),ctypes.c_void_p];fn.restype=ctypes.c_int
    def extract(self,r):
        payload=self.buf[r['off']:r['off']+r['stored']]
        if r['mode']==0:
            assert len(payload)==r['logical'];return payload
        if r['mode'] not in (2,4):raise ValueError(r)
        out=ctypes.create_string_buffer(r['logical']);length=ctypes.c_size_t(r['logical']);src=ctypes.create_string_buffer(payload)
        fn=getattr(self.lib,'lzo1x_decompress_safe' if r['mode']==2 else 'lzo1y_decompress_safe')
        rc=fn(src,len(payload),out,ctypes.byref(length),None)
        if rc!=0 or length.value!=r['logical']:raise ValueError((r,rc,length.value))
        return out.raw[:length.value]

def chunks(content):
    items=[];p=0
    while p+8<=len(content):
        tag,size=struct.unpack_from('<4sI',content,p)
        items.append({'tag':tag.decode('latin1'),'offset':p,'size':size})
        if size<8 or p+size>len(content):break
        p+=size
    return items,p==len(content)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--zfs',type=pathlib.Path,required=True)
    ap.add_argument('--out',type=pathlib.Path,required=True)
    ap.add_argument('--metadata',type=pathlib.Path,required=True,
                    help='Bundled evidence/retail_resource_digests.json')
    args=ap.parse_args();args.out.mkdir(parents=True,exist_ok=True)
    z=args.zfs.read_bytes();r=Reader(z);table={v['name'].lower():v for v in read_records(z)}
    expected=json.loads(args.metadata.read_text())
    assert hashlib.sha256(z).hexdigest()==expected['archive_sha256']
    target=['noal01.vcf','nobus1.vcf','s03vas01.vcf','valeprec.vdf',
            'vxbus.vdf','leprecn4.vtf','bus1.vtf','wauto_1a.wdf',
            'wbtck_1a.wdf','wftck_1a.wdf','compnent.cdf']
    for name in target:
        raw=r.extract(table[name]);(args.out/name).write_bytes(raw)
    pix_map={
        'valeprig': ['al1_sor.geo','al11bdym.geo','al51bdym.geo'],
        'vxbusg': ['xb1_sor.geo','xb11bdym.geo','xb51bdym.geo'],
        'leprcn4t':[n for n,v in expected['tmt'].items() if v['pix']=='leprcn4t.pix'],
        'bus1t':[n for n,v in expected['tmt'].items() if v['pix']=='bus1t.pix'],
    }
    count=0
    for family,names in pix_map.items():
        pix=r.extract(table[family+'.pix']).decode('latin1')
        pak=r.extract(table[family+'.pak'])
        entries={}
        for line in pix.splitlines()[1:]:
            name,off,size=line.split();entries[name.lower()]=(int(off),int(size))
        for name in names:
            off,size=entries[name.lower()]
            raw=pak[off:off+size]
            assert len(raw)==size
            known=expected['tmt'].get(name.lower(),expected['geo'].get(name.lower()))
            assert known is not None and hashlib.sha256(raw).hexdigest()==known['sha256']
            (args.out/name).write_bytes(raw);count+=1
    name='hdlt_msk.geo';raw=r.extract(table[name]);assert hashlib.sha256(raw).hexdigest()==expected['geo'][name]['sha256']
    (args.out/name).write_bytes(raw)
    print('Verified',len(target),'top-level retail inputs +',count+1,'GEO/TMT resources; private bytes stay in',args.out)
if __name__=='__main__':main()
