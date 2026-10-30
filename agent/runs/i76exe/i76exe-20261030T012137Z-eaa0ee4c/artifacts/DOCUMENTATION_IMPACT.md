# Documentation impact — selected initialization prerequisites

Run `i76exe-20261030T012137Z-eaa0ee4c`; i76exe, CAP-CONTROL-01, ENG/VEH/OBJ interfaces. Base `980037f49b348e14ccdde8ba2961174a8647f090`; PR pending at artifact creation. Binary/GZF/DLL identities: manifest and `evidence/results.json`. Classification: **candidate update; no canonical change in this run**.

Proposed separate targets: `manual/reference/engine/frame_scheduling.md` (now present after concurrent PR #62), selected lifecycle/vehicle initialization reference (new). Existing `manual/reference/engine/vehicle_construction.md` remains a bounded construction reference. Relevant historical context: `ref/mission_execution/MISSION_EXECUTION_CONTRACT.md` startup/frame order and `ref/vehicle_object_model/i76_vehicle_object_runtime_reference.md` lifecycle; not fully revalidated here.

## F1-pending-localization-prerequisite

- Claim/status: Original pending dispatcher 00461B80 calls and returns six descriptor initializers, then class32 damage-child construction reaches unresolved StrLookup_Global_Object/StrLookupFind imports before class1; independent EXE startup/import and retail DLL export checks identify the authentic localization construction prerequisite. **Proven in bounded original-instruction emulation with declared services**, high confidence.
- Evidence: `evidence/selected_events.json`, SHA-256 `46a7982940ce2d9e0360aec0d85d20ef71f6f5f9cb6868ae398b3cfcb7f77dcd`; independent PE/identities `evidence/results.json`, SHA-256 `af47444038c9c8f9ddbdc91c9a54b5c2accc24a4fff4e0ca2441bbe230febcef`; exact reproduction/verifier in owned scripts.
- Impact: add qualified prerequisite/control evidence; defer CAP-CONTROL completion.
- Limits/contrary evidence: No complete pending drain or class1 through pending; data import and lookup are unprovided. This is the next exposed dependency, not an exhaustive enumeration of later requirements.

## F2-peripheral-original-initialization

- Claim/status: Original class31 0046F2B0 allocates the animation consumed by 0046F420; original class34 0045F810 writes root/self linkage consumed by 0045FAF0. Initialized direct controls return without new invalid reads; omission reproduces the prior invalid reads. **Proven in bounded original-instruction emulation with declared services**, high confidence.
- Evidence: `evidence/selected_events.json`, SHA-256 `46a7982940ce2d9e0360aec0d85d20ef71f6f5f9cb6868ae398b3cfcb7f77dcd`; independent PE/identities `evidence/results.json`, SHA-256 `af47444038c9c8f9ddbdc91c9a54b5c2accc24a4fff4e0ca2441bbe230febcef`; exact reproduction/verifier in owned scripts.
- Impact: add qualified prerequisite/control evidence; defer CAP-CONTROL completion.
- Limits/contrary evidence: Direct init/post controls are separate from complete pending scheduling. Inherited optional-geometry null-string warning remains; no general radar/texture/device correctness.

## F3-bounded-hardware-fsincos

- Claim/status: Original FSINCOS 0049D409 and FSTP32 boundaries 0049D40B/0049D40E delegated to native x87 yield bit-identical original-helper returns to an independent native helper oracle for seven operands across four rounding modes; raw P-code negative stops at 0049D409. **Proven in bounded original-instruction emulation with declared services**, high confidence.
- Evidence: `evidence/selected_events.json`, SHA-256 `46a7982940ce2d9e0360aec0d85d20ef71f6f5f9cb6868ae398b3cfcb7f77dcd`; independent PE/identities `evidence/results.json`, SHA-256 `af47444038c9c8f9ddbdc91c9a54b5c2accc24a4fff4e0ca2441bbe230febcef`; exact reproduction/verifier in owned scripts.
- Impact: add qualified prerequisite/control evidence; defer CAP-CONTROL completion.
- Limits/contrary evidence: Numerical instruction services, masked finite abs(x)<2^63 domain. No complete FPU status/tag/unmasked exception or arbitrary-value equivalence; inherited numerical services remain.

## F4-selected-direct-init-post-control

- Claim/status: Entire original selected class1 initializer 00463120 and post 00463950 return in a direct control; original selected gate is true, initialization sets flag 0x80000 and seven list counts 6,5,4,5,4,5,4, without injected throttle/mode/speed commands. **Proven in bounded original-instruction emulation with declared services**, high confidence.
- Evidence: `evidence/selected_events.json`, SHA-256 `46a7982940ce2d9e0360aec0d85d20ef71f6f5f9cb6868ae398b3cfcb7f77dcd`; independent PE/identities `evidence/results.json`, SHA-256 `af47444038c9c8f9ddbdc91c9a54b5c2accc24a4fff4e0ca2441bbe230febcef`; exact reproduction/verifier in owned scripts.
- Impact: add qualified prerequisite/control evidence; defer CAP-CONTROL completion.
- Limits/contrary evidence: Direct control only. Complete selected pending initialization/frame/input delivery and control-induced physical state change not established. Optional resources/services and inherited setup warning remain.

## Reconciliation and next work

Confirms and narrows merged PR #58's selected-post diagnostic: peripheral null reads result from omitted original initializers; hardware FSINCOS alone is insufficient to reproduce directed-rounding float stores. Complete class1 callback return is now shown only in a direct control, not a complete original selected pending/frame path. The accepted roadmap is a planning snapshot; #58 is merged, but CAP-CONTROL-01 still lacks original input delivery and a measured control-induced vehicle change.

Recover authentic STRLKUP DLL binding (including data-import indirection), original lang.txt construction and lookup before resuming 00461B80. Then assess new pending nodes, original selected input production and full pre/post scheduling. The discovered localization dependency is the next observed prerequisite, not a claim that it is the sole remaining gap. No conflict with the existing vehicle-construction promotion, which did not claim complete selected initialization.

## Publication boundary

No edits to `ref/`, `agent/promotions/` or `manual/reference/`. A designated steward reconciles **merged** evidence and exact artifact hashes in a separate fresh-base documentation/promotion PR. Human acceptance is required. Live ruleset was disabled at bootstrap and restored active before publication; this run remains proposal-only, never self-merged or automatically promoted.

Publication recheck: main advanced to `8b0cf19` through documentation-only PRs #61/#62. Read the reconciled roadmap, new `frame_scheduling.md` and `engine_class1_frame_scheduling_20261029.md` promotion; their selected-path limits agree with this run. No policy/tooling or owned-run changes overlap. Original research base is preserved under the isolated run-only protocol.
