#!/usr/bin/env python3
"""Private retail replay. Requires Ghidra 12.1.4, x86 Linux i386 support, JDK, gcc/as/ld/7z."""
import argparse,pathlib,subprocess,sys,hashlib,shutil,json
p=argparse.ArgumentParser()
for k in ['headless','orig','gzf','private']:p.add_argument('--'+k,type=pathlib.Path,required=True)
p.add_argument('--run',type=pathlib.Path,default=pathlib.Path(__file__).resolve().parent.parent)
a=p.parse_args()
for k in vars(a):setattr(a,k,getattr(a,k).resolve())
s=a.run/'scripts';w=a.private;w.mkdir(exist_ok=True,parents=True);(w/'inputs').mkdir(exist_ok=True)
def check(path,digest):assert hashlib.sha256(path.read_bytes()).hexdigest()==digest,str(path)
check(a.orig/'i76.exe','bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3');check(a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce')
check(a.orig/'miss8/M06.MSN','923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f');check(a.orig/'miss8/M06.TER','fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea');check(a.orig/'miss8/M02.TER','08ae567ceac9647bacd95a352eaef9707c3fbf6a9ec7096b9fe2152afc6bc0e2')
(w/'inputs/M02.MSN').write_bytes(subprocess.check_output(['7z','x','-so',str(a.orig/'I76_CD1.ISO'),'MISSIONS/M02.MSN']))
check(w/'inputs/M02.MSN','b566539e260440b43d40e7b6ad5ed6a959e344bcb6ca365562641b8b4b060175')
msns={'M06':a.orig/'miss8/M06.MSN','M02':w/'inputs/M02.MSN'}
for name,msn in msns.items():subprocess.run([sys.executable,str(s/'make_cases.py'),str(msn),str(w/(name+'.cases.tsv'))],check=True)
subprocess.run(['gcc','-O2',str(s/'x87_fistp_service.c'),'-o',str(w/'x87_fistp_service')],check=True)
if not (w/'research.gpr').exists():
 target=w/'i76_mission_v97_verified_names.gzf'
 if target!=a.gzf:shutil.copyfile(a.gzf,target)
 with (w/'import.stdout.log').open('w') as log:subprocess.run([str(a.headless),str(w),'research','-import',str(target),'-noanalysis','-log',str(w/'import.log')],stdout=log,stderr=subprocess.STDOUT,check=True)
cmd=[str(a.headless),str(w),'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',str(s),'-postScript','CoordinateAudit.java',str(w/'audit.tsv')]
for variant,name in [('M06','M06'),('M02','M02'),('alias','M06'),('bit12','M06'),('repeat','M06')]:
 cmd+=['-postScript','CoordinateProbe.java',str(msns[name]),str(a.orig/('miss8/'+name+'.TER')),str(w/(name+'.cases.tsv')),str(w/(variant+'.tsv')),str(w/'x87_fistp_service')]
 if variant in ['alias','bit12']:cmd+=[variant]
cmd+=['-log',str(w/'replay.log')]
with (w/'replay.stdout.log').open('w') as log:subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT,check=True)
for variant,name in [('M06','M06'),('M02','M02'),('alias','M06'),('bit12','M06')]:
 subprocess.run([sys.executable,str(s/'native_replay.py'),'--exe',str(a.orig/'i76.exe'),'--ter',str(a.orig/('miss8/'+name+'.TER')),'--trace',str(w/(variant+'.tsv')),'--cases',str(w/(name+'.cases.tsv')),'--out',str(w/('native_'+variant)),'--variant',variant if variant in ['alias','bit12'] else 'retail'],check=True)
subprocess.run([sys.executable,str(s/'verify_coordinates.py'),'--private',str(w),'--orig',str(a.orig),'--gzf',str(a.gzf),'--run',str(a.run),'--emit'],check=True)
