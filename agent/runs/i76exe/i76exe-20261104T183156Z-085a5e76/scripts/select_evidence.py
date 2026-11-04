#!/usr/bin/env python3
"""Select reviewed address windows from private WrldAudit exports, no raw byte dump."""
import argparse
import json
from pathlib import Path

def select(exports):
    run=Path(__file__).resolve().parents[1]
    selections=json.loads((run/'evidence/review_selections.json').read_text())
    functions={}
    for folder in exports:
        for path in folder.glob('*.txt'):
            lines=path.read_text().splitlines()
            if lines and lines[0].startswith('TARGET ') and ' FUNCTION none' not in lines[0]:
                functions[lines[0].split()[-1]]=lines
    out=['# Reviewed original-instruction selections. Retail VA; v100 names are research aliases.','address\tinstruction']
    for fn,ranges in selections.items():
        lines=functions[fn];out.append('# '+lines[0])
        for line in lines:
            if len(line)<10 or line[8]!=' ':continue
            try:address=int(line[:8],16)
            except ValueError:continue
            if ranges is None or any(int(lo,16)<=address<=int(hi,16) for lo,hi in ranges):
                out.append(line[:8]+'\t'+line[9:])
    return '\n'.join(out)+'\n'

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('exports',type=Path,nargs='+');p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.write_text(select(a.exports))
