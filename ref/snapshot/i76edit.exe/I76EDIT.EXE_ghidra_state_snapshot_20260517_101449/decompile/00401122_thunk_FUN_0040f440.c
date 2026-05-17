/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f440
 * Entry: 00401122
 * Signature: undefined4 * __stdcall thunk_FUN_0040f440(void)
 */


undefined4 * thunk_FUN_0040f440(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_00434968;
  if (DAT_00434968 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  DAT_00434968 = (undefined4 *)*DAT_00434968;
  return puVar1;
}


