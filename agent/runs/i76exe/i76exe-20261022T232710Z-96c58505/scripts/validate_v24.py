#!/usr/bin/env python3
"""Validate v2.4 instruction trace and independently recorded retail payload identities.
Native execution of the original retail program is performed by the bundled Java
Ghidra probe; this validator checks its archived evidence, not a live Windows game.
"""
import csv,collections,hashlib,json,pathlib,re,sys
root=pathlib.Path(sys.argv[1] if len(sys.argv)>1 else '.').resolve()
rows=list(csv.DictReader((root/'evidence/native_vehicle_resources.tsv').open(),delimiter='\t'))
metadata=json.loads((root/'evidence/retail_resource_digests.json').read_text())
scenario={'gtsi_top_level_vcf':{'body':31,'nodes':46,'binds':912,'tmt':24,'main':('al11bdym.geo','al51bdym.geo'),'extra':'al1_sor.geo'},'bus_top_level_vcf':{'body':29,'nodes':44,'binds':856,'tmt':22,'main':('xb11bdym.geo','xb51bdym.geo'),'extra':'xb1_sor.geo'}}
passed=0

def check(condition,message):
 global passed
 if not condition:raise AssertionError(message)
 passed+=1

def pairs(detail):
 d={}
 for x in detail.split(';'):
  if '=' in x:
   k,v=x.split('=',1);d[k]=v
 return d

check(len(rows)>1000,'missing substantial native trace')
check(set(x['scenario'] for x in rows)==set(scenario),'unexpected scenarios')
for name,expected in scenario.items():
 r=[x for x in rows if x['scenario']==name]
 kinds=collections.defaultdict(list)
 for x in r:kinds[x['kind']].append(pairs(x['detail']))
 check(len(kinds['NATIVE_VCF_COMPLETE'])==1,name+' complete events')
 end=kinds['NATIVE_VCF_COMPLETE'][0]
 for field,value in [('nodes',expected['nodes']),('geoBindings',expected['binds']),('materialBinds',expected['tmt']),('nativeMaterialSuccess',expected['tmt']),('weaponConstructors',4),('parsers',7)]:
  check(int(end[field])==value,name+' '+field)
 check(len(kinds['BODY_SLOT_VERIFIED'])==expected['body'],name+' body part count')
 check({int(v['slot']) for v in kinds['BODY_SLOT_VERIFIED']}==set(range(expected['body'])),name+' body indices')
 for v in kinds['BODY_SLOT_VERIFIED']:
  check(v['basis']=='exact' and v['position']=='exact',name+' body transform '+v['slot'])
 check(len(kinds['MOUNT_VERIFIED'])==4,name+' mount count')
 check({int(v['slot']) for v in kinds['MOUNT_VERIFIED']}=={0,1,4,5},name+' mount layout')
 for v in kinds['MOUNT_VERIFIED']:
  check(v['class']=='30' and v['orientation']=='exact' and v['translation']=='exact',name+' mount '+v['slot'])
 check(len(kinds['NATIVE_TEXTURE_MATERIAL_BIND_RESULT'])==expected['tmt'],name+' native material count')
 check(len(kinds['NATIVE_TEXTURE_MATERIAL_BIND_ENTER'])==expected['tmt'],name+' requested material count')
 check(len(kinds['STUB_texture_material_registration'])==0,name+' no synthetic material bindings')
 for v in kinds['NATIVE_TEXTURE_MATERIAL_BIND_RESULT']:
  check(v['eax']=='1' and v['slot']!='00000000' and v['tmt']!='00000000',name+' TMT binding nonzero')
  check(v['owner']==v['slotOwner'] and v['key']==v['slotKey'],name+' TMT owner/name')
  check(v['tmtName'].lower() in metadata['tmt'],name+' TMT in stock resource set')
  source=metadata['tmt'][v['tmtName'].lower()]
  check(v['firstFrame'].lower().startswith(source['first_frame_basename'].lower()),name+' TMT correct first frame')
 check(len(kinds['NATIVE_GEO_CONSTRUCTOR'])==4,name+' real geometry construction count')
 check(len(kinds['STUB_geometry_materialization'])==0,name+' no fake geometry handles')
 for v in kinds['NATIVE_GEO_CONSTRUCTOR']:
  check(v['magic']=='2E47454F',name+' retail GEO magic')
 check(len(kinds['NATIVE_BODY_MESH_SELECTED'])==3,name+' mesh-switch events')
 selectors=kinds['NATIVE_BODY_MESH_SELECTED']
 check([v['group'] for v in selectors]==['0','4','0'],name+' selector ordering')
 check([v['resource'] for v in selectors]==[expected['main'][0],expected['main'][1],expected['main'][0]],name+' GEO selection names')
 check(selectors[0]['geometryHandle']==selectors[2]['geometryHandle']!=selectors[1]['geometryHandle'],name+' GEO cache handle identity')
 check([v['newConstructors'] for v in selectors]==['1','1','0'],name+' lazy GEO load and reuse')
 for v in selectors:
  check(v['stableClassBasisPositionParent']=='true',name+' transform and hierarchy invariants')
  check(int(v['vertices'])==metadata['geo'][v['resource']]['vertices'],name+' GEO vertex count')
 check(len(kinds['NATIVE_GEO_LOAD_RETURN'])==5,name+' GEO cache calls')
 check(any(v['key'].lower()==expected['extra'] for v in kinds['NATIVE_GEO_LOAD_RETURN']),name+' native auxiliary geometry')
 check(any(v['key'].lower()=='hdlt_msk.geo' for v in kinds['NATIVE_GEO_LOAD_RETURN']),name+' native headlight mask')
 outer=[v for v in kinds['RETURN'] if v['eax']=='1' and 'geoBindings' not in v]
 check(len(outer)>=1,name+' top-level return success')
check(set(metadata['tmt'])=={pairs(x['detail'])['tmtName'].lower() for x in rows if x['kind']=='NATIVE_TEXTURE_MATERIAL_BIND_RESULT'},'complete 46 material payload identities')
check(len(metadata['tmt'])==46,'46 TMT entries')
check(len(metadata['geo'])==7,'7 GEO identities (common plus 3 per vehicle)')
check(metadata['executable']['md5']=='a640ea0097dbb62e0c77b7f2847c7161','retail executable ID')
check(len(metadata['ghidra']['sha256'])==64,'baseline digest')
if (root/'SHA256SUMS').exists():
 for line in (root/'SHA256SUMS').read_text().splitlines():
  digest,rel=line.split('  ',1)
  check(hashlib.sha256((root/rel).read_bytes()).hexdigest()==digest,'package SHA: '+rel)
print('PASS',passed,'independent evidence/manifest assertions')
