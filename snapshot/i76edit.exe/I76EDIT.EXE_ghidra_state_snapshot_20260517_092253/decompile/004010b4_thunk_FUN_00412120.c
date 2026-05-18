/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00412120
 * Entry: 004010b4
 * Signature: undefined4 * __cdecl thunk_FUN_00412120(int param_1, int param_2)
 */


undefined4 * __cdecl thunk_FUN_00412120(int param_1,int param_2)

{
  if (param_2 == 1) {
    return (undefined4 *)(&DAT_0043c554 + param_1 * 0x4002);
  }
  if (param_2 == 2) {
    return (undefined4 *)(&DAT_00ebcaa4 + param_1 * 0x8004);
  }
  if (param_2 == 3) {
    return (undefined4 *)(&DAT_0113cbe4 + param_1 * 0x4002);
  }
  if (param_2 == 4) {
    return (undefined4 *)(&DAT_00c3c964 + param_1 * 0x8004);
  }
  if (param_2 == 5) {
    return &DAT_013bcd24 + param_1 * 0x2001;
  }
  return (undefined4 *)(&DAT_009bc824 + param_1 * 0x4002);
}


