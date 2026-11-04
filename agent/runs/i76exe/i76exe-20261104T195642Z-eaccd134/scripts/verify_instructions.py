"""Authenticate bounded Ghidra audit against PE sections; publish reviewed slices only."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

EXE_SHA = "bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3"
GZF_SHA = "f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0"
# Reviewed windows; full function bodies/decompilation remain private.
WINDOWS = [(0x4706ef,0x470700),(0x470823,0x47083f),(0x47099b,0x4709a0),
           (0x4709b4,0x4709d2),(0x4709e6,0x4709ea),(0x470a05,0x470a13),
           (0x470aa0,0x470aa9),(0x470ad6,0x470ade),(0x470af4,0x470b13),
           (0x470b84,0x470bb2),(0x470bfc,0x470c2a),(0x470cae,0x470cc9),
           (0x46ff25,0x46ff30),(0x47000f,0x470050),(0x42d5d0,0x42d5d0)]

def sha(data): return hashlib.sha256(data).hexdigest()

def pe_reader(raw):
    pe=struct.unpack_from("<I",raw,0x3c)[0]
    if raw[pe:pe+4]!=b"PE\0\0": raise ValueError("not a PE")
    count=struct.unpack_from("<H",raw,pe+6)[0]
    opt_size=struct.unpack_from("<H",raw,pe+20)[0]
    image=struct.unpack_from("<I",raw,pe+24+28)[0]
    sections=[]
    for i in range(count):
        off=pe+24+opt_size+40*i
        size,rva,stored,fileoff=struct.unpack_from("<4I",raw,off+8)
        sections.append((image+rva,stored,fileoff))
    def read(va,size):
        for start,stored,fileoff in sections:
            if start <= va and size <= stored-(va-start):
                result=raw[fileoff+va-start:fileoff+va-start+size]
                if len(result)!=size:break
                return result
        raise ValueError("range not backed by original PE")
    return read

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--exe",type=Path,required=True)
    ap.add_argument("--gzf",type=Path,required=True)
    ap.add_argument("--audit",type=Path,required=True)
    args=ap.parse_args()
    raw=args.exe.read_bytes(); gzf=args.gzf.read_bytes()
    assert sha(raw)==EXE_SHA and sha(gzf)==GZF_SHA
    audit=json.loads(args.audit.read_text())
    assert audit["modification_before"]==audit["modification_after"]
    assert audit["executable_sha256"]==EXE_SHA
    read=pe_reader(raw);functions=[];snippets=[];total=0
    for f in audit["functions"]:
        for r in f["ranges"]:
            assert sha(read(int(r["start"],16),r["length"]))==r["sha256"]
        for ins in f["instructions"]:
            va=int(ins["va"],16); code=bytes.fromhex(ins["bytes"])
            assert read(va,len(code))==code
            total+=1
            if any(lo<=va<=hi for lo,hi in WINDOWS):
                snippets.append({"function":f["entry"],"va":ins["va"],"bytes":ins["bytes"],"asm":ins["asm"]})
        functions.append({"entry":f["entry"],"ranges":f["ranges"],"instructions":len(f["instructions"])})
    print(json.dumps({"exe_sha256":sha(raw),"exe_md5":hashlib.md5(raw).hexdigest(),
                      "gzf_sha256":sha(gzf),"gzf_md5":hashlib.md5(gzf).hexdigest(),
                      "ghidra":audit["ghidra"],"program":audit["program"],
                      "modification_before":audit["modification_before"],"modification_after":audit["modification_after"],
                      "verified_instructions":total,"functions":functions,"reviewed_instructions":snippets},indent=2))
if __name__=="__main__": main()
