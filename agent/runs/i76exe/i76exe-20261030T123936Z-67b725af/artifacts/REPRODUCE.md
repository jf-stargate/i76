# Full reproduction

Reproduction requires a licensed local copy of the authenticated retail executable, the matching annotated Ghidra archive, and the original M06 mission and terrain files. These inputs and full traces stay outside the repository.

From the repository root, run:

```sh
agent/runs/i76exe/i76exe-20261030T123936Z-67b725af/scripts/reproduce.sh \
  /path/to/ghidra/support/analyzeHeadless \
  /private/path/i76_mission_v97_verified_names.gzf \
  /private/path/i76.exe \
  /private/path/M06.MSN \
  /private/path/M06.TER \
  /private/path/new-private-work-directory
```

The work directory must not already exist. The script imports the GZF twice into separate projects, audits original retail function bytes and selected functions, runs primary/contrast/rejected/pool scenarios, reruns primary from a fresh import, independently checks source TER provenance and transformed/candidate geometry, then validates the run manifest. The output directory contains private traces and binary snapshots; do not publish it.

The controlled primary, contrast and rejected views use an identity 3×3 basis with zero translation at record+0x40. The `pool` scenario is a separate diagnostic using an explicit translation and a test-owned 1 MiB record arena at 0x47000000. This initializes backing storage only; original allocator, emitter and clip instructions remain active. The diagnostic’s clip rejections are expected bounded findings, not a successful render.
