/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408ca0
 * Entry: 00401401
 * Signature: undefined4 * __stdcall thunk_FUN_00408ca0(void)
 */


undefined4 * thunk_FUN_00408ca0(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_00434748;
  if (DAT_00434748 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  DAT_00434748 = (undefined4 *)*DAT_00434748;
  return puVar1;
}


