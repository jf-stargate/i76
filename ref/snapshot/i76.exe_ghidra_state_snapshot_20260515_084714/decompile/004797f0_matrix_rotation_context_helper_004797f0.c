/*
 * Program: i76.exe
 * Function: matrix_rotation_context_helper_004797f0
 * Entry: 004797f0
 * Signature: undefined __cdecl matrix_rotation_context_helper_004797f0(int param_1, int param_2, int param_3, uint param_4)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix rotation context helper based
   on adjacent named subsystem context. */

void __cdecl
matrix_rotation_context_helper_004797f0(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  if ((((int)param_4 < 1) && (param_4 = DAT_00654b8c & 0xff, param_4 == 0)) || (10 < (int)param_4))
  {
    param_4 = 3;
  }
  iVar1 = param_4 * 0x100 + 0x6094a0;
  if (param_2 < param_3) {
    iVar3 = param_3 - param_2;
    pbVar2 = (byte *)(param_2 * 3 + 2 + param_1);
    do {
      pbVar2[-2] = *(byte *)(iVar1 + (uint)pbVar2[-2]);
      pbVar2[-1] = *(byte *)(iVar1 + (uint)pbVar2[-1]);
      iVar3 = iVar3 + -1;
      *pbVar2 = *(byte *)(iVar1 + (uint)*pbVar2);
      pbVar2 = pbVar2 + 3;
    } while (iVar3 != 0);
  }
  return;
}


