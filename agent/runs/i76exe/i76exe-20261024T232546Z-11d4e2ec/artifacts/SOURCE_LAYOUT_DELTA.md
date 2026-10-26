# Provisional vehicle-local attachment / camera source grouping

**Retail addresses proven:** `004AE000` VLOC tagged-record callback; `004B47C0` child wrapper; `00458BF0` world-status predicate; `00461970` class/runtime binder; `00463068` vehicle runtime initializer; `00467440` runtime getter; `00406AB0` default object-camera callback.

`004AE000` and neighboring `004ADxxx–004AExxx` vehicle-resource callbacks are likely one or several original vehicle descriptor/attachment modules. Camera callbacks at `004059xx–004071xx` are a distinct functional cluster. Links across these neighborhoods rely on object layout and the `+0x398` attachment pointer. This is **a source-layout hypothesis**, not recovered original `.c`/`.h` names or compiler object-file provenance.
