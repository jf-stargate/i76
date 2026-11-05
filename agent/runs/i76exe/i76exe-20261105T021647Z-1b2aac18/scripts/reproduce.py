"""Run-local experiment. Proprietary inputs and generated payloads stay private.
Linux x86-64 with ELF32 support, gcc, /usr/lib32 libc/libm and Ghidra 12.1.4.
Use a NEW --work directory; no shared files or existing runs are written.
"""
import argparse, hashlib, json, os, struct, subprocess, sys
from pathlib import Path
sys.dont_write_bytecode=True
from model import Arithmetic, f64, ext80, lum, digest, synthetic
S=Path(__file__).resolve().parent
EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
def put(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
def run(cmd,log):
    r=subprocess.run(list(map(str,cmd)),capture_output=True,text=True,env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1'))
    log.write_text(r.stdout+r.stderr)
    if r.returncode:raise RuntimeError(f'{cmd[0]} exited {r.returncode}; see {log}')
    if 'SCRIPT ERROR' in r.stdout+r.stderr or 'Error running script' in r.stdout+r.stderr:raise RuntimeError(str(log))
    return r.stdout+r.stderr

def gamma_check(trace,table,cw):
    a=Arithmetic(cw);ex=[0x3fe999999999999a,0x3feccccccccccccd,0x3ff0000000000000,0x3ff3333333333333,0x3ff6666666666666,0x3ff999999999999a,0x3ffccccccccccccd,0x4000000000000000,0x400199999999999a,0x4004000000000000]
    errors=[];near=[]
    for k in range(10):
        inv=a.spill(a.op(1/f64(ex[k])),53)
        for v in range(256):
            at=(k*256+v)*30
            base,exponent,power=[ext80(trace[at+j:at+j+10]) for j in [0,10,20]]
            assert base==a.op(v*f64(0x3f70101010101010)),(cw,k,v,'base')
            assert exponent==inv,(cw,k,v,'exponent')
            result=a.op(power*255)
            if int(result)&255!=table[k*256+v]:errors.append([k,v])
            delta=abs(result-round(result))
            near.append((delta,k,v,result))
    assert not errors,errors
    return [{'slot':k+1,'input':v,'scaled_exact':str(r),'distance_to_integer':str(d),'output':table[k*256+v]} for d,k,v,r in sorted(near)[:30]]

def main():
    p=argparse.ArgumentParser()
    for x in ['root','repo','exe','gzf','headless','work']:p.add_argument('--'+x,type=Path,required=True)
    p.add_argument('--skip-ghidra',action='store_true')
    a=p.parse_args();a.work=a.work.resolve();a.work.mkdir(exist_ok=False)
    assert digest(a.exe.read_bytes())==EXE and digest(a.gzf.read_bytes())==GZF
    # Reauthenticate extracted retail palettes against accepted archive provenance.
    corpus=json.loads((a.repo/'agent/runs/i76exe/i76exe-20261104T224244Z-4359bae0/evidence/corpus.json').read_text())
    palettes=synthetic();sources=[]
    for name in ['m05.act','m15.act','t01.act']:
        rec=next(r for r in corpus['resources'] if r['name']==name)
        b=(a.root/'zfs/resources'/name).read_bytes();assert digest(b)==rec['sha256']
        # Re-read packed source independently using accepted resource extractor.
        import importlib.util
        spec=importlib.util.spec_from_file_location('accepted_zfs',a.repo/'scripts/game/i76_zfs_extract.py');z=importlib.util.module_from_spec(spec);sys.modules[spec.name]=z;spec.loader.exec_module(z)
        archive=(a.root/'orig/I76.ZFS').read_bytes();h=z.parse_header(archive);records,_=z.parse_records(archive,h);r=next(r for r in records if r.name.lower()==name and not r.inactive)
        raw=archive[r.file_offset:r.file_offset+r.stored_size];raw=z.LzoDecompressor().decompress(r.mode,raw,r.logical_size) if r.mode&6 else raw
        assert b==raw;assert digest(archive)==corpus['archive']['sha256']
        palettes[name[:-4]]=b;sources.append({'name':name,'sha256':digest(b),'bytes':768,'archive_record':r.index})
    for n,b in palettes.items():(a.work/(n+'.act')).write_bytes(b)
    cmd=['gcc','-m32','-O0','-mfpmath=387','-fexcess-precision=standard','-fno-pie','-no-pie','-nostdlib',S/'native.c','-L/usr/lib32','-Wl,-dynamic-linker,/lib/ld-linux.so.2','-l:libm.so.6','-l:libc.so.6','-o',a.work/'native']
    run(cmd,a.work/'compile.log')
    identities={str(p):{'sha256':digest(p.read_bytes()),'bytes':p.stat().st_size} for p in [a.exe,a.gzf,Path('/usr/lib32/libm.so.6'),Path('/usr/lib32/libc.so.6'),Path('/lib/ld-linux.so.2')]}
    results=[];thresholds=[]
    cases=[(n,0x37f,0) for n in palettes]
    cases += [('permuted',(pc<<8)|(rc<<10)|0x7f,0) for pc in [0,2,3] for rc in range(4) if (pc,rc)!=(3,0)]
    cases += [('permuted',cw,1) for cw in [0x7f,0x27f,0x37f]]
    for n,cw,wide in cases:
        key=f'{n}-{cw:04x}-{wide}';lp=a.work/(key+'.lum');gp=a.work/(key+'.gamma')
        log=run([a.work/'native',a.exe,a.work/(n+'.act'),lp,gp,cw,wide],a.work/(key+'.log'))
        original=lp.read_bytes();ref=lum(palettes[n],cw);cr=Path(str(lp)+'.ref').read_bytes()
        assert original==ref,(key,'rational LUM',sum(x!=y for x,y in zip(original,ref)))
        assert original==cr,(key,'C LUM')
        conversion=Path(str(lp)+'.ftol').read_bytes();observed=struct.unpack('<24576q',conversion)
        seq=[Arithmetic(cw).channels(v)[0] for v in range(256)]
        expected=tuple(seq[palettes[n][3*c+k]][r] for c in range(256) for r in range(32) for k in range(3))
        assert observed==expected,(key,'original conversion sequence')
        gamma=gp.read_bytes();cg=Path(str(gp)+'.ref').read_bytes();assert gamma==cg,(key,'C gamma')
        trace=Path(str(gp)+'.power').read_bytes();near=gamma_check(trace,gamma,cw)
        row={'case':key,'palette_sha256':digest(palettes[n]),'cw':cw,'power_service':'glibc-powl' if wide else 'glibc-pow-double','lum_sha256':digest(original),'lum_bytes':len(original),'conversion_trace_sha256':digest(conversion),'conversion_sequence_mismatches':0,'rational_mismatches':0,'c_reference_mismatches':0,'gamma_sha256':digest(gamma),'gamma_row_sha256':[digest(gamma[k*256:(k+1)*256]) for k in range(10)],'gamma_endpoints':[[gamma[k*256],gamma[k*256+255]] for k in range(10)],'power_trace_sha256':digest(trace),'power_arithmetic_mismatches':0,'native_log':log.strip().splitlines()}
        results.append(row)
        if cw==0x37f:thresholds.append({'case':key,'near_integer':near})
        print('Validated '+key,flush=True)
    base=palettes['permuted'];gold=lum(base);diff=[]
    for mode,kw in [('no-cache',{'cache':False}),('last-tie',{'tie_last':True}),('row-major',{'row_major':True}),('early-spill',{'early':True})]:
        other=lum(base,**kw);diff.append({'variant':mode,'sha256':digest(other),'different_bytes':sum(x!=y for x,y in zip(gold,other)),'first_differences':[i for i,(x,y) in enumerate(zip(gold,other)) if x!=y][:16]})
    precision=[]
    ar=Arithmetic()
    for v in range(256):
        _,h=ar.channels(v);_,bad=ar.channels(v,True)
        for (r,s,d,q),(_,bs,bd,bq) in zip(h,bad):
            if (s,d,q)!=(bs,bd,bq):
                precision.append({'channel':v,'row':r,'state_exact':str(s),'step_exact':str(d),'scaled_exact':str(q),'early_spill_state':str(bs),'early_spill_step':str(bd),'early_spill_scaled':str(bq),'converted':int(q),'early_spill_converted':int(bq)});break
    put(a.work/'results.json',{'runtime_identities':identities,'retail_sources':sources,'cases':results,'counterfactuals':diff,'precision_examples':precision[:20],'gamma_thresholds':thresholds,'limitations':'Original image routines with authored FTOL and glibc pow/powl substitutes. No MSVCRT parity claim. Native Linux ELF32, not retail Windows process.'})
    if not a.skip_ghidra:
        project=a.work/'project';project.mkdir()
        common=[a.headless,project,'numeric','-noanalysis','-scriptPath',S]
        run(common+['-import',a.gzf],a.work/'import.log')
        run(common+['-process',a.gzf.stem,'-readOnly','-postScript','NumericAudit.java',a.exe,a.work/'audit.json'],a.work/'audit.log')
        run(common+['-process',a.gzf.stem,'-readOnly','-postScript','DependencyProbe.java',a.work/'dependencies.json'],a.work/'dependencies.log')
        for n,cw in [('permuted',0x37f),('ties',0x37f),('m05',0x37f),('permuted',0x7f)]:
            key=f'{n}-{cw:04x}-0';out=a.work/('gh-'+key)
            run(common+['-process',a.gzf.stem,'-readOnly','-postScript','NumericProbe.java',a.exe,a.work/(n+'.act'),out,a.work/(key+'.gamma.power'),cw],a.work/('gh-'+key+'.log'))
            gh=json.loads(Path(str(out)+'.json').read_text());native=(a.work/(key+'.lum')).read_bytes();gb=Path(str(out)+'.lum').read_bytes();gg=Path(str(out)+'.gamma').read_bytes()
            gh['lum_sha256']=digest(gb);gh['gamma_sha256']=digest(gg);gh['native_lum_different_bytes']=sum(x!=y for x,y in zip(native,gb));gh['native_gamma_different_bytes']=sum(x!=y for x,y in zip((a.work/(key+'.gamma')).read_bytes(),gg))
            if n=='ties':assert gh['direct_nearest']==[0,0,1]
            if cw==0x37f:assert not gh['native_lum_different_bytes'] and not gh['native_gamma_different_bytes'] and not gh['power_operand_mismatches']
            put(Path(str(out)+'.comparison.json'),gh);print('Ghidra validated '+key,flush=True)
        run(common+['-process',a.gzf.stem,'-readOnly','-postScript','GammaControl.java',a.work/'permuted-037f-0.gamma.power',a.work/'gamma-cw-control'],a.work/'gamma-cw-control.log')
    assert digest(a.exe.read_bytes())==EXE and digest(a.gzf.read_bytes())==GZF
    run([sys.executable,'-m','unittest','discover','-s',S,'-p','test_model.py','-v'],a.work/'tests.txt')
    print('Experiment passed: '+str(a.work),flush=True)
if __name__=='__main__':main()
