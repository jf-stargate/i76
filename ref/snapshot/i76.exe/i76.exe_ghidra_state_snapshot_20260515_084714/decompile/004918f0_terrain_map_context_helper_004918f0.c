/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004918f0
 * Entry: 004918f0
 * Signature: undefined __cdecl terrain_map_context_helper_004918f0(undefined2 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004918f0. Remove
   duplicated terrain wording. */

void __cdecl terrain_map_context_helper_004918f0(undefined2 *param_1)

{
  undefined2 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  undefined2 extraout_var;
  int iVar10;
  
  if (*(int *)(param_1 + 2) == 0) {
    iVar8 = ftol();
    iVar9 = ftol();
    iVar4 = DAT_006442ec;
    fVar2 = (float)(iVar9 >> 1);
    iVar10 = DAT_006442ec * 0xc;
    DAT_006442ec = DAT_006442ec + 1;
    *(float *)(DAT_005dd320 + iVar10) = fVar2;
    fVar3 = (float)(iVar8 >> 1);
    *(float *)(DAT_005dd320 + 8 + iVar10) = fVar3;
    uVar7 = terrain_map_context_helper_00493160(iVar9 >> 1,iVar8 >> 1);
    *(float *)(DAT_005dd320 + 4 + iVar10) = (float)CONCAT22(extraout_var,uVar7);
    *(float *)(DAT_005dd2ec + iVar10) = fVar2 * _DAT_004be80c;
    *(float *)(DAT_005dd2ec + 4 + iVar10) = fVar3 * _DAT_004be80c;
    puVar5 = DAT_00654380;
    puVar6 = DAT_00654380 + 6;
    *DAT_00654380 = *param_1;
    DAT_00654380 = puVar6;
    puVar5[1] = (short)iVar4;
    *(undefined4 *)(puVar5 + 2) = 0;
    *(undefined4 *)(puVar5 + 4) = 0;
    DAT_0059c568 = DAT_0059c568 + 1;
    uVar1 = param_1[1];
    *(undefined2 **)(param_1 + 2) = puVar5;
    puVar5 = DAT_00654380;
    puVar6 = DAT_00654380 + 6;
    *DAT_00654380 = (short)iVar4;
    DAT_00654380 = puVar6;
    puVar5[1] = uVar1;
    *(undefined4 *)(puVar5 + 2) = 0;
    *(undefined4 *)(puVar5 + 4) = 0;
    DAT_0059c568 = DAT_0059c568 + 1;
    *(undefined2 **)(param_1 + 4) = puVar5;
  }
  return;
}


