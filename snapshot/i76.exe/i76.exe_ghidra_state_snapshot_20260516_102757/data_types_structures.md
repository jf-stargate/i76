# Structure Data Types

## `_CONTEXT`

Category: `/excpt.h`  
Length: `716`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `ContextFlags` | `DWORD` |  |
| 1 | 4 | 4 | `Dr0` | `DWORD` |  |
| 2 | 8 | 4 | `Dr1` | `DWORD` |  |
| 3 | 12 | 4 | `Dr2` | `DWORD` |  |
| 4 | 16 | 4 | `Dr3` | `DWORD` |  |
| 5 | 20 | 4 | `Dr6` | `DWORD` |  |
| 6 | 24 | 4 | `Dr7` | `DWORD` |  |
| 7 | 28 | 112 | `FloatSave` | `FLOATING_SAVE_AREA` |  |
| 8 | 140 | 4 | `SegGs` | `DWORD` |  |
| 9 | 144 | 4 | `SegFs` | `DWORD` |  |
| 10 | 148 | 4 | `SegEs` | `DWORD` |  |
| 11 | 152 | 4 | `SegDs` | `DWORD` |  |
| 12 | 156 | 4 | `Edi` | `DWORD` |  |
| 13 | 160 | 4 | `Esi` | `DWORD` |  |
| 14 | 164 | 4 | `Ebx` | `DWORD` |  |
| 15 | 168 | 4 | `Edx` | `DWORD` |  |
| 16 | 172 | 4 | `Ecx` | `DWORD` |  |
| 17 | 176 | 4 | `Eax` | `DWORD` |  |
| 18 | 180 | 4 | `Ebp` | `DWORD` |  |
| 19 | 184 | 4 | `Eip` | `DWORD` |  |
| 20 | 188 | 4 | `SegCs` | `DWORD` |  |
| 21 | 192 | 4 | `EFlags` | `DWORD` |  |
| 22 | 196 | 4 | `Esp` | `DWORD` |  |
| 23 | 200 | 4 | `SegSs` | `DWORD` |  |
| 24 | 204 | 512 | `ExtendedRegisters` | `BYTE[512]` |  |

## `_div_t`

Category: `/stdlib.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `quot` | `int` |  |
| 1 | 4 | 4 | `rem` | `int` |  |

## `_EXCEPTION_POINTERS`

Category: `/excpt.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `ExceptionRecord` | `PEXCEPTION_RECORD` |  |
| 1 | 4 | 4 | `ContextRecord` | `PCONTEXT` |  |

## `_EXCEPTION_RECORD`

Category: `/excpt.h`  
Length: `80`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `ExceptionCode` | `DWORD` |  |
| 1 | 4 | 4 | `ExceptionFlags` | `DWORD` |  |
| 2 | 8 | 4 | `ExceptionRecord` | `_EXCEPTION_RECORD *` |  |
| 3 | 12 | 4 | `ExceptionAddress` | `PVOID` |  |
| 4 | 16 | 4 | `NumberParameters` | `DWORD` |  |
| 5 | 20 | 60 | `ExceptionInformation` | `ULONG_PTR[15]` |  |

## `_FILETIME`

Category: `/WinDef.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `dwLowDateTime` | `DWORD` |  |
| 1 | 4 | 4 | `dwHighDateTime` | `DWORD` |  |

## `_FLOATING_SAVE_AREA`

Category: `/winnt.h`  
Length: `112`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `ControlWord` | `DWORD` |  |
| 1 | 4 | 4 | `StatusWord` | `DWORD` |  |
| 2 | 8 | 4 | `TagWord` | `DWORD` |  |
| 3 | 12 | 4 | `ErrorOffset` | `DWORD` |  |
| 4 | 16 | 4 | `ErrorSelector` | `DWORD` |  |
| 5 | 20 | 4 | `DataOffset` | `DWORD` |  |
| 6 | 24 | 4 | `DataSelector` | `DWORD` |  |
| 7 | 28 | 80 | `RegisterArea` | `BYTE[80]` |  |
| 8 | 108 | 4 | `Cr0NpxState` | `DWORD` |  |

## `_iobuf`

Category: `/mbstring.h`  
Length: `32`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `_ptr` | `char *` |  |
| 1 | 4 | 4 | `_cnt` | `int` |  |
| 2 | 8 | 4 | `_base` | `char *` |  |
| 3 | 12 | 4 | `_flag` | `int` |  |
| 4 | 16 | 4 | `_file` | `int` |  |
| 5 | 20 | 4 | `_charbuf` | `int` |  |
| 6 | 24 | 4 | `_bufsiz` | `int` |  |
| 7 | 28 | 4 | `_tmpfname` | `char *` |  |

## `_MEMORY_BASIC_INFORMATION`

Category: `/winnt.h`  
Length: `28`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `BaseAddress` | `PVOID` |  |
| 1 | 4 | 4 | `AllocationBase` | `PVOID` |  |
| 2 | 8 | 4 | `AllocationProtect` | `DWORD` |  |
| 3 | 12 | 4 | `RegionSize` | `SIZE_T` |  |
| 4 | 16 | 4 | `State` | `DWORD` |  |
| 5 | 20 | 4 | `Protect` | `DWORD` |  |
| 6 | 24 | 4 | `Type` | `DWORD` |  |

## `_MEMORYSTATUS`

Category: `/winbase.h`  
Length: `32`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `dwLength` | `DWORD` |  |
| 1 | 4 | 4 | `dwMemoryLoad` | `DWORD` |  |
| 2 | 8 | 4 | `dwTotalPhys` | `SIZE_T` |  |
| 3 | 12 | 4 | `dwAvailPhys` | `SIZE_T` |  |
| 4 | 16 | 4 | `dwTotalPageFile` | `SIZE_T` |  |
| 5 | 20 | 4 | `dwAvailPageFile` | `SIZE_T` |  |
| 6 | 24 | 4 | `dwTotalVirtual` | `SIZE_T` |  |
| 7 | 28 | 4 | `dwAvailVirtual` | `SIZE_T` |  |

## `_s_FuncInfo`

Category: `/`  
Length: `28`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `magicNumber_and_bbtFlags` | `uint` |  |
| 1 | 4 | 4 | `maxState` | `__ehstate_t` |  |
| 2 | 8 | 4 | `pUnwindMap` | `UnwindMapEntry *` |  |
| 3 | 12 | 4 | `nTryBlocks` | `uint` |  |
| 4 | 16 | 4 | `pTryBlockMap` | `TryBlockMapEntry *` |  |
| 5 | 20 | 4 | `nIPMapEntries` | `uint` |  |
| 6 | 24 | 4 | `pIPToStateMap` | `void *` |  |

## `_s_HandlerType`

Category: `/`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `adjectives` | `uint` |  |
| 1 | 4 | 4 | `pType` | `TypeDescriptor *` |  |
| 2 | 8 | 4 | `dispCatchObj` | `ptrdiff_t` |  |
| 3 | 12 | 4 | `addressOfHandler` | `void *` |  |

## `_s_TryBlockMapEntry`

Category: `/`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `tryLow` | `__ehstate_t` |  |
| 1 | 4 | 4 | `tryHigh` | `__ehstate_t` |  |
| 2 | 8 | 4 | `catchHigh` | `__ehstate_t` |  |
| 3 | 12 | 4 | `nCatches` | `int` |  |
| 4 | 16 | 4 | `pHandlerArray` | `HandlerType *` |  |

## `_s_UnwindMapEntry`

Category: `/`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `toState` | `__ehstate_t` |  |
| 1 | 4 | 4 | `action` | `action *` |  |

## `_SECURITY_ATTRIBUTES`

Category: `/winbase.h`  
Length: `12`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `nLength` | `DWORD` |  |
| 1 | 4 | 4 | `lpSecurityDescriptor` | `LPVOID` |  |
| 2 | 8 | 4 | `bInheritHandle` | `BOOL` |  |

## `_startupinfo`

Category: `/internal.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `newmode` | `int` |  |

## `_STARTUPINFOA`

Category: `/winbase.h`  
Length: `68`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `cb` | `DWORD` |  |
| 1 | 4 | 4 | `lpReserved` | `LPSTR` |  |
| 2 | 8 | 4 | `lpDesktop` | `LPSTR` |  |
| 3 | 12 | 4 | `lpTitle` | `LPSTR` |  |
| 4 | 16 | 4 | `dwX` | `DWORD` |  |
| 5 | 20 | 4 | `dwY` | `DWORD` |  |
| 6 | 24 | 4 | `dwXSize` | `DWORD` |  |
| 7 | 28 | 4 | `dwYSize` | `DWORD` |  |
| 8 | 32 | 4 | `dwXCountChars` | `DWORD` |  |
| 9 | 36 | 4 | `dwYCountChars` | `DWORD` |  |
| 10 | 40 | 4 | `dwFillAttribute` | `DWORD` |  |
| 11 | 44 | 4 | `dwFlags` | `DWORD` |  |
| 12 | 48 | 2 | `wShowWindow` | `WORD` |  |
| 13 | 50 | 2 | `cbReserved2` | `WORD` |  |
| 14 | 52 | 4 | `lpReserved2` | `LPBYTE` |  |
| 15 | 56 | 4 | `hStdInput` | `HANDLE` |  |
| 16 | 60 | 4 | `hStdOutput` | `HANDLE` |  |
| 17 | 64 | 4 | `hStdError` | `HANDLE` |  |

## `_struct_531`

Category: `/winbase.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wProcessorArchitecture` | `WORD` |  |
| 1 | 2 | 2 | `wReserved` | `WORD` |  |

## `_SYSTEM_INFO`

Category: `/winbase.h`  
Length: `36`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `u` | `_union_530` |  |
| 1 | 4 | 4 | `dwPageSize` | `DWORD` |  |
| 2 | 8 | 4 | `lpMinimumApplicationAddress` | `LPVOID` |  |
| 3 | 12 | 4 | `lpMaximumApplicationAddress` | `LPVOID` |  |
| 4 | 16 | 4 | `dwActiveProcessorMask` | `DWORD_PTR` |  |
| 5 | 20 | 4 | `dwNumberOfProcessors` | `DWORD` |  |
| 6 | 24 | 4 | `dwProcessorType` | `DWORD` |  |
| 7 | 28 | 4 | `dwAllocationGranularity` | `DWORD` |  |
| 8 | 32 | 2 | `wProcessorLevel` | `WORD` |  |
| 9 | 34 | 2 | `wProcessorRevision` | `WORD` |  |

## `_WIN32_FIND_DATAA`

Category: `/winbase.h`  
Length: `320`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `dwFileAttributes` | `DWORD` |  |
| 1 | 4 | 8 | `ftCreationTime` | `FILETIME` |  |
| 2 | 12 | 8 | `ftLastAccessTime` | `FILETIME` |  |
| 3 | 20 | 8 | `ftLastWriteTime` | `FILETIME` |  |
| 4 | 28 | 4 | `nFileSizeHigh` | `DWORD` |  |
| 5 | 32 | 4 | `nFileSizeLow` | `DWORD` |  |
| 6 | 36 | 4 | `dwReserved0` | `DWORD` |  |
| 7 | 40 | 4 | `dwReserved1` | `DWORD` |  |
| 8 | 44 | 260 | `cFileName` | `CHAR[260]` |  |
| 9 | 304 | 14 | `cAlternateFileName` | `CHAR[14]` |  |

## `CLIENT_ID`

Category: `/`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `UniqueProcess` | `void *` |  |
| 1 | 4 | 4 | `UniqueThread` | `void *` |  |

## `HBITMAP__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HBRUSH__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HDC__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HFONT__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HICON__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HIMC__`

Category: `/imm.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HINSTANCE__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HKEY__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HMENU__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HPALETTE__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HWND__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `i76_ai_vehicle_behavior_state_partial`

Category: `/i76`  
Length: `43056`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 40192 | `pad_0` | `byte[40192]` | padding |
| 1 | 40192 | 4 | `special_damage_event_time_seconds` | `float` | Special/alternate damage event timestamp. |
| 2 | 40196 | 48 | `pad_9d04` | `byte[48]` | padding |
| 3 | 40244 | 4 | `secondary_behavior_expire_time` | `float` | AI secondary behavior expiry time. |
| 4 | 40248 | 2804 | `pad_9d38` | `byte[2804]` | padding |
| 5 | 43052 | 4 | `primary_behavior_expire_time` | `float` | AI primary behavior expiry time. |

## `i76_ai_vehicle_behavior_state_partial.conflict`

Category: `/i76`  
Length: `43088`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 40192 | 40192 | 4 | `special_damage_event_time_seconds` | `float` | Observed in record_vehicle_damage_source_event for damage flag class 0x0006 or null source. |
| 40241 | 40244 | 4 | `secondary_timer_expire_time_seconds` | `float` | Used by is_ai_behavior_secondary_timer_expired. |
| 42702 | 42708 | 4 | `recent_special_damage_tick` | `dword` | Recent special damage source tick/frame/event counter. |
| 42703 | 42712 | 4 | `recent_normal_damage_tick` | `dword` | Recent normal damage source tick/frame/event counter. |
| 42704 | 42716 | 4 | `latest_damage_tick` | `dword` | Latest damage source tick/frame/event counter. |
| 42705 | 42720 | 4 | `latest_damage_source_is_active_player` | `dword` | Set when latest damage source is active player/camera object. |
| 42706 | 42724 | 4 | `recent_normal_damage_source_object` | `pointer` | Recent normal damage source world object. |
| 42707 | 42728 | 4 | `recent_special_damage_source_object` | `pointer` | Recent special damage source world object. |
| 42708 | 42732 | 4 | `latest_damage_source_object` | `pointer` | Latest damage source world object. |
| 42709 | 42736 | 4 | `latest_damage_time_seconds` | `float` | Latest damage source gameplay-runtime seconds. |
| 43054 | 43084 | 4 | `primary_timer_expire_time_seconds` | `float` | Used by is_ai_behavior_primary_timer_expired. |

## `i76_runtime_clock_state_partial`

Category: `/i76`  
Length: `144`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `gameplay_step_seconds` | `float` | Gameplay step delta candidate. |
| 1 | 4 | 4 | `gameplay_step_inverse` | `float` | Reciprocal gameplay step candidate. |
| 2 | 8 | 4 | `raw_frame_delta_seconds` | `float` | Raw/clamped frame delta candidate. |
| 3 | 12 | 4 | `raw_frame_delta_inverse` | `float` | Reciprocal raw frame delta candidate. |
| 4 | 16 | 128 | `pad_10` | `byte[128]` | padding |

## `i76_vehicle_control_intent_candidate`

Category: `/i76`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `steering_or_axis_0` | `float` | Potential control axis field |
| 1 | 4 | 4 | `throttle_or_axis_1` | `float` | Potential control axis field |
| 2 | 8 | 4 | `brake_or_axis_2` | `float` | Potential control axis field |
| 3 | 12 | 4 | `handbrake_or_axis_3` | `float` | Potential control axis field |
| 4 | 16 | 4 | `fire_or_control_flags` | `dword` | Potential fire/control flags |

## `i76_vehicle_runtime_partial`

Category: `/i76`  
Length: `1152`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 56 | `pad_0` | `byte[56]` | padding |
| 1 | 56 | 4 | `contact_or_wheel_probe_state_38` | `undefined4` | Wheel/ground probe state area candidate. |
| 2 | 60 | 112 | `pad_3c` | `byte[112]` | padding |
| 3 | 172 | 4 | `speed_ac` | `float` | Vehicle speed magnitude candidate. |
| 4 | 176 | 4 | `inverse_speed_b0` | `float` | Reciprocal speed or huge sentinel candidate. |
| 5 | 180 | 8 | `pad_b4` | `byte[8]` | padding |
| 6 | 188 | 4 | `velocity_or_state_vec0_x` | `float` | Vehicle state/vector candidate X. |
| 7 | 192 | 4 | `velocity_or_state_vec0_y` | `float` | Vehicle state/vector candidate Y. |
| 8 | 196 | 4 | `velocity_or_state_vec0_z` | `float` | Vehicle state/vector candidate Z. |
| 9 | 200 | 4 | `orientation_or_state_vec1_x` | `float` | Vehicle state/vector candidate X. |
| 10 | 204 | 4 | `orientation_or_state_vec1_y` | `float` | Vehicle state/vector candidate Y. |
| 11 | 208 | 4 | `orientation_or_state_vec1_z` | `float` | Vehicle state/vector candidate Z. |
| 12 | 212 | 16 | `pad_d4` | `byte[16]` | padding |
| 13 | 228 | 4 | `engine_or_drivetrain_state_e4` | `dword` | Passed to engine gear/RPM/torque update. |
| 14 | 232 | 4 | `movement_or_drive_scalar_e8` | `float` | Tested against 0.0 in drivetrain update. |
| 15 | 236 | 28 | `pad_ec` | `byte[28]` | padding |
| 16 | 264 | 4 | `ai_fsm_damage_event_state` | `pointer` | Vehicle AI/FSM damage attribution state block. |
| 17 | 268 | 668 | `pad_10c` | `byte[668]` | padding |
| 18 | 936 | 4 | `tire_child_or_component_3a8` | `pointer` | Tire/child runtime pointer candidate. |
| 19 | 940 | 4 | `tire_child_or_component_3ac` | `pointer` | Tire/child runtime pointer candidate. |
| 20 | 944 | 4 | `optional_tire_child_3b0` | `pointer` | Optional tire/child runtime pointer candidate. |
| 21 | 948 | 4 | `optional_tire_child_3b4` | `pointer` | Optional tire/child runtime pointer candidate. |
| 22 | 952 | 4 | `tire_contact_component_3b8` | `pointer` | Tire contact runtime pointer candidate. |
| 23 | 956 | 4 | `tire_contact_component_3bc` | `pointer` | Tire contact runtime pointer candidate. |
| 24 | 960 | 4 | `pad_3c0` | `byte[4]` | padding |
| 25 | 964 | 4 | `engine_or_drivetrain_child_3c4` | `pointer` | Engine/drivetrain child/runtime pointer candidate. |
| 26 | 968 | 124 | `pad_3c8` | `byte[124]` | padding |
| 27 | 1092 | 4 | `fixed_step_accumulator_444` | `undefined4` | Vehicle fixed-step accumulator/timer area; initialized with 0.05f. |
| 28 | 1096 | 12 | `pad_448` | `byte[12]` | padding |
| 29 | 1108 | 4 | `vehicle_contact_runtime_flags_454` | `dword` | Central vehicle contact/status flags. |
| 30 | 1112 | 4 | `damage_speed_or_last_impact_458` | `float` | Damage/impact speed scalar candidate. |
| 31 | 1116 | 4 | `terrain_or_contact_state_45c` | `dword` | Terrain/contact/material state candidate. |
| 32 | 1120 | 4 | `surface_normal_or_up_x` | `float` | Surface normal/up vector X; initialized to 0. |
| 33 | 1124 | 4 | `surface_normal_or_up_y` | `float` | Surface normal/up vector Y; initialized to 1. |
| 34 | 1128 | 4 | `surface_normal_or_up_z` | `float` | Surface normal/up vector Z; initialized to 0. |
| 35 | 1132 | 4 | `surface_response_or_gravity_scalar_46c` | `float` | 9.8f default; gravity/contact-response candidate. |
| 36 | 1136 | 4 | `pad_470` | `byte[4]` | padding |
| 37 | 1140 | 4 | `previous_ground_height_or_contact_474` | `float` | Ground height/contact scalar candidate. |
| 38 | 1144 | 8 | `pad_478` | `byte[8]` | padding |

## `i76_vehicle_runtime_partial.conflict`

Category: `/i76`  
Length: `1127`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 16 | 16 | 4 | `aio_patch_gate_candidate_10` | `dword` | AIO patch uses this field instead of +0x44 in record_vehicle_damage_source_event gate. |
| 65 | 68 | 4 | `retail_damage_source_gate_candidate_44` | `dword` | Retail field used by record_vehicle_damage_source_event gate before AIO patch. |
| 258 | 264 | 4 | `damage_event_state` | `pointer` | Pointer/base used by vehicle damage event / AI reaction state helpers. |
| 1099 | 1108 | 4 | `vehicle_runtime_flags_454` | `dword` | Vehicle runtime flags; record_vehicle_damage_source_event tests bit 0x20. |

## `i76_vehicle_runtime_partial.conflict1`

Category: `/i76`  
Length: `1120`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `vehicle_runtime_header` | `dword` | Runtime header/first field candidate |
| 1 | 4 | 1 | `pad_4` | `undefined1` |  |
| 13 | 16 | 4 | `aio_patch_preferred_gate_field` | `dword` | AIO patch changed damage attribution gate to this field in related runtime |
| 14 | 20 | 1 | `pad_14` | `undefined1` |  |
| 62 | 68 | 4 | `retail_damage_attribution_gate_field` | `dword` | Retail damage attribution gate field in related runtime |
| 63 | 72 | 1 | `pad_48` | `undefined1` |  |
| 255 | 264 | 4 | `damage_event_state` | `pointer` | Vehicle damage/FSM attribution state block candidate |
| 256 | 268 | 1 | `pad_10c` | `undefined1` |  |
| 1080 | 1092 | 4 | `fixed_step_accumulator` | `undefined4` | Vehicle fixed-step accumulator area candidate |
| 1081 | 1096 | 1 | `pad_448` | `undefined1` |  |
| 1093 | 1108 | 4 | `vehicle_runtime_flags_454` | `dword` | Vehicle runtime flags observed in update/damage paths |
| 1094 | 1112 | 1 | `pad_458` | `undefined1` |  |
| 1098 | 1116 | 4 | `vehicle_runtime_flags_45c` | `dword` | Secondary runtime flags candidate |

## `i76_world_object_class_descriptor_partial`

Category: `/i76`  
Length: `52`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `class_id` | `dword` | Canonical world-object class id. |
| 1 | 4 | 4 | `construct_callback` | `pointer` | Class constructor/runtime allocation callback candidate. |
| 2 | 8 | 4 | `init_callback` | `pointer` | Class init callback candidate. |
| 3 | 12 | 4 | `pre_update_callback` | `pointer` | Pre-update/frame-begin class callback. |
| 4 | 16 | 4 | `post_update_or_visual_callback` | `pointer` | Post-update/visual/secondary callback candidate. |
| 5 | 20 | 4 | `callback_14` | `pointer` | Unknown descriptor callback slot. |
| 6 | 24 | 4 | `callback_18` | `pointer` | Unknown descriptor callback slot. |
| 7 | 28 | 4 | `vector_callback` | `pointer` | Damage/target vector callback candidate. |
| 8 | 32 | 4 | `transform_callback` | `pointer` | Transform/damage builder callback candidate. |
| 9 | 36 | 4 | `damage_transform_callback` | `pointer` | Damage transform callback candidate. |
| 10 | 40 | 4 | `target_or_placement_callback` | `pointer` | Target/placement callback candidate. |
| 11 | 44 | 4 | `damage_callback` | `pointer` | Damage callback candidate. |
| 12 | 48 | 4 | `release_callback` | `pointer` | Class release callback. |

## `i76_world_object_partial`

Category: `/i76`  
Length: `144`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 8 | `pad_0` | `byte[8]` | padding |
| 1 | 8 | 2 | `stop_or_destroyed_word_08` | `word` | Tested after fixed-step vehicle physics loop; stop/destroyed candidate. |
| 2 | 10 | 6 | `pad_a` | `byte[6]` | padding |
| 3 | 16 | 4 | `object_flags_10` | `dword` | World object flags; bit 0x20 gates/suppresses normal vehicle control update. |
| 4 | 20 | 28 | `pad_14` | `byte[28]` | padding |
| 5 | 48 | 4 | `pos_x` | `float` | World position X candidate. |
| 6 | 52 | 4 | `pos_y` | `float` | World position Y candidate. |
| 7 | 56 | 4 | `pos_z` | `float` | World position Z candidate. |
| 8 | 60 | 48 | `pad_3c` | `byte[48]` | padding |
| 9 | 108 | 4 | `class_id` | `dword` | World-object class id candidate. |
| 10 | 112 | 4 | `class_runtime` | `pointer` | Per-class runtime payload; VehicleRuntime for class 1. |
| 11 | 116 | 4 | `pad_74` | `byte[4]` | padding |
| 12 | 120 | 4 | `parent_or_owner` | `pointer` | Owner/parent candidate. |
| 13 | 124 | 8 | `pad_7c` | `byte[8]` | padding |
| 14 | 132 | 4 | `child_or_component_list` | `pointer` | Child/component list candidate. |
| 15 | 136 | 8 | `pad_88` | `byte[8]` | padding |

## `i76_world_object_partial.conflict`

Category: `/i76`  
Length: `119`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 112 | 112 | 4 | `runtime_or_vehicle_context` | `pointer` | Common world-object runtime pointer. Vehicle objects point at vehicle runtime/context here. |

## `i76_world_object_partial.conflict1`

Category: `/i76`  
Length: `136`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 1 | `pad_1` | `undefined1` |  |
| 15 | 15 | 4 | `flags10_or_runtime_flags` | `dword` | Observed in vehicle update gates |
| 16 | 19 | 1 | `pad_13` | `undefined1` |  |
| 45 | 48 | 4 | `pos_x` | `float` | World position X candidate |
| 46 | 52 | 4 | `pos_y` | `float` | World position Y candidate |
| 47 | 56 | 4 | `pos_z` | `float` | World position Z candidate |
| 48 | 60 | 1 | `pad_3c` | `undefined1` |  |
| 96 | 108 | 4 | `class_id` | `dword` | World-object class id candidate |
| 97 | 112 | 4 | `class_runtime` | `pointer` | Per-class runtime payload; vehicle runtime for class 1 |
| 98 | 116 | 1 | `pad_74` | `undefined1` |  |
| 102 | 120 | 4 | `parent_or_owner` | `pointer` | Owner/parent candidate |
| 103 | 124 | 1 | `pad_7c` | `undefined1` |  |
| 111 | 132 | 4 | `child_or_component_list` | `pointer` | Child/component list candidate |

## `IMAGE_DATA_DIRECTORY`

Category: `/PE`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `VirtualAddress` | `ImageBaseOffset32` |  |
| 1 | 4 | 4 | `Size` | `dword` |  |

## `IMAGE_DOS_HEADER`

Category: `/DOS`  
Length: `128`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `e_magic` | `char[2]` | Magic number |
| 1 | 2 | 2 | `e_cblp` | `word` | Bytes of last page |
| 2 | 4 | 2 | `e_cp` | `word` | Pages in file |
| 3 | 6 | 2 | `e_crlc` | `word` | Relocations |
| 4 | 8 | 2 | `e_cparhdr` | `word` | Size of header in paragraphs |
| 5 | 10 | 2 | `e_minalloc` | `word` | Minimum extra paragraphs needed |
| 6 | 12 | 2 | `e_maxalloc` | `word` | Maximum extra paragraphs needed |
| 7 | 14 | 2 | `e_ss` | `word` | Initial (relative) SS value |
| 8 | 16 | 2 | `e_sp` | `word` | Initial SP value |
| 9 | 18 | 2 | `e_csum` | `word` | Checksum |
| 10 | 20 | 2 | `e_ip` | `word` | Initial IP value |
| 11 | 22 | 2 | `e_cs` | `word` | Initial (relative) CS value |
| 12 | 24 | 2 | `e_lfarlc` | `word` | File address of relocation table |
| 13 | 26 | 2 | `e_ovno` | `word` | Overlay number |
| 14 | 28 | 8 | `e_res[4]` | `word[4]` | Reserved words |
| 15 | 36 | 2 | `e_oemid` | `word` | OEM identifier (for e_oeminfo) |
| 16 | 38 | 2 | `e_oeminfo` | `word` | OEM information; e_oemid specific |
| 17 | 40 | 20 | `e_res2[10]` | `word[10]` | Reserved words |
| 18 | 60 | 4 | `e_lfanew` | `dword` | File address of new exe header |
| 19 | 64 | 64 | `e_program` | `byte[64]` | Actual DOS program |

## `IMAGE_FILE_HEADER`

Category: `/PE`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `Machine` | `word` | 332 |
| 1 | 2 | 2 | `NumberOfSections` | `word` |  |
| 2 | 4 | 4 | `TimeDateStamp` | `dword` |  |
| 3 | 8 | 4 | `PointerToSymbolTable` | `dword` |  |
| 4 | 12 | 4 | `NumberOfSymbols` | `dword` |  |
| 5 | 16 | 2 | `SizeOfOptionalHeader` | `word` |  |
| 6 | 18 | 2 | `Characteristics` | `word` |  |

## `IMAGE_NT_HEADERS32`

Category: `/PE`  
Length: `248`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Signature` | `char[4]` |  |
| 1 | 4 | 20 | `FileHeader` | `IMAGE_FILE_HEADER` |  |
| 2 | 24 | 224 | `OptionalHeader` | `IMAGE_OPTIONAL_HEADER32` |  |

## `IMAGE_OPTIONAL_HEADER32`

Category: `/PE`  
Length: `224`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `Magic` | `word` |  |
| 1 | 2 | 1 | `MajorLinkerVersion` | `byte` |  |
| 2 | 3 | 1 | `MinorLinkerVersion` | `byte` |  |
| 3 | 4 | 4 | `SizeOfCode` | `dword` |  |
| 4 | 8 | 4 | `SizeOfInitializedData` | `dword` |  |
| 5 | 12 | 4 | `SizeOfUninitializedData` | `dword` |  |
| 6 | 16 | 4 | `AddressOfEntryPoint` | `ImageBaseOffset32` |  |
| 7 | 20 | 4 | `BaseOfCode` | `ImageBaseOffset32` |  |
| 8 | 24 | 4 | `BaseOfData` | `ImageBaseOffset32` |  |
| 9 | 28 | 4 | `ImageBase` | `pointer32` |  |
| 10 | 32 | 4 | `SectionAlignment` | `dword` |  |
| 11 | 36 | 4 | `FileAlignment` | `dword` |  |
| 12 | 40 | 2 | `MajorOperatingSystemVersion` | `word` |  |
| 13 | 42 | 2 | `MinorOperatingSystemVersion` | `word` |  |
| 14 | 44 | 2 | `MajorImageVersion` | `word` |  |
| 15 | 46 | 2 | `MinorImageVersion` | `word` |  |
| 16 | 48 | 2 | `MajorSubsystemVersion` | `word` |  |
| 17 | 50 | 2 | `MinorSubsystemVersion` | `word` |  |
| 18 | 52 | 4 | `Win32VersionValue` | `dword` |  |
| 19 | 56 | 4 | `SizeOfImage` | `dword` |  |
| 20 | 60 | 4 | `SizeOfHeaders` | `dword` |  |
| 21 | 64 | 4 | `CheckSum` | `dword` |  |
| 22 | 68 | 2 | `Subsystem` | `word` |  |
| 23 | 70 | 2 | `DllCharacteristics` | `word` |  |
| 24 | 72 | 4 | `SizeOfStackReserve` | `dword` |  |
| 25 | 76 | 4 | `SizeOfStackCommit` | `dword` |  |
| 26 | 80 | 4 | `SizeOfHeapReserve` | `dword` |  |
| 27 | 84 | 4 | `SizeOfHeapCommit` | `dword` |  |
| 28 | 88 | 4 | `LoaderFlags` | `dword` |  |
| 29 | 92 | 4 | `NumberOfRvaAndSizes` | `dword` |  |
| 30 | 96 | 128 | `DataDirectory` | `IMAGE_DATA_DIRECTORY[16]` |  |

## `IMAGE_RESOURCE_DATA_ENTRY`

Category: `/PE`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `OffsetToData` | `dword` |  |
| 1 | 4 | 4 | `Size` | `dword` |  |
| 2 | 8 | 4 | `CodePage` | `dword` |  |
| 3 | 12 | 4 | `Reserved` | `dword` |  |

## `IMAGE_RESOURCE_DIRECTORY`

Category: `/PE`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Characteristics` | `dword` |  |
| 1 | 4 | 4 | `TimeDateStamp` | `dword` |  |
| 2 | 8 | 2 | `MajorVersion` | `word` |  |
| 3 | 10 | 2 | `MinorVersion` | `word` |  |
| 4 | 12 | 2 | `NumberOfNamedEntries` | `word` |  |
| 5 | 14 | 2 | `NumberOfIdEntries` | `word` |  |

## `IMAGE_RESOURCE_DIRECTORY_ENTRY`

Category: `/PE`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `NameUnion` | `IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion` |  |
| 1 | 4 | 4 | `DirectoryUnion` | `IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion` |  |

## `IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct`

Category: `/`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `OffsetToDirectory` | `dword:31` |  |
| 1 | 3 | 1 | `DataIsDirectory` | `dword:1` |  |

## `IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct`

Category: `/PE`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `NameOffset` | `dword:31` |  |
| 1 | 3 | 1 | `NameIsString` | `dword:1` |  |

## `IMAGE_SECTION_HEADER`

Category: `/PE`  
Length: `40`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 8 | `Name` | `char[8]` |  |
| 1 | 8 | 4 | `Misc` | `Misc` |  |
| 2 | 12 | 4 | `VirtualAddress` | `ImageBaseOffset32` |  |
| 3 | 16 | 4 | `SizeOfRawData` | `dword` |  |
| 4 | 20 | 4 | `PointerToRawData` | `dword` |  |
| 5 | 24 | 4 | `PointerToRelocations` | `dword` |  |
| 6 | 28 | 4 | `PointerToLinenumbers` | `dword` |  |
| 7 | 32 | 2 | `NumberOfRelocations` | `word` |  |
| 8 | 34 | 2 | `NumberOfLinenumbers` | `word` |  |
| 9 | 36 | 4 | `Characteristics` | `SectionFlags` |  |

## `joyinfoex_tag`

Category: `/mmsystem.h`  
Length: `52`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `dwSize` | `DWORD` |  |
| 1 | 4 | 4 | `dwFlags` | `DWORD` |  |
| 2 | 8 | 4 | `dwXpos` | `DWORD` |  |
| 3 | 12 | 4 | `dwYpos` | `DWORD` |  |
| 4 | 16 | 4 | `dwZpos` | `DWORD` |  |
| 5 | 20 | 4 | `dwRpos` | `DWORD` |  |
| 6 | 24 | 4 | `dwUpos` | `DWORD` |  |
| 7 | 28 | 4 | `dwVpos` | `DWORD` |  |
| 8 | 32 | 4 | `dwButtons` | `DWORD` |  |
| 9 | 36 | 4 | `dwButtonNumber` | `DWORD` |  |
| 10 | 40 | 4 | `dwPOV` | `DWORD` |  |
| 11 | 44 | 4 | `dwReserved1` | `DWORD` |  |
| 12 | 48 | 4 | `dwReserved2` | `DWORD` |  |

## `StringFileInfo`

Category: `/PE`  
Length: `6`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wLength` | `word` |  |
| 1 | 2 | 2 | `wValueLength` | `word` |  |
| 2 | 4 | 2 | `wType` | `word` |  |

## `StringInfo`

Category: `/PE`  
Length: `6`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wLength` | `word` |  |
| 1 | 2 | 2 | `wValueLength` | `word` |  |
| 2 | 4 | 2 | `wType` | `word` |  |

## `StringTable`

Category: `/PE`  
Length: `6`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wLength` | `word` |  |
| 1 | 2 | 2 | `wValueLength` | `word` |  |
| 2 | 4 | 2 | `wType` | `word` |  |

## `tagAUXCAPSA`

Category: `/mmsystem.h`  
Length: `48`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wMid` | `WORD` |  |
| 1 | 2 | 2 | `wPid` | `WORD` |  |
| 2 | 4 | 4 | `vDriverVersion` | `MMVERSION` |  |
| 3 | 8 | 32 | `szPname` | `CHAR[32]` |  |
| 4 | 40 | 2 | `wTechnology` | `WORD` |  |
| 5 | 42 | 2 | `wReserved1` | `WORD` |  |
| 6 | 44 | 4 | `dwSupport` | `DWORD` |  |

## `tagBITMAPINFO`

Category: `/wingdi.h`  
Length: `44`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 40 | `bmiHeader` | `BITMAPINFOHEADER` |  |
| 1 | 40 | 4 | `bmiColors` | `RGBQUAD[1]` |  |

## `tagBITMAPINFOHEADER`

Category: `/wingdi.h`  
Length: `40`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `biSize` | `DWORD` |  |
| 1 | 4 | 4 | `biWidth` | `LONG` |  |
| 2 | 8 | 4 | `biHeight` | `LONG` |  |
| 3 | 12 | 2 | `biPlanes` | `WORD` |  |
| 4 | 14 | 2 | `biBitCount` | `WORD` |  |
| 5 | 16 | 4 | `biCompression` | `DWORD` |  |
| 6 | 20 | 4 | `biSizeImage` | `DWORD` |  |
| 7 | 24 | 4 | `biXPelsPerMeter` | `LONG` |  |
| 8 | 28 | 4 | `biYPelsPerMeter` | `LONG` |  |
| 9 | 32 | 4 | `biClrUsed` | `DWORD` |  |
| 10 | 36 | 4 | `biClrImportant` | `DWORD` |  |

## `tagJOYCAPSA`

Category: `/mmsystem.h`  
Length: `404`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wMid` | `WORD` |  |
| 1 | 2 | 2 | `wPid` | `WORD` |  |
| 2 | 4 | 32 | `szPname` | `CHAR[32]` |  |
| 3 | 36 | 4 | `wXmin` | `UINT` |  |
| 4 | 40 | 4 | `wXmax` | `UINT` |  |
| 5 | 44 | 4 | `wYmin` | `UINT` |  |
| 6 | 48 | 4 | `wYmax` | `UINT` |  |
| 7 | 52 | 4 | `wZmin` | `UINT` |  |
| 8 | 56 | 4 | `wZmax` | `UINT` |  |
| 9 | 60 | 4 | `wNumButtons` | `UINT` |  |
| 10 | 64 | 4 | `wPeriodMin` | `UINT` |  |
| 11 | 68 | 4 | `wPeriodMax` | `UINT` |  |
| 12 | 72 | 4 | `wRmin` | `UINT` |  |
| 13 | 76 | 4 | `wRmax` | `UINT` |  |
| 14 | 80 | 4 | `wUmin` | `UINT` |  |
| 15 | 84 | 4 | `wUmax` | `UINT` |  |
| 16 | 88 | 4 | `wVmin` | `UINT` |  |
| 17 | 92 | 4 | `wVmax` | `UINT` |  |
| 18 | 96 | 4 | `wCaps` | `UINT` |  |
| 19 | 100 | 4 | `wMaxAxes` | `UINT` |  |
| 20 | 104 | 4 | `wNumAxes` | `UINT` |  |
| 21 | 108 | 4 | `wMaxButtons` | `UINT` |  |
| 22 | 112 | 32 | `szRegKey` | `CHAR[32]` |  |
| 23 | 144 | 260 | `szOEMVxD` | `CHAR[260]` |  |

## `tagLOGFONTA`

Category: `/wingdi.h`  
Length: `60`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `lfHeight` | `LONG` |  |
| 1 | 4 | 4 | `lfWidth` | `LONG` |  |
| 2 | 8 | 4 | `lfEscapement` | `LONG` |  |
| 3 | 12 | 4 | `lfOrientation` | `LONG` |  |
| 4 | 16 | 4 | `lfWeight` | `LONG` |  |
| 5 | 20 | 1 | `lfItalic` | `BYTE` |  |
| 6 | 21 | 1 | `lfUnderline` | `BYTE` |  |
| 7 | 22 | 1 | `lfStrikeOut` | `BYTE` |  |
| 8 | 23 | 1 | `lfCharSet` | `BYTE` |  |
| 9 | 24 | 1 | `lfOutPrecision` | `BYTE` |  |
| 10 | 25 | 1 | `lfClipPrecision` | `BYTE` |  |
| 11 | 26 | 1 | `lfQuality` | `BYTE` |  |
| 12 | 27 | 1 | `lfPitchAndFamily` | `BYTE` |  |
| 13 | 28 | 32 | `lfFaceName` | `CHAR[32]` |  |

## `tagLOGPALETTE`

Category: `/wingdi.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `palVersion` | `WORD` |  |
| 1 | 2 | 2 | `palNumEntries` | `WORD` |  |
| 2 | 4 | 4 | `palPalEntry` | `PALETTEENTRY[1]` |  |

## `tagMSG`

Category: `/winuser.h`  
Length: `28`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `hwnd` | `HWND` |  |
| 1 | 4 | 4 | `message` | `UINT` |  |
| 2 | 8 | 4 | `wParam` | `WPARAM` |  |
| 3 | 12 | 4 | `lParam` | `LPARAM` |  |
| 4 | 16 | 4 | `time` | `DWORD` |  |
| 5 | 20 | 8 | `pt` | `POINT` |  |

## `tagPAINTSTRUCT`

Category: `/winuser.h`  
Length: `64`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `hdc` | `HDC` |  |
| 1 | 4 | 4 | `fErase` | `BOOL` |  |
| 2 | 8 | 16 | `rcPaint` | `RECT` |  |
| 3 | 24 | 4 | `fRestore` | `BOOL` |  |
| 4 | 28 | 4 | `fIncUpdate` | `BOOL` |  |
| 5 | 32 | 32 | `rgbReserved` | `BYTE[32]` |  |

## `tagPALETTEENTRY`

Category: `/wingdi.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 1 | `peRed` | `BYTE` |  |
| 1 | 1 | 1 | `peGreen` | `BYTE` |  |
| 2 | 2 | 1 | `peBlue` | `BYTE` |  |
| 3 | 3 | 1 | `peFlags` | `BYTE` |  |

## `tagPOINT`

Category: `/WinDef.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `x` | `LONG` |  |
| 1 | 4 | 4 | `y` | `LONG` |  |

## `tagRECT`

Category: `/WinDef.h`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `left` | `LONG` |  |
| 1 | 4 | 4 | `top` | `LONG` |  |
| 2 | 8 | 4 | `right` | `LONG` |  |
| 3 | 12 | 4 | `bottom` | `LONG` |  |

## `tagRGBQUAD`

Category: `/wingdi.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 1 | `rgbBlue` | `BYTE` |  |
| 1 | 1 | 1 | `rgbGreen` | `BYTE` |  |
| 2 | 2 | 1 | `rgbRed` | `BYTE` |  |
| 3 | 3 | 1 | `rgbReserved` | `BYTE` |  |

## `tagSIZE`

Category: `/WinDef.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `cx` | `LONG` |  |
| 1 | 4 | 4 | `cy` | `LONG` |  |

## `tagWNDCLASSA`

Category: `/winuser.h`  
Length: `40`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `style` | `UINT` |  |
| 1 | 4 | 4 | `lpfnWndProc` | `WNDPROC` |  |
| 2 | 8 | 4 | `cbClsExtra` | `int` |  |
| 3 | 12 | 4 | `cbWndExtra` | `int` |  |
| 4 | 16 | 4 | `hInstance` | `HINSTANCE` |  |
| 5 | 20 | 4 | `hIcon` | `HICON` |  |
| 6 | 24 | 4 | `hCursor` | `HCURSOR` |  |
| 7 | 28 | 4 | `hbrBackground` | `HBRUSH` |  |
| 8 | 32 | 4 | `lpszMenuName` | `LPCSTR` |  |
| 9 | 36 | 4 | `lpszClassName` | `LPCSTR` |  |

## `TypeDescriptor`

Category: `/`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `hash` | `dword` |  |
| 1 | 4 | 4 | `spare` | `void *` |  |
| 2 | 8 | 0 | `name` | `char[0]` |  |

## `Var`

Category: `/PE`  
Length: `6`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wLength` | `word` |  |
| 1 | 2 | 2 | `wValueLength` | `word` |  |
| 2 | 4 | 2 | `wType` | `word` |  |

## `VarFileInfo`

Category: `/PE`  
Length: `6`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `wLength` | `word` |  |
| 1 | 2 | 2 | `wValueLength` | `word` |  |
| 2 | 4 | 2 | `wType` | `word` |  |

## `VS_VERSION_INFO`

Category: `/PE`  
Length: `92`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 2 | `StructLength` | `word` |  |
| 1 | 2 | 2 | `ValueLength` | `word` |  |
| 2 | 4 | 2 | `StructType` | `word` |  |
| 3 | 6 | 32 | `Info` | `unicode` |  |
| 4 | 38 | 2 | `Padding` | `byte[2]` |  |
| 5 | 40 | 4 | `Signature` | `dword` |  |
| 6 | 44 | 4 | `StructVersion` | `word[2]` |  |
| 7 | 48 | 8 | `FileVersion` | `word[4]` |  |
| 8 | 56 | 8 | `ProductVersion` | `word[4]` |  |
| 9 | 64 | 8 | `FileFlagsMask` | `dword[2]` |  |
| 10 | 72 | 4 | `FileFlags` | `dword` |  |
| 11 | 76 | 4 | `FileOS` | `dword` |  |
| 12 | 80 | 4 | `FileType` | `dword` |  |
| 13 | 84 | 4 | `FileSubtype` | `dword` |  |
| 14 | 88 | 4 | `FileTimestamp` | `dword` |  |

