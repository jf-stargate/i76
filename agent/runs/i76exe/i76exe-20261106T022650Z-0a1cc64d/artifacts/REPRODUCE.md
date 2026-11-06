# Reproduction and validation

Use this checkout at base `19c755a77db404ba9cb0ab51f307b4261e983aff` plus this run. Both merged prerequisite runs are required: the scripts explicitly use immutable #140 observer/model/service sources and #141 authenticated resource identities. Source digests are in evidence/provenance.json. No mutable project from another investigation is used.

Requirements: Linux x86-64 with i386 execution and permission to ptrace one's own children, Python3, binutils `as`/`ld`, C compiler, Ghidra12.1.4 and Java (measured JDK27), liblzo2, and licensed inputs matching manifest.json. No pip package is required for the native probe; repository integrity validation uses the accepted protocol requirements. All work paths below must initially be absent. All arguments should be absolute paths. `RUN` is this owned run directory; `HEADLESS` is Ghidra's analyzeHeadless; `CD_M02_MSN` is the exact authenticated CD metadata from #141. TER payload identity must also match.

```
python3 "$RUN/scripts/reproduce.py" --exe "$EXE" \
  --m06-msn "$M06_MSN" --m06-ter "$M06_TER" \
  --m02-msn "$CD_M02_MSN" --m02-ter "$M02_TER" \
  --work "$PRIVATE/native" --emit "$PRIVATE/native-evidence"

python3 "$RUN/scripts/geometry_reproduce.py" --headless "$HEADLESS" \
  --exe "$EXE" --gzf "$GZF_V100" --zfs "$ZFS" \
  --msn "$M06_MSN" --ter "$M06_TER" --work "$PRIVATE/geometry"

python3 "$RUN/scripts/verify_geometry.py" --cases "$PRIVATE/geometry/cases" \
  --emit "$PRIVATE/geometry-evidence"
```

The geometry driver authenticates inputs, extracts exact accepted VCF fixtures, imports its own fresh GZF project, compares the full executable section, and runs six variants. Private script copies combine the immutable observer classes with the owned subclass; only the copied observer gains an allocation check before each adaptive word read. Original code bytes stay unchanged. Modified MSN/TER copies, raw geometry/traces and compiled shim/helper stay private. Passing Ghidra exit status alone is insufficient; the driver requires completion without BLOCKER, and the independent verifier checks every source vertex, complete arena, all decisions, flattened loops and complete class-read sequence.

Native `reproduce.py` maps the authenticated PE and controlled terrain, supplies the 16384-slot grid, stops a traced child before the original slice, installs origin/half-size registers, then single-steps unchanged CPU instructions. It records each conditional next PC and guards every terrain load against exact backing ownership before executing it. Full-grid equality to #141's original parser output was measured for both missions: 32768 slots match (environment_validation.json). The native slice starts after earlier LOD/height tests. Linux loading/tracing and this register entry are experimental services, not original Windows execution.

For asset-free review:

```
python3 "$RUN/scripts/verify_public.py"
python3 agent/protocol/tools/validate_protocol.py "$RUN"
```

The public verifier checks address/stride/site order and original class branches, exhaustive allowed page residues, and rejects address, word and branch corruption. It does not independently authenticate unpublished terrain bytes. For a geometry negative control, rerun verify_geometry.py with `--corrupt-arena`; it must fail at `exact original complete interleaved edge/leaf arena` and must not publish passing output.

Measured results: 124 native cases, 4380 attempted scan reads (4375 executed; five blocked), and six full M06 geometry cases. A fresh native repeat matches every case record exactly. Two fresh GZF imports produce all78 raw geometry/sidecar files byte-for-byte identically. A changed arena is rejected. See results.json, public_verification.json, geometry_comparisons.json, native_repeat.json, geometry_repeat.json and negative_control.json for counts/hashes. Full retail source geometry also matches #140 primary. Do not interpret full Ghidra geometry as native full-geometry numerical parity; #141's x87 qualifications remain applicable.
