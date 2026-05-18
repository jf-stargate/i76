/*
 * Program: i76.exe
 * Function: special_equipment_state_context_helper_00468c40
 * Entry: 00468c40
 * Signature: undefined * __cdecl special_equipment_state_context_helper_00468c40(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was vehicle_specials_runtime_special_equipment_state_helper_00468c40.
   Shorten readability label. */

undefined * __cdecl special_equipment_state_context_helper_00468c40(int param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  float10 fVar9;
  float local_10;
  float local_c;
  float local_8;
  
  iVar8 = DAT_00588dec;
  uVar7 = (param_1 * 0x6cd + 0xaabU) % 0x71;
  iVar6 = DAT_00588dec * 0x20;
  uVar1 = (&DAT_0054fa10)[uVar7];
  (&DAT_0054fa10)[uVar7] = DAT_00588dec;
  *(undefined4 *)(&DAT_0054e12c + iVar6) = uVar1;
  *(int *)(&DAT_0054e110 + iVar6) = param_1;
  fVar2 = *(float *)(param_1 + 0x30);
  fVar3 = *(float *)(param_1 + 0x34);
  fVar4 = *(float *)(param_1 + 0x38);
  local_10 = fVar2;
  local_c = fVar3;
  local_8 = fVar4;
  if ((fVar2 == _DAT_004be250) && (fVar4 == _DAT_004be250)) {
    *(undefined4 *)(&DAT_0054e118 + iVar6) = 0;
    *(undefined4 *)(&DAT_0054e114 + iVar6) = 0;
  }
  else {
    fVar9 = (float10)fpatan((float10)fVar2,(float10)fVar4);
    *(float *)(&DAT_0054e114 + iVar6) = (float)fVar9;
    iVar8 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar8 != 0) {
      iVar8 = get_vehicle_runtime_context(param_1);
      local_8 = *(float *)(iVar8 + 0xe8);
      local_10 = local_8 * fVar2;
      local_c = fVar3 * local_8;
      local_8 = fVar4 * local_8;
    }
    iVar8 = DAT_00588dec;
    fVar9 = (float10)fpatan((float10)local_10,(float10)local_8);
    *(float *)(&DAT_0054e118 + DAT_00588dec * 0x20) = (float)fVar9;
  }
  iVar8 = iVar8 * 0x20;
  puVar5 = (undefined4 *)entity_instance_table_context_helper_004576a0(&local_10,param_1);
  *(undefined4 *)(&DAT_0054e11c + iVar8) = *puVar5;
  *(undefined4 *)(&DAT_0054e120 + iVar8) = puVar5[1];
  *(undefined4 *)(&DAT_0054e124 + iVar8) = puVar5[2];
  *(undefined4 *)(&DAT_0054e128 + iVar8) = puVar5[3];
  DAT_00588dec = DAT_00588dec + 1;
  return &DAT_0054e110 + iVar8;
}


