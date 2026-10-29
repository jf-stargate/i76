#!/usr/bin/env python3
"""Sequential fresh-project reproduction of baseline and controlled pose cases."""
import argparse,hashlib,json,shutil,subprocess
from pathlib import Path

PARENT='agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8'
def main():
    p=argparse.ArgumentParser();p.add_argument('--source-repo',type=Path,required=True);p.add_argument('--work',type=Path,required=True);p.add_argument('--headless',type=Path,required=True)
    for k in ['exe','gzf','zfs','msn','ter']:p.add_argument('--'+k,type=Path,required=True)
    a=p.parse_args();run=Path(__file__).resolve().parents[1];source=a.source_repo.resolve()/PARENT;work=a.work.resolve();work.mkdir(parents=True,exist_ok=True)
    if (work/'research.gpr').exists():raise SystemExit('Use a fresh private work directory; existing project is protected')
    manifest=json.loads((source/'manifest.json').read_text());sha=lambda path:hashlib.sha256(path.read_bytes()).hexdigest()
    inputs={'i76.exe':a.exe,'I76.ZFS':a.zfs,'miss8/M06.MSN':a.msn,'miss8/M06.TER':a.ter}
    for item in manifest['inputs']:
        if item['name'] in inputs:assert sha(inputs[item['name']])==item['sha256'],item['name']
    assert sha(a.gzf)==manifest['baselines'][0]['baseline_sha256'],'GZF identity'
    for item in manifest['artifacts']:assert sha(source/item['path'])==item['sha256'],item['path']
    commands=[]
    def execute(cmd,name):
        cmd=list(map(str,cmd));commands.append(cmd);(work/'commands.json').write_text(json.dumps(commands,indent=2)+'\n')
        with (work/(name+'.log')).open('w') as f:subprocess.run(cmd,stdout=f,stderr=subprocess.STDOUT,check=True)
        log=(work/(name+'.log')).read_text(errors='replace')
        if 'Error running script' in log or 'REPORT SCRIPT ERROR' in log:raise RuntimeError('Ghidra script failed: '+name)
    execute(['python3',source/'scripts/prepare_private_inputs.py','--source-repo',a.source_repo,'--zfs',a.zfs,'--msn',a.msn,'--ter',a.ter,'--out',work/'fixtures'],'prepare')
    execute(['gcc','-O2',source/'scripts/x87_fistp_service.c','-o',work/'x87_fistp_service'],'compile_x87')
    shutil.copyfile(a.gzf,work/'i76_mission_v97_verified_names.gzf')
    execute([a.headless,work,'research','-import',work/'i76_mission_v97_verified_names.gzf','-noanalysis'],'import')
    def replay(name,scriptdir,script,vehicle,mode,frames,extra=()):
        execute([a.headless,work,'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scriptdir,'-postScript',script,work/'fixtures',work/(name+'.tsv'),vehicle,1,1,1,mode,a.msn,a.ter,work/'x87_fistp_service',frames,*extra],name)
    normal='math-clock-pop-terrain-host-filter-registry'
    for name,vehicle,mode,frames in [('bus','bus',normal,32),('bus_repeat','bus',normal,32),('gtsi','gtsi',normal,32),('slow','gtsi',normal+'-slow',4),('raw','bus','math-clock-pop-terrain-filter-registry',2)]:
        replay('publish_'+name,source/'scripts','I76_AuthenticTerrainPhysicsProbe.java',vehicle,mode,frames)
    for name,dy in [('control',0),('lower',-.25),('lower_repeat',-.25),('raised',1)]:
        replay(name,run/'scripts','I76_TerrainPoseProbe.java','bus',normal,32,[dy])
    cmd=['python3',run/'scripts/verify_pose.py','--run',run,'--source-run',source,'--private',work]
    for k in ['exe','gzf','zfs','msn','ter']:cmd+=['--'+k,getattr(a,k)]
    cmd+=['--x87-service',work/'x87_fistp_service']
    execute(cmd,'validation')
    print((work/'validation.log').read_text())
if __name__=='__main__':main()
