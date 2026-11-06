#!/usr/bin/env python3
import os,subprocess,argparse
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--work',type=Path);p.add_argument('--headless',required=True);p.add_argument('--msn',required=True);p.add_argument('--ter',required=True);p.add_argument('--cases',nargs='+',default=['primary','contrast','below','x2953.5','z47996.4','z47996.6','z47999.9','z48000.1','y20','y120','y300']);a=p.parse_args()
r=Path(__file__).resolve().parents[1];w=(a.work or r/'private').resolve()
for case in a.cases:
 cmd=[a.headless,str(w/'project'),'emission','-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',str(r/'scripts'),'-postScript','I76_EmissionProbe.java',str(w/'fixtures'),str(w/'cases'/f'{case}.tsv'),'bus',a.msn,a.ter,str(w/'x87_terrain_service'),case]
 with (w/(case+'.log')).open('w') as f:subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT,check=True,env=os.environ|{'XDG_CONFIG_HOME':str(w/'config'),'XDG_CACHE_HOME':str(w/'cache')})
 t=(w/'cases'/f'{case}.tsv').read_text();assert 'COHERENT_COMPLETE' in t and '\tBLOCKER\t' not in t
 print(case,'complete',flush=True)
