# Retail runtime object-lifetime cross-checks

**Scope:** v08–v15 findings discovered while exploring editor/game OBJ behavior. These concern **retail `i76.exe`**, not original editor algorithms. The repository's `ref/mission_execution` and `ref/vehicle_object_model` remain central architecture references.

- The 27-entry class callback descriptor system distinguishes one-time class-2/4 registration holds from persistent class-8 callback-list references. Dead, logically removed, unregistered and physically freed are different states.
- Classes 1 (car), 8 (artillery), and 9 (helicopter) share major allocations and vehicle components but differ in update and fatal-damage paths. Certain states are bulk-released when dedicated game-session heaps are destroyed.
- The 24-slot vehicle component array includes WDF weapon mounts, standalone primary vehicle components, GDF equipment, standalone class-`0x18` special equipment, local VDF attachments, and class-`0x20/0x21` damage visuals. A pointer slot is not itself an automatic counted reference.
- The class-1 initialization acquires additional references across populated slots after verified fresh-load equipment creation, and the destructor releases references from its then-current slots. In-place replacement or early pointer clearing therefore requires care; no normal triggering path has been demonstrated for every hypothetical imbalance.
- Separate class-`0x18` equipment starts as standalone roots. Under the inspected standard class-1 teardown, a possible original root reference remains unmatched, and respawn/multiplayer creation supplies a repeatable allocation path. This suggests **possible within-session retention**, not a measured permanent memory leak: the relevant world-object heap is destroyed during normal session cleanup.

These observations are for cross-binary consistency and prospective tests, not requirements to mimic engine heap management in a future editor.
