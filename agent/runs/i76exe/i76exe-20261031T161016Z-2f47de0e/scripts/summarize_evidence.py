#!/usr/bin/env python3
"""Publish bounded measurements, never private source palette or framebuffer bytes."""
import argparse,csv,hashlib,json
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--private',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();a.out.mkdir(exist_ok=True)
def events(name):
 return [s.split('\t',3) for s in (a.private/(name+'.tsv')).read_text().splitlines()[1:] if len(s.split('\t',3))==4]
def selected(name,kinds):return [s for s in events(name) if s[1] in kinds or s[1]=='RASTER_INSTRUCTION' and s[2]=='0047CC55']
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def write(name,data):(a.out/name).write_text(json.dumps(data,indent=2)+'\n')
write('measurements.json',{'events':selected('positive',['NATIVE_PALETTE_SETUP','NUMERICAL_SERVICE','NUMERICAL_SERVICE_AFTER','NEAREST_ENTER','TABLE_ORIGINAL_STORE','TABLE_COLUMN_COMPLETE','RASTER_BYTE_WRITE','FRAMEBUFFER_FINAL']), 'source_palette':{'name':'m02.act','archive_offset':23736814,'bytes':768,'sha256':sha(a.private/'fixtures/m02.act')}, 'fresh_repeat':{'trace_equal':(a.private/'positive.tsv').read_bytes()==(a.private/'repeat.tsv').read_bytes(),'frame_equal':(a.private/'positive.tsv.frame').read_bytes()==(a.private/'repeat.tsv.frame').read_bytes(),'trace_sha256':sha(a.private/'positive.tsv'),'guards_sha256':sha(a.private/'positive.tsv.guards')}})
write('controls.json',{'unserviced_numeric':selected('raw',['PALETTE_PRODUCER_ATTEMPT','UNSERVICED_NUMERICAL_STATE','ORIGINAL_FAILURE']),'missing_palette':selected('missing',['PALETTE_INPUT_BLOCKER']),'standalone_verification':json.loads((a.private/'verification.json').read_text()),'accepted_baseline_log_sha256':sha(a.private/'baseline77.log'),'private_trace_hashes':{n:sha(a.private/(n+'.tsv')) for n in ['positive','raw','missing','repeat']}})
write('retail_opcodes.json',{'instructions':list(csv.DictReader((a.private/'opcodes.tsv').open(),delimiter='\t')),'method':'fresh read-only GZF instruction listing; every byte independently compared to authenticated retail PE'})
write('retail_xrefs.json',{'references':list(csv.DictReader((a.private/'opcodes.tsv.xrefs').open(),delimiter='\t')),'limit':'Ghidra references to selected exact addresses; arithmetic/interior aliases require instruction inspection. Historical annotations are not source names.'})
write('verification.json',json.loads((a.private/'verification.json').read_text()))
print('bounded evidence assembled')
