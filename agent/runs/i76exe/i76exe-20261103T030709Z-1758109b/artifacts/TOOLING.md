# Separate tooling handoff

Path: `agent/tools/ghidra/reconcile-v100-v102/I76_Reconcile_v100_v102_20261103.java`.
Production source SHA-256: `40e5ce10abbd40f37e7d055f5dc7e2c6af962a9bf66b727a4b4d83ce01b9ba31`, bytes **63235**.
Shared branch: `tooling/reconcile-v100-v102-20261103`; separate draft tooling PR, link recorded at publication. Research branch owns only `agent/runs/i76exe/i76exe-20261103T030709Z-1758109b`. Production source tested byte-for-byte via private standalone copy; no destructive fixtures in its directory.

Both proposals require human review, passing exact-head integrity and mergeability. Neither merges or promotes a baseline. GUI test outstanding; exact-v99 headless validation passed.
