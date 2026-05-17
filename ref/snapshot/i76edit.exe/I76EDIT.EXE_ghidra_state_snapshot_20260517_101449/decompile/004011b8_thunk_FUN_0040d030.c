/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d030
 * Entry: 004011b8
 * Signature: undefined __cdecl thunk_FUN_0040d030(int * param_1, int param_2, uint * param_3, uint * param_4)
 */


void __cdecl thunk_FUN_0040d030(int *param_1,int param_2,uint *param_3,uint *param_4)

{
  int iVar1;
  short *psVar2;
  
  if (*param_1 < 0x32) {
    psVar2 = &DAT_0163ce72 + (*param_1 + param_2 * 0x32) * 2;
    do {
      if (*psVar2 != -1) {
        *param_3 = (uint)(byte)(&DAT_0163ce70)[(*param_1 + param_2 * 0x32) * 4];
        *param_4 = (uint)(byte)(&DAT_0163ce71)[(*param_1 + param_2 * 0x32) * 4];
        *param_1 = *param_1 + 1;
        return;
      }
      psVar2 = psVar2 + 2;
      iVar1 = *param_1;
      *param_1 = iVar1 + 1;
    } while (iVar1 + 1 < 0x32);
  }
  if (((&DAT_0163ce72)[(*param_1 + param_2 * 0x32) * 2] == -1) || (*param_1 == 0x32)) {
    *param_1 = -1;
  }
  return;
}


