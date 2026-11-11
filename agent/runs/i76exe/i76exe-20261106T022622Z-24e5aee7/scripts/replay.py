#!/usr/bin/env python3
import argparse,os,subprocess,struct
from coordinate_model import Terrain
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--work',type=Path);p.add_argument('--headless',default='/media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless');p.add_argument('--fixtures',required=True);p.add_argument('--msn',required=True);p.add_argument('--ter',required=True);p.add_argument('--cases',nargs='+',default=['primary','contrast','below','x2952.6','x2953.5','x2957.5','z47996.4','z47996.6','z47999.9','z48000.1','ground','groundzero','mixed','duplicate','collinear','lodwide','lodfov','quality1','quality2','yaw','pitch','clear_low','clear_exact','clear_high']);a=p.parse_args()
r=Path(__file__).resolve().parents[1];w=a.work or r/'private'
for c in a.cases:
 cmd=[a.headless,str(w/'project'),'camera','-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',str(r/'scripts'),'-postScript','I76_TopologyProbe.java',a.fixtures,str(w/'cases'/f'{c}.tsv'),'bus',a.msn,a.ter,str(w/'x87_terrain_service'),c]
 if c.startswith('clear_'):
  view=(w/'cases/primary.tsv.view.bin').read_bytes();x,y,z=struct.unpack_from('<3d',view,0x160)
  model=Terrain(Path(a.msn).read_bytes(),Path(a.ter).read_bytes(),bytes(32768));h=float(model.height(x,z)['expected'])
  cmd.append(repr(h+{'clear_low':.00999,'clear_exact':.01,'clear_high':.01001}[c]))
 with (w/f'{c}.log').open('w') as f:subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT,check=True,env=os.environ|{'XDG_CONFIG_HOME':str(w/'config'),'XDG_CACHE_HOME':str(w/'cache')})
 trace=(w/'cases'/f'{c}.tsv').read_text();assert 'COHERENT_COMPLETE' in trace and '\tBLOCKER\t' not in trace,c
 print(c,'complete',flush=True)
