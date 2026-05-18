/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004113c0
 * Entry: 0040132f
 * Signature: undefined4 __cdecl thunk_FUN_004113c0(int param_1, undefined4 * param_2)
 */


undefined4 __cdecl thunk_FUN_004113c0(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  long _Offset;
  int iStack_c;
  int iStack_8;
  long lStack_4;
  
  iStack_c = 0;
  iStack_8 = 0;
  lStack_4 = __tell(param_1);
  __write(param_1,&iStack_c,4);
  for (puVar1 = FUN_00411520(param_2); puVar1 != (undefined4 *)0x0;
      puVar1 = FUN_00411520((undefined4 *)*puVar1)) {
    __write(param_1,(void *)(puVar1[2] + 0x28),0x28);
    lVar2 = __tell(param_1);
    __write(param_1,&iStack_8,4);
    iStack_8 = FUN_00411550(param_1,(int)puVar1);
    _Offset = __tell(param_1);
    __lseek(param_1,lVar2,0);
    __write(param_1,&iStack_8,4);
    __lseek(param_1,_Offset,0);
    iStack_c = iStack_c + 1;
  }
  lVar2 = __tell(param_1);
  __lseek(param_1,lStack_4,0);
  __write(param_1,&iStack_c,4);
  __lseek(param_1,lVar2,0);
  return 0;
}


