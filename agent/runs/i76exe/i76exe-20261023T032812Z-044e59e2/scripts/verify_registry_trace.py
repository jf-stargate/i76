#!/usr/bin/env python3
"""Independent read-only validation of published original-instruction registry evidence."""
import argparse, csv, json, pathlib, collections, hashlib

def run(root):
    trace=list(csv.DictReader((root/'evidence/original_instruction_trace.tsv').open(),delimiter='\t'))
    assert trace and set(trace[0])=={'scenario','event','address','detail'}
    checks=0
    def ok(test, label):
        nonlocal checks
        assert test, label
        checks+=1
    groups={name:[r for r in trace if r['scenario']==name] for name in {r['scenario'] for r in trace}}
    def event(scenario,what):return [r for r in groups.get(scenario,[]) if r['event']==what]
    def detail(scenario,what):return '\n'.join(r['detail'] for r in event(scenario,what))
    ok(sum(r['event']=='ASSERT_PASS' for r in trace)==38,'native assertion count')
    for scenario in ['INIT','MISS_COLD','APPEND_FIRST','FIND_FIRST','APPEND_DUPLICATE','FIND_LATEST','OTHER_KEY_MISS','ACTOR_MISSING','ACTOR_TWO_SAME','ACTOR_TWO_DIFFERENT','ACTOR_TAURUS','APPEND_SUPPRESSED_DUPLICATE','FIND_SUPPRESSED_LATEST','DESTROY','GROWTH_SUCCESS_RETURN','GROWTH_NULL_ENTRY']:
        ok(bool(groups.get(scenario)),f'missing {scenario}')
    ok('count_before=0' in detail('APPEND_FIRST','ORIGINAL_COUNT_INCREMENT'),'original first append')
    ok('count_before=1' in detail('APPEND_DUPLICATE','ORIGINAL_COUNT_INCREMENT'),'original second append')
    ok(len(event('APPEND_DUPLICATE','ORIGINAL_ERROR_RET'))==1,'duplicate native reporter')
    ok(len(event('APPEND_SUPPRESSED_DUPLICATE','ORIGINAL_ERROR_RET'))==0,'suppression reporter absent')
    ok(len(event('ACTOR_MISSING','STUB_REF_ACQUIRE'))==0,'missing reference acquisition absent')
    ok(len(event('ACTOR_TWO_SAME','STUB_REF_ACQUIRE'))==2,'two independent acquisition calls')
    ok(len(event('ACTOR_TWO_DIFFERENT','ORIGINAL_ERROR_RET'))==2,'two mismatched-label reports')
    ok('taurus global cache=24000200' in detail('ACTOR_TAURUS','ASSERT_PASS'),'taurus original global')
    ok('EAX=24000200' in detail('FIND_LATEST','FUNCTION_EXIT'),'last registration lookup')
    ok('EAX=24000100' in detail('FIND_SUPPRESSED_LATEST','FUNCTION_EXIT'),'latest after suppression')
    ok('EAX=00000000' in detail('MISS_COLD','FUNCTION_EXIT'),'cold miss')
    ok('EAX=00000000' in detail('OTHER_KEY_MISS','FUNCTION_EXIT'),'other miss')
    ok('EAX=00000000' in detail('GROWTH_SUCCESS_RETURN','FUNCTION_EXIT'),'nonnull realloc premature zero return')
    ok('requested=36864 result=22000000' in detail('GROWTH_SUCCESS_RETURN','STUB_HEAP_REALLOC'),'successful realloc stub')
    ok('requested=36864 result=00000000' in detail('GROWTH_NULL_ENTRY','STUB_HEAP_REALLOC'),'failed realloc stub')
    ok('ctx.entries=00000000 count=2048' in detail('GROWTH_NULL_ENTRY','STOP_BEFORE_NULL_BACKING_WRITE'),'failed realloc invalid backing')
    ok('calculated store_address=00008000' in detail('GROWTH_NULL_ENTRY','STOP_BEFORE_NULL_BACKING_WRITE'),'computed low address')
    ok('destroyed count=00000000' in detail('DESTROY','ASSERT_PASS'),'destructor zeroed count')
    odef=list(csv.DictReader((root/'evidence/odef_counts.tsv').open(),delimiter='\t'))
    summary=json.loads((root/'evidence/odef_summary.json').read_text())
    ok(len(odef)==80,'corpus 80 files')
    ok(sum(int(x['odef_obj_records']) for x in odef)==5564,'serialized OBJ total')
    ok(all(int(x['odef_bytes'])==28+108*int(x['odef_obj_records']) for x in odef),'bounded section sizes')
    ok(all(x['odef_obj_size_modes']==f"108:{x['odef_obj_records']}" for x in odef),'all chunk sizes')
    ok({x['file'].split('/')[1] for x in odef if x['file'].startswith('miss8/')}=={x['file'].split('/')[1] for x in odef if x['file'].startswith('miss16/')} ,'paired names')
    byname=collections.defaultdict(list)
    for x in odef:byname[x['file'].split('/')[1]].append(int(x['odef_obj_records']))
    ok(all(len(v)==2 and v[0]==v[1] for v in byname.values()),'paired counts')
    ok(max(int(x['odef_obj_records']) for x in odef)==169,'maximum records')
    ok(min(int(x['odef_obj_records']) for x in odef)==13,'minimum records')
    ok(summary['total_serialized_obj_records']==5564 and summary['missions']==80,'summary agreement')
    return {'status':'passed','independent_checks':checks,'native_assertions':38,'total_checks':checks+38,'trace_sha256':hashlib.sha256((root/'evidence/original_instruction_trace.tsv').read_bytes()).hexdigest()}

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--run-root',type=pathlib.Path,default=pathlib.Path(__file__).resolve().parent.parent)
    a=p.parse_args();print(json.dumps(run(a.run_root),indent=2))
