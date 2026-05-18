/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00412300
 * Entry: 0040121c
 * Signature: undefined __cdecl thunk_FUN_00412300(int * param_1, uint param_2, uint param_3)
 */


void __cdecl thunk_FUN_00412300(int *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (int)param_3 >> 0x1f;
  uVar2 = (int)param_2 >> 0x1f;
  *param_1 = (int)(char)(&DAT_00439ef0)
                        [((int)(param_2 + (uVar2 & 0x7f)) >> 7) +
                         ((int)(param_3 + (uVar1 & 0x7f)) >> 7) * 0x50];
  param_1[1] = ((param_2 ^ uVar2) - uVar2 & 0x7f ^ uVar2) - uVar2;
  param_1[2] = ((param_3 ^ uVar1) - uVar1 & 0x7f ^ uVar1) - uVar1;
  return;
}


