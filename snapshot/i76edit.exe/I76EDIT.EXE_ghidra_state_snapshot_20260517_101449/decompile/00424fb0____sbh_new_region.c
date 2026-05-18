/*
 * Program: I76EDIT.EXE
 * Function: ___sbh_new_region
 * Entry: 00424fb0
 * Signature: undefined * * __stdcall ___sbh_new_region(void)
 */


/* Library Function - Single Match
    ___sbh_new_region
   
   Library: Visual Studio 1998 Release */

undefined ** ___sbh_new_region(void)

{
  undefined4 *lpAddress;
  LPVOID pvVar1;
  int iVar2;
  int iVar3;
  undefined **lpMem;
  undefined4 *puVar4;
  
  if (DAT_00438668 == 0) {
    lpMem = &PTR_LOOP_00437e58;
  }
  else {
    lpMem = HeapAlloc(DAT_016424f0,0,0x814);
    if (lpMem == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  lpAddress = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (lpAddress != (undefined4 *)0x0) {
    pvVar1 = VirtualAlloc(lpAddress,0x10000,0x1000,4);
    if (pvVar1 != (LPVOID)0x0) {
      if (lpMem == &PTR_LOOP_00437e58) {
        if (PTR_LOOP_00437e58 == (undefined *)0x0) {
          PTR_LOOP_00437e58 = (undefined *)&PTR_LOOP_00437e58;
        }
        if (PTR_LOOP_00437e5c == (undefined *)0x0) {
          PTR_LOOP_00437e5c = (undefined *)&PTR_LOOP_00437e58;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_00437e58;
        lpMem[1] = PTR_LOOP_00437e5c;
        PTR_LOOP_00437e5c = (undefined *)lpMem;
        *(undefined ***)lpMem[1] = lpMem;
      }
      lpMem[0x204] = (undefined *)lpAddress;
      lpMem[2] = (undefined *)0x0;
      lpMem[3] = (undefined *)0x10;
      iVar2 = 0;
      do {
        if (iVar2 < 0x10) {
          *(undefined1 *)((int)lpMem + iVar2 + 0x10) = 0xf0;
        }
        else {
          *(undefined1 *)((int)lpMem + iVar2 + 0x10) = 0xff;
        }
        iVar3 = iVar2 + 1;
        *(undefined1 *)((int)lpMem + iVar2 + 0x410) = 0xf1;
        iVar2 = iVar3;
      } while (iVar3 < 0x400);
      puVar4 = lpAddress;
      for (iVar2 = 0x4000; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      if (lpAddress < lpMem[0x204] + 0x10000) {
        do {
          *lpAddress = lpAddress + 2;
          lpAddress[1] = 0xf0;
          *(undefined1 *)(lpAddress + 0x3e) = 0xff;
          lpAddress = lpAddress + 0x400;
        } while (lpAddress < lpMem[0x204] + 0x10000);
      }
      return lpMem;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  if (lpMem != &PTR_LOOP_00437e58) {
    HeapFree(DAT_016424f0,0,lpMem);
  }
  return (undefined **)0x0;
}


