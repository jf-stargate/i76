#!/usr/bin/env python3
"""Run only against new private output. Does not publish raw capture files."""
import argparse
import hashlib
from pathlib import Path
import re
import shutil
import subprocess

GZF_SHA = 'd48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd'
PE_SHA = 'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    ap = argparse.ArgumentParser()
    for key in ('gzf', 'pe', 'headless', 'work'):
        ap.add_argument('--'+key, type=Path, required=True)
    a = ap.parse_args()
    assert digest(a.gzf) == GZF_SHA, 'Unrecognized private export; audit before adapting'
    assert digest(a.pe) == PE_SHA, 'Wrong retail executable'
    bundle = Path(__file__).resolve().parent
    a.work = a.work.resolve()
    a.work.mkdir(exist_ok=False)
    project = a.work/'project'
    project.mkdir()
    scripts = a.work/'accepted-scripts'
    scripts.mkdir()
    shutil.copy2(a.gzf, a.work/'input.gzf')
    calls = []
    for v, folder, name in [(99,'semantic-v99','I76_SemanticPass_v99'),
                           (100,'readability-v100','I76_SemanticTypes_v100'),
                           (101,'readability-v101','I76_ObjectDispatch_v101'),
                           (102,'readability-v102','I76_ClassDispatch_v102')]:
        source = (bundle.parent/folder/(name+'.java')).read_text()
        for mode in ('Preview','Apply'):
            new = f'Stage{v}{mode}'
            body = source.replace(name,new)
            if mode == 'Apply':
                body = re.sub(r'(boolean\s+APPLY\s*=\s*)false',r'\g<1>true',body)
            (scripts/(new+'.java')).write_text(body)
            calls += ['-postScript',new+'.java']
    base = [str(a.headless.resolve()),str(project),'consolidation','-noanalysis',
            '-scriptPath',str(scripts)+';'+str(bundle)]
    def run(args, log):
        with (a.work/log).open('w') as output:
            subprocess.run(base+args,stdout=output,stderr=subprocess.STDOUT,check=True)
        text = (a.work/log).read_text()
        # analyzeHeadless can return zero despite script errors.
        assert not re.search(r'(SCRIPT ERROR|ERROR.*\.java|migration rolled back)',text), log
    run(['-import',str(a.work/'input.gzf'),'-postScript','ConsolidationAudit.java',str(a.work/'input-audit')]+calls+
        ['-postScript','ConsolidationAudit.java',str(a.work/'before')], 'stage.log')
    args = ['-process','input']
    for phase, apply in [('preview',False),('after',True),('repeat',True)]:
        args += ['-postScript','ConsolidateSemantics.java',str(bundle),str(a.pe.resolve()),str(a.work/(phase+'-actions.tsv'))]
        if apply:
            args += ['APPLY']
        args += ['-postScript','ConsolidationAudit.java',str(a.work/phase)]
    run(args,'consolidation.log')
    print('Private captures:',a.work)

if __name__ == '__main__':
    main()
