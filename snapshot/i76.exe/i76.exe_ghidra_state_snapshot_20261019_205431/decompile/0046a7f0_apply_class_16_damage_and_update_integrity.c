/*
 * Program: i76.exe
 * Function: apply_class_16_damage_and_update_integrity
 * Entry: 0046a7f0
 * Signature: undefined4 __cdecl apply_class_16_damage_and_update_integrity(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl apply_class_16_damage_and_update_integrity(int param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar4 = 0;
  piVar5 = (int *)(param_2 + 8);
  fVar2 = *(float *)(iVar1 + 0xc) * _DAT_004be308;
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar4 & 0x1f)) != 0) {
      if (*(int *)(iVar1 + 4) < *piVar5) {
        *(int *)(param_2 + 8 + iVar4 * 4) = *(int *)(param_2 + 8 + iVar4 * 4) - *(int *)(iVar1 + 4);
        *(float *)(iVar1 + 0x10) = fVar2;
        *(undefined4 *)(iVar1 + 4) = 0;
        return 1;
      }
      *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) - *piVar5;
      *piVar5 = 0;
    }
    iVar4 = iVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar4 < 4);
  fVar3 = ((float)*(int *)(iVar1 + 4) / (float)*(int *)(iVar1 + 8)) * *(float *)(iVar1 + 0xc);
  *(float *)(iVar1 + 0x10) = fVar3;
  if (fVar3 < fVar2) {
    *(float *)(iVar1 + 0x10) = fVar2;
    return 0;
  }
  return 0;
}


