# Structure Data Types

## `__lc_time_data`

Category: `/crtdefs.h`  
Length: `356`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 28 | `wday_abbr` | `char *[7]` |  |
| 1 | 28 | 28 | `wday` | `char *[7]` |  |
| 2 | 56 | 48 | `month_abbr` | `char *[12]` |  |
| 3 | 104 | 48 | `month` | `char *[12]` |  |
| 4 | 152 | 8 | `ampm` | `char *[2]` |  |
| 5 | 160 | 4 | `ww_sdatefmt` | `char *` |  |
| 6 | 164 | 4 | `ww_ldatefmt` | `char *` |  |
| 7 | 168 | 4 | `ww_timefmt` | `char *` |  |
| 8 | 172 | 4 | `ww_caltype` | `int` |  |
| 9 | 176 | 4 | `refcount` | `int` |  |
| 10 | 180 | 28 | `_W_wday_abbr` | `wchar_t *[7]` |  |
| 11 | 208 | 28 | `_W_wday` | `wchar_t *[7]` |  |
| 12 | 236 | 48 | `_W_month_abbr` | `wchar_t *[12]` |  |
| 13 | 284 | 48 | `_W_month` | `wchar_t *[12]` |  |
| 14 | 332 | 8 | `_W_ampm` | `wchar_t *[2]` |  |
| 15 | 340 | 4 | `_W_ww_sdatefmt` | `wchar_t *` |  |
| 16 | 344 | 4 | `_W_ww_ldatefmt` | `wchar_t *` |  |
| 17 | 348 | 4 | `_W_ww_timefmt` | `wchar_t *` |  |
| 18 | 352 | 4 | `_W_ww_locale_name` | `wchar_t *` |  |

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

## `_cpinfo`

Category: `/winnls.h`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `MaxCharSize` | `UINT` |  |
| 1 | 4 | 2 | `DefaultChar` | `BYTE[2]` |  |
| 2 | 6 | 12 | `LeadByte` | `BYTE[12]` |  |

## `_CRT_DOUBLE`

Category: `/stdlib.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 8 | `x` | `double` |  |

## `_CRT_FLOAT`

Category: `/stdlib.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `f` | `float` |  |

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

## `_LDBL12`

Category: `/stdlib.h`  
Length: `12`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 12 | `ld12` | `uchar[12]` |  |

## `_OVERLAPPED`

Category: `/winbase.h`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Internal` | `ULONG_PTR` |  |
| 1 | 4 | 4 | `InternalHigh` | `ULONG_PTR` |  |
| 2 | 8 | 8 | `u` | `_union_518` |  |
| 3 | 16 | 4 | `hEvent` | `HANDLE` |  |

## `_PROCESS_INFORMATION`

Category: `/winbase.h`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `hProcess` | `HANDLE` |  |
| 1 | 4 | 4 | `hThread` | `HANDLE` |  |
| 2 | 8 | 4 | `dwProcessId` | `DWORD` |  |
| 3 | 12 | 4 | `dwThreadId` | `DWORD` |  |

## `_SECURITY_ATTRIBUTES`

Category: `/winbase.h`  
Length: `12`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `nLength` | `DWORD` |  |
| 1 | 4 | 4 | `lpSecurityDescriptor` | `LPVOID` |  |
| 2 | 8 | 4 | `bInheritHandle` | `BOOL` |  |

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

## `_strflt`

Category: `/fltintrn.h`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `sign` | `int` |  |
| 1 | 4 | 4 | `decpt` | `int` |  |
| 2 | 8 | 4 | `flag` | `int` |  |
| 3 | 12 | 4 | `mantissa` | `char *` |  |

## `_struct_519`

Category: `/winbase.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Offset` | `DWORD` |  |
| 1 | 4 | 4 | `OffsetHigh` | `DWORD` |  |

## `_TBBUTTON`

Category: `/commctrl.h`  
Length: `20`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `iBitmap` | `int` |  |
| 1 | 4 | 4 | `idCommand` | `int` |  |
| 2 | 8 | 1 | `fsState` | `BYTE` |  |
| 3 | 9 | 1 | `fsStyle` | `BYTE` |  |
| 4 | 10 | 2 | `bReserved` | `BYTE[2]` |  |
| 5 | 12 | 4 | `dwData` | `DWORD_PTR` |  |
| 6 | 16 | 4 | `iString` | `INT_PTR` |  |

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

## `HICON__`

Category: `/WinDef.h`  
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

## `HMENU__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HPEN__`

Category: `/WinDef.h`  
Length: `4`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `unused` | `int` |  |

## `HRGN__`

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

## `lconv`

Category: `/crtdefs.h`  
Length: `80`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `decimal_point` | `char *` |  |
| 1 | 4 | 4 | `thousands_sep` | `char *` |  |
| 2 | 8 | 4 | `grouping` | `char *` |  |
| 3 | 12 | 4 | `int_curr_symbol` | `char *` |  |
| 4 | 16 | 4 | `currency_symbol` | `char *` |  |
| 5 | 20 | 4 | `mon_decimal_point` | `char *` |  |
| 6 | 24 | 4 | `mon_thousands_sep` | `char *` |  |
| 7 | 28 | 4 | `mon_grouping` | `char *` |  |
| 8 | 32 | 4 | `positive_sign` | `char *` |  |
| 9 | 36 | 4 | `negative_sign` | `char *` |  |
| 10 | 40 | 1 | `int_frac_digits` | `char` |  |
| 11 | 41 | 1 | `frac_digits` | `char` |  |
| 12 | 42 | 1 | `p_cs_precedes` | `char` |  |
| 13 | 43 | 1 | `p_sep_by_space` | `char` |  |
| 14 | 44 | 1 | `n_cs_precedes` | `char` |  |
| 15 | 45 | 1 | `n_sep_by_space` | `char` |  |
| 16 | 46 | 1 | `p_sign_posn` | `char` |  |
| 17 | 47 | 1 | `n_sign_posn` | `char` |  |
| 18 | 48 | 4 | `_W_decimal_point` | `wchar_t *` |  |
| 19 | 52 | 4 | `_W_thousands_sep` | `wchar_t *` |  |
| 20 | 56 | 4 | `_W_int_curr_symbol` | `wchar_t *` |  |
| 21 | 60 | 4 | `_W_currency_symbol` | `wchar_t *` |  |
| 22 | 64 | 4 | `_W_mon_decimal_point` | `wchar_t *` |  |
| 23 | 68 | 4 | `_W_mon_thousands_sep` | `wchar_t *` |  |
| 24 | 72 | 4 | `_W_positive_sign` | `wchar_t *` |  |
| 25 | 76 | 4 | `_W_negative_sign` | `wchar_t *` |  |

## `localeinfo_struct`

Category: `/crtdefs.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `locinfo` | `pthreadlocinfo` |  |
| 1 | 4 | 4 | `mbcinfo` | `pthreadmbcinfo` |  |

## `localerefcount`

Category: `/crtdefs.h`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `locale` | `char *` |  |
| 1 | 4 | 4 | `wlocale` | `wchar_t *` |  |
| 2 | 8 | 4 | `refcount` | `int *` |  |
| 3 | 12 | 4 | `wrefcount` | `int *` |  |

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

## `tagOFNA`

Category: `/commdlg.h`  
Length: `88`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `lStructSize` | `DWORD` |  |
| 1 | 4 | 4 | `hwndOwner` | `HWND` |  |
| 2 | 8 | 4 | `hInstance` | `HINSTANCE` |  |
| 3 | 12 | 4 | `lpstrFilter` | `LPCSTR` |  |
| 4 | 16 | 4 | `lpstrCustomFilter` | `LPSTR` |  |
| 5 | 20 | 4 | `nMaxCustFilter` | `DWORD` |  |
| 6 | 24 | 4 | `nFilterIndex` | `DWORD` |  |
| 7 | 28 | 4 | `lpstrFile` | `LPSTR` |  |
| 8 | 32 | 4 | `nMaxFile` | `DWORD` |  |
| 9 | 36 | 4 | `lpstrFileTitle` | `LPSTR` |  |
| 10 | 40 | 4 | `nMaxFileTitle` | `DWORD` |  |
| 11 | 44 | 4 | `lpstrInitialDir` | `LPCSTR` |  |
| 12 | 48 | 4 | `lpstrTitle` | `LPCSTR` |  |
| 13 | 52 | 4 | `Flags` | `DWORD` |  |
| 14 | 56 | 2 | `nFileOffset` | `WORD` |  |
| 15 | 58 | 2 | `nFileExtension` | `WORD` |  |
| 16 | 60 | 4 | `lpstrDefExt` | `LPCSTR` |  |
| 17 | 64 | 4 | `lCustData` | `LPARAM` |  |
| 18 | 68 | 4 | `lpfnHook` | `LPOFNHOOKPROC` |  |
| 19 | 72 | 4 | `lpTemplateName` | `LPCSTR` |  |
| 20 | 76 | 4 | `pvReserved` | `void *` |  |
| 21 | 80 | 4 | `dwReserved` | `DWORD` |  |
| 22 | 84 | 4 | `FlagsEx` | `DWORD` |  |

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

## `threadlocaleinfostruct`

Category: `/crtdefs.h`  
Length: `184`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `refcount` | `int` |  |
| 1 | 4 | 4 | `lc_codepage` | `uint` |  |
| 2 | 8 | 4 | `lc_collate_cp` | `uint` |  |
| 3 | 12 | 4 | `lc_time_cp` | `uint` |  |
| 4 | 16 | 96 | `lc_category` | `locrefcount[6]` |  |
| 5 | 112 | 4 | `lc_clike` | `int` |  |
| 6 | 116 | 4 | `mb_cur_max` | `int` |  |
| 7 | 120 | 4 | `lconv_intl_refcount` | `int *` |  |
| 8 | 124 | 4 | `lconv_num_refcount` | `int *` |  |
| 9 | 128 | 4 | `lconv_mon_refcount` | `int *` |  |
| 10 | 132 | 4 | `lconv` | `lconv *` |  |
| 11 | 136 | 4 | `ctype1_refcount` | `int *` |  |
| 12 | 140 | 4 | `ctype1` | `ushort *` |  |
| 13 | 144 | 4 | `pctype` | `ushort *` |  |
| 14 | 148 | 4 | `pclmap` | `uchar *` |  |
| 15 | 152 | 4 | `pcumap` | `uchar *` |  |
| 16 | 156 | 4 | `lc_time_curr` | `__lc_time_data *` |  |
| 17 | 160 | 24 | `locale_name` | `wchar_t *[6]` |  |

## `threadmbcinfostruct`

Category: `/crtdefs.h`  
Length: `544`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `refcount` | `int` |  |
| 1 | 4 | 4 | `mbcodepage` | `int` |  |
| 2 | 8 | 4 | `ismbcodepage` | `int` |  |
| 3 | 12 | 12 | `mbulinfo` | `ushort[6]` |  |
| 4 | 24 | 257 | `mbctype` | `uchar[257]` |  |
| 5 | 281 | 256 | `mbcasemap` | `uchar[256]` |  |
| 6 | 540 | 4 | `mblocalename` | `wchar_t *` |  |

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

