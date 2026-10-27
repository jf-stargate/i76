# Documentation impact - original editor CRT small-block allocator

**Run:** `i76edit-20261027T003326Z-25e3484f`; track `i76edit`; original base SHA `34a15f060ff585a085619defeffca2fe20969609`; proposed PR pending. PE and annotated Ghidra identities are pinned in manifest.json.

**Disposition:** candidate reference addition at an editor object-ownership milestone; **no canonical change in this research run**.

**Relevant documentation:** `ref/editor/README.md`, `ref/editor/object_fsm_serialization.md` (legacy context), and potential future `manual/reference/editor/` ownership notes, subject to the documentation steward. Reconcile with merged original editor v31 destructor and v33 CRT allocator evidence (PR #35 and PR #41). No contradiction: this run directly executes the CRT SBH routines that previous original-instruction studies explicitly substituted.

**Evidence-linked candidates:**
- `editor.v34.sbh_native_reservation_and_metadata`: original `00424FB0` 4-MiB reserve/64-KiB initial commit and descriptor/page metadata bootstrap; native-original Ghidra trace with Windows VirtualAlloc isolated. Candidate ADD with OS limitation.
- `editor.v34.sbh_native_block_allocation_reuse`: original `00425310`, `00425590`, `00425260`, `004252C0` 30x128-byte page capacity and reclaim/reuse. Candidate ADD with controlled single-page fixture limitation.
- `editor.v34.sbh_native_cross_page_transition`: 31st 128-byte allocation goes to second page; both pages restore free capacity on free. Candidate ADD.
- `editor.v34.editor_object_full_native_sbh_lifetime`: original `00409840` constructor and `00409A60` destructor through original CRT SBH, node OS heap isolated. Candidate ADD but DO NOT claim native Windows heap was tested.

**Evidence:** `artifacts/ORIGINAL_CRT_SBH_RESEARCH.md`, `evidence/SBH_VALIDATION.json` and private checkpoint SHA256 `1b5b2d3f8e06c04b9cfa1380fe706eb91fee9c510eb4bae57d8632c1c78e5a94`. This run is not a promotion decision, and no existing immutable run or historical ref/ content is changed.

**Open questions:** Actual CRT startup config and small-block threshold, Win32 VirtualAlloc/HeapAlloc physical behavior, page decommit and region cleanup, failure handling and authentic editable .I76 export.
