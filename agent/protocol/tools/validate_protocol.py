#!/usr/bin/env python3
"""Advisory checks only. This is not GitHub access enforcement."""
import json, re, hashlib, pathlib, sys
import yaml
from jsonschema import Draft202012Validator
ROOT=pathlib.Path(__file__).resolve().parents[3]
P=ROOT/"agent/protocol"
R=re.compile(r"^(i76exe|i76edit|i76shell|shared)-[0-9]{8}T[0-9]{6}Z-[0-9a-f]{8}$")
def policy():
    p=yaml.safe_load((P/"access.yaml").read_text())
    assert p["default"]=="deny" and p["publication"]["direct_main_push"] is False
    assert p["publication"]["autonomous_run_merge"] is False
    assert (P/"VERSION").read_text().strip()==p["schema_version"]=="1.0.4"
    assert p["publication"]["required_formal_approvals"]==0
    assert p["publication"]["manual_maintainer_decision_required"] is True
    assert p["publication"]["require_separate_reviewer_for_authoritative_changes"] is False
    assert p["publication"]["require_current_base_revalidation"] is False
    assert p["publication"]["require_fresh_base_for_canonical_changes"] is True
    assert p["publication"]["require_current_head_integrity_at_acceptance"] is True
    assert p["publication"]["require_mergeability_check_at_acceptance"] is True
    assert p["documentation"]["legacy_checkpoint"]=="ref/"
    assert p["documentation"]["living_reference"]=="manual/reference/"
    assert p["documentation"]["mutate_merged_runs"] is False
    assert (P/"templates"/"DOCUMENTATION_IMPACT.md").is_file()
    assert (ROOT/"manual/roadmap/DOCUMENTATION_WORKFLOW.md").is_file()
    versions=json.loads((P/"SCHEMA_VERSIONS.json").read_text())
    assert versions["publication_protocol_version"]==p["schema_version"]
    assert versions["default_research_schema_version"]=="1.2.0"
    assert versions["supported_research_schema_versions"]==["1.0.0","1.1.0","1.2.0"]
    assert p["run_identity"]["tracks"]==["i76exe","i76edit","i76shell","shared"]
    for version in versions["supported_research_schema_versions"]:
        for kind,example in (("run","manifest"),("finding","findings")):
            schema=json.loads((P/versions["schemas"][version][kind]).read_text())
            Draft202012Validator.check_schema(schema)
            example_dir=P/"examples"
            if version!="1.0.0": example_dir=example_dir/("v"+version)
            if (example_dir/(example+".json")).exists():
                Draft202012Validator(schema).validate(json.loads((example_dir/(example+".json")).read_text()))
    return p
def safe_path(name):
    if not name or name.startswith("/") or "\\" in name or "//" in name or any(s in ("",".","..") for s in name.split("/")): raise ValueError("unsafe path")
    return name
def evaluate(path,run,branch,existing=False):
    p=policy();path=safe_path(path)
    if not R.fullmatch(run):return False
    track=run.split("-")[0]
    if branch!=f"agent/{track}/{run}":return False
    if path.startswith("agent/runs/"):
        return not existing and path.startswith(f"agent/runs/{track}/{run}/")
    return any(path==e["prefix"] or (e["prefix"].endswith("/") and path.startswith(e["prefix"])) for e in p["path_rules"])
def validate_run(directory):
    directory=pathlib.Path(directory).resolve()
    manifest=json.loads((directory/"manifest.json").read_text())
    findings=json.loads((directory/"findings.json").read_text())
    version=manifest.get("schema_version")
    registry=json.loads((P/"SCHEMA_VERSIONS.json").read_text())
    assert version in registry["supported_research_schema_versions"] and findings.get("schema_version")==version
    for s,v in (("run",manifest),("finding",findings)):
        Draft202012Validator(json.loads((P/registry["schemas"][version][s]).read_text())).validate(v)
    run=manifest["run_id"];assert R.fullmatch(run)
    assert directory.name==run and directory.parent.name==manifest["track"] and run.startswith(manifest["track"]+"-") and findings["run_id"]==run
    for artifact in manifest["artifacts"]:
        rel=safe_path(artifact["path"]);target=directory/rel
        assert target.is_file() and not target.is_symlink() and target.resolve().is_relative_to(directory)
        assert target.suffix.lower() not in {".exe",".dll",".pak",".zfs",".gzf",".msn",".ter",".zip",".tar"}
        assert target.stat().st_size<=5*1024*1024
        if "bytes" in artifact:assert target.stat().st_size==artifact["bytes"]
        assert hashlib.sha256(target.read_bytes()).hexdigest()==artifact["sha256"]
    assert manifest["validation"]["passed_count"]<=manifest["validation"]["test_count"]
    return True
if __name__=="__main__":
    policy()
    if len(sys.argv)>1:validate_run(sys.argv[1])
    print("I76 protocol checks passed (advisory; no merge authority)")
