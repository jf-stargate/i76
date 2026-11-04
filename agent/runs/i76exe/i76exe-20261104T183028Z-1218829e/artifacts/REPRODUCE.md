# Reproduction and provenance

Track i76exe; owned run i76exe-20261104T183028Z-1218829e; base 7406234ef017a3fbb3539f2cc29cfd9e601dddbd. Main was independently resolved by Git transport and GitHub API. It had advanced beyond the assignment's fc1f10ab4d86cd8546897634431b56a575dc2cfe. Protocol 1.0.5; schema 1.2.0. See bootstrap.json for live enforcement. Research-only proposal, never self-merge.

From the run directory, Python's standard library alone reproduces the public ranking:

```sh
python3 scripts/reproduce.py --ranking-only --private-dir /tmp/i76-boundary-public-new
```

Use a new, nonexistent output directory each time. It checks the frozen hashes and recreates ranking.json and BOUNDARY_RANKING.md exactly. The two reports originally frozen at run root were relocated byte-for-byte to artifacts/ for protocol compliance. No frozen content changed. The freeze's local Git commit preserves the original layout and chronological declaration; it is not a signed independent timestamp or a proof of what a person read.

Full extraction requires licensed private retail PE, exact user-supplied v100 GZF, and Ghidra 12.1.4:

```sh
python3 scripts/reproduce.py \
  --headless /path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless \
  --pe /private/i76.exe --gzf /private/i76exe_v100.gzf \
  --private-dir /tmp/i76-boundary-full-new
```

This imports to a fresh disposable project with `-noanalysis`, extracts, verifies every body range against retail PE sections, reopens `i76exe_v100` with `-readOnly -noanalysis`, checks identical exported content, then regenerates compact features and ranks. Ghidra may require permission to initialize its normal user configuration. Do not point it at an existing project. Full private output includes instructions/references/whole-program users of relevant objects; it must not be committed. Input digests are enforced before analysis. No internet, Python package, compiler, decompiler or semantic-name lookup is required by the detector. Ghidra itself supplies listing/reference APIs; schema/integrity tooling has the repository's separate dependencies.

The public feature table contains only bounded functions and aggregate whole-program users of referenced data. It is sufficient for ranking but cannot independently regenerate Ghidra references or original byte comparisons without private inputs. Absence of indirect targets and exact undefined-object normalization are limitations, not verified emptiness at source level.

Optional post-freeze ablation/replay diagnostics, writing to a separate scratch directory:

```sh
python3 scripts/evaluate.py --out-dir /tmp/i76-boundary-diagnostics \
  /private/extraction.json /private/replay.json
```

It always uses this run's frozen features. `AuditControl.java` runs separately in the disposable project with `-process i76exe_v100 -readOnly -noanalysis`, returning private control.json. Then:

```sh
python3 scripts/validate_review.py /private/i76.exe /private/extraction.json \
  /private/control.json /tmp/i76-boundary-control-validation.json
```

The control is a separately scoped, post-freeze review of 00412C30–00412CBF; no out-of-range functions enter the blind ranking. validate_review.py checks all 21 internal gaps against PE bytes, five comparator-address pushes and the original switch-table addresses/entries without emitting retail bytes.

Three phases are separately recorded: (1) automated discovery and freeze, (2) manual original-instruction adjudication and method diagnostics, (3) comparison with accepted pilots. Manual interpretation names responsibilities only after the freeze and never overwrites a frozen rank. STRUCTURAL_EVIDENCE.md reviews all five top cuts, the next competitor, five bottom cuts and two wrapper-interior controls.

Ghidra reported 2,102 defined functions, image base 00400000, x86:LE:32:default. Source program metadata SHA-256 matched the PE. Private GZF and PE remained unchanged; source GZF was never reopened for saving. Program-wide modification number did not change during any of three extraction/audit scripts. Import/save bookkeeping raised it from 2 to 3 across sessions; read-only export content was identical. This is evidence of no analysis-script modification, not a claim that two database serializations have identical hashes.

The supplied annotated v100 database is an input identity, not an authoritative annotation baseline promoted by this run. Ghidra-defined bodies, references and datatypes may contain prior analyst choices. Semantic function names were omitted, not used as graph or scoring features. Exact function-boundary recovery and unrecognized functions remain outside this experiment.
