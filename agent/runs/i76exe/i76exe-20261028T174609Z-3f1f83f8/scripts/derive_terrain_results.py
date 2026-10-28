#!/usr/bin/env python3
"""Regenerate safe results.json/selected_events.tsv from private original-code traces."""
import argparse,csv,json,math,struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--private',type=Path,required=True);p.add_argument('--msn',type=Path,required=True);p.add_argument('--ter',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();a.out.mkdir(parents=True,exist_ok=True)
msn=a.msn.read_bytes();ter=a.ter.read_bytes();zi=msn.index(b'ZMAP');zm=msn[zi+9:zi+6409]
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def word(x,z):return struct.unpack_from('<H',ter,zm[(z//128)*80+x//128]*32768+2*((z%128)*128+x%128))[0]
def height(x,z):
 sx=x*f32(.2);sz=z*f32(.2);ix=math.floor(sx);iz=math.floor(sz);fx=sx-ix;fz=sz-iz;h00=word(ix,iz)&4095;h10=word(ix+1,iz)&4095;h01=word(ix,iz+1)&4095;h11=word(ix+1,iz+1)&4095;top=f32(h00+(h10-h00)*fx);bottom=f32(h01+(h11-h01)*fx);return (top+(bottom-top)*fz)*f32(.1)
def fields(x):return dict(y.split('=',1) for y in x['detail'].split(';') if '=' in y)
summary={};selected=[]
for name in ['bus','bus_repeat','gtsi','slow','raw']:
 with (a.private/f'publish_{name}.tsv').open() as f:r=list(csv.DictReader(f,delimiter='\t'))
 ev=lambda k:[x for x in r if x['kind']==k]
 samples=[fields(x) for x in ev('TERRAIN_SAMPLE')+ev('HEIGHT_RETURN')];errors=[abs(float(x['height'])-height(float(x['x']),float(x['z']))) for x in samples]
 tires=[fields(x) for x in ev('TIRE_CONTACT_RETURN')];contacts=[x for x in tires if x['mode']=='0'];frames=[fields(x) for x in ev('TWO_FRAME_NUMERICAL_RESULT')]
 summary[name]={'frames':len(frames),'solver_returns':len(ev('SOLVER_RETURN')),'height_returns':len(ev('HEIGHT_RETURN')),'logged_terrain_reads':len(ev('TERRAIN_NATIVE_READ')),'max_height_error':max(errors),'contact_mode_tire_updates':len(contacts),'compression_min':min(float(x['compression']) for x in tires),'compression_max':max(float(x['compression']) for x in tires),'body_probe_positive':sum(fields(x)['eax']!='0' for x in ev('GROUND_PROBE_RETURN')),'filter_initializers':len(ev('FILTER_INIT_RETURN')),'fistp_hardware_calls':len(ev('HARDWARE_FISTP')),'fcos_hardware_calls':len(ev('HARDWARE_FCOS')),'construction_diagnostics':[fields(x) for x in ev('NATIVE_reporter_RET')],'callback_errors':len(ev('POSE_CLASS_CALLBACK_ERROR')),'final_position':frames[-1]['rootPositionXYZ'],'max_axis_norm_error':max(abs(float(x['axisNormSq'])-1) for x in frames)}
 if name!='bus_repeat':
  keep={'TERRAIN_INITIALIZED','TERRAIN_PAGE_CHECK','TERRAIN_PAGE','WRLD_MATERIALS','TERRAIN_SAMPLE','FILTER_INIT_RETURN','RETAIL_SPAWN_POSE','CONTACT_GEOMETRY','NATIVE_reporter_RET','ENGINE_VARIANTS_INITIALIZED','ENGINE_VARIANT_ROW','COMPONENT_RECORDS','TWO_FRAME_NUMERICAL_RESULT','POSE_GRAM'}
  selected.extend({'test':name,**{k:x[k] for k in ['kind','pc','detail']}} for x in r if x['kind'] in keep or x['kind']=='TIRE_CONTACT_RETURN' and fields(x)['mode']=='0')
(a.out/'results.json').write_text(json.dumps(summary,indent=2)+'\n')
with (a.out/'selected_events.tsv').open('w') as f:
 w=csv.DictWriter(f,fieldnames=['test','kind','pc','detail'],delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(selected)
print('Derived safe numerical evidence in',a.out)
