/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ce70
 * Entry: 00401456
 * Signature: undefined __stdcall thunk_FUN_0040ce70(void)
 */


void thunk_FUN_0040ce70(void)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  
  puVar3 = &DAT_0163ce72;
  iVar1 = 0x50;
  do {
    iVar2 = 0x32;
    puVar4 = puVar3;
    do {
      *puVar4 = 0xffff;
      puVar3 = puVar4 + 2;
      iVar2 = iVar2 + -1;
      *(undefined1 *)(puVar4 + -1) = 0xff;
      *(undefined1 *)((int)puVar4 + -1) = 0xff;
      puVar4 = puVar3;
    } while (iVar2 != 0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


