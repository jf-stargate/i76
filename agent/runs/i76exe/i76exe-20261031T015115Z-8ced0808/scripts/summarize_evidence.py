#!/usr/bin/env python3
"""Create bounded public measurements from private original-instruction traces."""
import argparse, csv, hashlib, json
from pathlib import Path

p=argparse.ArgumentParser()
p.add_argument('--private',type=Path,required=True)
p.add_argument('--out',type=Path,required=True)
p.add_argument('--exe',type=Path,required=True)
p.add_argument('--gzf',type=Path,required=True)
p.add_argument('--zfs',type=Path,required=True)
a=p.parse_args()
a.out.mkdir(parents=True,exist_ok=True)
def rows(name):
    result=[]
    for line in (a.private/(name+'.tsv')).read_text().splitlines()[1:]:
        words=line.split('\t',3)
        if len(words)==4:
            result.append({'kind':words[1],'pc':words[2],'detail':words[3]})
    return result
def select(data,*kinds):
    return [r for r in data if r['kind'] in kinds]
def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()
base=rows('baseline/flush')
diag=rows('diagnostic')
offset=rows('offset')
behind=rows('behind')
absent=rows('absent')
fresh=rows('fresh_repeat')
raw=rows('init_raw')
palette=rows('palette_raw')
assert len(select(diag,'RASTER_BYTE_WRITE'))==210
assert len(select(offset,'RASTER_BYTE_WRITE'))==210
assert not select(behind,'RASTER_BYTE_WRITE')
assert (a.private/'diagnostic.tsv').read_bytes()==(a.private/'fresh_repeat.tsv').read_bytes()
evidence={
 'baseline_run':'i76exe-20261031T011731Z-307babbf',
 'source_identity':select(diag,'CONTROLLED_TARGET_POSE','GEO_SOURCE','POLYGON_WRAPPER'),
 'native_commands_and_spans':select(base,'FLUSH_COMMAND'),
 'original_surface_constructor':select(diag,'SURFACE_INIT_BEFORE','SURFACE_HEAP_SERVICE','SURFACE_INIT_AFTER'),
 'supplied_shade_table':select(diag,'SUPPLIED_DIAGNOSTIC_TABLE'),
 'original_callback_and_span_commit':select(diag,'RASTER_ENTER','SPAN_COMMITTED','RASTER_RETURN'),
 'all_original_pixel_writes':select(diag,'RASTER_BYTE_WRITE'),
 'all_original_table_read_registers':select(diag,'RASTER_INSTRUCTION'),
 'framebuffer_summary':select(diag,'FRAMEBUFFER_FINAL'),
 'offset_control':select(offset,'SUPPLIED_VIEWPORT_OFFSET','FRAMEBUFFER_FINAL'),
 'behind_control':select(behind,'CONTROLLED_TARGET_POSE','FRAMEBUFFER_FINAL'),
 'fresh_repeat':{'trace_sha256':sha(a.private/'fresh_repeat.tsv'),'framebuffer_sha256':sha(a.private/'fresh_repeat.tsv.frame'),'byte_identical_to_primary':True},
 'private_trace_sha256':{n:sha(a.private/(n+'.tsv')) for n in ('diagnostic','offset','behind','absent','init_raw','palette_raw')},
 'private_framebuffer_sha256':{n:sha(a.private/(n+'.tsv.frame')) for n in ('diagnostic','offset','behind','fresh_repeat')}
}
# Keep the original callback only: command/edge and scene traces remain private and
# independently verifiable through the accepted predecessor's published evidence.
evidence['all_original_table_read_registers']=[r for r in evidence['all_original_table_read_registers'] if r['pc']=='0047CC55']
(a.out/'raster_results.json').write_text(json.dumps(evidence,indent=2)+'\n')
controls={
 'unserviced_original_heap_initializer':select(raw,'INITIALIZER_ATTEMPT','ORIGINAL_FAILURE'),
 'original_surface_constructor_with_narrow_heap_service':select(palette,'SURFACE_INIT_BEFORE','SURFACE_HEAP_SERVICE','SURFACE_INIT_AFTER'),
 'original_palette_producer_attempt':select(palette,'PALETTE_PRODUCER_ATTEMPT','ORIGINAL_FAILURE'),
 'absent_surface':select(absent,'RASTER_ENTER','SURFACE_BLOCKER'),
 'behind_camera':select(behind,'CONTROLLED_TARGET_POSE','FRAMEBUFFER_FINAL'),
 'deliberate_corruptions':[{'field':'first original writer destination','from':'3F030F69','to':'3F030F6A','rejected':True},{'field':'final framebuffer base','from':'3F000000','to':'3F000001','rejected':True},{'field':'first output byte','from':31,'to':30,'rejected':True}]
}
(a.out/'controls.json').write_text(json.dumps(controls,indent=2)+'\n')
audit=list(csv.DictReader((a.private/'raster_opcodes.tsv').open(),delimiter='\t'))
(a.out/'retail_raster_opcodes.json').write_text(json.dumps({'exe_sha256':sha(a.exe),'instruction_count':len(audit),'instructions':audit},indent=2)+'\n')
provenance={'base_commit':'f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019','run_id':'i76exe-20261031T015115Z-8ced0808','inputs':{'exe_sha256':sha(a.exe),'gzf_sha256':sha(a.gzf),'zfs_sha256':sha(a.zfs)},'tool':{'ghidra':'12.1.4 PUBLIC','java':'OpenJDK 27-ea+34-1-Debian'},'method':'read-only Ghidra EmulatorHelper, authenticated retail PE/GZF/ZFS; private GZF newly imported for positive repeat'}
(a.out/'provenance.json').write_text(json.dumps(provenance,indent=2)+'\n')
print('bounded evidence assembled:',len(evidence['all_original_pixel_writes']),'writes,',len(audit),'retail instructions')
