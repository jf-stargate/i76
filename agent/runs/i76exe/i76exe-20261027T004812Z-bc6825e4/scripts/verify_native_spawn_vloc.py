#!/usr/bin/env python3
"""Independent PRIVATE-INPUT verifier for native I76 selected-vehicle VLOC/camera replay.

Inputs are held privately and are never part of the public research run.
Usage:
 python verify_native_spawn_vloc.py --pe /private/i76.exe --gzf /private/v97.gzf \
      --zfs /private/I76.ZFS --fixtures /private/fixtures \
      --traces /private/traces --anchors evidence/retail_opcode_anchors.tsv \
      --summary evidence/scenario_results.tsv
"""
import argparse, collections, csv, hashlib, pathlib, struct

EXPECTED_EXE_MD5='a640ea0097dbb62e0c77b7f2847c7161'
EXPECTED_EXE_SHA256='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
EXPECTED_GZF='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'
EXPECTED_ZFS='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'

class Verifier:
    def __init__(self):self.passed=0
    def ck(self,condition,description):
        if not condition:raise AssertionError(description)
        self.passed+=1
    def sha(self,p):return hashlib.sha256(p.read_bytes()).hexdigest()

def pe_rva_to_offset(b,va):
    pe_off=struct.unpack_from('<I',b,0x3c)[0]
    assert b[pe_off:pe_off+4]==b'PE\0\0'
    n=struct.unpack_from('<H',b,pe_off+6)[0]
    osize=struct.unpack_from('<H',b,pe_off+20)[0]
    base=struct.unpack_from('<I',b,pe_off+24+28)[0]
    rva=va-base
    for i in range(n):
        p=pe_off+24+osize+i*40
        sz,sv,raw_size,raw_off=struct.unpack_from('<IIII',b,p+8)
        if sv<=rva<sv+max(sz,raw_size):return raw_off+(rva-sv)
    raise ValueError('unmapped PE VA '+hex(va))

def events(path):
    with path.open(newline='') as f:
        return list(csv.DictReader(f,delimiter='\t'))

def one(rows,event):return [r for r in rows if r['kind']==event]

def detail(row):return dict(s.split('=',1) for s in row['detail'].split(';') if '=' in s)

def main():
    p=argparse.ArgumentParser();
    for s in ('pe','gzf','zfs','fixtures','traces','anchors','summary'):p.add_argument('--'+s,type=pathlib.Path,required=True)
    args=p.parse_args();v=Verifier()
    pe=args.pe.read_bytes();v.ck(hashlib.md5(pe).hexdigest()==EXPECTED_EXE_MD5,'retail MD5')
    v.ck(hashlib.sha256(pe).hexdigest()==EXPECTED_EXE_SHA256,'retail SHA256')
    v.ck(v.sha(args.gzf)==EXPECTED_GZF,'annotated Ghidra v97 identity')
    v.ck(v.sha(args.zfs)==EXPECTED_ZFS,'ZFS archive identity')
    v.ck(pe[:2]==b'MZ','DOS signature');v.ck(pe[struct.unpack_from('<I',pe,0x3c)[0]:][:4]==b'PE\0\0','PE signature')
    with args.anchors.open(newline='') as f:anchors=list(csv.DictReader(f,delimiter='\t'))
    v.ck(len(anchors)>=20,'anchor coverage')
    for row in anchors:
        n=int(row['va'],16);expected=bytes.fromhex(row['hex_bytes']);off=pe_rva_to_offset(pe,n)
        v.ck(pe[off:off+len(expected)]==expected,f'original PE anchor {row["va"]}')
    for name in ('valeprec.vdf','vxbus.vdf'):
        raw=(args.fixtures/name).read_bytes();v.ck(raw[0x10A:0x10E]==b'VLOC',name+' VLOC tag');v.ck(struct.unpack_from('<I',raw,0x10A+8)[0]==0x28,name+' type 0x28')
        v.ck(len(raw)>0x10A+60,name+' record payload')
    result_rows=[]
    for vehicle in ('gtsi','bus'):
        for selected in (False,True):
            name=vehicle+('_selected' if selected else '_unselected')
            rows=events(args.traces/(name+'.tsv'))
            v.ck(len(rows)>100,name+' trace rows')
            v.ck(all(r['scenario']==name for r in rows),name+' trace isolated')
            def only(event):
                hits=one(rows,event);v.ck(len(hits)==1,f'{name}: {event} count {len(hits)}')
                return detail(hits[0])
            spawn=only('NATIVE_SPAWN_STATUS')
            v.ck(spawn['originalVCFCallReached']=='true',name+' original boundary reached')
            v.ck(spawn['formattingBoundary']=='true',name+' declared formatting interception')
            v.ck(spawn['status']==('00010010' if selected else '00020000'),name+' status written by original instructions')
            v.ck(spawn['selected']==str(selected).lower(),name+' selector')
            native=only('FLAGGED_VCF_POST')
            v.ck(native['status']==('00010810' if selected else '00020800'),name+' final world flags')
            v.ck(native['nodes']==str((47 if selected else 46) if vehicle=='gtsi' else (45 if selected else 44)),name+' node counts')
            v.ck(native['runtime398']==('27000800' if selected else '00000000'),name+' camera attachment pointer')
            v.ck(native['class28']==('40' if selected else 'NULL'),name+' VLOC class discriminator')
            v.ck(native['vlocNineWords']==('EXACT' if selected else 'NOT_CREATED'),name+' checked source transform')
            completed=only('NATIVE_VCF_COMPLETE')
            v.ck(completed['vcfc']=='1' and completed['parsers']=='7',name+' native VCF/dependency parse count')
            v.ck(completed['nodes']==native['nodes'],name+' loader/attachment node agreement')
            v.ck(completed['materialBinds']==('24' if vehicle=='gtsi' else '22'),name+' TMT binding count')
            v.ck(completed['nativeMaterialSuccess']==completed['materialBinds'],name+' original TMT success')
            v.ck(completed['geoBindings']==('912' if vehicle=='gtsi' else '856'),name+' GEO cache bindings')
            read=only('NATIVE_CAMERA_RUNTIME_READ')
            v.ck(read['runtime398']==native['runtime398'],name+' camera shares runtime field')
            v.ck(len(one(rows,'NATIVE_CAMERA_PAST_ATTACHMENT_GUARD'))==(1 if selected else 0),name+' post-guard branch')
            v.ck(len(one(rows,'NATIVE_CAMERA_NULL_EXIT'))==(0 if selected else 1),name+' null guard branch')
            v.ck(len(one(rows,'NATIVE_VLOC28_ENTER'))==1,name+' genuine VLOC type-28 parser entry')
            v.ck(any('class=40;' in r['detail'] for r in one(rows,'NATIVE_CLASS_REGISTRATION'))==selected,name+' original class-40 binder event')
            v.ck(len(one(rows,'NATIVE_BODY_MESH_SELECTED')) in (0,3),name+' optional later geometry test count')
            result_rows.append(dict(vehicle=vehicle,selected=str(int(selected)),spawn_status=spawn['status'],post_vcf_status=native['status'],class28=native['class28'],attachment=native['runtime398'],nodes=native['nodes'],tmt=completed['materialBinds'],geo_bindings=completed['geoBindings'],camera=('past_guard' if selected else 'null_exit'),trace_sha256=v.sha(args.traces/(name+'.tsv'))))
    b1=args.traces/'bus_selected.tsv';b2=args.traces/'bus_selected_replay2.tsv'
    v.ck(b1.read_bytes()==b2.read_bytes(),'byte-identical independent bus selected replay')
    v.ck(len(events(b1))==len(events(b2)),'same event count across bus selected replays')
    with args.summary.open(newline='') as f:
        reported=list(csv.DictReader(f,delimiter='\t'))
    v.ck(reported==result_rows,'published summary agrees exactly with independently parsed private traces')
    print(f'PASSED {v.passed}/{v.passed} original executable/resource/trace/anchor/summary checks')
    for row in result_rows:print(f"  {row['vehicle']:4} selected={row['selected']} status={row['post_vcf_status']} attachment={row['attachment']} nodes={row['nodes']} camera={row['camera']}")
if __name__=='__main__':main()
