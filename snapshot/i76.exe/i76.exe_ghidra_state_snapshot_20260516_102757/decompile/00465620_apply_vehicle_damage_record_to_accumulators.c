/*
 * Program: i76.exe
 * Function: apply_vehicle_damage_record_to_accumulators
 * Entry: 00465620
 * Signature: int __cdecl apply_vehicle_damage_record_to_accumulators(int param_1, int * param_2, int param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Applies a vehicle damage record against component damage accumulators, honoring
   special equipment and suppression flags. */

int __cdecl
apply_vehicle_damage_record_to_accumulators(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  
  iVar4 = param_1;
  if ((int *)0x4 < param_2) {
    return 0;
  }
  if ((param_2 == (int *)0x0) || (param_2 == (int *)0x3)) {
    iVar2 = *(int *)(param_1 + 0x3ec);
    iVar1 = get_special_equipment_runtime_index(iVar2);
    if ((iVar1 != 5) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
      iVar2 = *(int *)(param_1 + 0x3f0);
      iVar1 = get_special_equipment_runtime_index(iVar2);
      if ((iVar1 != 5) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
        iVar2 = *(int *)(param_1 + 0x3f4);
        iVar1 = get_special_equipment_runtime_index(iVar2);
        if (iVar1 == 5) {
          is_special_equipment_component_active(iVar2);
        }
      }
    }
  }
  iVar2 = *(int *)(param_1 + 0x3ec);
  iVar1 = get_special_equipment_runtime_index(iVar2);
  if ((iVar1 != 7) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
    iVar2 = *(int *)(param_1 + 0x3f0);
    iVar1 = get_special_equipment_runtime_index(iVar2);
    if ((iVar1 != 7) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
      iVar2 = *(int *)(param_1 + 0x3f4);
      iVar1 = get_special_equipment_runtime_index(iVar2);
      if (iVar1 == 7) {
        is_special_equipment_component_active(iVar2);
      }
    }
  }
  iVar2 = *(int *)(param_1 + 0x3ec);
  iVar1 = get_special_equipment_runtime_index(iVar2);
  if ((iVar1 != 6) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
    iVar2 = *(int *)(param_1 + 0x3f0);
    iVar1 = get_special_equipment_runtime_index(iVar2);
    if ((iVar1 != 6) || (iVar2 = is_special_equipment_component_active(iVar2), iVar2 == 0)) {
      iVar2 = *(int *)(param_1 + 0x3f4);
      iVar1 = get_special_equipment_runtime_index(iVar2);
      if (iVar1 == 6) {
        is_special_equipment_component_active(iVar2);
      }
    }
  }
  if (param_2 != (int *)0x4) {
    if (((*(byte *)(param_3 + 4) & 8) == 0) ||
       (((((byte)DAT_00654b98 & 0x10) != 0 && (param_4 != 0)) &&
        (iVar2 = is_damage_side_effects_suppressed(), iVar2 == 0)))) {
      if (((((byte)DAT_00654b98 & 0x10) != 0) && (param_4 != 0)) &&
         (iVar2 = is_damage_side_effects_suppressed(), iVar2 == 0)) {
        *(undefined4 *)(param_3 + 0x14) = 0;
      }
    }
    else {
      iVar2 = *(int *)(param_1 + 0x148 + (int)param_2 * 4);
      uVar5 = ftol();
      if (uVar5 < *(uint *)(param_3 + 0x14)) {
        *(uint *)(param_3 + 0x14) = *(uint *)(param_3 + 0x14) - uVar5;
        *(undefined4 *)(param_1 + 0x148 + (int)param_2 * 4) = 0;
        *(undefined4 *)(param_1 + 0x18c + (int)param_2 * 4) = 0;
      }
      else {
        iVar1 = ftol();
        *(int *)(param_1 + 0x148 + (int)param_2 * 4) = iVar2 - iVar1;
        iVar2 = ftol();
        *(int *)(param_1 + 0x18c + (int)param_2 * 4) =
             *(int *)(param_1 + 0x18c + (int)param_2 * 4) - iVar2;
        *(undefined4 *)(param_3 + 0x14) = 0;
      }
    }
    puVar6 = (uint *)(param_3 + 8);
    param_1 = 4;
    puVar7 = puVar6;
    do {
      if (((*(byte *)(param_3 + 4) & 3) == 0) ||
         (((((byte)DAT_00654b98 & 8) != 0 && (param_4 != 0)) &&
          (iVar2 = is_damage_side_effects_suppressed(), iVar2 == 0)))) {
        if (((((byte)DAT_00654b98 & 8) != 0) && (param_4 != 0)) &&
           (iVar2 = is_damage_side_effects_suppressed(), iVar2 == 0)) {
          *puVar7 = 0;
        }
      }
      else {
        iVar2 = *(int *)(iVar4 + 0x138 + (int)param_2 * 4);
        uVar5 = ftol();
        if (uVar5 < *puVar7) {
          *puVar7 = *puVar7 - uVar5;
          *(undefined4 *)(iVar4 + 0x138 + (int)param_2 * 4) = 0;
          *(undefined4 *)(iVar4 + 0x178 + (int)param_2 * 4) = 0;
        }
        else {
          iVar1 = ftol();
          *(int *)(iVar4 + 0x138 + (int)param_2 * 4) = iVar2 - iVar1;
          iVar2 = ftol();
          *(int *)(iVar4 + 0x178 + (int)param_2 * 4) =
               *(int *)(iVar4 + 0x178 + (int)param_2 * 4) - iVar2;
          *puVar7 = 0;
        }
      }
      puVar7 = puVar7 + 1;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
    iVar4 = 0;
    iVar2 = 0;
    do {
      if (((uint)*(ushort *)(param_3 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
        iVar4 = iVar4 + *puVar6;
      }
      iVar2 = iVar2 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar2 < 4);
    return iVar4;
  }
  if ((*(byte *)(param_3 + 4) & 8) != 0) {
    iVar4 = *(int *)(param_1 + 0x19c);
    uVar5 = *(uint *)(param_3 + 0x14);
    uVar3 = ftol();
    if (uVar3 < uVar5) {
      puVar6 = (uint *)(param_3 + 8);
      *(undefined4 *)(param_1 + 0x19c) = 0;
      param_4 = 4;
      goto LAB_00465862;
    }
    iVar2 = ftol();
    *(int *)(param_1 + 0x19c) = iVar4 - iVar2;
  }
  puVar6 = (uint *)(param_3 + 8);
  param_4 = 4;
LAB_00465862:
  do {
    param_2 = (int *)(param_3 + 8);
    if ((*(byte *)(param_3 + 4) & 3) != 0) {
      iVar4 = *(int *)(param_1 + 0x188);
      uVar5 = *puVar6;
      uVar3 = ftol();
      if (uVar3 < uVar5) {
        *(undefined4 *)(param_1 + 0x188) = 0;
      }
      else {
        iVar2 = ftol();
        *(int *)(param_1 + 0x188) = iVar4 - iVar2;
      }
    }
    puVar6 = puVar6 + 1;
    param_4 = param_4 + -1;
  } while (param_4 != 0);
  iVar4 = 0;
  iVar2 = 0;
  do {
    if (((uint)*(ushort *)(param_3 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
      iVar4 = iVar4 + *param_2;
    }
    iVar2 = iVar2 + 1;
    param_2 = param_2 + 1;
  } while (iVar2 < 4);
  return iVar4;
}


