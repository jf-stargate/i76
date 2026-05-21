# Structure Data Types

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

## `_struct_19`

Category: `/winnt.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `LowPart` | `DWORD` |  |
| 1 | 4 | 4 | `HighPart` | `LONG` |  |

## `_struct_20`

Category: `/winnt.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `LowPart` | `DWORD` |  |
| 1 | 4 | 4 | `HighPart` | `LONG` |  |

## `_struct_519`

Category: `/winbase.h`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Offset` | `DWORD` |  |
| 1 | 4 | 4 | `OffsetHigh` | `DWORD` |  |

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

## `IMAGE_DATA_DIRECTORY`

Category: `/PE`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `VirtualAddress` | `ImageBaseOffset32` |  |
| 1 | 4 | 4 | `Size` | `dword` |  |

## `IMAGE_DIRECTORY_ENTRY_EXPORT`

Category: `/PE`  
Length: `40`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `Characteristics` | `dword` |  |
| 1 | 4 | 4 | `TimeDateStamp` | `dword` |  |
| 2 | 8 | 2 | `MajorVersion` | `word` |  |
| 3 | 10 | 2 | `MinorVersion` | `word` |  |
| 4 | 12 | 4 | `Name` | `ImageBaseOffset32` |  |
| 5 | 16 | 4 | `Base` | `dword` |  |
| 6 | 20 | 4 | `NumberOfFunctions` | `dword` |  |
| 7 | 24 | 4 | `NumberOfNames` | `dword` |  |
| 8 | 28 | 4 | `AddressOfFunctions` | `ImageBaseOffset32` |  |
| 9 | 32 | 4 | `AddressOfNames` | `ImageBaseOffset32` |  |
| 10 | 36 | 4 | `AddressOfNameOrdinals` | `ImageBaseOffset32` |  |

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

## `joyinfo_tag`

Category: `/mmsystem.h`  
Length: `16`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `wXpos` | `UINT` |  |
| 1 | 4 | 4 | `wYpos` | `UINT` |  |
| 2 | 8 | 4 | `wZpos` | `UINT` |  |
| 3 | 12 | 4 | `wButtons` | `UINT` |  |

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

## `TypeDescriptor`

Category: `/`  
Length: `8`

| Ordinal | Offset | Length | Name | Type | Comment |
|---:|---:|---:|---|---|---|
| 0 | 0 | 4 | `hash` | `dword` |  |
| 1 | 4 | 4 | `spare` | `void *` |  |
| 2 | 8 | 0 | `name` | `char[0]` |  |

