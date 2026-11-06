#!/usr/bin/env python3
"""Guarded native i386 original-slice observation versus independent model.

Requires Linux x86-64 with i386 execution and ptrace child access; as/ld, Python.
Only reads within TER's exact allocation or the initialized default are executed.
Default-page overrun is stopped even if unrelated PE memory is mapped there.
"""
import argparse,ctypes,hashlib,json,os,signal,struct,subprocess
from pathlib import Path
from scan_model import TER,DEFAULT,PCS,resolve,read,predict
EXE_SHA='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
libc=ctypes.CDLL(None,use_errno=True);libc.ptrace.restype=ctypes.c_long
fields='r15 r14 r13 r12 rbp rbx r11 r10 r9 r8 rax rcx rdx rsi rdi orig_rax rip cs eflags rsp ss fs_base gs_base ds es fs gs'.split()
class Regs(ctypes.Structure):_fields_=[(n,ctypes.c_ulonglong) for n in fields]
def ptrace(req,pid,addr=0,data=0):
 ctypes.set_errno(0);v=libc.ptrace(ctypes.c_uint(req),ctypes.c_int(pid),ctypes.c_void_p(addr),data if isinstance(data,ctypes.c_void_p) else ctypes.c_void_p(data))
 if v==-1 and ctypes.get_errno():raise OSError(ctypes.get_errno(),os.strerror(ctypes.get_errno()))
 return v
def getregs(pid):
 r=Regs();ptrace(12,pid,0,ctypes.cast(ctypes.byref(r),ctypes.c_void_p));return r
def native(shim,image,terrain,x,z,size,work):
 # File stdin avoids pipe deadlocks. Mapped padding is never considered owned.
 with (work/'input.bin').open('wb') as f:f.write(image);f.write(terrain);f.write(bytes(0x800000-len(terrain)))
 with (work/'input.bin').open('rb') as f:p=subprocess.Popen([str(shim)],stdin=f,stdout=subprocess.DEVNULL)
 try:
  _,status=os.waitpid(p.pid,0)
  if not os.WIFSTOPPED(status):raise RuntimeError('native shim did not reach ptrace trap; child tracing permission required')
  r=getregs(p.pid);r.rip=0x491556;r.rbx=size//2;r.rsi=x+size//2;r.rdi=z+size//2
  ptrace(13,p.pid,0,ctypes.cast(ctypes.byref(r),ctypes.c_void_p))
  reads=[];branches=[]
  for step in range(20000):
   r=getregs(p.pid);pc=r.rip
   if pc in (0x491674,0x4917b4):return {'outcome':'split' if pc==0x491674 else 'leaf','reads':reads,'branches':branches,'steps':step}
   if pc in PCS:
    address=getattr(r,{PCS[0]:'rbx',PCS[1]:'rdi',PCS[2]:'rcx',PCS[3]:'rsi'}[pc])&0xffffffff
    word=read(terrain,address)
    reads.append({'pc':pc,'address':address,'word':word,'i':r.rdx&0xffffffff})
    if word is None:return {'outcome':'unsafe','reads':reads,'branches':branches,'steps':step,'stopped_before_dereference':True}
    actual=ptrace(2,p.pid,address)&65535
    assert actual==word,('native installed memory',address,actual,word)
   opcode=ptrace(2,p.pid,pc)&255
   ptrace(9,p.pid)
   _,status=os.waitpid(p.pid,0)
   if not os.WIFSTOPPED(status) or os.WSTOPSIG(status)!=signal.SIGTRAP:raise RuntimeError(('unexpected native signal',status,hex(pc)))
   if opcode in (0x7c,0x7d,0x75,0x0f):branches.append({'pc':pc,'next':getregs(p.pid).rip})
  raise RuntimeError('instruction limit')
 finally:
  try:os.kill(p.pid,signal.SIGKILL);os.waitpid(p.pid,0)
  except ProcessLookupError:pass
  p.returncode=-signal.SIGKILL
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_text(json.dumps(x,indent=2,sort_keys=True)+'\n')
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--exe',type=Path,required=True);ap.add_argument('--m06-msn',type=Path,required=True);ap.add_argument('--m06-ter',type=Path,required=True);ap.add_argument('--m02-msn',type=Path,required=True);ap.add_argument('--m02-ter',type=Path,required=True);ap.add_argument('--work',type=Path,required=True);ap.add_argument('--emit',type=Path,required=True);a=ap.parse_args()
 a.work.mkdir(parents=True,exist_ok=False);a.emit.mkdir(parents=True,exist_ok=True)
 exe=a.exe.read_bytes();assert sha(exe)==EXE_SHA
 ph=struct.unpack_from('<I',exe,60)[0];sec=ph+24+struct.unpack_from('<H',exe,ph+20)[0];image=bytearray(0x300000)
 for i in range(struct.unpack_from('<H',exe,ph+6)[0]):
  _,vs,rv,n,off=struct.unpack_from('<8sIIII',exe,sec+i*40);image[rv:rv+n]=exe[off:off+n]
 assert image[DEFAULT-0x400000:DEFAULT-0x400000+32768]==bytes(32768)
 src=Path(__file__).parent;shim=a.work/'shim'
 subprocess.run(['as','--32',str(src/'native_scan.S'),'-o',str(a.work/'shim.o')],check=True);subprocess.run(['ld','-m','elf_i386',str(a.work/'shim.o'),'-o',str(shim)],check=True)
 prior=src.parents[1]/'i76exe-20261106T011534Z-5a34de5f/evidence/input_identities.json';ids=json.loads(prior.read_text());results=[];checks=0;identities={}
 for mission in ('M06','M02'):
  msn=getattr(a,mission.lower()+'_msn').read_bytes();terrain=getattr(a,mission.lower()+'_ter').read_bytes()
  for ext,b in [('MSN',msn),('TER',terrain)]:assert sha(b)==ids[mission+'.'+ext]['sha256'];identities[mission+'.'+ext]={'sha256':sha(b),'bytes':len(b)}
  at=msn.index(b'ZMAP');zm=msn[at+9:at+6409]
  # First horizontal/vertical active pairs, diagonal, active/default and final allocated page.
  pairs={}
  for z in range(79):
   for x in range(79):
    p=zm[z*80+x]
    if p==255:continue
    if zm[z*80+x+1]!=255:pairs.setdefault('horizontal',(x,z))
    if zm[(z+1)*80+x]!=255:pairs.setdefault('vertical',(x,z))
    if zm[(z+1)*80+x+1]!=255:pairs.setdefault('diagonal',(x,z))
    if zm[z*80+x+1]==255:pairs.setdefault('active_default',(x,z))
    if p==len(terrain)//32768-1:pairs['last_allocated']=(x,z)
  cases=[]
  for kind,(px,pz) in pairs.items():
   for size in (8,16,32):
    # Aligned last region includes sample127 but not neighbor0; supplied unaligned phase crosses.
    cases.append((f'{kind}_aligned_{size}',px*128+128-size,pz*128+128-size,size,'retail',None))
   if kind in ('horizontal','active_default'):x,z=px*128+124,pz*128+32
   elif kind=='vertical':x,z=px*128+32,pz*128+124
   else:x,z=px*128+124,pz*128+124
   cases.append((kind+'_unaligned',x,z,8,'retail',None))
  px,pz=pairs['horizontal'];x,z=px*128+124,pz*128+32
  # Controlled TER copies clear class bits only, retain authentic low13 data.
  for cls in range(8):cases.append((f'class_{cls}_aligned',px*128+96,pz*128+32,32,'class_flat',cls))
  for site in range(4):
   for cls in (2,3,4,6,7):cases.append((f'site{site}_class{cls}_bit12',px*128+96,pz*128+32,32,'site'+str(site),cls))
  for kind in ('horizontal','vertical','diagonal','active_default','last_allocated'):
   if kind not in pairs:continue
   px,pz=pairs[kind];x=px*128+(32 if kind=='vertical' else 124);z=pz*128+(32 if kind in ('horizontal','active_default') else 124)
   cases.append((kind+'_clear_cross',x,z,8,'clear',None))
   cases.append((kind+'_neighbor_class3',x,z,8,'neighbor',3))
  px,pz=pairs['horizontal']
  for aligned in (True,False):cases.append(('repeat_'+('aligned' if aligned else 'cross'),px*128+(120 if aligned else 124),pz*128+32,8,'repeat',3))
  cases.extend([('default_aligned',0,0,32,'retail',None),('default_cross',124,124,8,'retail',None),('origin_negative',-1,0,8,'retail',None),('origin_limit',10240,10240,32,'retail',None),('origin_above_limit',10241,0,8,'retail',None)])
  for name,x,z,size,variant,cls in cases:
   t=bytearray(terrain);m=bytearray(zm);mods=[]
   if variant!='retail':
    for k in range(1,len(t),2):t[k]&=31
    mods.append({'operation':'clear all TER class bits; retain low13','bytes_sha256':sha(t)})
   if variant=='class_flat':
    address=resolve(m,x+size-1,z);off=address-TER;t[off+1]|=cls<<5;mods.append({'address':address,'class':cls})
   if variant.startswith('site'):
    dx,dz=[(size-2,0),(size-2,size-1),(0,size-2),(size-1,size-2)][int(variant[-1])]
    address=resolve(m,x+dx,z+dz);t[address-TER+1]|=(cls<<5)|16;mods.append({'address':address,'class':cls,'bit12':True})
   if variant=='repeat':
    slot=(z//128)*80+x//128;m[slot+1]=m[slot];mods.append({'zmap_index':slot+1,'page':m[slot]})
   if variant in ('neighbor','repeat'):
    address=resolve(m,x+size-1,z if variant=='repeat' else z+size-1)
    if address>=TER:
     t[address-TER+1]|=cls<<5;mods.append({'address':address,'class':cls})
   im=bytearray(image)
   for slot in range(16384):
    px,pz=slot%128-24,slot//128-24;pg=m[pz*80+px] if 0<=px<80 and 0<=pz<80 else 255
    struct.pack_into('<I',im,0x244380+4*slot,DEFAULT if pg==255 else TER+pg*32768)
   observed=native(shim,im,t,x,z,size,a.work);expected=predict(m,t,x,z,size);ordinary=predict(m,t,x,z,size,True)
   assert observed['outcome']==expected['outcome'] and observed['reads']==expected['reads'],(mission,name,observed,expected)
   checks+=1+len(observed['reads'])
   results.append({'id':mission+'_'+name,'mission':mission,'origin':[x,z],'size':size,'variant':variant,'modifications':mods,'normal_alignment':x%size==0 and z%size==0,'native':observed,'bounded_model_equal':True,'per_coordinate':ordinary,'class_decision_differs':observed['outcome']!=ordinary['outcome'],'modified_ter_sha256':sha(t),'modified_zmap_sha256':sha(m)})
   print(mission,name,observed['outcome'],len(observed['reads']),flush=True)
 with (a.emit/'scan_cases.jsonl').open('w') as f:
  for r in results:f.write(json.dumps(r,sort_keys=True)+'\n')
 dump(a.emit/'results.json',{'status':'passed','cases':len(results),'checks':checks,'attempted_reads':sum(len(r['native']['reads']) for r in results),'executed_reads':sum(sum(v['word'] is not None for v in r['native']['reads']) for r in results),'unsafe_cases':[r['id'] for r in results if r['native']['outcome']=='unsafe'],'decision_differences':[r['id'] for r in results if r['class_decision_differs']],'inputs':identities,'exe_sha256':sha(exe),'slice':[0x491556,0x491674],'method':'Unmodified original instructions on i386 CPU, ptrace single step with bounded pre-read checks; supplied PE/grid/Linux environment. No earlier LOD/height test execution.'})
if __name__=='__main__':main()
