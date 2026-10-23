#!/usr/bin/env python3
"""Independently verify native camera/arena/type-10 retail traces, exact PE anchors, and identity.
No private data is distributed; pass private paths explicitly. Stdlib only."""
import argparse,hashlib,json,pathlib,struct,csv
p=argparse.ArgumentParser();p.add_argument('--run',type=pathlib.Path,required=True);p.add_argument('--pe',type=pathlib.Path,required=True);p.add_argument('--zfs',type=pathlib.Path,required=True);p.add_argument('--gzf',type=pathlib.Path,required=True);p.add_argument('--arena',type=pathlib.Path,required=True);p.add_argument('--arena-repeat',type=pathlib.Path,required=True);p.add_argument('--camera',type=pathlib.Path,required=True);p.add_argument('--camera-repeat',type=pathlib.Path,required=True);p.add_argument('--type10',type=pathlib.Path,required=True);p.add_argument('--type10-repeat',type=pathlib.Path,required=True);p.add_argument('--baseline',type=pathlib.Path,required=True);a=p.parse_args()
d=json.loads((a.run/'evidence/experiment_summary.json').read_text());tests=0
def check(x,msg):
 global tests;tests+=1
 if not x:raise AssertionError(msg)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
for key,path in [('retail_pe_sha256',a.pe),('zfs_sha256',a.zfs),('ghidra_gzf_sha256',a.gzf),('arena_original_trace_sha256',a.arena),('arena_repeat_trace_sha256',a.arena_repeat),('camera_original_trace_sha256',a.camera),('camera_repeat_trace_sha256',a.camera_repeat),('vehicle_original_trace_sha256',a.type10),('vehicle_repeat_trace_sha256',a.type10_repeat),('v5_baseline_sha256',a.baseline)]:check(sha(path)==d[key],key)
for label,p1,p2 in [('arena',a.arena,a.arena_repeat),('camera',a.camera,a.camera_repeat),('type10',a.type10,a.type10_repeat)]:check(p1.read_bytes()==p2.read_bytes(),label+' not deterministic')
check('RETURN\t1\tsteps=73776' in a.arena.read_text(),'arena native return')
check('TABLE_VERIFY\tentriesPerTable=4096\tstride=12\tnonzero=0' in a.arena.read_text(),'arena zero checks')
alloc=[int(ln.split('size=')[1].split('\t')[0]) for ln in a.arena.read_text().splitlines() if ln.startswith('ALLOC\t')]
check(alloc==d['arena_alloc_requests'],'allocator service sizes')
check('CAMERA_INIT\tcompleted=true;steps=2708' in a.camera.read_text(),'camera native return')
check('FTOL_BOUNDARY\t004BA090\tconverted=639' in a.camera.read_text(),'640 viewport - 1')
check('FTOL_BOUNDARY\t004BA090\tconverted=479' in a.camera.read_text(),'480 viewport - 1')
with (a.run/'evidence/type10_dispatch.tsv').open() as f: rows=list(csv.DictReader(f,delimiter='\t'))
check(len(rows)==2,'vehicle rows')
for r in rows:
 lines=[ln for ln in a.type10.read_text().splitlines() if ln.startswith(r['vehicle']+'\tNATIVE_TYPE10_')]
 check(len(lines)==4,r['vehicle']+' native phases');check('\tNATIVE_TYPE10_DISPATCH_ENTER\t00490640' in lines[0],r['vehicle']+' dispatch');check('\tNATIVE_TYPE10_FACE_DEPTH_TEST\t004906C0' in lines[2],r['vehicle']+' face');check('\tNATIVE_TYPE10_FACE_CULLED\t004907C5' in lines[3],r['vehicle']+' cull');check(r['face_list'] in lines[0] and r['depth_float_hex'] in lines[2],'type10 field mismatch');check(r['polygon_submit_calls']=='0','unexpected submission')
pe=a.pe.read_bytes();off=struct.unpack_from('<I',pe,0x3c)[0];image=struct.unpack_from('<I',pe,off+24+28)[0];n=struct.unpack_from('<H',pe,off+6)[0];ops=struct.unpack_from('<H',pe,off+20)[0];sections=[]
for i in range(n):
 h=off+24+ops+i*40;name,vs,va,rawsz,raw=struct.unpack_from('<8sIIII',pe,h);sections.append((va,max(vs,rawsz),raw))
with (a.run/'evidence/native_opcode_anchors.tsv').open() as f:
 for row in csv.DictReader(f,delimiter='\t'):
  address=int(row['address'],16)-image;val=bytes.fromhex(row['bytes_hex']);matches=[pe[raw+address-va:raw+address-va+len(val)]==val for va,size,raw in sections if va<=address<va+size]
  check(matches==[True],row['address']+' retail PE bytes')
print('VERIFIED',tests,'independent assertions')
