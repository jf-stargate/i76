# Documentation impact - editor CRT startup and small-block reclamation

Research run: i76edit-20261027T010513Z-3eb837e1; track i76edit; original base 34a15f060ff585a085619defeffca2fe20969609; original PE/Ghidra identities in manifest. PR and merge decision: pending.

Disposition: **candidate addition / qualifies existing v34 findings**. Do not directly change manual/reference or legacy ref/ in this research PR. Candidate steward-owned subsystem: manual/reference/editor/ object construction and CRT memory ownership. Related historical ref/editor/README.md and v34 proposed run i76edit-20261027T003326Z-25e3484f (draft PR #43).

Evidence-linked candidate findings:
- editor.v35.original_CRT_default_threshold: original PE .data 00438674 has 0x1e0; 00424181 calls 00424F00; 00424F90 setter has no detected static xrefs. Add carefully, avoid claims about all possible indirect calls.
- editor.v35.native_CRT_startup_and_failure_cleanup: original 00424F00/00424FB0 init and initial VirtualAlloc failure cleanup, 00424F40 native heap shutdown; Win32 service callbacks isolated.
- editor.v35.natural_SBH_page_decommit: original 004252C0 counts 32 wholly freed pages and itself calls 00425180(16); validated with 931 original CRT allocations/frees and synthetic OS reserve/commit/decommit calls.
- editor.v35.native_empty_region_release: an explicit second call 00425180(16) causes original 00425120 region release when all 1024 page states decommitted; do NOT describe that second call as naturally scheduled.

Evidence: artifacts/V35_STARTUP_DECOMMIT.md; evidence/V35_AGGREGATE.json; original VAs above; private checkpoint SHA256 193c98b07a68b922cb8a2a400036a8309e92f346a45216f7ba4124b79182f5d0. Native Ghidra x86 code executed with Win32 heap/virtual memory stubbed; exact scripts and trace in private checkpoint.

Reconciliation: extends v34 original SBH allocation/free evidence; eliminates synthetic SBH threshold setting in tested startup while leaving Windows OS/CRT startup integration unverified. One wrong-address second-commit harness was rejected and corrected. No conflict with v31/v33 destructor research.

Handoff only, not a promotion decision. Documentation steward should reconcile accepted run findings separately under current main with human review. No edits to ref/, manual/reference/ or agent/promotions/ here.
