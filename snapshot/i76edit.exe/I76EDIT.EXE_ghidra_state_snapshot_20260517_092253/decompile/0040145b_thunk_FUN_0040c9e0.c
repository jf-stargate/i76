/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040c9e0
 * Entry: 0040145b
 * Signature: undefined4 * __stdcall thunk_FUN_0040c9e0(void)
 */


undefined4 * thunk_FUN_0040c9e0(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_004347bc;
  if (DAT_004347bc == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  DAT_004347bc = (undefined4 *)*DAT_004347bc;
  return puVar1;
}


