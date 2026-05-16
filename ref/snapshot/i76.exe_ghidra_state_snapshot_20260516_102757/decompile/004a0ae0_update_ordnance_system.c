/*
 * Program: i76.exe
 * Function: update_ordnance_system
 * Entry: 004a0ae0
 * Signature: undefined __cdecl update_ordnance_system(int param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

void __cdecl update_ordnance_system(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 *puVar7;
  int iVar8;
  float local_c [2];
  int *local_4;
  
  iVar2 = *(int *)(param_1 + 0x70);
  piVar3 = (int *)param_2[2];
  iVar8 = param_2[4];
  if ((float)param_2[7] == _DAT_004bea34) {
    param_2[7] = 0x40a00000;
  }
  iVar1 = param_2[7];
  *(int *)(iVar2 + 8) = iVar1;
  *(int *)(iVar2 + 4) = iVar1;
  iVar1 = param_2[1];
  *(int *)(iVar2 + 0xc) = iVar1;
  if (iVar1 != 0) {
    increment_refcount_recursive_for_object_tree(iVar1,s_ordnc_004fe6f0);
  }
  iVar1 = param_2[10];
  *(int *)(iVar2 + 0x10) = iVar1;
  if (iVar1 != 0) {
    increment_refcount_recursive_for_object_tree(iVar1,s_ordnc_004fe6f0);
  }
  if ((float)param_2[10] == 0.0) {
    *(undefined4 *)(iVar2 + 0x20) = 0;
    *(undefined4 *)(iVar2 + 0x24) = 0;
    *(undefined4 *)(iVar2 + 0x28) = 0;
  }
  else {
    puVar7 = (undefined4 *)get_world_object_position_vector(local_c,(float)param_2[10]);
    *(undefined4 *)(iVar2 + 0x20) = *puVar7;
    *(undefined4 *)(iVar2 + 0x24) = puVar7[1];
    *(undefined4 *)(iVar2 + 0x28) = puVar7[2];
  }
  *(int *)(iVar2 + 0x38) = iVar8;
  *(int *)(iVar2 + 0x3c) = param_2[9];
  *(undefined4 *)(iVar2 + 0x40) = 0;
  *(int *)(iVar2 + 0x44) = param_2[5];
  iVar8 = *param_2;
  if (((iVar8 == 0x10) || (iVar8 == 0xf)) || (param_2 = piVar3, iVar8 == 0x13)) {
    param_2 = (int *)0x40a00000;
  }
  local_c[0] = 0.0;
  local_c[1] = 0.0;
  local_4 = param_2;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  *(undefined4 *)(iVar2 + 0x48) = 0;
  *(undefined4 *)(iVar2 + 0x18) = 0;
  *(int **)(iVar2 + 0x1c) = param_2;
  iVar8 = rand();
  fVar4 = (float)iVar8 * _DAT_004bea38 * _DAT_004bea64 - _DAT_004bea68;
  iVar8 = rand();
  fVar5 = (float)iVar8 * _DAT_004bea38 * _DAT_004bea6c - _DAT_004bea70;
  iVar8 = rand();
  fVar5 = fVar5 * _DAT_004bea44;
  fVar6 = (float)iVar8 * _DAT_004bea38 * _DAT_004bea70 - _DAT_004bea74;
  *(float *)(iVar2 + 0x2c) = fVar4 * _DAT_004bea44;
  fVar6 = fVar6 * _DAT_004bea44;
  *(float *)(iVar2 + 0x30) = fVar5;
  *(float *)(iVar2 + 0x34) = fVar6;
  return;
}


