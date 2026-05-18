/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00411ba0
 * Entry: 00401154
 * Signature: undefined __cdecl thunk_FUN_00411ba0(int param_1, int param_2, int param_3)
 */


void __cdecl thunk_FUN_00411ba0(int param_1,int param_2,int param_3)

{
  thunk_FUN_00411b30((int)(param_1 + (param_1 >> 0x1f & 0x7fU)) >> 7,
                     (int)(param_2 + (param_2 >> 0x1f & 0x7fU)) >> 7,param_3);
  return;
}


