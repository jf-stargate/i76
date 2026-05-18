/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499950
 * Entry: 00499950
 * Signature: uint __stdcall system_cutscene_memory_context_helper_00499950(void)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499950. Shorten readability
   label for system/cutscene/virtual-memory context. */

uint system_cutscene_memory_context_helper_00499950(void)

{
  int iVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  ushort uVar5;
  short sVar6;
  uint uVar7;
  _SYSTEM_INFO local_2c;
  
  GetSystemInfo(&local_2c);
  if (local_2c.dwProcessorType == 0x182) {
    uVar7 = 3;
  }
  else if (local_2c.dwProcessorType == 0x1e6) {
    uVar7 = 4;
  }
  else {
    if (local_2c.dwProcessorType != 0x24a) {
      return 0xffffffff;
    }
    uVar7 = 5;
  }
  if (uVar7 < 3) {
    return 0xfffffd66;
  }
  out(0x43,0xb8);
  bVar2 = in(0x61);
  out(0x61,bVar2 | 1);
  out(0x42,0);
  out(0x42,0);
  sVar6 = 0x50;
  do {
    for (iVar1 = 0; (0x80000000U >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
    }
    sVar6 = sVar6 + -1;
  } while (0 < sVar6);
  uVar3 = in(0x42);
  uVar4 = in(0x42);
  uVar5 = -(short)CONCAT31(CONCAT21(0x8000,uVar4),uVar3);
  if (uVar5 == 0) {
    return 0xffffffff;
  }
  uVar7 = (uint)(((ulonglong)((uint)(ushort)(*(short *)(uVar7 * 2 + 0x4fe240) * 0x50) * 0x1234dc) /
                 (ulonglong)uVar5) / 1000000);
  if ((0x37 < uVar7) && (uVar7 < 0x41)) {
    return 0x3c;
  }
  if ((0x46 < uVar7) && (uVar7 < 0x50)) {
    return 0x4b;
  }
  if ((0x5f < uVar7) && (uVar7 < 0x69)) {
    return 100;
  }
  if ((0x73 < uVar7) && (uVar7 < 0x7d)) {
    return 0x78;
  }
  if ((0x80 < uVar7) && (uVar7 < 0x8a)) {
    return 0x85;
  }
  if ((0x91 < uVar7) && (uVar7 < 0x9b)) {
    return 0x96;
  }
  if ((0xa1 < uVar7) && (uVar7 < 0xab)) {
    return 0xa6;
  }
  if ((0xaf < uVar7) && (uVar7 < 0xb9)) {
    return 0xb4;
  }
  if ((0xc3 < uVar7) && (uVar7 < 0xcd)) {
    uVar7 = 200;
  }
  return uVar7;
}


