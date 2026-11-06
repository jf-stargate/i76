"""Fresh private import, byte-authenticated audit and independent executable replay.
Python environment: unicorn==2.1.4; standard library and accepted liblzo2 adapter.
"""
import argparse,json,subprocess,sys,re
from pathlib import Path
sys.dont_write_bytecode=True
from corpus import sha,EXE,GZF
from validate import run
from review import review
REQUESTS={1:['004474b0','00471980','004478b0','00447b20','0044a290','00485120','004828e0','00471c10'],2:['0044b430','00487ea0','00487480','0044ac80','00471840','00447ce0','00495060'],3:['00472ee0','00473670','00471fd0','00447e10','0044b190','0044b090'],4:['0044ab90','004859e0','00482fe0','00473236','00447290']}
def main():
    a=argparse.ArgumentParser()
    for k in ['repo','root','work','headless']:a.add_argument('--'+k,type=Path,required=True)
    a=a.parse_args();a.work=a.work.resolve();a.work.mkdir(exist_ok=False);repo=a.repo.resolve();root=a.root.resolve();scripts=Path(__file__).resolve().parent
    exe=root/'orig/i76.exe';gzf=root/'scratch_data/i76exe_v100.gzf';assert sha(exe.read_bytes())==EXE and sha(gzf.read_bytes())==GZF
    project=a.work/'project';project.mkdir()
    def gh(args,name):
        p=subprocess.run([str(a.headless),str(project),'texture','-noanalysis','-scriptPath',str(scripts),*args],text=True,capture_output=True)
        log=p.stdout+p.stderr;(a.work/(name+'.log')).write_text(log)
        assert p.returncode==0 and not re.search(r'SCRIPT ERROR|ERROR.*\.java|Exception:',log),name
    gh(['-import',str(gzf)],'import')
    def snapshot():return {str(p.relative_to(project)):sha(p.read_bytes()) for p in sorted(project.rglob('*')) if p.is_file() and (p.suffix in ('.gbf','.prp') or p.name=='~index.dat')}
    before=snapshot()
    for n,entries in REQUESTS.items():
        gh(['-process','i76exe_v100','-readOnly','-postScript','TextureAudit.java',str(a.work/f'pass{n}.json'),*entries],f'pass{n}')
        print('Static export',n,'passed',flush=True)
    assert snapshot()==before
    run(repo,root,a.work/'metadata');result=review(exe,gzf,a.work,a.work/'metadata')
    assert sha(exe.read_bytes())==EXE and sha(gzf.read_bytes())==GZF
    (a.work/'metadata/reproduction.json').write_text(json.dumps(dict(status='passed',private_program_files_unchanged=True,private_input_hashes_unchanged=True,static_instructions=result['static_instructions_verified'],executed_instructions=result['retired_instructions'],method='Unicorn 2.1.4 original x86 with supplied resource/CRT/heap services; no original Windows process'),indent=2)+'\n')
    print('Fresh reproduction passed',flush=True)
if __name__=='__main__':main()
