# Documentation impact — PIX/PAK indexing and resource resolution

Run `i76exe-20261104T195642Z-eaccd134`, i76exe, base `5f408a117da6d55e495714b648f41b43d708bf6e`.
PR pending at artifact creation. Original EXE/GZF identities: `instructions.json`
and manifest inputs/baseline. No canonical change in this PR; candidate update
for a separate designated-steward reconciliation after human acceptance.

Target: `manual/reference/engine/resource_acquisition.md`; possible new format
page under the same engine reference. Historical sources: the resource-acquisition,
ZFS extraction and vehicle-model references named in `BOOTSTRAP.json`.

- `pix.text.contract`: add verified decimal/LF text contract and variable token
  byte positions; explicitly distinguish 0x1C runtime rows from serialized text.
  Evidence: `PIX_PAK_FORMAT.md`, `instructions.json`, functions 00470660/00470B20;
  binary-static + authenticated corpus, high confidence.
- `pix.absolute.spans`: add absolute logical-PAK offsets, no member decompressor,
  1,758 pairs and 23,507 range-validated entries. Evidence: `corpus.json`,
  `examples.json`, 00470BAA..00470BB2; high confidence within base-game scope.
- `pix.lookup.duplicates`: retain four-DWORD comparison and flag unresolved CRT
  duplicate winner. Add 264 equal-content duplicate names, without claiming
  runtime collision testing. Evidence: `RESOURCE_PRECEDENCE.md` and corpus;
  high confidence on static path/corpus, unknown on selected original duplicate.
- `pix.lifecycle.boundaries`: narrow teardown/reinit assurances and add returning
  reporter/missing-PAK hazard. Evidence: `RESOURCE_LIFETIME.md`, 00470AC0,
  00470B84..00470BB2, 0042D5D0. Binary-static, high confidence, not native execution.

This confirms the accepted Pilot C RES route asymmetry; it fills its deferred
index serialization/teardown scope rather than replacing its evidence. Context
helper names 004B32F0 and 004B3550 are misleading: they allocate registered bytes
and HeapFree respectively, not size/lookup-only operations. This is a candidate
annotation clarification, not an applied rename. No contradiction with maintained
handle-based lifetime is implied; that is an independent safe design.

Unresolved: CRT equal-key winner, non-ASCII locale semantics, mission preference
state/media callbacks, original external teardown sequencing and other products'
variants. Direct compressed-ZFS integration still needs its own validated stream
layer. Proposed staged implementation is in `RECONSTRUCTION_HANDOFF.md`.

Every evidence artifact's SHA-256 and byte length is listed in `manifest.json`.
This handoff does not edit `manual/`, `ref/`, `agent/promotions/`, baselines or
protocol. The designated steward may reconcile merged findings in a separate
fresh-base documentation PR; only the human maintainer accepts that promotion.
