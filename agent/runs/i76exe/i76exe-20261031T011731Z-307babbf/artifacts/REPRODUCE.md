# Reproduce original draw and native spans

Prerequisites: private licensed retail EXE and ZFS, the annotated v97 GZF matching manifest/provenance, Ghidra 12.1.4 PUBLIC with compatible Java (measured OpenJDK 27-ea), Python3, liblzo2 and accepted protocol Python dependencies. No game binary, archive or Ghidra payload is published.

Set SRC to a checkout containing this run, RUN to `$SRC/agent/runs/i76exe/i76exe-20261031T011731Z-307babbf`, and WORK to a nonexistent private scratch directory outside SRC. Set HEADLESS, EXE, GZF and ZFS to independently located inputs. Run:

```bash
python3 "$RUN/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
```

The driver authenticates all three inputs before experiments, invokes the unchanged accepted complete camera/queue and polygon drivers, then runs three staged prerequisite failures. These expected failures are accepted only at `000C0DD2`, `00473788` (zero-capacity stop) and `000C0DC2`; no completion marker is allowed. It then runs native visible/behind, native fresh-GZF repeat, native finalizer/span extension and a separately imported finalizer repeat. It compares each complete positive trace byte-for-byte, extracts opcodes through a read-only GZF audit, matches those bytes against retail PE and runs the standalone verifier with six corruption controls. No output is written into accepted runs or the published evidence.

All final five cases have exactly the inherited optional-name warning at 004461E0. Successful cases must contain PRODUCER_COMPLETE and no ERROR. Finalizer positives explicitly contain BOUNDARY_STOP at the pre-instruction 0047CB00 boundary, not an original finalizer return. Import/config/cache/log paths live under WORK; probes process projects read-only.

Independent verification after reproduction:

```bash
python3 "$RUN/scripts/verify_draw.py" --source-repo "$SRC" --private "$WORK" --exe "$EXE" --corruptions
```

Expected native verifier count: 11,350 positive assertions plus 292 upstream source/projection assertions delegated to the accepted independent oracle; six corruptions reject. The accepted drivers independently pass 1,402 baseline checks and 2,769 polygon checks before their additional mutation controls. Public-only verification needs no private assets:

```bash
python3 "$RUN/scripts/verify_draw.py" --source-repo "$SRC" --corruptions
python3 "$RUN/scripts/verify_draw.py" --source-repo "$SRC" --evidence "$RUN/evidence/corrupted_sample.json"
```

The first command passes 9,810 assertions plus 292 upstream assertions. The second **must exit nonzero**; the intentionally modified native source-polygon argument disagrees with original fallback output. Its inherited upstream oracle's diagnostic mentions a substituted draw because the oracle's terminal row is normalized for source-only verification; the actual CE40 body executes in this run. Native command/edge/plane/span checks are independent in verify_draw.py, and CE40 service events are forbidden.

`--emit` is for assembling provisional evidence in a new run only. Ordinary reproduction must not use it or mutate any immutable artifact. `audit_retail.py` verifies the GZF-derived instruction bytes independently against the EXE; annotated names do not authenticate semantics. The static audit script can be used privately to inspect callees without mutating functions or symbols.

Trusted preflight uses a pristine checkout at exact base `4de0c902628535fd91c3a5bd7b15b3af622d7ee8`:

```bash
python3 -m unittest discover -s .github/tests -v
python3 "$TRUSTED/agent/protocol/tools/validate_protocol.py" "$RUN"
python3 "$TRUSTED/.github/scripts/pr_integrity.py" --repo "$SRC" --trusted-root "$TRUSTED" --base-sha 4de0c902628535fd91c3a5bd7b15b3af622d7ee8 --head-sha "$HEAD" --branch agent/i76exe/i76exe-20261031T011731Z-307babbf
```

Run the unit command with TRUSTED as the current directory. Validate the exact proposed commit, then verify GitHub's required integrity check on the published exact head. Passing CI does not approve the research. Leave the PR unmerged.
