#!/usr/bin/env python3
"""Post-freeze diagnostics. Never overwrites the blind model or its artifacts."""
import argparse,copy,hashlib,json,pathlib,sys
from analyze import calculate,dump
run=pathlib.Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--out-dir',type=pathlib.Path,required=True);p.add_argument('captures',nargs='*');args=p.parse_args();out=args.out_dir;out.mkdir(parents=True,exist_ok=True)
d=json.loads((run/'artifacts/features.json').read_text())
# No earlier-pilot data is consumed: these are extraction-only ablations.
clean=copy.deepcopy(d)
for o in clean['objects'].values():
 if o['category']=='literal' and o['type']=='pointer':o['category']='readonly_pointer'
for f in clean['functions']:f['literal']=[x for x in f['literal'] if clean['objects'][x]['category']=='literal']
callback=copy.deepcopy(d)
for target in callback['functions']:
 for r in target['address_taken']:
  if r['type']=='DATA' and r.get('function'):
   for source in callback['functions']:
    if source['entry']==r['function']:source['jumps'].append(target['entry'])
combined=copy.deepcopy(clean)
for i,f in enumerate(combined['functions']):f['jumps']=callback['functions'][i]['jumps']
variants={'exclude_readonly_pointers':clean,'include_address_taken_edges':callback,'both':combined}
result={k:[dict(rank=i+1,right=r['right'],score=r['score']) for i,r in enumerate(calculate(v))] for k,v in variants.items()}
dump(out/'postfreeze_ablations.json',result)
dump(out/'data_taxonomy.json',{k:dict(**o,distinction='import address slot, not pooled text' if o['category']=='readonly_pointer' else 'defined text; possible pooling' if 'string' in o['type'].lower() else 'observed write, not proof of file-static linkage' if o['category']=='mutable' else 'unresolved storage or non-text constant') for k,o in clean['objects'].items()})
# Reopening a saved import can increment framework bookkeeping; compare content,
# and independently require zero modification delta in each session.
if len(args.captures)==2:
 a,b=[json.loads(pathlib.Path(p).read_text()) for p in args.captures]
 mods=[]
 for x in [a,b]:
  assert x['modification_before']==x['modification_after'];mods.append([x.pop('modification_before'),x.pop('modification_after')])
 assert a==b
 dump(out/'replay_validation.json',dict(content_equal=True,session_modifications=mods,capture_sha256=[hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest() for p in args.captures],note='Import/save changed framework modification number from 2 to 3 between sessions. Within each extraction delta is zero; all exported instructions, ranges, references and objects are identical. Read-only replay was not saved.'))
print('Post-freeze diagnostics written to',out)
