/*
 * Program: i76.exe
 * Function: build_vehicle_ordnance_runtime_context
 * Entry: 004a7370
 * Signature: undefined __cdecl build_vehicle_ordnance_runtime_context(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/runtime rename v14; confidence=medium_high] Finds ordnc child objects,
   reads vehicle runtime/mission table fields, computes ordnance position/offset context, and emits
   a 0x7c-byte runtime block. */

void __cdecl build_vehicle_ordnance_runtime_context(undefined4 *param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  LPVOID pvVar5;
  float *pfVar6;
  int *piVar7;
  int iVar8;
  LPVOID *ppvVar9;
  float local_ac;
  float local_a8;
  float local_94 [3];
  float local_88;
  float local_84;
  float local_80;
  LPVOID local_7c [3];
  int local_70;
  int local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_7c[0] = release_world_object_tree_reference
                          (*(LPVOID *)(*(int *)(param_2 + 0x70) + 0xc),s_ordnc_004fe6f0);
  local_7c[2] = (LPVOID)0x0;
  *(LPVOID *)(*(int *)(param_2 + 0x70) + 0xc) = local_7c[0];
  pvVar5 = release_world_object_tree_reference
                     (*(LPVOID *)(*(int *)(param_2 + 0x70) + 0x10),s_ordnc_004fe6f0);
  local_7c[1] = pvVar5;
  *(LPVOID *)(*(int *)(param_2 + 0x70) + 0x10) = pvVar5;
  piVar1 = *(int **)(param_2 + 0x70);
  local_6c = 0;
  piVar7 = &g_mission_runtime_vehicle_table;
  local_70 = *piVar1;
  do {
    if (*piVar7 == *piVar1) goto LAB_004a73f1;
    piVar7 = piVar7 + 0x34;
    local_6c = local_6c + 1;
  } while ((int)piVar7 < 0x6562c0);
  local_6c = -1;
LAB_004a73f1:
  local_88 = (float)*(double *)(param_2 + 0x40);
  local_68 = local_88;
  local_5c = local_88;
  local_84 = (float)*(double *)(param_2 + 0x48);
  local_50 = *(undefined4 *)(param_2 + 0x30);
  local_80 = (float)*(double *)(param_2 + 0x50);
  local_4c = *(undefined4 *)(param_2 + 0x34);
  local_48 = *(undefined4 *)(param_2 + 0x38);
  local_44 = 0;
  local_3c = 0;
  local_64 = local_84;
  local_60 = local_80;
  local_40 = (float)(&DAT_006552b8)[local_6c * 0x34] * _DAT_004beb50;
  local_58 = local_84;
  local_54 = local_80;
  local_38 = piVar1[5];
  local_34 = piVar1[6];
  local_20 = piVar1[0xe];
  local_30 = piVar1[7];
  local_18 = piVar1[1];
  local_1c = piVar1[0xf];
  fVar2 = (float)piVar1[8];
  local_14 = piVar1[2];
  fVar3 = (float)piVar1[9];
  fVar4 = (float)piVar1[10];
  if (pvVar5 == (LPVOID)0x0) {
    local_4 = 0.0;
    local_ac = 0.0;
    local_a8 = 0.0;
  }
  else {
    pfVar6 = (float *)get_world_object_position_vector(local_94,(float)pvVar5);
    local_ac = *pfVar6;
    local_a8 = pfVar6[1];
    local_4 = pfVar6[2];
  }
  iVar8 = *(int *)(param_2 + 0x70);
  *(float *)(iVar8 + 0x20) = local_ac;
  *(float *)(iVar8 + 0x24) = local_a8;
  *(float *)(iVar8 + 0x28) = local_4;
  local_2c = local_ac - fVar2;
  local_28 = local_a8 - fVar3;
  local_24 = local_4 - fVar4;
  if (pvVar5 == (LPVOID)0x0) {
    local_c = 0.0;
    local_8 = 0.0;
    local_4 = 0.0;
    local_10 = 0.0;
  }
  else {
    local_c = local_ac;
    local_8 = local_a8;
    local_10 = SQRT((local_80 - local_4) * (local_80 - local_4) +
                    (local_84 - local_a8) * (local_84 - local_a8) +
                    (local_88 - local_ac) * (local_88 - local_ac));
  }
  ppvVar9 = local_7c;
  for (iVar8 = 0x1f; iVar8 != 0; iVar8 = iVar8 + -1) {
    *param_1 = *ppvVar9;
    ppvVar9 = ppvVar9 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


