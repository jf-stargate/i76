#!/usr/bin/env python3
"""Run owned observers on a private imported project; never use another worker's project."""
import argparse,os,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--headless',required=True);p.add_argument('--project',required=True,type=Path);p.add_argument('--program',default='i76exe_v100');p.add_argument('--msn',required=True);p.add_argument('--ter',required=True);p.add_argument('--cases',nargs='+',default=['primary','contrast','below','x2952.6','x2953.5','x2957.5','z47999.9','z48000.1']);a=p.parse_args()
r=Path(__file__).resolve().parents[1];work=r/'private';(work/'cases').mkdir(exist_ok=True)
for case in a.cases:
 cmd=[a.headless,str(a.project),'topology','-process',a.program,'-readOnly','-noanalysis','-scriptPath',str(r/'scripts'),'-postScript','I76_TopologyProbe.java',str(work/'fixtures'),str(work/'cases'/f'{case}.tsv'),'bus',a.msn,a.ter,str(work/'x87_terrain_service'),case]
 with (work/f'{case}.log').open('w') as f: subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT,check=True,env=os.environ|{'XDG_CONFIG_HOME':str(work/'config'),'XDG_CACHE_HOME':str(work/'cache')})
 trace=(work/'cases'/f'{case}.tsv').read_text();assert 'COHERENT_COMPLETE' in trace and '\tBLOCKER\t' not in trace
 print(case,'complete',flush=True)
