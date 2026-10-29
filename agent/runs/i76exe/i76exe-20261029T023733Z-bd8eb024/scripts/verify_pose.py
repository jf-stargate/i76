#!/usr/bin/env python3
"""Validate run-owned original-instruction traces against authenticated source data.
This is an experimental comparator, not an engine implementation.
"""
import argparse,csv,hashlib,json,math,struct,subprocess
from pathlib import Path

def fields(x): return dict(y.split('=',1) for y in x['detail'].split(';') if '=' in y)
def rows(p):
    with p.open() as f:return list(csv.DictReader(f,delimiter='\t'))
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def fhex(x):return struct.unpack('<f',struct.pack('<I',int(x,16)))[0]
def ext80(h):
    v=int(h,16);e=(v>>64)&32767
    n=0.0 if v==0 else math.ldexp(float(v&((1<<64)-1)),e-16383-63)
    return -n if v>>79 else n

def main():
    p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--source-run',type=Path,required=True);p.add_argument('--private',type=Path,required=True)
    for k in ['exe','gzf','zfs','msn','ter','x87-service']:p.add_argument('--'+k,type=Path,required=True)
    p.add_argument('--emit',action='store_true',help='write safe derived evidence; otherwise compare it')
    a=p.parse_args();count=0
    def check(v,msg):
        nonlocal count;count+=1
        if not v:raise AssertionError(str(count)+': '+msg)
    cmd=['python3',str(a.source_run/'scripts/verify_authentic_terrain.py'),'--run',str(a.source_run),'--private',str(a.private)]
    for k in ['exe','gzf','zfs','msn','ter','x87-service']:cmd+=['--'+k,str(getattr(a,k.replace('-','_')))]
    baseline=json.loads(subprocess.run(cmd,capture_output=True,text=True,check=True).stdout)
    check(baseline['test_count']==baseline['passed_count']==35452,'unchanged accepted baseline verifier')
    msn=a.msn.read_bytes();ter=a.ter.read_bytes();zi=msn.index(b'ZMAP');zm=msn[zi+9:zi+6409]
    def word(ix,iz):
        check(0<=ix<10240 and 0<=iz<10240,'source grid domain')
        zone=zm[(iz//128)*80+ix//128];check(zone!=255,'active authentic page')
        off=zone*32768+2*((iz%128)*128+ix%128)
        return struct.unpack_from('<H',ter,off)[0]
    def height(x,z):
        sx=x*f32(.2);sz=z*f32(.2);ix=math.floor(sx);iz=math.floor(sz);fx=sx-ix;fz=sz-iz
        v=[word(ix+dx,iz+dz)&4095 for dx,dz in [(0,0),(1,0),(0,1),(1,1)]]
        lo=f32(v[0]+(v[1]-v[0])*fx);hi=f32(v[2]+(v[3]-v[2])*fx)
        return (lo+(hi-lo)*fz)*f32(.1)
    expected=bytearray(struct.pack('<I',0x0059c588)*16384)
    for iz in range(80):
        for ix in range(80):
            zone=zm[iz*80+ix]
            if zone!=255:struct.pack_into('<I',expected,4*((iz+24)*128+ix+24),0x40000000+zone*32768)
    cases={};traces={};selected=[];frames_out=[];normal_out=[];read_examples=[];hardware=[];answers=[]
    for name,dy in [('control',0),('lower',-.25),('lower_repeat',-.25),('raised',1)]:
        path=a.private/(name+'.tsv');r=rows(path);traces[name]=r;ev=lambda kind:[x for x in r if x['kind']==kind]
        check((a.private/(name+'.tsv.grid.bin')).read_bytes()==expected,'all page pointers '+name)
        check(not ev('POSE_CLASS_CALLBACK_ERROR') and not ev('NATIVE_reporter_RET'),'no callback or original reporter errors')
        pose=fields(ev('CONTROLLED_POSE')[0]);check(float(pose['y'])==31.5+dy and float(pose['x'])==2952.5 and float(pose['z'])==48152.5,'one controlled pose dimension')
        check(len(ev('FILTER_INIT_RETURN'))==len(ev('HARDWARE_FCOS'))==4,'original filter and localized FCOS')
        check([x['detail'].split(';frame=')[0] for x in ev('FILTER_INIT_RETURN')]==[x['detail'].split(';frame=')[0] for x in traces['control'] if x['kind']=='FILTER_INIT_RETURN'],'unchanged original filter coefficients')
        initial=fields(ev('POSE_BEFORE_FRAME')[0]);src=msn[0xacf6+16:0xacf6+52].hex()
        check(''.join(bytes.fromhex(h)[::-1].hex() for h in initial['rootBasis'].split(',')[:9])==src,'authentic nine-float spawn orientation')
        heights=[];normal_reads=[];normal_active=False;normal_errors=[];normal_norms=[];read_count=0;reads_by_frame={}
        for index,x in enumerate(r):
            d=fields(x);kind=x['kind']
            if kind=='TERRAIN_NORMAL_ENTER':normal_reads=[];normal_active=True
            if kind=='TERRAIN_NATIVE_READ':
                off=int(d['offset'],16);check(0<=off<=len(ter)-2 and int(d['address'],16)==0x40000000+off,'original mapped address')
                check(int(d['word'],16)==struct.unpack_from('<H',ter,off)[0],'original source uint16')
                if normal_active:normal_reads.append((off,int(d['word'],16)))
                frame=int(d['frame']);reads_by_frame[frame]=reads_by_frame.get(frame,0)+1
                if read_count<4 or frame in [0,14,26,31] and reads_by_frame[frame]<=2:read_examples.append({'test':name,'pc':x['pc'],**d})
                read_count+=1
            if kind in ['HEIGHT_RETURN','TERRAIN_SAMPLE']:
                err=abs(float(d['height'])-height(float(d['x']),float(d['z'])));heights.append(err);check(err<2e-5,'independent bilinear oracle')
                if 'material' in d:check(int(d['material'])==word(round(float(d['x'])*f32(.2)),round(float(d['z'])*f32(.2)))>>13,'source material')
            if kind=='TERRAIN_MATERIAL_RETURN':check(int(d['material'])==word(round(float(d['x'])*f32(.2)),round(float(d['z'])*f32(.2)))>>13,'original contact material')
            if kind=='TERRAIN_NORMAL_RETURN':
                check(len(normal_reads)==3,'three original triangle source reads')
                # Independent geometric plane normal from the three actual source locations.
                check(len({off//32768 for off,_ in normal_reads})==1,'normal triangle on one authentic page in this pose test')
                pts=[((off%32768//2)%128*5,(v&4095)*.1,(off%32768//2)//128*5) for off,v in normal_reads]
                u=[pts[1][j]-pts[0][j] for j in range(3)];v=[pts[2][j]-pts[0][j] for j in range(3)]
                n=[u[1]*v[2]-u[2]*v[1],u[2]*v[0]-u[0]*v[2],u[0]*v[1]-u[1]*v[0]]
                if n[1]<0:n=[-q for q in n]
                length=math.sqrt(sum(q*q for q in n));oracle=[q/length for q in n];got=list(map(fhex,d['normal'].split(',')))
                err=max(abs(q-t) for q,t in zip(got,oracle));norm=abs(sum(q*q for q in got)-1)
                check(err<3e-5 and norm<5e-5,'independent triangle normal within approximate inverse-sqrt tolerance')
                normal_errors.append(err);normal_norms.append(norm);normal_active=False
                normal_out.append({'test':name,'pc':x['pc'],**d,'oracle':','.join(map(str,oracle)),'max_component_error':err,'source_offsets':','.join(hex(off) for off,_ in normal_reads),'source_words':','.join(hex(v) for _,v in normal_reads)})
            if kind=='HARDWARE_FISTP':
                cw=int(d['cw'],16);check(cw&0xc00==0x400,'original round-down control');check(int(d['result'])==math.floor(ext80(d['st0'])),'independent FISTP floor')
                hardware.append(int(d['st0'],16).to_bytes(10,'little')+struct.pack('<H',cw));answers.append(('int',int(d['result'])))
            if kind=='HARDWARE_FCOS':
                check(abs(ext80(d['result'])-math.cos(ext80(d['input'])))<1e-15,'FCOS scalar check')
                hardware.append(int(d['input'],16).to_bytes(10,'little')+struct.pack('<H',int(d['cw'],16)|0x8000));answers.append(('cos',int(d['result'],16)))
        fr=ev('TWO_FRAME_NUMERICAL_RESULT');returns=[x for x in ev('RETURN') if x['pc']=='00463800']
        check(len(fr)==len(returns)==len(ev('SOLVER_ENTER'))==len(ev('SOLVER_RETURN'))==32,'32 callbacks and solvers return')
        check([int(fields(x)['frame']) for x in returns]==list(range(32)),'callback frame chronology')
        for x in ev('SOLVER_ENTER'):check(float(fields(x)['dt'])>0 and fields(x)['substep']=='0','positive original substep')
        for x in ev('POSE_GRAM'):
            b=list(map(fhex,fields(x)['basis'].split(',')));g=[sum(b[i*3+k]*b[j*3+k] for k in range(3)) for i in range(3) for j in range(i,3)]
            check(max(abs(q-t) for q,t in zip(g,[1,0,0,1,0,1]))<1e-4,'typed root Gram matrix')
        tires=ev('TIRE_CONTACT_RETURN');contacts=[x for x in tires if fields(x)['mode']=='0']
        check(len(tires)==128 and contacts and any(abs(float(fields(x)['compression']))>.001 for x in contacts),'original tires and positive nonzero contact branch')
        for x in tires:
            d=fields(x);v=float(d['compression']);check(math.isfinite(float(d['height'])) and float(d['rangeMin'])-1e-6<=v<=float(d['rangeMax'])+1e-6,'finite bounded compression')
        for x in fr:
            d=fields(x);check(d['basisBadF32']==d['positionBadD64']==d['cameraBadD64']=='0','typed finite pose and camera')
            f=int(d['frame']);tt=[fields(t) for t in tires if int(fields(t)['frame'])==f];gp=[fields(t) for t in ev('GROUND_PROBE_RETURN') if int(fields(t)['frame'])==f]
            check(len(tt)==4 and len(gp)==1,'four tire returns and separate special probe per frame')
            frames_out.append({'test':name,'frame':f,'position':d['rootPositionXYZ'],'velocity':fields(ev('POSE_CLASS_CALLBACK_END')[f])['runtimeVelocity'],'flags':d['flags'],'axis_norm_sq':d['axisNormSq'],'tire_modes':','.join(t['mode'] for t in tt),'compressions':','.join(t['compression'] for t in tt),'special_eax':gp[0]['eax']})
        selected.extend({'test':name,'kind':x['kind'],'pc':x['pc'],'detail':x['detail']} for x in ev('HARDWARE_FISTP')[:2]+ev('HARDWARE_FCOS')[:1])
        keep={'CONTROLLED_POSE','TERRAIN_SAMPLE','TERRAIN_NORMAL_RETURN','TERRAIN_MATERIAL_RETURN','FILTER_INIT_RETURN'}
        selected.extend({'test':name,'kind':x['kind'],'pc':x['pc'],'detail':x['detail']} for x in r if x['kind'] in keep or x['kind']=='TIRE_CONTACT_RETURN' and fields(x)['mode']=='0')
        cases[name]={'frames':len(fr),'solver_returns':len(ev('SOLVER_RETURN')),'terrain_reads':read_count,'height_returns':len(ev('HEIGHT_RETURN')),'max_height_error':max(heights),'normal_returns':len(normal_errors),'max_normal_component_error':max(normal_errors),'max_normal_norm_error':max(normal_norms),'tire_returns':len(tires),'mode0_returns':len(contacts),'first_mode0_frame':int(fields(contacts[0])['frame']),'special_positive':sum(fields(x)['eax']!='0' for x in ev('GROUND_PROBE_RETURN')),'compression_min':min(float(fields(x)['compression']) for x in tires),'compression_max':max(float(fields(x)['compression']) for x in tires),'final_position':fields(fr[-1])['rootPositionXYZ'],'trace_sha256':sha(path),'trace_bytes':path.stat().st_size,'fistp_calls':len(ev('HARDWARE_FISTP')),'fcos_calls':len(ev('HARDWARE_FCOS'))}
    check((a.private/'lower.tsv').read_bytes()==(a.private/'lower_repeat.tsv').read_bytes(),'separate invocation byte-identical repeat')
    extra={'CONTROLLED_POSE','TERRAIN_NORMAL_RETURN','TERRAIN_MATERIAL_RETURN'}
    control=[{**x,'detail':x['detail'].rsplit(';frame=',1)[0]} for x in traces['control'] if x['kind'] not in extra]
    check(control==rows(a.private/'publish_bus.tsv'),'instrumented zero-offset control equals accepted baseline events')
    check(cases['lower']['final_position']!=cases['control']['final_position'] and cases['lower']['first_mode0_frame']!=cases['control']['first_mode0_frame'],'new pose changes original state/contact chronology')
    got=subprocess.run([str(a.x87_service.resolve())],input=b''.join(hardware),capture_output=True,check=True).stdout;off=0
    for kind,want in answers:
        size=8 if kind=='int' else 10;check(int.from_bytes(got[off:off+size],'little',signed=kind=='int')==want,'independent hardware request replay');off+=size
    check(off==len(got),'hardware response length')
    derived={'results.json':json.dumps(cases,indent=2)+'\n','selected_events.tsv':None,'frames.tsv':None,'normal_checks.tsv':None,'source_read_examples.json':json.dumps(read_examples,indent=2)+'\n'}
    import io
    for filename,rr in [('selected_events.tsv',selected),('frames.tsv',frames_out),('normal_checks.tsv',normal_out)]:
        s=io.StringIO();writer=csv.DictWriter(s,fieldnames=list(rr[0]),delimiter='\t',lineterminator='\n');writer.writeheader();writer.writerows(rr);derived[filename]=s.getvalue()
    for filename,content in derived.items():
        path=a.run/'evidence'/filename
        if a.emit:path.parent.mkdir(parents=True,exist_ok=True);path.write_text(content)
        else:check(path.read_text()==content,'published derived evidence '+filename)
    print(json.dumps({'status':'passed','test_count':count,'passed_count':count,'notes':'Includes unchanged accepted baseline verifier (35452 checks), all new logged source reads/heights/materials, independent source-triangle normals, typed poses, tire bounds, callback chronology, byte-identical repeat, unchanged control and localized hardware replay. Count excludes nested baseline checks.'},indent=2))
if __name__=='__main__':main()
