# v96 provisional source-layout observations (not original filenames)

**Confirmed machine-code adjacency:** The serialized FSM importer has helpers at `004102D0`, `00410490`, `004105A0`, `00410720` and adjacent finalization helpers at `004122D0`, `00412400`, `00412500`, `004125C0`. They share a stream cursor, FSM heap inputs, consistent allocation strategy, and the same load/finalize sequencing. This strongly supports one or more closely related source modules, but does **not** prove a single original `.c` file.

**Confirmed low-level registry adjacency:** `004AD450` inserts an instance key and object pointer; `004AD5B0` performs backward lookup in the same 16-byte-entry table. Their tight code placement, shared data layout, and complementary operations are strong evidence of a coherent low-level registry source neighborhood.

**Confirmed wrapper separation:** `00457610` and `00457630` are short registry adapters in a different world-object registration neighborhood. This is consistent with a distinct compilation unit interfacing with the low-level registry via header declarations, but is only a probable source-layout inference.

**Confirmed cross-unit usage:** The scene-object loader `004B7AC0` registers keys; the FSM actor finalizer `00412400` later looks them up. Different code neighborhoods exchange paired keys and pointers through common registry helpers. This suggests a shared engine-facing registry interface, but the original header name or precise translation-unit split cannot be recovered from these facts alone.

**Original source names:** None proposed. Confidence is high for local co-location, medium for translation-unit separation, and low for any particular `.c`/`.h` filename.
