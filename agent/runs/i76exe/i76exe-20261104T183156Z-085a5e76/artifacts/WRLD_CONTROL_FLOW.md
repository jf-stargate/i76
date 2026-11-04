# WRLD control flow and instruction audit

Evidence tier: binary-static, exact retail EXE and imported v100 program. The existing annotations were inspected, never altered. Names are research aliases, not original symbols; several aliases are too broad or misleading (audio “flag”, environment helper “palette DIB”, material physical names). Original accesses determine claims below. `evidence/reviewed_instructions.tsv` supplies curated instructions; `instruction_byte_validation.tsv` independently compares all defined instruction bytes in 28 bounded function bodies (including the top-level caller body) with the authenticated retail PE. The full private exports are reproduction intermediates, excluded from publication.

## Callback ABI

004b4550 forwards three arguments to 004b89e0. 004b89e0 invokes 004b3db0 with WDEF table 00500ca0, count3, null context, sequential mode1, and the forwarded end pointer. Its descriptors are WREV callback004b4610 flags0x2004, WRLD callback004b8a10 flags1, EXIT callback004b4290 flags0x1000. Exact table values are preserved as metadata in wdef_descriptor_table.tsv.

At 004b403a..004b4046, the generic parser computes `chunk + 8*((flags>>1)&1)` and calls the descriptor callback. WRLD flags1 has bit1 clear, so argument1 points at its **header**, not payload. 004b8a11 loads that argument to EBX. The handler's extra caller arguments/end pointer are not consumed. No descriptor flag1 meaning beyond this observed argument selection is required here.

WREV is separate: the accepted revision handler policy expects WREV9. It is not validated by reading WRLD's first word. Generic parser bounds/return behavior remains as documented in the accepted loader failure contract: incomplete header checks, diagnostic-only report_error stub, persistent descriptor-seen bits, and unconditional selected-mission success return must not be copied into a new reader.

## Ordered handler effects

1. 004b8a17 reads header+8 (payload+0), calls 00423320, stores audio selection at 004ed800. Later 00423330 tests availability/configuration and passes this word through track range validation and playback. Immediate handler effect is state only.
2. 004b8a21 reads header+0x9b (payload+0x93), calls 00477b00. It clears light-related runtime storage, calculates signed eight-row selector using IDIV24, loads built-in sun/moon MAP through 0046ffc0 at 00477b60 and retains pointer 006435e0. No WRLD name string supplies that MAP.
3. 004b8a33/53 forms header+0x26/+0x33 (payload+0x1e/+0x2b); acquisition calls at 004b8a37/57. Non-null ACT permits a 768-byte copy to 004fa170 and indirect palette callback at 004b8a9b with LUM pointer. Independent release calls at 004b8ab0/ac0. LUM null is reported but not a gate for that callback; report_error is a RET in this executable.
4. 004b8ac8 forms header+0x40 (payload+0x38); acquisition at 004b8acc. Non-null result initializes auxiliary tables at 00478b30 and copies 65536 bytes to 0060afa0. Release at 004b8b0c. 00479780 then installs the 0xff identity row even if no TBL was acquired. Resource sizes are not checked in this handler.
5. 004b8b26..47 copies header+0x9f (payload+0x97), eight 20-byte rows, to 00644220. The three float and one signed integer getter accesses at 00492777/87/97/a7 establish row member types; +0c remains opaque.
6. 004b8b49..6c uses unbounded strlen-style SCASB and copies sky from header+0x5a to 005dce60. 004b8b6e..8d similarly retains NPT from header+0x4d to 006094f0. 004b8b8f..b1 retains map from header+0x81 to 005a7ec8. These are persistent C strings, not relocated pointers into the mission resource.
7. 004b8bb3..b7 passes header+0x67 to 004b8500. That helper rejects empty input, splits path, uses eight basename bytes, creates support object, formats .sdf and invokes the generic SDF descriptor reader if object creation succeeds. WRLD ignores its result.
8. 004b8bbf..c3 passes header+0x74 to 004908f0. This copies/expands default terrain names without acquisition there. Later 004909b0 loads the five generated names.
9. 004b8bcb..d2 passes header+0x8e to 00401540. It resets enabled state, returns on empty name, acquires HZD text, parses sixteen texture names, releases manifest, calls 00471c10 for each. WRLD ignores failures/return status.
10. 004b8bd7..004b8c20 copies movie slots from header+0x0c/+0x19 as three dwords + one byte each, to 005dd300/310. Later top-level game paths call 0049a070 with those buffers. That callee builds a media path and invokes SmackOpen, distinct from 0046ffc0 acquisition.
11. 004b8c2a FILD reads signed header+0x13f (payload+0x137), stores float at 004c271c at 004b8c31. Camera code at 004059d5..00405a0f selects it only when 00654b8a is nonzero; otherwise uses 0x43160000 (150.0f), then calls projection helper00472220. Source and runtime representation differ.
12. 004b8c25 sets EAX=1 and returns after effects; no handler success aggregation or rollback.

## Downstream distinctions and explicit bounds gaps

Sky, terrain defaults and HZD child textures reach 00471c10: primary resource decode/cache via 004474b0, optional .m16 companion only if 00495060 reports 005dd2a8==1. NPT's later 0045df0b acquisition is controlled by its stored string and the UI initialization path. Map's 004703a0 call has arguments (name,1,4,...), copies the template and replaces character4 using display-variant table004f8aaf before 004478b0. PCF is generated from a separate caller name by 004026c0; it is not serialized in WRLD.

No field in the WRLD handler has an explicit local source-capacity check. Two exact 13-byte movie copies still require the source record to be that long and do not ensure NUL termination. Other slots are scanned without a 13-byte maximum. Material and numeric reads ignore the declared record end. Child helpers' empty-name checks, terrain fifth-character check and resource null checks do not establish chunk bounds. HZD parsing also scans acquired text without a demonstrated safe token/record bound. No malformed retail mission was executed.

## Unresolved

No instruction in 004b8a10 reads payload+0x13b..0x14b. Material row+0c is copied but not interpreted by the bounded getter audit. Broader aliased readers may exist; this is not whole-program read closure. The selected palette callback's LUM math, all physics meanings, complete HZD grammar, full bitmap variant table, full downstream texture decoding and asset load success remain unproved here.
