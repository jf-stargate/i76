#!/usr/bin/env python3
"""Compare independent predictions against separately captured observations.
Default is asset-free; --extract needs private traces and licensed source files.
"""
import argparse,csv,json,struct,math,hashlib
from pathlib import Path
import numpy as np
from coordinate_model import Terrain
from predict import predict,TABLE

RUN=Path(__file__).resolve().parents[1]
def readrows(p):
    rows=list(csv.DictReader(p.open(),delimiter='\t'))
    for row in rows:row['d']=dict(t.split('=',1) for t in row['detail'].split(';') if '=' in t)
    return rows
def words(v):return bytes.fromhex(''.join(bytes.fromhex(x)[::-1].hex() for x in v.split(',')))
def dump(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
def extract(cases,msn,ter,native,dest):
    terrain=Terrain(msn.read_bytes(),ter.read_bytes(),bytes(32768));fixtures=[]
    selected=[]
    for p in sorted(cases.glob('*.tsv')):
        rows=readrows(p)
        one=lambda k:next((r['d'] for r in rows if r['kind']==k),None)
        view=Path(str(p)+'.view.bin').read_bytes();x,y,z=struct.unpack_from('<3d',view,0x160)
        h=terrain.height(x,z);samples={','.join(map(str,c['global'])):c['height12'] for c in h['corners']}
        original={'accepted':one('BOUNDS_RESULT')['eax']=='1'}
        result=one('BOUNDS_RESULT')
        original['root']=list(struct.unpack('<3i',words(result['grid'])))
        if one('FOOTPRINT_FINAL'):
            for k,e in [('initial','FOOTPRINT_INITIAL'),('points','FOOTPRINT_FINAL')]:original[k]=np.array(struct.unpack('<15d',words(one(e)['points']))).reshape(5,3).tolist()
            original['keep']=[r['d']['keep']=='1' for r in rows if r['kind']=='POINT_FILTER']
        if one('ORDERED_HULL'):
            n=int(one('ORDERED_HULL')['count']);original['hull']=np.array(struct.unpack('<'+'d'*n*3,words(one('ORDERED_HULL')['points']))).reshape(n,3).tolist()
        lod=one('LOD_INPUTS')
        # Thresholds are initialized before any root rejection. Original prefix
        # native capture supplies their bits for rejected cases separately.
        if lod:original['threshold_bits']=lod['thresholds'].split(',')
        planes=[]
        if one('ROOT_PLANES'):
            data=words(one('ROOT_PLANES')['data'])
            for j in range(int(one('ROOT_PLANES')['count'])):
                off=j*24;nx,ny,nz,pad=struct.unpack_from('<4I',data,off)
                planes.append({'nx_bits':f'{nx:08X}','nz_bits':f'{nz:08X}','offset_le':data[off+16:off+24].hex(),'ny_bits':f'{ny:08X}','padding_bits':f'{pad:08X}'})
        original['planes']=planes
        scores=[{'slot':int(r['d']['slot']),'score':struct.unpack('<d',words(r['d']['score']))[0]} for r in rows if r['kind']=='ANGLE_SCORE']
        original['scores']=scores
        tables=[r['d']['table'] for r in rows if r['kind']=='INVSQRT_INPUT']
        assert all(t==TABLE.hex() for t in tables)
        fixtures.append({'case':p.stem,'input':{'view_hex':view.hex(),'viewport_width':int(one('ROOT_CONSTANTS')['viewport'].split(',')[0],16),'height_stencil':samples,'quality':int(p.stem[-1]) if p.stem.startswith('quality') else 0},'emulated':original,'native':native[p.stem],'trace_sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
        for r in rows:
            if r['kind'] in ['ROOT_CONSTANTS','HEIGHT_TEST','FOOTPRINT_INITIAL','FOOTPRINT_FINAL','POINT_FILTER','ORDERED_HULL','ROOT_PLANES','ROOT_REJECT','BOUNDS_RESULT','ANGLE_SCORE','CONTROLLED_FRUSTUM']:
                selected.append({k:v for k,v in r.items() if k!='d'})
    dest.mkdir(exist_ok=True,parents=True)
    dump(dest/'camera_fixtures.json',fixtures)
    with (dest/'selected_original_events.tsv').open('w') as f:
        w=csv.DictWriter(f,fieldnames=['scenario','kind','pc','detail'],delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(selected)

class Stencil(Terrain):
    def __init__(self,samples):self.samples=samples
    def sample(self,x,z):return {'height12':self.samples[f'{x},{z}']}

def predictions(fixture,T):
    inp=fixture['input'];provider=Stencil(inp['height_stencil'])
    def height(x,z):
        h=provider.height(x,z)['expected']
        return T(h.numerator)/T(h.denominator)
    return predict(bytes.fromhex(inp['view_hex']),inp['viewport_width'],height,T,inp.get('quality',0))

def compare(fixtures):
    checks=0;summary={};predicted={}
    def ck(v,label):
        nonlocal checks
        checks+=1
        if not v:raise AssertionError(label)
    for f in fixtures:
        case=f['case'];p=predictions(f,np.longdouble);predicted[case]=p
        row={};em=f['emulated'];native=f['native']
        for name,obs in [('emulated',em),('native',native)]:
            if p['accepted']!=obs['accepted']:
                ck(name=='emulated' and case=='clear_exact' and p['accepted'] and not obs['accepted'],case+' unexpected admission mismatch')
                row[name]={'admission_mismatch':True,'reason':'known Ghidra sampler rounding at clearance boundary','plane_comparison':'unavailable after emulator rejection'}
                continue
            ck(p['accepted']==obs['accepted'],case+' '+name+' admission')
            if 'root' in p:ck(p['root']==obs['root'],case+' '+name+' root')
            if 'threshold_bits' in obs:ck(p['threshold_bits']==obs['threshold_bits'],case+' '+name+' thresholds')
            ck(len(p.get('planes',[]))==len(obs['planes']),case+' '+name+' plane count')
            normal_mismatch=0;offset_mismatch=0;max_abs=0;max_ulp=0
            for pp,op in zip(p.get('planes',[]),obs['planes']):
                normal_mismatch+=sum(pp[k]!=op[k] for k in ['nx_bits','ny_bits','nz_bits','padding_bits'] if k in op)
                offset_mismatch+=pp['offset_le']!=op['offset_le']
                a,b=(struct.unpack('<d',bytes.fromhex(q['offset_le']))[0] for q in [pp,op])
                err=abs(a-b);max_abs=max(max_abs,err);max_ulp=max(max_ulp,err/math.ulp(b))
            row[name]={'normal_bit_mismatches':normal_mismatch,'offset_bit_mismatches':offset_mismatch,'max_offset_absolute_error':max_abs,'max_offset_ulps':max_ulp}
            ck(normal_mismatch==0,case+' '+name+' normal bits')
            ck(max_ulp<=16,case+' '+name+' offset tolerance')
        if 'hull' in em:
            ck(p['keep']==em['keep'],case+' keep decisions')
            ck(len(p['hull'])==len(em['hull']),case+' hull length')
            err=max(abs(a-b) for pp,op in zip(p['hull'],em['hull']) for a,b in zip(pp,op))
            row['hull_max_absolute_error']=err
            ck(err<=4e-12,case+' hull position tolerance')
        if 'points' in em:
            row['ground']=p['ground']
            err=max(abs(a-b) for pp,op in zip(p['points'],em['points']) for a,b in zip(pp,op))
            ck(err<=4e-12,case+' footprint tolerance')
        if em['scores']:
            ck(len(p['scores'])==len(em['scores']),case+' score count')
            ulps=[abs(q['score']-o['score'])/math.ulp(o['score']) for q,o in zip(p['scores'],em['scores'])]
            row['score_max_double_ulps']=max(ulps)
            ck(all(q['slot']==o['slot'] for q,o in zip(p['scores'],em['scores'])),case+' candidate score slots')
            ck(max(ulps)<=2,case+' score tolerance')
        row['accepted']=p['accepted'];row['root']=p.get('root');row['threshold_bits']=p['threshold_bits']
        summary[case]=row
    return {'checks':checks,'cases':summary},predicted

if __name__=='__main__':
    a=argparse.ArgumentParser();a.add_argument('--extract',action='store_true');a.add_argument('--cases',type=Path);a.add_argument('--msn',type=Path);a.add_argument('--ter',type=Path);a.add_argument('--native',type=Path);a.add_argument('--emit-dir',type=Path);args=a.parse_args();dest=args.emit_dir or RUN/'evidence'
    if args.extract:extract(args.cases,args.msn,args.ter,json.loads(args.native.read_text()),dest)
    result,pred=compare(json.loads((dest/'camera_fixtures.json').read_text()))
    if args.extract:
        dump(dest/'comparison.json',result);dump(dest/'predictions.json',pred)
    else:
        assert result==json.loads((RUN/'evidence/comparison.json').read_text())
        assert pred==json.loads((RUN/'evidence/predictions.json').read_text())
    print('Camera cases:',len(result['cases']),'checks:',result['checks'])
