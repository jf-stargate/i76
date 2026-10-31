#!/usr/bin/env python3
"""Independent retail-source, command, fixed-point edge, plane and packed-span verifier."""
import argparse,copy,csv,hashlib,importlib.util,json,math,struct,sys
from pathlib import Path
sys.dont_write_bytecode=True
N=0
def ck(ok,why):
 global N
 N+=1
 if not ok:raise AssertionError(why)
def sha(b):return hashlib.sha256(b).hexdigest()
def fields(r):return dict(v.split('=',1) for v in r['detail'].split(';') if '=' in v)
def unpack(b,fmt,off=0):return struct.unpack_from('<'+fmt,b,off)
def low(v):return unpack(struct.pack('<d',v),'I')[0]
def f32(v):return unpack(struct.pack('<f',v),'f')[0]
def near(a,b):return math.isclose(a,b,rel_tol=3e-5,abs_tol=3e-5)
def module(path,name):
 spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
def collect(work,upstream):
 result={}
 for case in ['visible','behind','repeat','flush','flush_repeat']:
  rows=list(csv.DictReader((work/(case+'.tsv')).open(),delimiter='\t'))
  writers={r['pc'] for r in rows if r['kind']=='DRAW_STORE_BYTE'}
  keep=[]
  for r in rows:
   k=r['kind']
   if k=='DRAW_INSTRUCTION' and r['pc'] not in writers and not (0x47ce40<=int(r['pc'],16)<=0x47cfb3 or 0x472ee0<=int(r['pc'],16)<=0x472f16 or 0x472f20<=int(r['pc'],16)<=0x472fc1 or 0x48d140<=int(r['pc'],16)<=0x48d2dd):continue
   if k.startswith(('DRAW_','COMMAND_','EDGE_','MATRIX_','WORKSPACE_')) or k in {'FLUSH_COMMAND','RASTER_CALLBACK_BOUNDARY','BOUNDARY_STOP'} or k in upstream.SAFE|{'NATIVE_PREPARE_ENTER','NATIVE_PREPARE_RETURN','PREPARE_INSTRUCTION','PREPARE_DWORD','DISPATCH_CALL','FALLBACK_ORIGINAL_ENTER','FALLBACK_ORIGINAL_RETURN','ORIGINAL_FAILURE'} or k=='RETURN' and r['pc'] in {'00493C50','004572B0','0048F9B0','00457FF0','0048FAC0'}:
    if k in {'SERVICE_STRICMP','SERVICE_MEMCPY'} and 'producer=true' not in r['detail']:continue
    keep.append(r)
  result[case]=keep
 return result

def verify(data,repo,retail):
 old=repo/'agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6'
 pv=module(old/'scripts/verify_polygon.py','polygon_oracle')
 # Use the accepted source/camera/projection oracle only. Its terminal placeholder
 # row is normalized to the actual native callback argument event; native output
 # verification below does not call the accepted draw substitution or its code.
 adapted={}
 for case in ['visible','behind','repeat']:
  rr=[]
  for r in data['cases'][case]:
   r=r.copy()
   if r['kind']=='DRAW_ENTER':
    d=fields(r);r['kind']='SERVICE_DRAW';r['detail']='count='+str(int(d['args'].split(',')[2],16))+';vertices='+d['vertices']
   rr.append(r)
  adapted[case]=rr
 source_checks_before=pv.N
 pv.verify({'source_vertex_excerpt':data['source_vertex_excerpt'],'cases':adapted},json.loads((old/'evidence/retail_dispatch.json').read_text()))
 ck(data['cases']['visible']==data['cases']['repeat'],'fresh original command/edge trace exact repeat')
 ck(data['cases']['flush']==data['cases']['flush_repeat'],'fresh finalizer/span trace exact repeat')
 anchors={x['va']:x for x in retail['instructions']}
 constants=retail['constants'];one=unpack(bytes.fromhex(constants['004BE778']),'f')[0];scale=unpack(bytes.fromhex(constants['004FA48C']),'f')[0];stepbias=unpack(bytes.fromhex(constants['004F9D84']),'f')[0];xbias=unpack(bytes.fromhex(constants['004F9D88']),'d')[0]
 summaries={}
 for case,rr in data['cases'].items():
  get=lambda k:[r for r in rr if r['kind']==k]
  ck(not get('ORIGINAL_FAILURE') and len(get('PRODUCER_COMPLETE'))==1,case+' original scene completes')
  ck(not any(r['pc']=='0047CE40' for r in get('SERVICE_DRAW')),case+' CE40 never substituted')
  ck(len(get('WORKSPACE_INITIALIZED'))==1,case+' original startup workspace initializer')
  init=fields(get('WORKSPACE_INITIALIZED')[0])['context'].split(',');ck(int(init[13],16)==128 and int(init[12],16)==0x58da94,case+' original capacity and output-list tail')
  if case=='behind':
   ck(not get('DRAW_ENTER') and not get('COMMAND_BEFORE') and not get('EDGE_ENTER'), 'behind-camera original cull prevents all draw output')
   summaries[case]={'commands':0,'edges':0,'visibility':'original rejection'};continue
  enters=get('DRAW_ENTER');rets=get('DRAW_RETURN');before=get('COMMAND_BEFORE');initialized=get('COMMAND_INITIALIZED');edges=get('EDGE_ENTER');edgeouts=get('EDGE_RETURN');matrices=get('MATRIX_ENTER');matrixouts=get('MATRIX_RETURN')
  ck(len(enters)==len(rets)==len(before)==len(initialized)==len(matrices)==len(matrixouts)==2,case+' two original native commands and planes')
  ck(len(edges)==len(edgeouts)==4,case+' four original edges')
  ck([r['pc'] for r in rets]==['004721B3']*2,case+' original CE40 returns to wrapper')
  state={};allocations={};last_instruction=None;instruction_count=0
  for r in rr:
   d=fields(r);k=r['kind']
   if k=='DRAW_HEAP_BACKING':
    base=int(d['address'],16);size=int(d['size']);ck(all(base>=p+n+16 or base+size+16<=p for p,n in allocations.items()),'disjoint guarded heap backing')
    allocations[base]=size;state.update({base+i:0 for i in range(size)})
   if k=='DRAW_INSTRUCTION':
    last_instruction=r;instruction_count+=1;ck(r['pc'] in anchors,'executed original draw opcode has retail evidence')
   if k=='DRAW_STORE_BYTE':
    addr=int(d['address'],16);v=int(d['before']);w=int(d['after']);ck(last_instruction is not None and last_instruction['pc']==r['pc'],'retired original writer chronology')
    ck(addr in state or 0x58da68<=addr<0x58dac4 or 0x4f9d7c<=addr<0x4f9d84,'output store belongs to allocation or raster globals')
    if addr in state:ck(state[addr]==v,'retired byte before agrees with independently replayed memory')
    state[addr]=w
   if k in {'COMMAND_INITIALIZED','DRAW_RETURN','EDGE_RETURN','FLUSH_COMMAND'}:
    base=int(d.get('address',d.get('command','0')),16);out=bytes.fromhex(d['bytes']);ck(all(state.get(base+i)==v for i,v in enumerate(out)),'original retired stores reproduce full output bytes')
   if k=='FLUSH_COMMAND':
    base=int(d['spanAddress'],16);out=bytes.fromhex(d['spans']);ck(all(state.get(base+i)==v for i,v in enumerate(out)),'retired original stores reproduce packed span buffer')
  command_summaries=[]
  for ix,(en,re,bi,ini,me,mo) in enumerate(zip(enters,rets,before,initialized,matrices,matrixouts)):
   e,d,b0,ini,m,mout=map(fields,[en,re,bi,ini,me,mo]);args=[int(v,16) for v in e['args'].split(',')];cmd=int(d['command'],16);out=bytes.fromhex(d['bytes']);words=unpack(out,'24I')
   ck(args[0]==0x5dcec0 and args[2]==4 and args[3]==0,'exact authentic descriptor, polygon count and color argument')
   ck(cmd==int(b0['address'],16)==int(ini['address'],16) and len(out)==96,'exact original command address and 0x60 size')
   ck(any(p<=cmd and cmd+96<=p+n and n==65536 for p,n in allocations.items()),'command belongs to original allocated raster arena')
   initial=unpack(bytes.fromhex(ini['bytes']),'24I');ck(initial[0]==args[3] and initial[2]==0x47cb00 and initial[7]==0 and initial[10]==0xffffffff and initial[11]==0 and initial[13]==4*(ix+1),'exact command constructor fields and serial')
   ck(words[0]==args[3] and words[2]==0x47cb00 and words[13]==4*(ix+1) and words[11]==0 and words[10]==0xffffffff,'persistent deferred command, no pre-finalizer packed spans')
   vertices=[unpack(bytes.fromhex(e['vertices']),'6f',24*j) for j in range(4)]
   ck(any(fields(x)['dst']==e['vertices'] for x in get('FALLBACK_ORIGINAL_RETURN')),'draw input exactly matches original clip output')
   tri=[unpack(bytes.fromhex(m['vertices']),'6f',24*j) for j in range(3)];ck(all(v in vertices for v in tri),'interpolation triangle selected from authentic polygon')
   x0,y0=tri[0][:2];x1,y1=tri[1][:2];x2,y2=tri[2][:2];det=(x1-x0)*(y2-y0)-(x2-x0)*(y1-y0)
   expected=[[(x1*y2-x2*y1)/det,(y1-y2)/det,(x2-x1)/det],[(x2*y0-x0*y2)/det,(y2-y0)/det,(x0-x2)/det],[(x0*y1-x1*y0)/det,(y0-y1)/det,(x1-x0)/det]]
   actual=unpack(bytes.fromhex(mout['bytes']),'9f')
   # Independent algebraic inverse, honoring measured float32 spill boundaries.
   # p20/p12 remain in x87 while the other four coordinate products are spilled.
   p20=x2*y0;p12=x1*y2;p21=f32(x2*y1);p02=f32(x0*y2);p01=f32(x0*y1);p10=f32(x1*y0)
   inv=1/(((((p20+p12-p21)-p02)+p01)-p10));inv32=f32(inv)
   predicted=list(map(f32,[(p12-p21)*inv,(y1-y2)*inv32,(x2-x1)*inv32,(f32(p20)-p02)*inv32,(y2-y0)*inv32,(x0-x2)*inv32,(p01-p10)*inv32,(y0-y1)*inv32,(x1-x0)*inv32]))
   ck(struct.pack('<9f',*predicted)==bytes.fromhex(mout['bytes']),'exact independent barycentric inverse with original float32 spills')
   shade=[f32(one-v[5])*scale for v in tri];plane=[sum(shade[j]*expected[j][k] for j in range(3)) for k in range(3)]
   measured=[unpack(out,'f',offset)[0] for offset in [0x18,0x58,0x5c]]
   arithmetic_plane=[f32(sum(shade[j]*predicted[3*j+k] for j in range(3))) for k in range(3)]
   ck(struct.pack('<3f',*measured)==struct.pack('<3f',*arithmetic_plane),'exact independent shade plane from source polygon and spill-aware inverse')
   ylo,yhi=round(min(v[1] for v in vertices)),round(max(v[1] for v in vertices));ck(words[12]==yhi-ylo,'exact original scanline extent')
   actual_edges=[]
   for ee,eo in zip(edges[2*ix:2*ix+2],edgeouts[2*ix:2*ix+2]):
    a,b=fields(ee),fields(eo);aa=[int(v,16) for v in a['args'].split(',')];v=unpack(bytes.fromhex(a['start']),'6f');w=unpack(bytes.fromhex(a['end']),'6f');edge=unpack(bytes.fromhex(b['bytes']),'8I');ptr=int(a['address'],16)
    ck(v in vertices and w in vertices and aa[0]==cmd,'edge source and command ownership')
    ck(ptr==int(b['address'],16) and ptr in [words[8],words[9]],'command points to original 0x20-byte edge')
    slope=(w[0]-v[0])/(w[1]-v[1]);step=(low(stepbias+slope)+1)&0xfffffffe;x=(low(v[0]+(aa[3]-v[1])*slope+xbias)+1)&0xfffffffe
    ck(edge[0]==x and edge[6]==step,'exact independently computed fixed-point x and delta')
    ck(edge[2]==0 and edge[3]==cmd and edge[4]==aa[3]==ylo and edge[7]==aa[4]==yhi,'exact edge metadata and scanline endpoints')
    ck(unpack(bytes.fromhex(b['bytes']),'I',20)[0]==unpack(bytes.fromhex(a['start']),'I',8)[0],'exact source reciprocal depth edge copy')
    actual_edges.append((ptr,edge))
   command_summaries.append({'address':f'{cmd:08X}','bytes':96,'callback':'0047CB00','y_start':ylo,'y_end_exclusive':yhi,'shade_plane':measured,'ideal_shade_plane':plane,'matrix_and_plane_comparison':'exact float32 bits for this corpus','edges':[f'{p:08X}' for p,_ in actual_edges]})
   if case.startswith('flush'):
    final=fields(get('FLUSH_COMMAND')[ix]);fb=bytes.fromhex(final['bytes']);fw=unpack(fb,'24I');packed=list(unpack(bytes.fromhex(final['spans']),str(len(bytes.fromhex(final['spans']))//4)+'I'))
    ck(fw[2]==0x47cb00 and fw[13]==words[13] and fw[8:10]==words[8:10] and fw[6]==words[6] and fw[22:24]==words[22:24],'finalizer preserves callback, edge and shade ownership')
    ck(packed[0]==0xffffffff and fw[11]==int(final['spanAddress'],16) and fw[12]-fw[11]==4*(yhi-ylo),'exact span-list address, leading sentinel and reserved extent')
    # The consumer's first instruction installs command+0x28 at the last slot.
    # Inspect its logical stream without claiming that instruction has executed.
    native=packed[1:-1]+[fw[10]];expected_spans=[]
    left,right=sorted([e for _,e in actual_edges],key=lambda e:e[0])
    for y in range(ylo,yhi):
     xl=((left[0]+left[6]*(y-ylo))&0xffffffff)>>21;xr=((right[0]+right[6]*(y-ylo))&0xffffffff)>>21
     if xl<xr:expected_spans.append((xl<<21)|((xr-xl)<<10)|y)
    ck(native==expected_spans,'exact independently recomputed packed scanline spans')
    ck(fw[1]==(int(fields(get('FLUSH_COMMAND')[ix+1])['address'],16) if ix==0 else 0),'original persistent draw-list links and final terminator')
    command_summaries[-1]['packed_spans']=[{'y':p&1023,'x':p>>21,'length':(p>>10)&2047} for p in native]
  if case.startswith('flush'):
   boundary=get('RASTER_CALLBACK_BOUNDARY');ck(len(boundary)==1 and boundary[0]['pc']=='0047CB00','exact pre-pixel callback boundary')
   d=fields(boundary[0]);ck(d['args']==command_summaries[0]['address']+',005DCEC0','consumer receives original command and inherited descriptor')
   desc=unpack(bytes.fromhex(d['descriptor']),'16I');ck(desc[0]==0 and desc[5]==0 and desc[7]==0,'missing original framebuffer pitch/base state measured')
   ck(len(get('BOUNDARY_STOP'))==1 and not any(r['pc']=='00473640' for r in get('RETURN')),'finalizer explicitly stopped, never reported returned')
  summaries[case]={'commands':command_summaries,'original_retained_instructions':instruction_count,'allocation_bytes':sum(allocations.values()),'allocation_count':len(allocations),'pixels_written':False}
 return {'cases':summaries,'source_projection_assertions':pv.N-source_checks_before}

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--source-repo',type=Path,required=True);ap.add_argument('--private',type=Path);ap.add_argument('--evidence',type=Path);ap.add_argument('--exe',type=Path);ap.add_argument('--emit',action='store_true');ap.add_argument('--corruptions',action='store_true');a=ap.parse_args();run=Path(__file__).resolve().parents[1];ev=run/'evidence'
 upstream=module(a.source_repo/'agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/scripts/verify_integration.py','integration_oracle')
 data={'source_vertex_excerpt':(a.private/'baseline/fixtures/xb11bdym.geo').read_bytes()[36:228].hex(),'cases':collect(a.private,upstream)} if a.emit else json.loads((a.evidence or ev/'draw_events.json').read_text());retail=json.loads((ev/'retail_opcodes.json').read_text())
 if a.private:
  ck(data['cases']==collect(a.private,upstream),'exact regenerated original trace selection')
  for c,r in [('visible','repeat'),('flush','flush_repeat')]:ck((a.private/(c+'.tsv')).read_bytes()==(a.private/(r+'.tsv')).read_bytes(),'full private fresh import trace equality')
  accepted=list(csv.DictReader((a.private/'baseline/native_visible.tsv').open(),delimiter='\t'))
  def prefix(rows):
   keys=upstream.SAFE|{'NATIVE_PREPARE_ENTER','NATIVE_PREPARE_RETURN','PREPARE_INSTRUCTION','PREPARE_DWORD','DISPATCH_CALL','FALLBACK_ORIGINAL_ENTER','FALLBACK_ORIGINAL_RETURN','ORIGINAL_FAILURE'};rr=[r for r in rows if r['kind'] in keys or r['kind']=='RETURN' and r['pc'] in {'00493C50','004572B0','0048F9B0','00457FF0','0048FAC0'}];rr=[r for r in rr if r['kind'] not in {'SERVICE_STRICMP','SERVICE_MEMCPY'} or 'producer=true' in r['detail']];end=next(i for i,r in enumerate(rr) if r['kind']=='QUEUE_SNAPSHOT' and fields(r)['phase']=='produced');return rr[:end+1]
  ck(prefix(accepted)==prefix(data['cases']['visible']),'unchanged accepted scene/camera/queue chronology through produced polygon')
 if a.exe:
  b=a.exe.read_bytes();ck(sha(b)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','retail EXE identity');pv=module(a.source_repo/'agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/scripts/verify_polygon.py','pe_reader')
  for item in retail['instructions']:ck(pv.pe_slice(b,int(item['va'],16),len(bytes.fromhex(item['hex']))).hex()==item['hex'],'independent retail opcode '+item['va'])
  for va,h in retail['constants'].items():ck(pv.pe_slice(b,int(va,16),len(bytes.fromhex(h))).hex()==h,'retail arithmetic constant')
 result=verify(data,a.source_repo,retail)
 if a.emit:(ev/'draw_events.json').write_text(json.dumps(data,separators=(',',':'))+'\n');(ev/'numerical_results.json').write_text(json.dumps(result,indent=2)+'\n')
 else:ck(result==json.loads((ev/'numerical_results.json').read_text()),'independent numerical results match published artifact')
 positive_count=N
 if a.corruptions:
  rejected=[]
  for name in ['command_callback','edge_delta','shade_plane','packed_span','writer_order','source_polygon']:
   bad=copy.deepcopy(data)
   cases=['visible','repeat'] if name not in ['packed_span'] else ['flush','flush_repeat']
   for case in cases:
    rr=bad['cases'][case];kind={'command_callback':'COMMAND_INITIALIZED','edge_delta':'EDGE_RETURN','shade_plane':'DRAW_RETURN','packed_span':'FLUSH_COMMAND','writer_order':'DRAW_STORE_BYTE','source_polygon':'DRAW_ENTER'}[name];r=next(r for r in rr if r['kind']==kind);d=fields(r)
    if name=='writer_order':r['pc']='0047CE40'
    else:
     key='spans' if name=='packed_span' else 'vertices' if name=='source_polygon' else 'bytes';blob=bytearray.fromhex(d[key]);off={'command_callback':8,'edge_delta':24,'shade_plane':24,'packed_span':4,'source_polygon':0}[name];blob[off]^=1;r['detail']=r['detail'].replace(key+'='+d[key],key+'='+blob.hex())
   try:verify(bad,a.source_repo,retail)
   except AssertionError as err:rejected.append({'mutation':name,'rejected':True,'reason':str(err)})
   else:raise AssertionError('corruption accepted '+name)
  if a.emit:(ev/'negative_controls.json').write_text(json.dumps(rejected,indent=2)+'\n');(ev/'corrupted_sample.json').write_text(json.dumps(bad,separators=(',',':'))+'\n')
  print(json.dumps({'corruptions':rejected}))
 print(json.dumps({'status':'passed','assertions':positive_count,'native_cases':5,'source_projection_assertions':result['source_projection_assertions']}))
if __name__=='__main__':main()
