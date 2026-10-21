# Mission execution contract addendum — original-code emulator v0.6.0

This is an **evidence addendum** to I76-MISSION-0.4.0, not a replacement for the cumulative v0.4.0 document or a claim that all loader behaviors are specified.

## Observed contract upgrades

1. **Selected-wrapper failure return (D-E):** On cold missing-BWD2 and wrong-root-REV inputs, the real wrapper suffix at `004B4463` returns `EAX=1` even though the original root parser has written `NULL` to global `005DB97C`. This verifies the earlier static prediction for these concrete inputs.
2. **Repeated-load state across wrapper suffix (D-E):** Root BWD2 bit `0x80` is retained between two original-code wrapper/parser invocations. Missing BWD2 then reaches the world/ADEF parser after an earlier valid or revision-failed parse. Paired tests stub FSM imports to avoid modeling unrelated teardown.
3. **Nested AREV diagnostic (D-E):** Wrong nested AREV logs two native no-op reporter calls and the original parser still enters the FSM importer on the tested stock M06 layout.
4. **Optional FSM presence (D-E):** Renaming the nested FSM tag results in a non-null end cursor without any FSM initialization call. `cursor==end` is **not** equivalent to `FSM loaded`.
5. **Optional ADEF presence (D-E):** Renaming outer ADEF results in a non-null cursor before end and no FSM invocation; the wrapper still returns `1`.
6. **Seven-table import semantics (D-E):** Original importer and finalizer run to completion for both empty M06 and nonempty T01, using a synthetic Windows heap; T01 resulting counts match all independently decoded table sizes.

## Unchanged caveats

The wrapper is entered after its full original preamble, world-load callbacks are replaced by returns, and external CRT/OS functions are simulated. Static v0.4.0 rules concerning the real resource cache, path resolution and world-object registry are not dynamically upgraded. No game-provided successful actor/media bindings are tested. Error/no-op effects apply to this exact retail PE identity only.

## Further analysis target

Trace full wrapper preamble and the real world-section callback chain under a controlled enough emulated environment to test object creation, *then* emulate legitimate FSM teardown before multiple complete mission loads. Until then a full Windows game session remains the only way to settle actual mission switching/cleanup semantics.
