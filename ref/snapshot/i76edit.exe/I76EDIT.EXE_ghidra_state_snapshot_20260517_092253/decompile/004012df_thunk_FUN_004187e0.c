/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004187e0
 * Entry: 004012df
 * Signature: undefined __cdecl thunk_FUN_004187e0(int param_1, int param_2)
 */


void __cdecl thunk_FUN_004187e0(int param_1,int param_2)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  ushort *puStack_4;
  
  puVar1 = (ushort *)thunk_FUN_00412120(param_1,0);
  if (2 < param_2) {
    puStack_4 = (ushort *)thunk_FUN_00412120(param_1,3);
  }
  iVar2 = 0x80;
  do {
    iVar3 = 0x80;
    do {
      *puVar1 = *puVar1 & 0xfff;
      if ((2 < param_2) && (*puStack_4 != 0x8000)) {
        *puStack_4 = *puStack_4 & 0xfff;
      }
      puStack_4 = puStack_4 + 1;
      puVar1 = puVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


