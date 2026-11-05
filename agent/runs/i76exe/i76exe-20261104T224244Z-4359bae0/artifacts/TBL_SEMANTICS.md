# TBL serialized bytes and runtime composition

All18 mission-selected TBL names resolve uniquely to18 different65536-byte payloads authenticated against I76.ZFS. Names match selected LUM stems but are independent serialized choices. All40 miss8/miss16 mission pairs select identical TBL payloads, even when ACT changes. No function audited here derives the serialized TBL from ACT.

## State construction

On successful TBL acquire, WRLD004B8A10 calls00478B30 before its65536-byte copy into0060AFA0. 00478B30 creates:

| Address / length | Exact state |
|---|---|
| 0061AFA0 /256 | Identity `I[i]=i` |
| 0062B2C0 /65536 | Auxiliary composition `C[source*256+destination]=source` |
| 0061B0A0 /256 | Constant255 |

00479780(context,key) zero-extends the low byte of key, copies I into C[key*256:key*256+256], fills0061B0A0 with key, then copies I into TBL[key*256:key*256+256]. It ignores context for the observed table writes. WRLD supplies255 at004B8B1E, producing `runtime_TBL[255,d]=d`. It runs even on missing-TBL paths; that does not safely initialize other rows if no earlier state exists. The model requires a complete TBL and rejects absence/truncation rather than reproducing stale-state behavior.

All18 serialized row255 values differ from identity at250..252 positions; retaining the file unchanged therefore demonstrably differs from initialized runtime state. Auxiliary00479740 changes a row of C to a constant, with `(arg1 &255)*256` row and low-byte arg2 output; this is not a write to serialized TBL or a matrix operation.

## Lookup axes and consumers

The exact indexed composition contract is `uint8 out = runtime_TBL[(uint8(source)<<8)|uint8(destination)]`. There is no arithmetic blend factor in this lookup itself. Source and destination indexes are not interchangeable.

At0047A4B6 AH receives the sampled source byte;0047A4B9 AL receives existing destination;0047A4BC loads one output byte from0060AFA0+EAX, then stores it to destination. The coordinate/indexing setup has bounded upper bits; do not emulate the AH/AL fragment with arbitrary stale EAX high16 bits. 0047AA50 indexed branch selector2 has the same source-high/destination-low contract at0047AF2F. Selector1 uses auxiliary C; other branches use identity/constant state rather than TBL. This function is a clipped bitmap-surface blit with format-dependent branches, not proof all drawing uses TBL.

Four textured span consumers004828E0,00483210,00483CC0,00484630 load sampled texture index, shift it left8, load existing destination unsigned byte, and read/write the TBL result. Representative00482B16..29 establishes each operand. Their unrolled accesses pack the same inputs in high/low8-bit registers. This is palette-index composition with existing destination, supporting a translucency/composition role; it does **not** prove a50/50 RGB average, fixed opacity, or that file values can be regenerated from ACT.

All raw TBLs are strongly asymmetric:63392..63590 of65536 positions differ from their transpose. A symmetric-average interpretation would already fail this observed property. Source255 preserving destination is installed by code, not inferred from the palette color at255.

## Temporary mutation

00483CC0 at00483CE9..00483D04 and00484630 at00484659..74 save the256 bytes `TBL[row,255]`, then replace each with its row index. They do this by starting0060B09F (=0060AFA0+255), incrementing address256 and row0..255. This produces `TBL[source,255]=source`, allowing a source index to pass through when destination255 in those operations. Normal exit loops004843DB..F4 /00484E40..59 restore every saved byte. These are **column** writes, not a second source-row overwrite. No exception/abnormal-return restoration guarantee or thread safety is established for retail; the independent model uses finally for safe restoration.

## Backend boundary and closure limits

The observed TBL consumers are8-bit software paths and all use the same axis order. 0047AA50's indexed-source/high-color-destination branch instead reads a uint16 palette remap00608460; selected modes explicitly skip source255. No evidence supports transposing TBL for a high-color backend. Native raster plugins receive separate pixel/palette state; their internal composition is unresolved.

The audit walked original references to **every byte** of0060AFA0..0061AF9F and scanned all defined instruction operands for immediates in that range, not only the base symbol. Interior computed-address mutation references are retained in table_references.json. No additional direct TBL writer was identified beyond load, identity-row construction and the two temporary column patches. This statement is limited to identifiable code/references in the supplied baseline; arbitrary alias/external/self-modified consumers are not proved absent.
