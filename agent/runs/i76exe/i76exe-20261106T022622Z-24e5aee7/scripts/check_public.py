#!/usr/bin/env python3
"""Asset-free comparison, observation isolation and deliberate corruption controls."""
import copy,json,struct
import numpy as np
from compare import RUN,compare,predictions,dump
fixtures=json.loads((RUN/'evidence/camera_fixtures.json').read_text())
report,pred=compare(fixtures)
assert report==json.loads((RUN/'evidence/comparison.json').read_text())
assert pred==json.loads((RUN/'evidence/predictions.json').read_text())
controls={}
for f in fixtures:
    bare={'case':f['case'],'input':copy.deepcopy(f['input'])}
    assert predictions(bare,np.longdouble)==pred[f['case']]
controls['remove_all_original_outputs']='prediction unchanged for every case'
for key in ['threshold','normal','offset','hull','keep','native_admission']:
    bad=copy.deepcopy(fixtures);f=next(v for v in bad if v['case']=='primary')
    if key=='threshold':f['native']['threshold_bits'][0]='00000000'
    if key=='normal':f['native']['planes'][0]['nx_bits']='00000000'
    if key=='offset':f['native']['planes'][0]['offset_le']=struct.pack('<d',123.).hex()
    if key=='hull':f['emulated']['hull'][0][0]+=1
    if key=='keep':f['emulated']['keep'][0]=False
    if key=='native_admission':f['native']['accepted']=False
    try:compare(bad)
    except AssertionError:controls[key]='rejected'
    else:raise AssertionError('undetected '+key)
f=copy.deepcopy(next(v for v in fixtures if v['case']=='primary'))
f['input']['viewport_width']=800
assert predictions(f,np.longdouble)['threshold_bits'][0]!=pred['primary']['threshold_bits'][0]
controls['viewport_input']='prediction changes'
print('Public comparisons:',report['checks'],'; isolation/corruption controls:',len(controls))
if __name__=='__main__':
    import sys
    if '--record' in sys.argv:dump(RUN/'evidence/negative_controls.json',controls)
