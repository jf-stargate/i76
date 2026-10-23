#!/usr/bin/env python3
"""Private-input verifier for original x86 vehicle→GEO→TMT→raster-boundary research.
Never uploads or rewrites user-proprietary resources or Ghidra databases.
"""
import argparse,csv,hashlib,json,struct
from pathlib import Path
MD5='a640ea0097dbb62e0c77b7f2847c7161'
SHA='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
ZFS='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'
BASE_V24='9ea1c890ec8523464eccc572a018fb8a00a27447de053b4eeb49673a466826ce'
INTEGRATED='cbaa3cc5b59ddd3f183d530478875776be455a2d518f2e3a5c84338239e6e911'
def rows(p):
 with p.open(newline='') as f:return list(csv.DictReader(f,delimiter='\t'))
def pe_offset(b,va):
 hdr=struct.unpack_from('<I',b,0x3c)[0]
 assert b[hdr:hdr+4]==b'PE\0\0'
 num=struct.unpack_from('<H',b,hdr+6)[0]; opt=struct.unpack_from('<H',b,hdr+20)[0]
 base=struct.unpack_from('<I',b,hdr+24+28)[0];rva=va-base
 for i in range(num):
  ent=hdr+24+opt+40*i;vs,rv,rs,raw=struct.unpack_from('<IIII',b,ent+8)
  if rv<=rva<rv+max(vs,rs):return raw+rva-rv
 raise ValueError(f'unmapped {va:08x}')
def verify(run,pe,zfs,v24,trace_a,trace_b):
 count=0
 def ck(pred,message):
  nonlocal count
  assert pred,message
  count+=1
 b=pe.read_bytes()
 ck(hashlib.md5(b).hexdigest()==MD5,'retail MD5')
 ck(hashlib.sha256(b).hexdigest()==SHA,'retail PE SHA256')
 ck(hashlib.sha256(zfs.read_bytes()).hexdigest()==ZFS,'source ZFS')
 ck(hashlib.sha256(v24.read_bytes()).hexdigest()==BASE_V24,'v2.4 original x86 replay regression')
 ck(hashlib.sha256(trace_a.read_bytes()).hexdigest()==INTEGRATED,'first integrated Ghidra execution trace')
 ck(hashlib.sha256(trace_b.read_bytes()).hexdigest()==INTEGRATED,'second independent integrated replay')
 anchor=rows(run/'evidence/native_x86_anchors.tsv')
 ck(len(anchor)==13,'opcode anchor count')
 for a in anchor:
  va=int(a['va'],16);wire=bytes.fromhex(a['original_x86_bytes']);off=pe_offset(b,va)
  ck(b[off:off+len(wire)]==wire,'opcode at '+a['va'])
 summary=rows(run/'evidence/geo_render_summary.tsv')
 ck(len(summary)==4,'four real GEO variants')
 expected=[('gtsi','al11bdym.geo',24,17,1320,1),('gtsi','al51bdym.geo',81,69,8136,3),('bus','xb11bdym.geo',16,5,456,1),('bus','xb51bdym.geo',169,93,15240,0)]
 for line,exp in zip(summary,expected):
  ck((line['vehicle'],line['geo'],int(line['vertices']),int(line['sections']),int(line['scratch_bytes']),int(line['textured_records']))==exp,'four variant details')
  ck(int(line['render_records'])==int(line['sections']),'one original temp slot per source section')
  ck(int(line['native_submit_calls'])==int(line['clip_stub_calls'])==int(line['draw_stub_calls'])==int(line['textured_records']),'native submit to clip and draw')
 materials=rows(run/'evidence/material_owner_bridge.tsv')
 ck(len(materials)==5,'five original material resolutions')
 direct=[m for m in materials if m['material_name']=='V1 MD UN.MAP']
 ck(len(direct)==2,'paired exterior TMT materials')
 ck(sorted(x['initial_tmt_frame'].lower() for x in direct)==['al11mdu1.map','xb11mdu1.map'],'retail initial TMT frames')
 ck(all(x['tmt_record']!='00000000' for x in direct),'genuine native TMT records')
 ck(len([m for m in materials if m['material_name']=='V1 BO DY.MAP'])==3,'GTSi cockpit fallback')
 dispatch=rows(run/'evidence/raster_dispatch_boundaries.tsv')
 ck(len(dispatch)==5,'five original raster wrappers')
 for row in dispatch:
  ck((row['clip_index'],row['original_clip_target'],row['original_draw_target'])==('21','0047C2F0','00487EA0'),'true original raster table branches')
  ck(row['return_eax']=='00000800','returned original FPU control flag, not a raster success assertion')
  ck(row['intercepted_clip_calls']==row['intercepted_draw_calls'],'intercept paired calls')
 meta=json.loads((run/'evidence/experiment_summary.json').read_text())
 ck(meta['records']==184 and meta['original_submit_wrappers']==5 and meta['refresh_invocations']==10 and meta['vqm_load_intercepts']==3,'summarized native event counts')
 ck(meta['sha256_repeated_full_trace']==INTEGRATED,'private trace provenance')
 return {'status':'passed','passed_count':count,'test_count':count,'source_executable_md5':MD5,'source_executable_sha256':SHA,'archive_sha256':ZFS,'original_code_passes':4,'render_records':184,'native_polygon_submit_wrappers':5,'intercepted_clip_and_draw_pairs':5,'limitations':'Original VCF/GEO/TMT/render record/texture-binding/submit wrapper instructions, but services for VQM pixels, raster clipping/drawing, OS heap, CRT, and camera/lighting setup are emulated. Ghidra x87 warnings. No full display output.'}
if __name__=='__main__':
 p=argparse.ArgumentParser()
 p.add_argument('run',type=Path);p.add_argument('--pe',type=Path,required=True);p.add_argument('--zfs',type=Path,required=True);p.add_argument('--v24',type=Path,required=True);p.add_argument('--trace',type=Path,required=True);p.add_argument('--trace-repeat',type=Path,required=True)
 a=p.parse_args();print(json.dumps(verify(a.run,a.pe,a.zfs,a.v24,a.trace,a.trace_repeat),indent=2))
