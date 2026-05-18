/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ac20
 * Entry: 0040103c
 * Signature: undefined __stdcall thunk_FUN_0040ac20(void)
 */


void thunk_FUN_0040ac20(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  do {
    for (puVar1 = (undefined4 *)(&DAT_00439be8)[uVar4]; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      puVar3 = thunk_FUN_00412120(uVar4,0);
      iVar2 = puVar1[2];
      *(uint *)(iVar2 + 0xc) =
           (uint)*(ushort *)((int)puVar3 + (*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4)) * 2);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x50);
  return;
}


