#!/usr/bin/env python3
"""Fresh private Ghidra project and eight sequential, separate process replays.

Requires licensed inputs. The work directory must not exist. Nothing is written
to source inputs or the source checkout. Use verify_schedule.py afterward.
"""
import argparse, shutil, subprocess, sys
from pathlib import Path

p = argparse.ArgumentParser()
for key in ['headless','source-repo','work','exe','gzf','zfs','msn','ter','strlkup']:
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
subprocess.run(['gcc','-O2',str(scripts/'x87_oracle.c'),'-o',str(a.work/'x87_oracle')], check=True)
with (a.work/'x87_oracle.tsv').open('w') as f: subprocess.run([a.work/'x87_oracle'],stdout=f,check=True)
for name, vehicle, selected, suffix in [('pending_bus','bus',1,'-pending-initonly'),
 ('pending_repeat','bus',1,'-pending-initonly'),('pending_unselected','bus',0,'-pending-initonly'),
 ('peripheral','bus',1,'-peripheral'),('noinit','bus',1,'-peripheral-noinit'),
 ('postcontrol','bus',1,'-directinit-postcontrol'),('x87','bus',1,'-x87only'),('rawx87','bus',1,'-x87only-rawx87')]:
    cmd = [a.headless,a.work,'research','-process','i76_mission_v97_verified_names',
           '-readOnly','-noanalysis','-scriptPath',scripts,'-postScript',
           'I76_SelectedInitProbe.java',a.work/'fixtures',a.work/(name+'.tsv'),
           vehicle,str(selected),'1','1','math-clock-pop-terrain-host-filter-registry'+suffix,
           a.msn,a.ter,a.work/'x87_fistp_service','1']
    code, log = run(cmd,name+'.log')
    if name.startswith('pending'):
        assert 'PC=000c09e8' in log and 'LOCALIZATION_PREREQUISITE' in (a.work/(name+'.tsv')).read_text(), name
        print(name+': expected unresolved localization prerequisite', flush=True)
    elif name == 'rawx87':
        assert 'Unimplemented CALLOTHER pcodeop (fcos), PC=0049d409' in log, name
        print(name+': expected emulator FSINCOS blocker', flush=True)
    else:
        assert code == 0 and 'ERROR' not in log, name+'.log'
        print(name+': completed'+(' with expected invalid reads' if name=='noinit' else ''), flush=True)
print('Private replay complete; run verify_selected.py.', flush=True)
