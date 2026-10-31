#!/usr/bin/env python3
"""Standalone verification of original CB00 stores against measured spans and guarded output."""
import argparse, csv, hashlib, json, struct
from pathlib import Path

EXE_SHA = 'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
WRITER = 0x47cc62
TABLE_SHA = '9208ae951af7fe2624047061396611af79b718114d45bb918acf20ce1e0a6a7e'

def check(condition, message):
    global assertions
    assertions += 1
    if not condition:
        raise AssertionError(message)

def events(path):
    out = []
    for line in path.read_text().splitlines()[1:]:
        s = line.split('\t', 3)
        if len(s) == 4:
            out.append((s[1], int(s[2], 16), dict(part.split('=', 1) for part in s[3].split(';') if '=' in part), s[3]))
    return out

def word(data, offset):
    return struct.unpack_from('<I', data, offset)[0]

def pe_bytes(data, va, size):
    pe = word(data, 0x3c)
    check(data[pe:pe+4] == b'PE\0\0', 'PE signature')
    section_count = struct.unpack_from('<H', data, pe+6)[0]
    optional = struct.unpack_from('<H', data, pe+20)[0]
    base = word(data, pe+24+28)
    for i in range(section_count):
        at = pe+24+optional+40*i
        virtual_size, rva, raw_size, raw = struct.unpack_from('<IIII', data, at+8)
        if base+rva <= va and va+size <= base+rva+min(raw_size, virtual_size):
            return data[raw+va-base-rva:raw+va-base-rva+size]
    raise AssertionError('VA outside raw PE sections')

def baseline_spans(rows):
    commands = {}
    for kind, pc, fields, _ in rows:
        if kind != 'FLUSH_COMMAND':
            continue
        cmd = bytes.fromhex(fields['bytes'])
        raw = bytes.fromhex(fields['spans'])
        check(len(cmd) == 96 and len(raw) % 4 == 0, 'native command/span sizes')
        words = list(struct.unpack('<' + 'I'*(len(raw)//4), raw))
        check(words[0] == 0xffffffff and words[-1] == 0, 'native sentinel and pending slot')
        check(word(cmd, 8) == 0x47cb00, 'native callback pointer')
        check(word(cmd, 0x30) == int(fields['spanAddress'], 16)+len(raw)-4, 'pending slot pointer')
        commands[int(fields['address'], 16)] = {'packed': words[1:-1]+[word(cmd, 0x28)], 'pending':word(cmd, 0x28), 'slot':word(cmd, 0x30), 'color':cmd[0]}
    check(len(commands) == 2, 'two native commands')
    return commands

def verify_case(name, rows, frame, commands, offset, need_pixels):
    calls = [r for r in rows if r[0] == 'RASTER_ENTER']
    returns = [r for r in rows if r[0] == 'RASTER_RETURN']
    writes = [r for r in rows if r[0] == 'RASTER_BYTE_WRITE']
    finishes = [r for r in rows if r[0] == 'FRAMEBUFFER_FINAL']
    if not need_pixels:
        check(len(calls) == 0 and len(returns) == 0 and len(writes) == 0, name+' has no raster output')
        return {'case':name,'writes':0,'returns':0}
    check(len(calls) == 2 and len(returns) == 2, name+' two original callback returns')
    check(len(finishes) == 1, name+' final framebuffer record')
    check(len(frame) == 640*480, name+' exact 8-bit framebuffer length')
    f = finishes[0][2]
    base = int(f['base'], 16)
    check(base == 0x3f000000 and int(f['pitch']) == 640 and int(f['size']) == len(frame), name+' original descriptor base/pitch/size')
    check(f['guards'] == 'CD_intact', name+' guards intact')
    check(hashlib.sha256(frame).hexdigest() == f['sha256'], name+' framebuffer hash')
    check(int(f['writes']) == len(writes) and int(f['calls']) == len(calls) and int(f['returns']) == len(returns), name+' trace counts')
    table = bytes(((i & 255)+(i >> 8)) & 255 for i in range(8192))
    check(hashlib.sha256(table).hexdigest() == TABLE_SHA, 'declared table bytes')
    supplied = [r for r in rows if r[0] == 'SUPPLIED_DIAGNOSTIC_TABLE']
    check(len(supplied) == 1 and supplied[0][2]['sha256'] == TABLE_SHA and int(supplied[0][2]['bytes']) == 8192, name+' supplied table identity')
    init = [r for r in rows if r[0] == 'SURFACE_INIT_AFTER']
    check(len(init) == 1 and init[0][2]['ready'] == 'true', name+' original constructor returned valid descriptor')
    desc = bytes.fromhex(init[0][2]['descriptor'])
    check(word(desc, 0) == 640 and word(desc, 0x14) == base and word(desc, 0x1c) == 0 and word(desc, 0x20) == 0, name+' original descriptor field ownership')
    for kind, pc, fields, _ in calls:
        cmd = int(fields['command'], 16)
        check(cmd in commands, name+' original command identity')
        check(int(fields['pending'],16) == commands[cmd]['pending'] and int(fields['slot'],16) == commands[cmd]['slot'], name+' split pending span')
    commit = [r for r in rows if r[0] == 'SPAN_COMMITTED']
    check(len(commit) == 2, name+' pending span finalized by original callback')
    for call, stored in zip(calls, commit):
        cmd = commands[int(call[2]['command'],16)]
        check(int(stored[2]['slot'],16) == cmd['slot'] and int(stored[2]['value'],16) == cmd['pending'], name+' pending slot bytes')
    expected = []
    for call in calls:
        cmd = commands[int(call[2]['command'],16)]
        for packed in cmd['packed']:
            x, length, y = packed >> 21, (packed >> 10)&0x7ff, packed&0x3ff
            check(0 <= x < 640 and 0 < length <= 640-x and 0 <= y < 480, name+' decoded native span bounds')
            expected.extend(base + 640*y + x + offset + j for j in range(length))
    check(len(expected) == 210 and len(writes) == 210, name+' complete native span coverage')
    actual = [int(r[2]['address'],16) for r in writes]
    check(actual == expected, name+' exact writer chronology and destination formula')
    check(len(set(actual)) == 210, name+' no duplicate destination stores')
    table_reads = [r for r in rows if r[0] == 'RASTER_INSTRUCTION' and r[1] == 0x47cc55]
    check(len(table_reads) == len(writes), name+' one original table read per store')
    expected_bytes = bytearray(b'\xa5' * len(frame))
    for i, (write, read) in enumerate(zip(writes, table_reads), 1):
        w, r = write[2], read[2]
        check(write[1] == WRITER and int(w['ordinal']) == i, name+' original writer PC/ordinal')
        check(int(w['before']) == 0xa5, name+' sentinel before original store')
        index = int(r['edx'],16)+int(r['ecx'],16)
        check(0 <= index < len(table), name+' shade lookup index bounds')
        value = table[index]
        check(int(w['after']) == value, name+' original indexed table lookup value')
        expected_bytes[actual[i-1]-base] = value
    check(frame == expected_bytes, name+' every framebuffer byte, including untouched region')
    check(int(f['changed']) == sum(v != 0xa5 for v in frame), name+' changed-byte count')
    return {'case':name,'writes':len(writes),'returns':len(returns),'changed':int(f['changed']),'sha256':f['sha256'],'addresses':actual[:3]}

def main():
    global assertions
    assertions = 0
    p=argparse.ArgumentParser()
    p.add_argument('--private',type=Path,required=True)
    p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--gzf',type=Path)
    p.add_argument('--zfs',type=Path)
    p.add_argument('--corruptions',action='store_true')
    a=p.parse_args()
    exe=a.exe.read_bytes()
    check(hashlib.sha256(exe).hexdigest() == EXE_SHA, 'authenticated retail EXE')
    if a.gzf:
        check(hashlib.sha256(a.gzf.read_bytes()).hexdigest() == 'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce', 'authenticated annotated GZF')
    if a.zfs:
        check(hashlib.sha256(a.zfs.read_bytes()).hexdigest() == '0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d', 'authenticated retail ZFS')
    audit=list(csv.DictReader((a.private/'raster_opcodes.tsv').open(),delimiter='\t'))
    check(len(audit) == 459, 'Ghidra instruction audit count')
    for row in audit:
        code=bytes.fromhex(row['hex'])
        check(pe_bytes(exe,int(row['va'],16),len(code))==code,'Ghidra opcode matches retail PE '+row['va'])
    for va, code in [(0x474c60,'83ec34'),(0x47cb2f,'8911'),(0x47cc55,'8a840aa0b26100'),(0x47cc62,'8807'),(0x47ce38,'c3')]:
        check(pe_bytes(exe,va,len(bytes.fromhex(code))).hex()==code, 'original instruction bytes '+hex(va))
    base = events(a.private/'baseline/flush.tsv')
    commands = baseline_spans(base)
    diagnostic_rows = events(a.private/'diagnostic.tsv')
    for kind in ('CONTROLLED_TARGET_POSE','VIEW_RECORD','GEO_SOURCE','GEO_OUTPUT','NATIVE_PREPARE_ENTER','DRAW_ENTER','DRAW_RETURN'):
        old=[r[3] for r in base if r[0]==kind]
        new=[r[3] for r in diagnostic_rows if r[0]==kind]
        check(old==new and len(old)>0, 'authenticated upstream event equality '+kind)
    sources=[r for r in diagnostic_rows if r[0]=='GEO_SOURCE']
    check(any(r[2].get('vertices_sha256')=='31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468' for r in sources), 'authenticated stock-bus GEO vertices')
    check(any(r[0]=='CONTROLLED_TARGET_POSE' and r[2].get('z')=='50.0' for r in diagnostic_rows), 'visible stock-bus pose')
    result=[]
    for name, off, positive in [('diagnostic',0,True),('offset',4,True),('behind',0,False)]:
        rows=events(a.private/(name+'.tsv'))
        if name == 'offset':
            offsets=[r for r in rows if r[0]=='SUPPLIED_VIEWPORT_OFFSET']
            check(len(offsets)==1 and offsets[0][2]['x']=='4' and offsets[0][2]['y']=='0','controlled viewport offset')
        frame=(a.private/(name+'.tsv.frame')).read_bytes() if positive else b''
        result.append(verify_case(name,rows,frame,commands,off,positive))
    absent=events(a.private/'absent.tsv')
    blockers=[r for r in absent if r[0]=='SURFACE_BLOCKER']
    check(len(blockers)==1 and blockers[0][1]==0x47cc25, 'absent surface rejected at original destination read')
    check(not [r for r in absent if r[0]=='RASTER_BYTE_WRITE'], 'absent surface no byte writes')
    behind=events(a.private/'behind.tsv')
    check(any(r[0]=='CONTROLLED_TARGET_POSE' and r[2].get('z')=='-50.0' for r in behind), 'original behind-camera pose')
    check(not [r for r in behind if r[0] in ('DRAW_ENTER','RASTER_ENTER','RASTER_BYTE_WRITE')], 'behind-camera no eligible draw')
    check((a.private/'behind.tsv.frame').read_bytes()==b'\xa5'*(640*480), 'behind-camera framebuffer unchanged')
    repeat=events(a.private/'fresh_repeat.tsv')
    repeat_frame=(a.private/'fresh_repeat.tsv.frame').read_bytes()
    repeat_result=verify_case('fresh_repeat',repeat,repeat_frame,commands,0,True)
    check(repeat_frame==(a.private/'diagnostic.tsv.frame').read_bytes(), 'fresh-project exact framebuffer equality')
    check([(r[0],r[1],r[2]) for r in repeat if r[0] in ('RASTER_ENTER','RASTER_BYTE_WRITE','RASTER_RETURN','FRAMEBUFFER_FINAL')]==[(r[0],r[1],r[2]) for r in events(a.private/'diagnostic.tsv') if r[0] in ('RASTER_ENTER','RASTER_BYTE_WRITE','RASTER_RETURN','FRAMEBUFFER_FINAL')], 'fresh-project exact raster events')
    positive_assertions=assertions
    if a.corruptions:
        original=a.private/'diagnostic.tsv'
        for key,old,new in [('span','RASTER_BYTE_WRITE\t0047CC62\taddress=3F030F69','RASTER_BYTE_WRITE\t0047CC62\taddress=3F030F6A'),('destination','FRAMEBUFFER_FINAL\t00000000\tbase=3F000000','FRAMEBUFFER_FINAL\t00000000\tbase=3F000001'),('byte','RASTER_BYTE_WRITE\t0047CC62\taddress=3F030F69;before=165;after=31','RASTER_BYTE_WRITE\t0047CC62\taddress=3F030F69;before=165;after=30')]:
            text=original.read_text()
            check(old in text, key+' mutation target exists')
            bad=a.private/('corrupt_'+key+'.tsv')
            bad.write_text(text.replace(old,new,1))
            try:
                verify_case(key,events(bad),(a.private/'diagnostic.tsv.frame').read_bytes(),commands,0,True)
            except AssertionError:
                pass
            else:
                raise AssertionError(key+' corruption was accepted')
            print('rejected corruption',key)
    print(json.dumps({'status':'passed','positive_assertions':positive_assertions,'mutation_assertions':assertions-positive_assertions,'total_assertions':assertions,'results':result+[repeat_result]},sort_keys=True))

if __name__=='__main__':
    main()
