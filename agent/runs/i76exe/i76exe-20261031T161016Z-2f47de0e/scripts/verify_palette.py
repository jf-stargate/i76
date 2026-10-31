from pathlib import Path
import argparse,hashlib,math,json,struct
p=argparse.ArgumentParser();p.add_argument('--trace',type=Path,required=True);p.add_argument('--palette',type=Path,required=True);
for key in ['exe','audit','baseline']:p.add_argument('--'+key,type=Path)
a=p.parse_args()
def verify(text,frame,palette):
 rows=[]
 for line in text.splitlines()[1:]:
  s=line.split('\t',3)
  if len(s)==4:rows.append((s[1],s[2],dict(t.split('=',1) for t in s[3].split(';') if '=' in t)))
 assert hashlib.sha256(palette).hexdigest()=='d1f57fdef1029e2f2b41d25c2db52f641ada6d55b89342970c50bc49bd9bccb8'
 setup=[r[2] for r in rows if r[0]=='NATIVE_PALETTE_SETUP'];assert len(setup)==1
 assert setup[0]['palette_sha256']==hashlib.sha256(palette).hexdigest()
 assert setup[0]['cache_sha256']==hashlib.sha256(bytes([255])*32768).hexdigest()
 assert setup[0]['squares_sha256']==hashlib.sha256(b''.join(struct.pack('<I',k*k) for k in range(-256,256))).hexdigest()
 nums=[r[2] for r in rows if r[0]=='NUMERICAL_SERVICE'];assert len(nums)==96
 for r in nums:
  x=int(r['st0'],16);v=math.ldexp(x&((1<<64)-1),((x>>64)&32767)-16383-63)*(-1 if x>>79 else 1)
  assert v==float(r['input']) and int(v)==int(r['output']) and r['control']=='895'
 after=[r[2] for r in rows if r[0]=='NUMERICAL_SERVICE_AFTER'];assert len(after)==96
 for before,end in zip(nums,after):
  assert int(end['sp'],16)==int(before['sp'],16)+4 and end['eip']==before['return']
  assert int(end['eax'],16)==(int(before['output'])&0xffffffff) and int(end['edx'],16)==((int(before['output'])>>32)&0xffffffff)
  assert end['fpu'].split(',')[:7]==before['fpu'].split(',')[1:]
 f32=lambda x:struct.unpack('<f',struct.pack('<f',x))[0]
 curr=[f32(.01)]*3
 delta=[f32((c*f32(1/255)-f32(.01))*f32(.04032258064516129)) for c in palette[:3]]
 computed=[]
 for phase,count in [(0,24),(1,8)]:
  if phase:delta=[f32((1-c)*f32(.05813953488372093)) for c in curr]
  for i in range(count):
   computed.extend(c*255 for c in curr)
   curr=[f32(c+d) for c,d in zip(curr,delta)]
 assert all(float(r['input'])==v for r,v in zip(nums,computed)), 'independent shade arithmetic'
 nearest=[r[2] for r in rows if r[0]=='NEAREST_ENTER'];assert len(nearest)==32
 cache={};values=[]
 for j,r in enumerate(nearest):
  rgb=[int(r[k]) for k in ['r','g','b']];assert rgb==[max(0,min(255,int(v))) for v in computed[j*3:j*3+3]]
  key=tuple(v>>3 for v in rgb)
  if key not in cache:
   # Original search stops at 006435DD: excludes entry 255.
   cache[key]=min(range(255),key=lambda i:sum((rgb[k]-palette[3*i+k])**2 for k in range(3)))
  values.append(cache[key])
 stores=[r for r in rows if r[0]=='TABLE_ORIGINAL_STORE'];assert len(stores)==256
 expected=[]
 for k in range(24):expected.append(('004793A4',0x61d1a0-256*k,values[k]))
 for k in range(8):expected.append(('004794AF',0x61b9a0-256*k,values[24+k]))
 expected += [('004794ED',0x61d2a0+256*k,values[0]) for k in range(112)]
 expected += [('0047950B',0x62b1a0-256*k,values[-1]) for k in range(112)]
 table={}
 for r,(pc,addr,v) in zip(stores,expected):
  assert r[1]==pc and int(r[2]['address'],16)==addr and int(r[2]['value'])==v
  table[addr]=v
 assert len(table)==256
 column=[r[2]['bytes'] for r in rows if r[0]=='TABLE_COLUMN_COMPLETE'];assert len(column)==1
 assert bytes.fromhex(column[0])==bytes(table[0x61b2a0+256*k] for k in range(256))
 assert len(set(values))>=2, 'source-backed shade contrast'
 calls=[r for r in rows if r[0]=='RASTER_RETURN'];assert len(calls)==2
 assert Path(str(a.trace)+'.guards').read_bytes()==bytes([205])*32
 reads=[r for r in rows if r[0]=='RASTER_INSTRUCTION' and r[1]=='0047CC55'];writes=[r for r in rows if r[0]=='RASTER_BYTE_WRITE'];assert len(reads)==len(writes)==210
 expect=bytearray([165])*(640*480)
 for i,(rd,wr) in enumerate(zip(reads,writes)):
  idx=int(rd[2]['edx'],16)+int(rd[2]['ecx'],16);assert idx==7936
  addr=0x3f000000+(313+i//15)*640+233+i%15
  assert wr[1]=='0047CC62' and int(wr[2]['address'],16)==addr and int(wr[2]['after'])==table[0x61b2a0+idx]
  expect[addr-0x3f000000]=table[0x61b2a0+idx]
 assert frame==expect
 return dict(original_table_stores=256,original_pixel_stores=210,index=7936,value=values[0],distinct_table_values=sorted(set(values)),frame_sha256=hashlib.sha256(frame).hexdigest(),arithmetic_limit='exact float32 shade recurrence, conversions, nearest-color and cache independently checked')
t=a.trace.read_text();f=Path(str(a.trace)+'.frame').read_bytes();pal=a.palette.read_bytes();assert len(pal)==768
result=verify(t,f,pal)
if a.exe:
 exe=a.exe.read_bytes();assert hashlib.sha256(exe).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
 import csv
 pe=struct.unpack_from('<I',exe,60)[0];n=struct.unpack_from('<H',exe,pe+6)[0];sections=pe+24+struct.unpack_from('<H',exe,pe+20)[0]
 def pe_bytes(va,size):
  for k in range(n):
   vs,rva,sz,off=struct.unpack_from('<IIII',exe,sections+k*40+8)
   if rva<=va-0x400000 and va-0x400000+size<=rva+min(vs,sz):return exe[off+va-0x400000-rva:off+va-0x400000-rva+size]
  raise AssertionError('PE mapping')
 audit=list(csv.DictReader(a.audit.open(),delimiter='\t'));assert len(audit)>500
 for row in audit:
  code=bytes.fromhex(row['hex']);assert pe_bytes(int(row['va'],16),len(code))==code
 result['retail_instructions_verified']=len(audit)
if a.baseline:
 def select(text,kind):return [x.split('\t',3)[3] for x in text.splitlines() if '\t'+kind+'\t' in x]
 for kind in ['GEO_SOURCE','DRAW_ENTER','DRAW_RETURN','VIEW_RECORD','RASTER_ENTER','SPAN_COMMITTED']:
  assert select(t,kind)==select(a.baseline.read_text(),kind) and select(t,kind),kind+' accepted source/command/span linkage'
 result['accepted_source_linkage']=True
bad=t.replace('TABLE_ORIGINAL_STORE\t004793A4\taddress=0061D1A0','TABLE_ORIGINAL_STORE\t004793A4\taddress=0061D1A1',1)
assert bad!=t
try:verify(bad,f,pal)
except AssertionError:result['corruption_rejected']=True
else:raise AssertionError('corruption accepted')
print(json.dumps(result,sort_keys=True))
