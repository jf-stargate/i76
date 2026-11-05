"""Rebuild metadata hashes for this owned research run; no proprietary artifacts."""
import json,hashlib
from pathlib import Path
RUN='i76exe-20261105T021753Z-998542c9'
BASE='999fcc0798c7756bab34d0fa46e43bf2a21e8236'
def sha(b):return hashlib.sha256(b).hexdigest()
def main():
    r=Path(__file__).resolve().parent.parent
    def dump(n,o):(r/n).write_text(json.dumps(o,sort_keys=True,indent=2)+'\n')
    validation=dict(status='passed',test_count=76,passed_count=76,notes='20 authentic original decodes; 14 original synthetic; 6 bounded-decoder rejects; 24 authentic callbacks (296 stores); 8 selection; 2 original M16 selection/mark; 2 reserved-index callbacks (10 synthetic stores). Fresh-project static audit/input checks and exact execution replay also passed; no native Windows/frame claim.')
    claims=[
      ('texture.decode','Original 0044B430 reconstructs tightly packed indexed texels from row-major CBK tiles or solid tokens; 20 authentic complete-buffer comparisons cover all 18 observed shapes.','proven','high','VQM_CBK_SPEC.md',['execution.json','instruction_validation.json'], '0044B430','Original-x86 emulation with supplied inputs; 5987 independent corpus decodes are not all original executions; host validation is stricter than retail.'),
      ('texture.selection','Decoded VQM cache precedes preference; MAP-first and VQM-first fallback rules differ, and selected VQM with missing CBK fails without MAP recovery.','proven','high','TEXTURE_SELECTION.md',['selection.json','callgraph.json'],'004474B0','Resource APIs substituted; original archive selection/collisions and failed-allocation recovery are not executed.'),
      ('texture.owner','Authentic bus/GTSi TMT decoding and original owner-slot construction feed 0044A290 and original VQM/CBK runtime texture construction in one state per fixture.','proven','high','RUNTIME_TEXTURE.md',['execution.json'],'0044A290','Owner, material relationship, descriptor backing and root invocations supplied; no vehicle/GEO constructor or animation clock in these states.'),
      ('texture.samples','Original full shade and composition callbacks consume authentic original-decoded textures and perform 296 verified indexed framebuffer stores with recorded texel/table reads.','proven','high','SOFTWARE_SAMPLING.md',['execution.json','executed_instructions.json','constants.json'],'00485120','Commands, surface and table installation supplied; q1 and selected exact slopes; no actual GEO textured commands, general perspective equivalence or display RGB.'),
      ('texture.m16','Qualifying owner contexts select authentic raw M16 resources through original 00471980 and update FULLRES header bits, independently of the indexed texture slot.','proven','high','TEXTURE_SELECTION.md',['execution.json'],'00471980','Context and initialized empty FULLRES bitmap supplied; no M16 payload decoding, list parser or native16-bit sampling.'),
      ('texture.perspective','General varying-q precision, authentic textured GEO command production and renderer cache invalidation on reused addresses remain unvalidated.','unresolved','unknown','RECONSTRUCTION_HANDOFF.md',['texture_references.json'],'004859E0','Static instruction contracts and bounded constant-q original execution do not establish full scene or CPU precision equivalence.')]
    findings=[]
    for fid,claim,status,conf,report,evidence,address,limit in claims:
        refs=['artifacts/'+report]+['evidence/'+e for e in evidence]
        findings.append(dict(finding_id=fid,claim=claim,status=status,confidence=conf,scope='game',limitations=limit,evidence=[dict(kind='run-artifact',ref=p,sha256=sha((r/p).read_bytes())) for p in refs]+[dict(kind='retail-address',ref='private:i76.exe',address=address,notes='Exact EXE identity in manifest; original bytes excluded')]))
    dump('findings.json',dict(schema_version='1.2.0',run_id=RUN,findings=findings));dump('validation.json',validation)
    artifacts=[]
    for d in ['artifacts','evidence','scripts']:
        for p in sorted((r/d).iterdir()):
            if not p.is_file() or p.suffix not in ['.py','.java','.json','.md']:continue
            kind='script' if d=='scripts' else 'report' if p.suffix=='.md' else 'table'
            artifacts.append(dict(path=p.relative_to(r).as_posix(),kind=kind,bytes=p.stat().st_size,sha256=sha(p.read_bytes())))
    inputs=[]
    root=r.parents[4] # checkout; private inputs are identified, not loaded by packager
    for name,kind,md5,digest in [
      ('i76.exe','retail-executable','a640ea0097dbb62e0c77b7f2847c7161','bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),
      ('i76exe_v100.gzf','other','bd62f1b3dc87548e7b27fc97a68cddd6','f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'),
      ('I76.ZFS','other','6dd57b1627d73e814247c0d9521f9778','0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d')]:
        inputs.append(dict(name=name,kind=kind,md5=md5,sha256=digest,notes='Private payload excluded; SHA-256 asserted by reproduction; identity corroborated by accepted resource/color runs.'))
    dump('manifest.json',dict(schema_version='1.2.0',protocol_version='1.0.5',run_id=RUN,track='i76exe',topic='Original VQM/CBK texture decoding, material ownership and indexed software sampling',base_commit=BASE,started_at='2026-11-05T02:17:53Z',summary='Research-only candidate: 20 authentic original decoder comparisons covering18 shapes; two authentic TMT/owner/texture fixtures reach296 original indexed stores under explicit services. Human review required; no reconstruction or canonical changes.',inputs=inputs,baselines=[dict(version='v100',program_name='i76.exe',baseline_id='i76exe_v100.gzf',baseline_sha256=inputs[1]['sha256'],storage_ref='private:scratch_data/i76exe_v100.gzf',notes='Authenticated private annotated input used by accepted resource/color runs; no new baseline promotion. Ghidra12.1.4 fresh import without analysis, domain file i76exe_v100, read-only exports; annotations unchanged.')],artifacts=artifacts,validation=validation,reproducibility=dict(status='complete',methods=['Authenticated private retail PE/GZF/ZFS inputs; reuse accepted bounded outer resource readers','Fresh read-only Ghidra12.1.4 static exports and exact PE byte/range checks','Unicorn2.1.4 original x86 with explicit provider/heap/CRT services; every original instruction authenticated','Independent bounded decoder, coordinate/table checks and negative controls; fresh replay'],script_refs=[dict(kind='run-artifact',ref=a['path'],sha256=a['sha256']) for a in artifacts if a['kind']=='script'],limitations='Complete for bounded procedures only; private inputs required. No native Windows/full frame, original archive runtime, scene-selected color state, general varying-q precision, M16 decode or display RGB.')))
if __name__=='__main__':main()
