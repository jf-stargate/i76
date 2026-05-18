/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041bcb0
 * Entry: 0040114f
 * Signature: undefined4 __cdecl thunk_FUN_0041bcb0(int param_1)
 */


undefined4 __cdecl thunk_FUN_0041bcb0(int param_1)

{
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_8 = 0x54495845;
  uStack_4 = 8;
  __write(param_1,&uStack_8,8);
  return 8;
}


