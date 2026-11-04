#!/usr/bin/env python3
"""Read-only reproduction. Full Ghidra exports go ONLY to supplied private work dir."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import wrld

EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
TARGETS='004b8a10 004b89e0 004b4550 004b3db0 00423320 00477b00 004908f0 00401540 004b8500 00479780 00402b30 0045dea0 0049cdf0 00471c10 004b41e0 00404e50 00405970 004026c0 00423330 00492770 00492780 00492790 004927a0 004909b0 00495060 0049a070 004703a0 004ad640'.split()

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    p=argparse.ArgumentParser(description=__doc__)
    for arg in ('exe','gzf','corpus-root','work'):p.add_argument('--'+arg,type=Path,required=True)
    p.add_argument('--headless',type=Path,help='Optional Ghidra analyzeHeadless path; requires Java runtime')
    args=p.parse_args();assert digest(args.exe)==EXE;assert digest(args.gzf)==GZF
    scripts=Path(__file__).resolve().parent
    assert not args.work.resolve().is_relative_to(scripts.parent.resolve()), 'work must be outside public run'
    args.work.mkdir(parents=True,exist_ok=True)
    (args.work/'corpus.json').write_text(json.dumps(wrld.survey(args.corpus_root),indent=2)+'\n')
    subprocess.run([sys.executable,'-m','unittest','discover','-s',str(scripts),'-p','test_wrld.py','-v'],check=True)
    subprocess.run([sys.executable,str(scripts/'check_fields.py'),str(args.corpus_root)],check=True)
    if args.headless:
        project=args.work/'project';project.mkdir(exist_ok=True)
        assert not (project/'research.gpr').exists(),'use a fresh disposable work directory'
        common=[str(args.headless),str(project),'research']
        subprocess.run(common+['-import',str(args.gzf.resolve()),'-noanalysis','-scriptPath',str(scripts),'-postScript','WrldAudit.java',str(args.work/'exports'),*TARGETS,'00500ca0'],check=True)
        subprocess.run(common+['-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',str(scripts),'-postScript','WrldVerify.java',str(args.exe.resolve()),str(args.work/'instruction_byte_validation.tsv'),*TARGETS,'-postScript','WrldRefs.java',str(args.work/'references.txt')],check=True)
    print('Read-only reproduction passed; private outputs remain in',args.work)

if __name__=='__main__':main()
