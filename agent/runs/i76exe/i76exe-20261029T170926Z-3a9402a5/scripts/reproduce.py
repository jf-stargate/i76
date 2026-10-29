#!/usr/bin/env python3
"""Fresh private Ghidra project and five sequential, separate process replays.

Requires licensed inputs. The work directory must not exist. Nothing is written
to source inputs or the source checkout. Use verify_schedule.py afterward.
"""
import argparse, shutil, subprocess, sys
from pathlib import Path

p = argparse.ArgumentParser()
for key in ['headless','source-repo','work','exe','gzf','zfs','msn','ter']:
    p.add_argument('--'+key, type=Path, required=True)
a = p.parse_args()
for key, value in vars(a).items():
    setattr(a, key, value.resolve())
scripts = Path(__file__).resolve().parent
a.work.mkdir(parents=True, exist_ok=False)

def run(command, log):
    with (a.work/log).open('w') as f:
        result = subprocess.run([str(x) for x in command], stdout=f, stderr=subprocess.STDOUT)
    return result.returncode, (a.work/log).read_text()

cmd = [sys.executable, scripts/'prepare_private_inputs.py', '--source-repo',a.source_repo,
       '--zfs',a.zfs,'--msn',a.msn,'--ter',a.ter,'--out',a.work/'fixtures']
code, _ = run(cmd,'prepare.log')
assert code == 0, 'prepare.log'
subprocess.run(['gcc','-O2',str(scripts/'x87_fistp_service.c'),'-o',str(a.work/'x87_fistp_service')], check=True)
shutil.copyfile(a.gzf, a.work/a.gzf.name)
code, log = run([a.headless,a.work,'research','-import',a.work/a.gzf.name,'-noanalysis'],'import.log')
assert code == 0 and 'Import succeeded' in log, 'import.log'
for name, vehicle, selected, suffix in [('bus','bus',0,''),('gtsi','gtsi',0,''),
                                     ('direct_bus','bus',0,'-direct'),('bus_repeat','bus',0,''),
                                     ('diagnostic','bus',1,'-diagnostic')]:
    cmd = [a.headless,a.work,'research','-process','i76_mission_v97_verified_names',
           '-readOnly','-noanalysis','-scriptPath',scripts,'-postScript',
           'I76_DescriptorScheduleProbe.java',a.work/'fixtures',a.work/(name+'.tsv'),
           vehicle,str(selected),'1','1','math-clock-pop-terrain-host-filter-registry'+suffix,
           a.msn,a.ter,a.work/'x87_fistp_service','1' if name=='diagnostic' else '3']
    code, log = run(cmd,name+'.log')
    if name == 'diagnostic':
        assert 'Unimplemented CALLOTHER pcodeop (fcos), PC=0049d409' in log, name
        print(name+': expected original FSINCOS / fcos P-code blocker', flush=True)
    else:
        assert code == 0 and 'ERROR' not in log, name+'.log'
        print(name+': completed', flush=True)
print('Private replay complete; run verify_schedule.py against this work directory.', flush=True)
