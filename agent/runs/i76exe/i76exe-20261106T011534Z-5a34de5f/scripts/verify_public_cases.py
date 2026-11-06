#!/usr/bin/env python3
"""Verify bounded coordinate/numerical records without any proprietary inputs.
This checks internal model/output consistency; private replay authenticates source words.
"""
import pathlib,json,struct,math,sys
sys.dont_write_bytecode=True
from coordinate_model import F,R,H,rounded,bias,admitted,location,ext_fraction
r=pathlib.Path(__file__).resolve().parent.parent;N=0
def check(ok,msg):
 global N
 N+=1
 if not ok:raise AssertionError(msg)
def source(s):
 slot,off=location(*s['global']);check(slot==s['grid_slot'] and off==s['local_sample'],'address decomposition')
 if 'outcome' in s:
  check(slot>=16384 and s['height12']==0,'only bounded invalid high slot');return
 pg=s['page'];word=int(s['raw_word'],16)
 check(s['runtime_grid']==[slot%128,slot//128],'runtime slot axes');check(s['local']==[off%128,off//128],'local axes')
 check(s['height12']==word&4095 and s['class']==word>>13 and s['bit12']==bool(word&4096),'word fields')
 address=(0x59c588 if pg=='default' else 0x40000000+pg*32768)+2*off
 check(int(s['address'],16)==address,'sample pointer')
 check(s['ter_byte_offset']==(None if pg=='default' else pg*32768+2*off),'TER stride')
 x,z=s['global'];check(s['world_position']==[x*5,float((word&4095)*H),z*5],'world mapping')
rows=[json.loads(l) for l in (r/'evidence/coordinate_cases.jsonl').read_text().splitlines()]
for d in rows:
 if d['kind']=='sample':source(d['source']);check(d['original']==d['expected']==d['source']['height12'],'lattice result');continue
 x,z=d['input'];bx,bz=bias(x),bias(z);check(d['admission']==[bx,bz] and d['admitted']==admitted(bx,bz),'admission stages')
 if not d['admitted']:
  check(not d['corners'] and d['original_class']==5 and ext_fraction(d['original_st0_le'])==0,'rejected height/class');continue
 sx=rounded(rounded(F(x)*R,64,'down'),53,'down');sz=rounded(rounded(F(z)*R,64,'down'),53,'down');ix,iz=math.floor(sx),math.floor(sz);fx,fz=sx-ix,sz-iz
 check(d['floor']==[ix,iz],'floor corners')
 check([v['global'] for v in d['corners']]==[[ix,iz],[ix+1,iz],[ix,iz+1],[ix+1,iz+1]],'four independent neighbors')
 for s in d['corners']:source(s)
 a,b,c,e=[v['height12'] for v in d['corners']]
 top=rounded(rounded(rounded((b-a)*fx,64,'down')+a,64,'down'),24,'down');bottom=rounded(rounded(rounded((e-c)*fx,64,'down')+c,64,'down'),24,'down')
 expected=rounded(rounded(rounded(rounded(bottom-top)*fz)+top)*H)
 check(ext_fraction(d['original_st0_le'])==expected,'CPU ST0 exact rational value')
 check(F(*map(int,d['expected_rational']))==expected,'published expected rational')
 check(d['original']==float(expected),'double rendering')
 native_rows=[struct.unpack('<f',struct.pack('<I',int(v,16)))[0] for v in d['native_row_bits']]
 check(native_rows==[float(top),float(bottom)],'native downward row stores')
 source(d['class_sample']);check(d['class_sample']['global']==[bx,bz] and d['original_class']==d['class_sample']['class'],'rounded material class')
subset=[json.loads(l) for l in (r/'evidence/boundary_cases.jsonl').read_text().splitlines()];all_by={(d['variant'],d['id']):d for d in rows}
for d in subset:check(all_by[(d['variant'],d['id'])]==d,'boundary subset identity')
print(json.dumps({'status':'passed','test_count':N,'passed_count':N,'cases':len(rows),'boundary_cases':len(subset),'limitation':'Checks published internal consistency; source authenticity requires private original replay.'}))
