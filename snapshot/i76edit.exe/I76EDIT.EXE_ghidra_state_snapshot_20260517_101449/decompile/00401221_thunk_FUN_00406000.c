/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00406000
 * Entry: 00401221
 * Signature: undefined4 __cdecl thunk_FUN_00406000(undefined4 param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00406000(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined8 uVar1;
  
  DAT_00434438 = 0;
  uVar1 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  if (DAT_00434434 == 5) {
    DAT_00439b98 = (int)uVar1;
    DAT_00439b9c = (int)((ulonglong)uVar1 >> 0x20);
    thunk_FUN_00406b70();
    DAT_00439b90 = 0xffffffff;
    DAT_00439b98 = 0xffffffff;
    DAT_00439b94 = 0xffffffff;
    DAT_00439b9c = 0xffffffff;
  }
  return 1;
}


