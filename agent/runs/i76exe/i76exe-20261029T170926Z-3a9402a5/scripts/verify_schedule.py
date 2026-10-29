#!/usr/bin/env python3
"""Independent PE/collection/event checks; private inputs never copied to evidence.

--emit writes only reviewed derived records. Without it, regenerated records must
equal the published evidence. Assertion count is dataset-specific, not coverage.
"""
import argparse, csv, hashlib, json, math, struct
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--run', type=Path, required=True)
p.add_argument('--private', type=Path, required=True)
p.add_argument('--exe', type=Path, required=True)
p.add_argument('--gzf', type=Path, required=True)
p.add_argument('--zfs', type=Path, required=True)
p.add_argument('--msn', type=Path, required=True)
p.add_argument('--ter', type=Path, required=True)
p.add_argument('--emit', action='store_true')
a = p.parse_args()
count = 0

def check(ok, message):
    global count
    count += 1
    if not ok:
        raise AssertionError(message)

def sha(b):
    return hashlib.sha256(b).hexdigest()

expected = {
    'exe': 'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3',
    'gzf': 'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce',
    'zfs': '0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d',
    'msn': '923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f',
    'ter': 'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea',
}
identities = {}
for key, digest in expected.items():
    data = getattr(a, key).read_bytes()
    check(sha(data) == digest, key + ' identity')
    identities[key] = dict(sha256=digest, md5=hashlib.md5(data).hexdigest(), bytes=len(data))
pe = a.exe.read_bytes()
ter = a.ter.read_bytes()
nt = struct.unpack_from('<I', pe, 0x3c)[0]
sections = nt + 24 + struct.unpack_from('<H', pe, nt + 20)[0]
image_base = struct.unpack_from('<I', pe, nt + 24 + 28)[0]

def read(va, size):
    rva = va - image_base
    for i in range(struct.unpack_from('<H', pe, nt + 6)[0]):
        _, vsize, start, rawsize, raw = struct.unpack_from('<8sIIII', pe, sections + i * 40)
        if start <= rva and rva + size <= start + rawsize:
            return pe[raw + rva - start:raw + rva - start + size]
    raise AssertionError(hex(va))

def word(va):
    return struct.unpack('<I', read(va, 4))[0]

# Sparse reviewed anchors, deliberately not full original-code dumps.
anchors = [
    (0x461c81, '8b3504b25400', 'pre collection head'),
    (0x461d51, '8b3504b25400', 'post collection head'),
    (0x461c91, '8b4608', 'pre node value'),
    (0x461c94, '8b1e', 'pre saved next'),
    (0x461c9c, 'e84fd4ffff', 'pre original handle lookup'),
    (0x461d6c, 'e87fd3ffff', 'post original handle lookup'),
    (0x461d19, '83c034', 'descriptor stride'),
    (0x461d2c, '8b0495ec764f00', 'pre slot load'),
    (0x461dfc, '8b0495f0764f00', 'post slot load'),
    (0x461d38, 'ffd0', 'pre indirect call'),
    (0x461e08, 'ffd0', 'post indirect call'),
    (0x4619de, 'e83da90300', 'registration first list insertion'),
    (0x4619e6, 'a304b25400', 'registration head store'),
    (0x49c32b, 'ff1508c14b00', 'original node HeapAlloc service boundary'),
    (0x49c341, '8908', 'original node next store'),
    (0x49c348, '897008', 'original node value store'),
    (0x463956, 'e89552ffff', 'class1 post status predicate'),
    (0x458bf8, 'f6401010', 'status bit 0x10'),
    (0x463960, '7412', 'post false predicate skips side effects'),
    (0x463963, 'e83866ffff', 'selected post input/cockpit boundary'),
    (0x46396c, 'e82f22feff', 'selected post audio boundary'),
    (0x49d409, 'd9fb', 'diagnostic FSINCOS (fcos P-code blocker)'),
]
anchor_text = 'va\tbytes\trole\n'
for va, h, role in anchors:
    check(read(va, len(bytes.fromhex(h))).hex() == h, role)
    anchor_text += f'{va:08X}\t{h}\t{role}\n'
check(word(0x4f777c) == 1, 'descriptor class1')
for slot, target in [(0x4f7784, 0x463120), (0x4f7788, 0x463800), (0x4f778c, 0x463950)]:
    check(word(slot) == target, 'descriptor target')
    anchor_text += f'{slot:08X}\t{read(slot,4).hex()}\tdescriptor word {target:08X}\n'

def rows(name):
    with (a.private / (name + '.tsv')).open() as f:
        out = list(csv.DictReader(f, delimiter='\t'))
    for i, r in enumerate(out):
        r['index'] = i
        r['fields'] = dict(x.split('=', 1) for x in r['detail'].split(';') if '=' in x)
    return out

def select(rs, kind):
    return [r for r in rs if r['kind'] == kind]

def f32(h):
    return struct.unpack('<f', bytes.fromhex(h)[::-1])[0]

summary = {}
selected = 'case\tsequence\tkind\tpc\tdetail\n'
safe = {'HARNESS_ENTRY', 'HARNESS_RETURN', 'EMPTY_CONTROL_RETURN',
        'ORIGINAL_LIST_RETURN', 'NATIVE_CLASS_REGISTRATION', 'COLLECTION_READY',
        'COLLECTION_VISIT', 'LOOKUP_RETURN', 'DESCRIPTOR_FETCH', 'INDIRECT_CALL',
        'CLASS1_ENTER', 'POST_GATE', 'INDIRECT_RETURN', 'PHASE_STATE',
        'SERVICE_PERIPHERAL_POST', 'POSE_CLASS_CALLBACK_ERROR'}
all_rows = {}
for case in ['bus', 'gtsi', 'direct_bus', 'bus_repeat']:
    rs = rows(case)
    all_rows[case] = rs
    for r in rs:
        if r['kind'] in safe:
            selected += f"{case}\t{r['index']}\t{r['kind']}\t{r['pc']}\t{r['detail']}\n"
    check(not select(rs, 'POSE_CLASS_CALLBACK_ERROR'), case + ' no callback error')
    empty = select(rs, 'EMPTY_CONTROL_RETURN')
    check(len(empty) == 1 and empty[0]['fields']['head'] == '00000000', 'empty control')
    check(not [r for r in select(rs, 'CLASS1_ENTER') if r['index'] < empty[0]['index']], 'empty has no callbacks')
    states = select(rs, 'PHASE_STATE')
    check(len(states) == 9, case + ' three states per frame')
    for frame in range(3):
        triplet = states[3*frame:3*frame+3]
        check([r['fields']['phase'] for r in triplet] == ['before_pre', 'after_pre', 'after_post'], 'state chronology')
        check(all(r['fields']['frame'] == str(frame) for r in triplet), 'frame identity')
        for r in triplet:
            d = r['fields']
            check(int(d['status'], 16) & 0x10 == 0, 'post predicate false input')
            check(all(math.isfinite(float(x)) for x in d['position'].split(',')), 'finite position')
            basis = [f32(x) for x in d['basis'].split(',')]
            velocity = [f32(x) for x in d['velocity'].split(',')]
            check(len(basis) == 9 and all(math.isfinite(x) for x in basis + velocity), 'typed finite basis/velocity')
            for row in range(3):
                for col in range(row, 3):
                    g = sum(basis[row*3+k] * basis[col*3+k] for k in range(3))
                    check(abs(g - int(row == col)) < 5e-5, 'Gram bound')
        check(triplet[0]['fields']['position'] != triplet[1]['fields']['position'], 'pre mutates position')
        d1, d2 = dict(triplet[1]['fields']), dict(triplet[2]['fields'])
        d1.pop('phase'); d2.pop('phase')
        check(d1 == d2, 'post sampled fields unchanged')
    enters = select(rs, 'CLASS1_ENTER')
    check([r['pc'] for r in enters] == ['00463800', '00463950'] * 3, 'pre/post class1 chronology')
    check(all(r['fields']['owner'] == '26000000' and r['fields']['runtime'] == '36000000' for r in enters), 'class1 owner/runtime')
    gates = select(rs, 'POST_GATE')
    check(len(gates) == 3 and all(r['fields']['eax'] == '0' for r in gates), 'original post false gates')
    for r in select(rs, 'TERRAIN_NATIVE_READ'):
        d = r['fields']; offset = int(d['offset'], 16)
        check(0 <= offset < len(ter)-1 and int(d['address'],16) == 0x40000000+offset, 'authentic read address')
        check(struct.unpack_from('<H', ter, offset)[0] == int(d['word'],16), 'authentic read word')
    check(len(select(rs, 'SOLVER_RETURN')) == 3, 'three original solver returns')
    if case != 'direct_bus':
        check(not [r for r in select(rs, 'HARNESS_ENTRY') if r['pc'] in ('00463800','00463950')], 'no harness callback injection')
        check([r['fields']['return'] for r in enters] == ['00461D3A','00461E0A'] * 3, 'original callback return addresses')
        ready = select(rs, 'COLLECTION_READY')[0]['fields']
        registered = {r['fields']['child']: int(r['fields']['class']) for r in select(rs, 'NATIVE_CLASS_REGISTRATION')}
        inserted = {r['fields']['node']: r['fields'] for r in select(rs, 'ORIGINAL_LIST_RETURN')}
        visits = select(rs, 'COLLECTION_VISIT')
        n = int(ready['count'])
        check(len(visits) == n*6, 'all six collection walks')
        for walk in range(6):
            chunk = visits[walk*n:(walk+1)*n]
            check(chunk[0]['fields']['node'] == ready['head'], 'head used')
            for i, r in enumerate(chunk):
                d = r['fields']; next_node = chunk[i+1]['fields']['node'] if i+1<n else '00000000'
                check(d['next'] == next_node, 'native next traversal')
                check(d['node'] in inserted and inserted[d['node']]['owner'] == d['owner'], 'native inserted owner')
                check(inserted[d['node']]['next'] == d['next'], 'native inserted next')
                check(d['owner'] in registered, 'native class registration')
        fetches = select(rs, 'DESCRIPTOR_FETCH')
        check(len(fetches) == len(visits), 'descriptor per owner')
        for r in fetches:
            d = r['fields']; slot = int(d['slot'],16)
            check(word(slot) == int(d['target'],16), 'original PE target')
            check(registered[d['owner']] == int(d['class']), 'registered class matches lookup')
            if d['class'] == '1':
                check(slot == (0x4f7788 if r['pc']=='00461D2C' else 0x4f778c), 'class1 exact slot')
        for enter in enters:
            prior = [r for r in select(rs, 'INDIRECT_CALL') if r['index'] < enter['index']][-1]
            check(prior['fields']['target'] == enter['pc'] and prior['fields']['owner'] == '26000000', 'indirect entry linkage')
            returns = [r for r in select(rs, 'INDIRECT_RETURN') if r['index'] > enter['index']]
            check(returns and returns[0]['pc'] == enter['fields']['return'] and returns[0]['fields']['owner'] == '26000000', 'original return linkage')
        check(len(select(rs,'SERVICE_PERIPHERAL_POST')) == 6, 'declared two peripheral services per post')
    summary[case] = dict(callbacks=len(enters), solvers=len(select(rs,'SOLVER_RETURN')),
                         phase_states=[r['fields'] for r in states],
                         collection_count=int(select(rs,'COLLECTION_READY')[0]['fields']['count']),
                         trace_sha256=sha((a.private/(case+'.tsv')).read_bytes()))

check((a.private/'bus.tsv').read_bytes() == (a.private/'bus_repeat.tsv').read_bytes(), 'separate repeat byte equality')
check(summary['bus']['phase_states'] == summary['direct_bus']['phase_states'], 'direct baseline sampled states equality')
diagnostic = rows('diagnostic')
for r in diagnostic:
    if r['kind'] in safe:
        selected += f"diagnostic\t{r['index']}\t{r['kind']}\t{r['pc']}\t{r['detail']}\n"
check([r['pc'] for r in select(diagnostic,'CLASS1_ENTER')] == ['00463800','00463950'], 'diagnostic reaches both')
errors = select(diagnostic, 'POSE_CLASS_CALLBACK_ERROR')
check(len(errors)==1 and '0049D409' in errors[0]['detail'] and 'fcos' in errors[0]['detail'], 'exact diagnostic blocker')
check(len(select(diagnostic,'PHASE_STATE'))==2, 'diagnostic no completed post')
summary['diagnostic'] = dict(trace_sha256=sha((a.private/'diagnostic.tsv').read_bytes()),
                             blocker='Original FSINCOS at 0049D409 hits unsupported fcos P-code; selected cockpit/input state and class31/34 peripheral post state not fully initialized; no completed raw post claim.')
for case in ['bus','gtsi','direct_bus','bus_repeat']:
    log = (a.private/(case+'.log')).read_text()
    check('ERROR' not in log, 'primary log no errors')
    warnings = [line for line in log.splitlines() if 'Uninitialized memory read' in line]
    check(len(warnings)==1 and '004461e0' in warnings[0] and 'ram:00000000:1' in warnings[0], 'only inherited setup null warning')
log = (a.private/'diagnostic.log').read_text()
check('Unimplemented CALLOTHER pcodeop (fcos)' in log, 'diagnostic log corroborates blocker')

outputs = {'instruction_anchors.tsv':anchor_text,
           'dispatch_events.tsv':selected,
           'results.json':json.dumps(dict(identities=identities, cases=summary), indent=2)+'\n'}
for name, value in outputs.items():
    target = a.run/'evidence'/name
    if a.emit:
        target.write_text(value)
    else:
        check(target.read_text() == value, 'published derived evidence '+name)
print(json.dumps(dict(status='passed', test_count=count, passed_count=count,
                      notes='PE identities/anchors, original list/descriptor/call/return chronology, sampled state/Gram/terrain reads, empty/direct/repeat controls, expected raw diagnostic blocker.')))
