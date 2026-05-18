/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040edb0
 * Entry: 004012ee
 * Signature: undefined __cdecl thunk_FUN_0040edb0(int param_1)
 */


void __cdecl thunk_FUN_0040edb0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  long _Offset;
  long _Offset_00;
  int iStack_4;
  
  iStack_4 = 0;
  _Offset = __tell(param_1);
  __write(param_1,&iStack_4,4);
  for (puVar2 = DAT_00434964; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    iVar1 = puVar2[2];
    __write(param_1,(void *)(iVar1 + 0x29),0x28);
    __write(param_1,(void *)(iVar1 + 0x58),8);
    iStack_4 = iStack_4 + 1;
  }
  _Offset_00 = __tell(param_1);
  __lseek(param_1,_Offset,0);
  __write(param_1,&iStack_4,4);
  __lseek(param_1,_Offset_00,0);
  return;
}


