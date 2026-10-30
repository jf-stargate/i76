#!/usr/bin/env python3
"""Independent byte/numeric/chronology checks; never executes the emulator.
Public-only: --run RUN. Full source verification: also --private WORK --exe PE
--gzf GZF --zfs ZFS. --emit writes deterministic derived evidence, then verifies it.
"""
import argparse,csv,hashlib,io,json,math,pathlib,struct
C=0x4c2730
KEEP={'RETURN','CONTROLLED_INPUTS','CONTROLLED_GUARD','CONTROLLED_RESET','CONTROLLED_POSE','SAMPLE','CAMERA_ENTER','CAMERA_RETURN','CALL_EVENT','ROOT_READ_ANCHOR','CAMERA_SOURCE','ROOT_MATRIX','NATIVE_CHANGED_DWORD','VIEW_POINT','SERVICE_TRIG','SERVICE_FTOL','NATIVE_ROOT_CTOR','NATIVE_WORLD_REGISTRATION','NATIVE_VCF_COMPLETE','VLOC_ATTACHMENT_FIELDS','CAMERA_PROJECTION_INIT_END'}
FILES={'bus_persistent':'final_bus_persistent.tsv','bus_reset':'final_bus_reset.tsv','bus_zero':'final_bus_zero.tsv','bus_guard':'final_bus_guard.tsv','bus_coldB':'final_bus_coldB.tsv','bus_stationary':'final_bus_stationary.tsv','gtsi_persistent':'final_gtsi.tsv','bus_repeat':'repeat/bus'}
N=0
def check(ok,msg):
 global N
 N+=1
 if not ok:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def fields(row):return dict(s.split('=',1) for s in row['detail'].split(';') if '=' in s)
def unpack(b,fmt,off=0):return struct.unpack_from('<'+fmt,b,off)
def gram(b,off):
 f=unpack(b,'9f',off)
 return [sum(f[3*i+k]*f[3*j+k] for k in range(3)) for i in range(3) for j in range(i,3)]
def near(a,b,tol=1e-7):return all(math.isclose(x,y,rel_tol=tol,abs_tol=tol) for x,y in zip(a,b))
def emit_tsv(rows):
 out=io.StringIO(newline='');w=csv.DictWriter(out,fieldnames=['experiment','scenario','kind','pc','detail'],delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(rows);return out.getvalue().encode()
def load_events(p):return list(csv.DictReader(p.open(),delimiter='\t'))
def pe_bytes(pe,va,n):
 at=unpack(pe,'I',0x3c)[0];check(pe[at:at+4]==b'PE\0\0','PE signature')
 count=unpack(pe,'H',at+6)[0];size=unpack(pe,'H',at+20)[0];image=unpack(pe,'I',at+24+28)[0];rva=va-image
 for i in range(count):
  p=at+24+size+i*40;vsize,start,rawsize,raw=unpack(pe,'4I',p+8)
  if start<=rva<start+max(vsize,rawsize):return pe[raw+rva-start:raw+rva-start+n]
 raise ValueError(hex(va))
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run',type=pathlib.Path,required=True);ap.add_argument('--private',type=pathlib.Path);ap.add_argument('--exe',type=pathlib.Path);ap.add_argument('--gzf',type=pathlib.Path);ap.add_argument('--zfs',type=pathlib.Path);ap.add_argument('--emit',action='store_true');a=ap.parse_args();run=a.run;ev=run/'evidence';rows=[]
 if a.private:
  for name,file in FILES.items():
   for r in load_events(a.private/file):
    if r['kind'] in KEEP:rows.append(dict(experiment=name,**r))
  data=emit_tsv(rows)
  if a.emit:(ev/'camera_events.tsv').write_bytes(data)
  check((ev/'camera_events.tsv').read_bytes()==data,'private source to exact public filtered trace')
 else:rows=load_events(ev/'camera_events.tsv')
 by={name:[r for r in rows if r['experiment']==name] for name in FILES};samples={};summaries=[]
 for name,rr in by.items():
  get=lambda kind:[r for r in rr if r['kind']==kind]
  check(len(get('NATIVE_ROOT_CTOR'))==1,name+' original root')
  check(len(get('NATIVE_WORLD_REGISTRATION'))==1,name+' registration')
  d=fields(get('NATIVE_WORLD_REGISTRATION')[0]);check(d['entry']=='00542830' and d['owner']=='26000000' and d['countAfter']=='1',name+' registry owner')
  d=fields(get('VLOC_ATTACHMENT_FIELDS')[0]);check(d['class']=='00000028' and d['parent']=='27000A00' and d['root']=='26000000',name+' native VLOC')
  check(len([r for r in get('RETURN') if r['pc']=='00493C50'])==1,name+' original math initializer returns')
  count=2 if name=='bus_coldB' else 8;check(len(get('CAMERA_RETURN'))==count,name+' full normal return count')
  check(all(r['pc']=='70000000' for r in get('CAMERA_RETURN')),name+' return sentinel')
  sample={(int(fields(r)['frame']),fields(r)['phase']):fields(r) for r in get('SAMPLE')};samples[name]=sample
  check(len(sample)==2*count,name+' complete samples')
  for f in range(count):
   before=sample[f,'before'];after=sample[f,'after'];b=bytes.fromhex(before['camera']);z=bytes.fromhex(after['camera']);sb=bytes.fromhex(before['smooth']);sz=bytes.fromhex(after['smooth']);root=bytes.fromhex(before['root'])
   check(len(b)==len(z)==472,name+' full 118 dwords')
   check(before['root']==after['root'],name+' native camera preserves controlled pose')
   check(before['dt']=='3C83126F' and before['velocity']=='00000040000000000000803f',name+' explicit frame/velocity')
   if f and name not in ('bus_reset',):
    check(before['camera']==sample[f-1,'after']['camera'] and before['smooth']==sample[f-1,'after']['smooth'],name+' persistent boundary')
   # Replay only original changed-dword events; every byte of output must be accounted for.
   state={C+i:b[i:i+4] for i in range(0,472,4)}
   state.update({0x4c2964+i:sb[i:i+4] for i in range(0,24,4)})
   state.update({0x52b93c+i:sb[24+i:28+i] for i in range(0,12,4)})
   writes=[r for r in get('NATIVE_CHANGED_DWORD') if int(fields(r)['frame'])==f]
   for r in writes:
    d=fields(r);addr=int(d['address'],16)
    check(addr in state and state[addr].hex()==d['before'],name+' write chronology '+r['pc'])
    check(0x400000<=int(r['pc'],16)<0x4bc000,name+' retail writer PC')
    state[addr]=bytes.fromhex(d['after'])
   check(b''.join(state[C+i] for i in range(0,472,4))==z,name+' original writes explain entire camera')
   check(b''.join(state[0x4c2964+i] for i in range(0,24,4))+b''.join(state[0x52b93c+i] for i in range(0,12,4))==sz,name+' original writes explain smoothing')
   views=unpack(z,'6d',0x160);g=gram(z,0x40);poseg=gram(root,0);finite=sum(math.isfinite(x) for x in views)
   if name=='bus_guard':
    check(not writes and b==z and sb==sz,name+' guard no camera/smoothing writes')
    check(not [r for r in get('CAMERA_SOURCE') if int(fields(r)['frame'])==f],name+' guard no source')
   else:
    src=[r for r in get('CAMERA_SOURCE') if int(fields(r)['frame'])==f];check(len(src)==1,name+' original source')
    s=bytes.fromhex(fields(src[0])['bytes']);check(z[0x160:0x178]==s[40:64],name+' exact source translation copy')
    check(len([r for r in get('ROOT_READ_ANCHOR') if int(fields(r)['frame'])==f])==6,name+' source pose-read anchors')
    if name=='bus_zero':check(finite==0,name+' degenerate gives 6 invalid doubles')
    else:
     check(finite==6,name+' finite six doubles')
     check(near(poseg,[1,0,0,1,0,1],1e-12),name+' controlled valid root Gram')
     check(near(g,[1,0,0,1,0,1],1e-4),name+' bounded near-unit view Gram')
     rot=unpack(s,'9f');pos=unpack(s,'3d',40);inv=unpack(z,'9f',0x40)
     check(near(inv,[rot[j*3+i] for i in range(3) for j in range(3)],0),name+' original inverse basis transpose')
     check(near(unpack(z,'3d',0x68),[-sum(pos[k]*rot[j*3+k] for k in range(3)) for j in range(3)],1e-12),name+' inverse translation')
     for corner in range(4):
      p=unpack(z,'3f',0x130+corner*12);out=unpack(z,'3d',0x178+corner*24)
      pred=[sum(p[k]*rot[k*3+j] for k in range(3))+pos[j] for j in range(3)]
      check(near(out,pred,1e-12),name+' original transformed frustum corner')
     points=[pos]+[unpack(z,'3d',0x178+k*24) for k in range(4)]
     center=[(min(p[j] for p in points)+max(p[j] for p in points))/2 for j in range(3)]
     radius=math.sqrt(max(sum((p[j]-center[j])**2 for j in range(3)) for p in points))
     check(near(unpack(z,'3d',0x80),center,1e-12),name+' original five-point bounding center')
     check(near(unpack(z,'d',0x98),[radius],1e-12),name+' original bounding radius')
     # Confirm original 00472D30 output for point (0,0,0), rounded to float32.
     point=[r for r in get('VIEW_POINT') if int(fields(r)['frame'])==f];check(len(point)==1,name+' original view consumer')
     bits=fields(point[0])['result'].split(',');expected=[struct.pack('<f',v).hex() for v in unpack(z,'3d',0x68)]
     check([int(v,16).to_bytes(4,'little').hex() for v in bits]==expected,name+' consumer equals inverse translation at origin')
   summaries.append(dict(experiment=name,frame=f,camera_sha256=sha(z),changed_camera_bytes=sum(x!=y for x,y in zip(b,z)),finite_view_doubles=finite,view=[x if math.isfinite(x) else str(x) for x in views],view_gram=[x if math.isfinite(x) else str(x) for x in g],root_gram=poseg,smoothing_hex=sz.hex(),writer_events=len(writes)))
 p=samples['bus_persistent'];q=samples['bus_stationary'];r=samples['bus_reset'];cold=samples['bus_coldB']
 def cam(x,f):return bytes.fromhex(x[f,'after']['camera'])
 origin=lambda x,f:unpack(cam(x,f),'3d',0x160)
 for f in (2,3):
  check(near([x-y for x,y in zip(origin(p,f),origin(q,f))],[10,20,30],1e-12),'translation-only differential vs time-matched stationary')
  check(p[f,'after']['smooth']==q[f,'after']['smooth'],'translation does not change supplied-velocity smoothing')
  check(near(gram(cam(p,f),0x40),gram(cam(q,f),0x40),0),'translation preserves basis')
 for f in (0,2,4,6):
  check(origin(p,f)==origin(p,f+1),'fixed pose origin stable across consecutive calls')
  check(cam(p,f)!=cam(p,f+1),'persistent fixed-pose camera evolves')
  check(cam(r,f)==cam(r,f+1),'explicit reset removes within-pose evolution')
 # For first four identity-orientation frames, the native smoother follows
 # s_next=s_prev+2*dt*(target-s_prev). Derive the fixed target from first cold step.
 alpha=2*struct.unpack('<f',bytes.fromhex('6f12833c'))[0]
 smooth=[unpack(bytes.fromhex(p[f,'after']['smooth']),'3f',24) for f in range(4)]
 target=[v/alpha for v in smooth[0]]
 for f in range(1,4):check(near(smooth[f],[smooth[f-1][k]+alpha*(target[k]-smooth[f-1][k]) for k in range(3)],2e-9),'source-anchored smoothing recurrence')
 check(cam(p,0)==cam(r,0),'first persistent and reset states agree')
 check(cam(r,2)==cam(cold,0),'cold-B agrees with reset-B')
 check(cam(p,2)!=cam(cold,0),'history-bearing B differs from cold-B')
 check(origin(p,6)==origin(p,0) and cam(p,6)!=cam(p,0),'return to A retains camera history')
 for name in ('bus_persistent','gtsi_persistent'):
  sm=samples[name];a0=origin(sm,0);b0=origin(sm,2);c0=origin(sm,4)
  check(near([b0[i]-a0[i] for i in range(3)],[10,20,30],1e-12),name+' translated attachment origin')
  check(near(c0,[10+a0[2],20+a0[1],30-a0[0]],1e-12),name+' 90-degree controlled root rotates attachment origin')
 check([dict(r,experiment='bus_persistent') for r in by['bus_repeat']]==by['bus_persistent'],'independent fresh-project repeat events identical')
 summary=json.dumps(summaries,indent=2,allow_nan=False).encode()+b'\n'
 if a.emit:(ev/'numerics.json').write_bytes(summary)
 check((ev/'numerics.json').read_bytes()==summary,'independently derived numerical summary')
 if a.exe:
  pe=a.exe.read_bytes();check(sha(pe)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','retail PE SHA256')
  anchors=list(csv.DictReader((ev/'opcode_anchors.tsv').open(),delimiter='\t'))
  for r in anchors:check(pe_bytes(pe,int(r['va'],16),len(bytes.fromhex(r['hex'])))==bytes.fromhex(r['hex']),'PE opcode '+r['va'])
  writers={r['pc'] for r in rows if r['kind']=='NATIVE_CHANGED_DWORD'};check(writers<={r['va'] for r in anchors},'all changed-state writer opcodes anchored')
 for path,digest,label in ((a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','GZF'),(a.zfs,'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','ZFS')):
  if path:check(sha(path.read_bytes())==digest,label+' SHA256')
 if a.private:
  check((a.private/FILES['bus_persistent']).read_bytes()==(a.private/FILES['bus_repeat']).read_bytes(),'full private repeat byte identity')
  prov=json.loads((ev/'provenance.json').read_text())
  for name,file in FILES.items():check(sha((a.private/file).read_bytes())==prov['private_traces'][name]['sha256'],'trace provenance '+name)
  for r in prov['fixtures']:check(sha((a.private/'fixtures'/r['name']).read_bytes())==r['sha256'],'fixture digest '+r['name'])
  check(sha((run/'scripts/I76_CameraContinuityProbe.java').read_bytes())==prov['measured_probe_sha256'],'measured probe identity')
 print(json.dumps({'status':'passed','assertions':N,'experiments':len(by),'camera_calls':len(summaries),'source_verification':bool(a.private),'private_identity_verification':bool(a.exe and a.gzf and a.zfs)}))
if __name__=='__main__':main()
