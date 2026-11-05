# Reproduce privately

Use the exact base commit recorded in manifest.json. Required private inputs:
retail orig/i76.exe and orig/I76.ZFS plus scratch_data/i76exe_v100.gzf, with hashes
in the manifest. Ghidra12.1.4, a supported JDK, Python3 with Unicorn2.1.4, and
system liblzo2 are required. Capstone is not used by the harness. Do not place
original resources, decoded images or Ghidra exports in the public run.

From a checkout containing this run, set shell variables to absolute paths:

```sh
run_scripts=/absolute/checkout/agent/runs/i76exe/i76exe-20261105T021753Z-998542c9/scripts
python_env=/absolute/private/venv/bin/python
"$python_env" "$run_scripts/reproduce.py" \
  --repo /absolute/checkout \
  --root /absolute/private-input-root \
  --work /absolute/new-private-output-directory \
  --headless /absolute/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
```

The work directory must not exist. The input root must have the relative paths
above. The script imports the GZF into a fresh project without analysis, exports
four request groups read-only, compares saved program-file snapshots, authenticates
all exported instructions/ranges against the original PE, runs corpus/model and
original-x86 comparisons, and checks input hashes again. Metadata is in work/
metadata; full exports and project stay private. Reproduction does not require
pre-extracted zfs/resources files or existing mutable projects.

For execution-only debugging, validate.py accepts --repo, --root and a new --out;
it authenticates the same inputs and creates only aggregate/sample metadata.
review.py provides the independent PE checks used by reproduce.py. CPU instruction
hash checks happen on every executed original instruction as well as at review.
No screenshot or image oracle is required: comparisons are exact indexed bytes,
coordinates, memory reads and output-buffer hashes for bounded fixtures.

Final recorded run: fresh private project, original input and saved-program
hashes unchanged. The published metadata is copied from that final reproduction.
See reproduction.json and VALIDATION.md. This does not execute a native Windows
installation, build reconstruction, or publish any decoded image.
