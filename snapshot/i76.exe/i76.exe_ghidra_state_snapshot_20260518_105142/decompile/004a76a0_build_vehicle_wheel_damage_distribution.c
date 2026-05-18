/*
 * Program: i76.exe
 * Function: build_vehicle_wheel_damage_distribution
 * Entry: 004a76a0
 * Signature: undefined __cdecl build_vehicle_wheel_damage_distribution(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Distributes a damage/scalar
   value across four wheel slots based on mission table mask. */

void __cdecl build_vehicle_wheel_damage_distribution(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10 [4];
  
  puVar6 = &local_18;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  piVar1 = *(int **)(param_2 + 0x70);
  iVar4 = world_object_has_optional_runtime_flag(piVar1[3]);
  if (iVar4 != 0) {
    is_damage_side_effects_suppressed();
  }
  if (piVar1 == (int *)0x0) {
    local_14 = (uint)local_14._2_2_ << 0x10;
    local_10[0] = 0;
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
  }
  else {
    iVar4 = 0;
    piVar2 = &g_mission_runtime_vehicle_table;
    do {
      if (*piVar2 == *piVar1) goto LAB_004a7741;
      piVar2 = piVar2 + 0x34;
      iVar4 = iVar4 + 1;
    } while ((int)piVar2 < 0x6562c0);
    iVar4 = -1;
LAB_004a7741:
    uVar7 = 0;
    local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)(&DAT_006552e8 + iVar4 * 0x34));
    uVar3 = ftol();
    iVar4 = 0;
    do {
      if ((local_14 & 0xffff & 1 << ((byte)iVar4 & 0x1f)) != 0) {
        uVar7 = uVar7 + 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    if (1 < (int)uVar7) {
      uVar3 = uVar3 / uVar7;
    }
    iVar4 = 0;
    puVar5 = local_10;
    do {
      *puVar5 = 0;
      if ((local_14 & 0xffff & 1 << ((byte)iVar4 & 0x1f)) != 0) {
        *puVar5 = uVar3;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 4);
  }
  puVar6 = &local_18;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *param_1 = *puVar6;
    puVar6 = puVar6 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


