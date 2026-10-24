# Provisional original source neighborhoods, not recovered source files

* **Static original PE:** `00405970` projection creation, `00405B90`/`004061B0` object-relative follow routines, and `00406920`/`00406AB0` default mode selection and update share `004C27xx`/`004C29xx` mutable camera globals. This is evidence for a camera-related code neighborhood, **not** original `.c`/`.h` filename recovery.
* **Separate class-1 vehicle subsystem:** original `00463068` initializes `runtime+0x398` null. `00467440` returns `object+0x70`, used by default camera callback to reach that field. Ownership and non-null field producer remain unidentified.
* The undefined Ghidra function at `00406AB0` is a **function-boundary annotation gap**; disassembly demonstrates entry prologue and unconditional final return within its own code. A later guarded analysis-script change may propose defining it in the private Ghidra baseline after confirming its complete extent.
