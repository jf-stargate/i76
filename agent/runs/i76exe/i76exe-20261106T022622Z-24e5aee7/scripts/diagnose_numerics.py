#!/usr/bin/env python3
"""Reproduce arithmetic contrast and sampler-boundary diagnostics asset-free."""
import json,struct,sys
from fractions import Fraction as F
import numpy as np
from compare import RUN,predictions,Stencil,readrows,dump
from predict import f32,bits
fixtures=json.loads((RUN/'evidence/camera_fixtures.json').read_text())
events=readrows(RUN/'evidence/selected_original_events.tsv');result={}
for fixture in fixtures:
    case=fixture['case'];p=predictions(fixture,np.longdouble);d=predictions(fixture,float)
    fields=sum(a[k]!=b[k] for a,b in zip(p.get('planes',[]),d.get('planes',[])) for k in ['nx_bits','ny_bits','nz_bits','offset_le'])
    view=bytes.fromhex(fixture['input']['view_hex']);t=struct.unpack_from('<f',view,0x2c)[0];quality=fixture['input']['quality']
    qz={0:1/256,1:f32(1/384),2:struct.unpack('<f',bytes.fromhex('f853e33a'))[0]}[quality];v=t
    for factor in [t,4,qz,5,10]:v=f32(v*factor)
    row={'all_float64_plane_field_mismatches':fields,'premature_float32_height_threshold_bits':bits(v),'native_height_threshold_bits':p['threshold_bits'][1]}
    if case.startswith('clear'):
        x,y,z=struct.unpack_from('<3d',view,0x160)
        height=Stencil(fixture['input']['height_stencil']).height(x,z)['expected'];clearance=F(y)-height
        h=next(v['d']['height'] for v in events if v['kind']=='HEIGHT_TEST' and v['scenario']=='bus_coherent_'+case)
        ib=int(h,16);mant=ib&((1<<64)-1);exp=((ib>>64)&32767)-16383-63
        eh=F(mant)*(F(2)**exp)*(-1 if ib>>79 else 1)
        row|={'native_model_height':float(height),'emulated_height':float(eh),'emulator_height_error':float(eh-height),'native_model_clearance':float(clearance),'clearance_minus_double_0_01':float(clearance-F(.01))}
    result[case]=row
assert sum(v['all_float64_plane_field_mismatches'] for v in result.values())>0
assert any(v['premature_float32_height_threshold_bits']!=v['native_height_threshold_bits'] for v in result.values())
if '--record' in sys.argv:dump(RUN/'evidence/numeric_diagnostics.json',result)
else:assert result==json.loads((RUN/'evidence/numeric_diagnostics.json').read_text())
print('Numerical diagnostics verified:',len(result))
