# Reproduction and service boundary

Requires licensed inputs matching manifest.json; Ghidra 12.1.4/JDK27;
Python3 with NumPy (x86 longdouble 64-bit significand), jsonschema/PyYAML;
GNU cc/as/ld; liblzo2 for the accepted fixture extractor; and Linux i386 execution.
The hosted sandbox blocks i386 syscalls with SIGSYS: native replay must run in
an authorized environment permitting those calls. No game payloads are shipped.

Asset-free review, from repository root:

```
python3 "$RUN/scripts/check_public.py"
python3 "$RUN/scripts/compare.py"
python3 agent/protocol/tools/validate_protocol.py "$RUN"
```

Fresh original-instruction replay (absolute paths; WORK must not exist):

```
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --exe "$EXE" \
  --gzf "$GZF_V100" --zfs "$ZFS" --msn "$MSN" --ter "$TER" \
  --work "$WORK" --repo "$REPO"
```

The driver authenticates every source and GZF digest, extracts private stock bus
fixtures with the unchanged accepted extractor, compiles the narrow numerical
service, imports a fresh project, checks the full executable section, executes
24 camera scenarios, runs the native numerical prefix/root probe and compares
independent predictions. It separately reconstructs complete downstream source
graphs from predicted camera geometry. The driver compares its comparison report
with the packaged report; trace hashes and derived output live only in WORK.
Do not use another worker's mutable Ghidra project. All measured fresh replay
outputs/digests are listed in reproduction.json/private_output_hashes.json.

The inherited #140 `I76_CameraBase.java` is unchanged. The owned topology observer
adds root stack snapshots, filter/order/plane observations, extra controlled
inputs and quality-setting calls. Stock resource/OS/heap/CRT services and source
backing are inherited; root/topology output regions and retained view are guarded
against harness writes. Controlled corners/clearance are installed **before**
sealing; their labels identify synthetic experiments, not coherent gameplay.

E executes original camera constructor/callbacks and terrain/frame/source code.
The unsupported FISTP pair and FPATAN use the accepted x86 host instruction
service. CRT `_ftol`, camera sin/cos, allocation, file mapping and other omitted
peripheral services are declared in the inherited source. Full service inventories
are in accepted #76/#140; this run does not advance raster/material claims.

H supplies a private mapped PE, independent page grid/default memory, TER,
view, viewport and explicit quality. It executes original table initializer and
quality setter, then original `00490A8B..00490B22` plus called root/sampler/math
bodies on i386. Only the continuation at `00490B23` is replaced with
`ADD ESP,4;RET` to stop before source topology. Arithmetic and root bodies are
unchanged; original CRT/camera setup are not invoked in H. This is a supplied
Linux research environment, not Win32 or a native retail frame. Native topology,
draw and raster are not measured.

`predict.py` independently derives everything from the camera input subobject
and independent height provider. `coordinate_model.py` and `verify_topology.py`
are unchanged accepted research dependencies from #141/#140, respectively.
Their identities and original accepted paths are recorded in provenance.json.
`compare.py` reads observations only after prediction; `check_public.py` removes
all observations and verifies identical predictions, and rejects six corruptions.

Public data contain controlled camera state, sparse height stencils, geometric
results, selected sparse instruction anchors and hashes. Original assets, complete
private traces, imported projects and generated native binaries remain excluded.
