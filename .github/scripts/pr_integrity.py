#!/usr/bin/env python3
"""I76: validate pull-request Git objects using trusted base-branch code only."""
import argparse, hashlib, json, re, subprocess, sys
from pathlib import Path, PurePosixPath
import yaml
from jsonschema import Draft202012Validator, FormatChecker, ValidationError
RUN=re.compile(r"^(i76exe|i76edit|shared)-[0-9]{8}T[0-9]{6}Z-[0-9a-f]{8}$")
SHA=re.compile(r"^[0-9a-f]{40}$")
FORBIDDEN={".exe",".dll",".pak",".zfs",".gzf",".msn",".ter",".zip",".tar",".7z",".rar",".iso",".ghidra",".gpr"}
SECRET=re.compile(rb"(?:ghp_[A-Za-z0-9]{36,}|github_pat_[A-Za-z0-9_]{40,}|-----BEGIN (?:RSA |EC |OPENSSH )?PRIVATE KEY-----)")
class Rejected(Exception): pass
def git(repo,*args,binary=False):
    p=subprocess.run(["git","-C",str(repo),*args],capture_output=True)
    if p.returncode: raise Rejected("Git operation failed: "+" ".join(args[:3])+" "+p.stderr.decode(errors="replace")[:200])
    return p.stdout if binary else p.stdout.decode().strip()
def path_ok(path):
    if not path or path.startswith("/") or "\\" in path or "\0" in path or "//" in path or any(p in ("",".","..") for p in path.split("/")) or path!=str(PurePosixPath(path)):
        raise Rejected("Unsafe path: "+repr(path))
    return path
def blob(repo,sha,path): return git(repo,"show",sha+":"+path_ok(path),binary=True)
def diff(repo,base,head):
    fields=[x for x in git(repo,"diff","--name-status","--no-renames","-z",base,head,binary=True).split(b"\0") if x]
    if len(fields)%2:raise Rejected("Malformed git diff")
    rows=[(fields[i].decode(),path_ok(fields[i+1].decode("utf8"))) for i in range(0,len(fields),2)]
    if len({p for _,p in rows})!=len(rows):raise Rejected("Repeated path")
    return rows
def mode(repo,sha,path):
    fields=[x for x in git(repo,"ls-tree","-z",sha,"--",path,binary=True).split(b"\0") if x]
    vals=[x.split(b" ",1)[0].decode() for x in fields if x.split(b"\t",1)[-1].decode("utf8")==path]
    if len(vals)!=1:raise Rejected("Missing tree entry: "+path)
    return vals[0]
def rule_for(path,rules):
    for r in sorted(rules,key=lambda x:len(x["prefix"]),reverse=True):
        prefix=r["prefix"]
        if (path.startswith(prefix) if prefix.endswith("/") else path==prefix):return r
    return None
def verify_run(repo,head,root,files,trusted):
    required={root+"/manifest.json",root+"/findings.json",root+"/validation.json"}
    if not required.issubset(files):raise Rejected("Incomplete run: "+root)
    m=json.loads(blob(repo,head,root+"/manifest.json"))
    f=json.loads(blob(repo,head,root+"/findings.json"))
    v=json.loads(blob(repo,head,root+"/validation.json"))
    for kind,obj in (("run",m),("finding",f)):
        schema=json.loads((trusted/"agent/protocol/schemas"/(kind+".schema.json")).read_text())
        Draft202012Validator(schema,format_checker=FormatChecker()).validate(obj)
    rid=root.rsplit("/",1)[1];track=root.split("/")[2]
    if not RUN.fullmatch(rid) or m["run_id"]!=rid or f["run_id"]!=rid or m["track"]!=track or v!=m["validation"]:raise Rejected("Run identity/validation mismatch")
    if not SHA.fullmatch(m["base_commit"]):raise Rejected("Invalid run base SHA")
    git(repo,"merge-base","--is-ancestor",m["base_commit"],head)
    if v["passed_count"]>v["test_count"] or (v["status"]=="passed" and v["passed_count"]!=v["test_count"]):raise Rejected("Invalid test counts")
    ids=[x["finding_id"] for x in f["findings"]]
    if len(ids)!=len(set(ids)):raise Rejected("Duplicate finding ID")
    used=set()
    for artifact in m["artifacts"]:
        p=root+"/"+path_ok(artifact["path"])
        if p not in files or p in used:raise Rejected("Untracked/duplicate artifact: "+p)
        used.add(p);raw=blob(repo,head,p)
        if len(raw)>5242880 or hashlib.sha256(raw).hexdigest()!=artifact["sha256"]:raise Rejected("Artifact hash/size mismatch: "+p)
        if "bytes" in artifact and artifact["bytes"]!=len(raw):raise Rejected("Artifact bytes mismatch")
    if files-required-used:raise Rejected("Unlisted run artifacts")
    return {"run_id":rid,"artifacts":len(used),"findings":len(ids)}
def inspect(repo,base,head,trusted,branch=None):
    if not SHA.fullmatch(base) or not SHA.fullmatch(head):raise Rejected("Requires exact 40-char commit SHAs")
    for commit in (base,head):
        if git(repo,"cat-file","-t",commit)!="commit":raise Rejected("Ref is not a commit")
    policy=yaml.safe_load((trusted/"agent/protocol/access.yaml").read_text())
    if policy["default"]!="deny":raise Rejected("Policy must be default-deny")
    rows=diff(repo,base,head)
    if not rows:raise Rejected("Empty changeset")
    runs={};classes={}
    for state,p in rows:
        r=rule_for(p,policy["path_rules"])
        if not r:raise Rejected("Unlisted path: "+p)
        classes[r["class"]]=classes.get(r["class"],0)+1
        if state=="D":raise Rejected("Deletion forbidden without separate governance: "+p)
        if state not in ("A","M"):raise Rejected("Unexpected change type")
        m=mode(repo,head,p)
        if m not in ("100644","100755"):raise Rejected("Symlink or nonregular file: "+p)
        raw=blob(repo,head,p)
        if len(raw)>5242880 or PurePosixPath(p).suffix.lower() in FORBIDDEN:raise Rejected("Oversized/proprietary file: "+p)
        if SECRET.search(raw):raise Rejected("Potential secret in: "+p)
        if p.startswith("agent/runs/"):
            bits=p.split("/")
            if state!="A" or m!="100644" or len(bits)<5 or not RUN.fullmatch(bits[3]) or bits[2]!=bits[3].split("-")[0]:raise Rejected("Invalid append-only run: "+p)
            runs.setdefault("/".join(bits[:4]),set()).add(p)
    validated=[]
    if runs:
        if len(runs)!=1:raise Rejected("Only one run per PR")
        root,files=next(iter(runs.items()));track=root.split("/")[2];rid=root.split("/")[3]
        if branch and branch!="agent/"+track+"/"+rid:raise Rejected("Run branch does not own run")
        if len(rows)!=len(files):raise Rejected("Cannot mix run with shared changes")
        validated=[verify_run(repo,head,root,files,trusted)]
    return {"changed_files":len(rows),"classes":classes,"runs":validated,"publication":"review-required"}
def main():
    p=argparse.ArgumentParser()
    for x in ("base-sha","head-sha"):p.add_argument("--"+x,required=True)
    p.add_argument("--repo",type=Path,default=Path("."))
    p.add_argument("--trusted-root",type=Path,default=Path("."))
    p.add_argument("--branch")
    a=p.parse_args()
    try:print(json.dumps(inspect(a.repo.resolve(),a.base_sha,a.head_sha,a.trusted_root.resolve(),a.branch),indent=2))
    except (Rejected,ValueError,KeyError,OSError,ValidationError,AssertionError) as exc:
        print("I76 PR INTEGRITY FAILED: "+str(exc),file=sys.stderr);sys.exit(1)
if __name__=="__main__":main()
