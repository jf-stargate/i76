/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00411b30
 * Entry: 00401320
 * Signature: int __cdecl thunk_FUN_00411b30(int param_1, int param_2, int param_3)
 */


int __cdecl thunk_FUN_00411b30(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if ((param_1 < 0x50) && (param_2 < 0x50)) {
    iVar1 = (int)(char)(&DAT_00439ef0)[param_1 + param_2 * 0x50];
    if ((iVar1 == -1) && (param_3 != 0)) {
      iVar1 = FUN_004125a0();
      (&DAT_00439ef0)[param_1 + param_2 * 0x50] = (char)iVar1;
      thunk_FUN_0041ea60(iVar1);
    }
    return iVar1;
  }
  return -1;
}


