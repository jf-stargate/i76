"""Metadata-only survey. Original names and payloads stay in --private output.
Uses pinned accepted WRLD/ZFS readers; authenticates extracted HZD against ZFS.
"""
import argparse, collections, hashlib, importlib.util, json, struct, sys
from pathlib import Path
sys.dont_write_bytecode = True
from hzd import parse

def sha(b): return hashlib.sha256(b).hexdigest()
def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    m=importlib.util.module_from_spec(spec);sys.modules[name]=m;spec.loader.exec_module(m);return m

def survey(root, repo, private):
    z=load('accepted_zfs',repo/'scripts/game/i76_zfs_extract.py')
    w=load('accepted_wrld',repo/'agent/runs/i76exe/i76exe-20261104T183156Z-085a5e76/scripts/wrld.py')
    archive=root/'orig/I76.ZFS'; blob=archive.read_bytes()
    header=z.parse_header(blob); records,_=z.parse_records(blob,header)
    assert header.xor_key==0
    live={rec.name.lower():rec for rec in records if not rec.inactive}
    dec=z.LzoDecompressor(); cache={}
    def payload(n):
        n=n.lower()
        if n not in cache:
            rec=live[n]; b=blob[rec.file_offset:rec.file_offset+rec.stored_size]
            assert len(b)==rec.stored_size
            b=dec.decompress(rec.mode,b,rec.logical_size) if rec.mode&6 else b
            assert len(b)==(rec.logical_size if rec.mode&6 else rec.stored_size), (n,rec.mode,rec.logical_size,len(b))
            cache[n]=b
        return cache[n]
    inventory=collections.defaultdict(list)
    for n in live: inventory[n].append(('zfs',n,None,None))
    pix_count=0
    for n in live:
        if not n.endswith('.pix'):continue
        lines=payload(n).decode('ascii').splitlines()
        if not lines:continue
        count=int(lines[0]); rows=[line.split() for line in lines[1:] if line.strip()]
        assert len(rows)==count
        pak=n[:-4]+'.pak'; assert pak in live
        for name,off,size in rows:
            inventory[name.lower()].append(('pix',pak,int(off,0),int(size,0)))
        pix_count+=1
    for directory in ['orig/miss8','orig/miss16','orig/ADDON','orig']:
        for p in sorted((root/directory).iterdir()):
            if p.is_file():inventory[p.name.lower()].append(('loose',str(p.relative_to(root)),None,None))
    def resolve(n):
        out=[]
        for kind,source,off,size in inventory.get(n.lower(),[]):
            if kind=='zfs':b=payload(source);loc={'kind':kind,'record_index':live[source].index}
            elif kind=='pix':
                p=payload(source);assert off>=0 and size>=0 and off+size<=len(p)
                b=p[off:off+size];loc={'kind':kind,'pak_record_index':live[source].index,'offset':off}
            else:b=(root/source).read_bytes();loc={'kind':kind,'source':source}
            out.append(dict(loc,length=len(b),sha256=sha(b),_bytes=b))
        return out
    missions=[]; use=collections.defaultdict(list)
    for mode in ['miss8','miss16']:
        for p in sorted((root/'orig'/mode).glob('*.MSN')):
            data=p.read_bytes(); rows=w.inspect(data);assert len(rows)==1
            h=rows[0][3].names['horizon_manifest']
            item={'path':str(p),'sha256':sha(data),'length':len(data),'hzd':h}
            missions.append(item)
            if h:use[h.lower()].append(f'{mode}/{p.name}')
    # Inspect all available HZD records, including resources not selected by missions.
    specimens=[]; private_rows=[]; allnames=set(); depcounts=collections.Counter(); unique_deps={}
    hzdnames=sorted(set(n for n in live if n.endswith('.hzd')) | set(use))
    for n in hzdnames:
        b=payload(n); p=root/'zfs/resources'/n
        assert p.read_bytes()==b, f'extraction mismatch {n}'
        m=parse(b); names=[s.lower() for s in m.names];allnames.update(names)
        depstats=collections.Counter();deps=[]
        for name in sorted(set(names)):
            candidates={}
            for ext in ['.map','.vqm','.m16']:
                key=name.rsplit('.',1)[0]+ext
                rows=resolve(key)
                candidates[ext]=[{k:v for k,v in row.items() if k!='_bytes'} for row in rows]
                if rows:depstats[ext]+=1
                if ext=='.vqm':
                    for row in rows:
                        vb=row['_bytes']; assert len(vb)>=24
                        cbk=vb[8:24].split(b'\0',1)[0].decode('ascii')
                        hits=resolve(cbk);assert hits, 'unresolved CBK'
                        depstats['vqm_cbk_edges']+=1
                        candidates.setdefault('cbk',[]).extend([{k:v for k,v in hit.items() if k!='_bytes'} for hit in hits])
            assert candidates['.map'] or candidates['.vqm'], 'unresolved primary candidate'
            dep={'name':name,'id':sha(name.encode()),'candidates':candidates};deps.append(dep);unique_deps[name]=dep
        rec=live[n]
        row={'logical_name':n,'path':str(p),'sha256':sha(b),'length':len(b),
             'zfs_record_index':rec.index,'zfs_file_offset':rec.file_offset,'stored_size':rec.stored_size,'mode':rec.mode,
             'archive_payload_matches_extracted':True,'records':len(names),'unique_references':len(set(names)),
             'duplicate_slots':len(names)-len(set(names)),'empty_records':names.count(''),
             'record_lengths':dict(collections.Counter(map(len,names))),
             'offsets':m.offsets,'first_half_equals_second':names[:8]==names[8:],
             'slot_equality_classes':[names.index(s) for s in names],
             'missions':use.get(n,[]),'dependency_counts':dict(depstats)}
        specimens.append(row);private_rows.append(dict(row,names=m.names,dependencies=deps))
        depcounts.update(depstats)
    pairs=[]
    bypath={Path(m['path']).parent.name+'/'+Path(m['path']).name:m for m in missions}
    byname={r['logical_name']:r for r in specimens}
    for a in missions:
        if '/miss8/' not in a['path']:continue
        b=bypath['miss16/'+Path(a['path']).name]; na=a['hzd'].lower();nb=b['hzd'].lower()
        pairs.append({'mission':Path(a['path']).name,'miss8':na,'miss16':nb,
                      'same_name':na==nb,'same_payload':byname[na]['sha256']==byname[nb]['sha256'] if na and nb else na==nb})
    summary={'mission_count':len(missions),'nonempty_hzd_fields':sum(bool(m['hzd']) for m in missions),
             'referenced_logical_names':len(use),'hzd_files':len(specimens),'distinct_payloads':len(set(r['sha256'] for r in specimens)),
             'distinct_referenced_payloads':len(set(r['sha256'] for r in specimens if r['missions'])),
             'global_candidate_counts':dict(collections.Counter(ext for d in unique_deps.values() for ext,hits in d['candidates'].items() if hits)),
             'global_routes':dict(collections.Counter(ext+':'+hit['kind'] for d in unique_deps.values() for ext,hits in d['candidates'].items() for hit in hits)),
             'unique_texture_names':len(allnames),'pix_indexes_examined':pix_count,
             'pair_count':len(pairs),'pairs_same_name':sum(p['same_name'] for p in pairs),'pairs_same_payload':sum(p['same_payload'] for p in pairs),
             'lengths':dict(collections.Counter(r['length'] for r in specimens)),
             'record_counts':dict(collections.Counter(r['records'] for r in specimens)),
             'unique_reference_counts':dict(collections.Counter(r['unique_references'] for r in specimens)),
             'dependency_counts_over_specimen_unique_references':dict(depcounts)}
    sources=[]
    for n in ['scripts/game/i76_zfs_extract.py','agent/runs/i76exe/i76exe-20261104T183156Z-085a5e76/scripts/wrld.py']:
        sources.append({'path':n,'sha256':sha((repo/n).read_bytes())})
    public={'summary':summary,'archive':{'path':str(archive),'length':len(blob),'sha256':sha(blob)},
            'accepted_readers':sources,'specimens':specimens,'missions':missions,'mode_pairs':pairs}
    private.mkdir(parents=True,exist_ok=True)
    (private/'corpus_private.json').write_text(json.dumps(private_rows,indent=2)+'\n')
    public['anonymized_dependencies']=[{'name_sha256':d['id'],'candidates':d['candidates']} for _,d in sorted(unique_deps.items())]
    return public

if __name__=='__main__':
    p=argparse.ArgumentParser()
    for k in ['root','repo','private','output']:p.add_argument('--'+k,type=Path,required=True)
    a=p.parse_args();data=survey(a.root,a.repo,a.private)
    deps=data.pop('anonymized_dependencies')
    a.output.with_name('dependency_inventory.json').write_text(json.dumps(deps,sort_keys=True,indent=2)+'\n')
    a.output.write_text(json.dumps(data,sort_keys=True,indent=2)+'\n');print(json.dumps(data['summary'],indent=2))
