/*
 * Program: i76.exe
 * Function: extract_trip_vehicle_vsf_state_from_world_object
 * Entry: 004b10e0
 * Signature: undefined __cdecl extract_trip_vehicle_vsf_state_from_world_object(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Builds the large VSF/VCST
   state buffer for trip mode by extracting current vehicle components, wheels, weapons, and special
   equipment from a world object. */

void __cdecl extract_trip_vehicle_vsf_state_from_world_object(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 local_2c;
  uint local_28;
  undefined4 uStack_24;
  int local_20;
  int local_1c [7];
  
  puVar7 = param_2;
  iVar1 = get_vehicle_runtime_context(param_1);
  world_object_has_optional_runtime_flag(param_1);
  puVar2 = param_2;
  for (iVar4 = 0x900; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_2 + 0x16;
  iVar4 = 0x60;
  do {
    *puVar2 = 0x6c6c756e;
    puVar2[1] = 0;
    puVar2 = puVar2 + 0x18;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar2 = param_2 + 0x610;
  param_2 = (undefined4 *)0x10;
  do {
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = puVar2 + 0x18;
    param_2 = (undefined4 *)((int)param_2 + -1);
  } while (param_2 != (undefined4 *)0x0);
  puVar2 = puVar7 + 0x790;
  param_2 = (undefined4 *)0x10;
  do {
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = puVar2 + 0x18;
    param_2 = (undefined4 *)((int)param_2 + -1);
  } while (param_2 != (undefined4 *)0x0);
  world_object_has_optional_runtime_flag(param_1);
  puVar2 = puVar7 + 0xb8;
  extract_engine_or_suspension_state_pair(*(int *)(iVar1 + 0x3c4),puVar2,&local_2c);
  local_28 = *puVar2;
  iVar6 = 0;
  uStack_24 = 0;
  uVar3 = ftol();
  *puVar2 = uVar3;
  iVar4 = get_vehicle_engine_runtime_component(iVar1);
  if (iVar4 != 0) {
    sprintf((char *)(puVar7 + 0xbe),s__s_02d_004ffeb4,s_eng_004ffebc,*(int *)(iVar4 + 0x28) + 1);
  }
  puVar2 = puVar7 + 0xd0;
  extract_engine_or_suspension_state_pair(*(int *)(iVar1 + 0x3c8),puVar2,&local_2c);
  local_28 = *puVar2;
  uStack_24 = 0;
  uVar3 = ftol();
  *puVar2 = uVar3;
  iVar4 = get_vehicle_suspension_runtime_component(iVar1);
  if (iVar4 != 0) {
    sprintf((char *)(puVar7 + 0xd6),s__s_02d_004ffeb4,s_sus_004ffeb0,*(int *)(iVar4 + 8) + 1);
  }
  puVar2 = puVar7 + 0xe8;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3cc),puVar2,&local_2c);
  local_28 = *puVar2;
  uStack_24 = 0;
  uVar3 = ftol();
  *puVar2 = uVar3;
  iVar4 = get_vehicle_brake_runtime_component(iVar1);
  if (iVar4 != 0) {
    sprintf((char *)(puVar7 + 0xee),s__s_02d_004ffeb4,&PTR_DAT_004ffeac,*(int *)(iVar4 + 0x14) + 1);
  }
  if (*(int *)(iVar1 + 0x3a8) != 0) {
    puVar2 = puVar7 + 0x10;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3a8),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3a8);
    puVar7[0x16] = *puVar2;
    puVar7[0x17] = puVar2[1];
  }
  if (*(int *)(iVar1 + 0x3ac) != 0) {
    puVar2 = puVar7 + 0x28;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3ac),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3ac);
    puVar7[0x2e] = *puVar2;
    puVar7[0x2f] = puVar2[1];
  }
  if (*(int *)(iVar1 + 0x3b0) != 0) {
    puVar2 = puVar7 + 0x40;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3b0),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3b0);
    puVar7[0x46] = *puVar2;
    puVar7[0x47] = puVar2[1];
  }
  if (*(int *)(iVar1 + 0x3b4) != 0) {
    puVar2 = puVar7 + 0x58;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3b4),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3b4);
    puVar7[0x5e] = *puVar2;
    puVar7[0x5f] = puVar2[1];
  }
  if (*(int *)(iVar1 + 0x3b8) != 0) {
    puVar2 = puVar7 + 0x70;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3b8),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3b8);
    puVar7[0x76] = *puVar2;
    puVar7[0x77] = puVar2[1];
  }
  if (*(int *)(iVar1 + 0x3bc) != 0) {
    puVar2 = puVar7 + 0x88;
    extract_part_damage_state_pair(*(int *)(iVar1 + 0x3bc),puVar2,&local_2c);
    local_28 = *puVar2;
    uStack_24 = 0;
    uVar3 = ftol();
    *puVar2 = uVar3;
    puVar2 = *(undefined4 **)(iVar1 + 0x3bc);
    puVar7[0x8e] = *puVar2;
    puVar7[0x8f] = puVar2[1];
  }
  uStack_24 = 0;
  local_28 = (uint)(*(int *)(iVar1 + 0x3ec) != 0);
  uVar3 = ftol();
  puVar7[0x1a8] = uVar3;
  uVar3 = get_special_equipment_runtime_index(*(int *)(iVar1 + 0x3ec));
  sprintf((char *)(puVar7 + 0x1ae),s__s_02d_004ffea0,&PTR_DAT_004ffea8,uVar3);
  local_28 = (uint)(*(int *)(iVar1 + 0x3f0) != 0);
  uStack_24 = 0;
  uVar3 = ftol();
  puVar7[0x1c0] = uVar3;
  uVar3 = get_special_equipment_runtime_index(*(int *)(iVar1 + 0x3f0));
  sprintf((char *)(puVar7 + 0x1c6),s__s_02d_004ffea0,&PTR_DAT_004ffea8,uVar3);
  local_28 = (uint)(*(int *)(iVar1 + 0x3f4) != 0);
  uStack_24 = 0;
  uVar3 = ftol();
  puVar7[0x1d8] = uVar3;
  uVar3 = get_special_equipment_runtime_index(*(int *)(iVar1 + 0x3f4));
  sprintf((char *)(puVar7 + 0x1de),s__s_02d_004ffea0,&PTR_DAT_004ffea8,uVar3);
  iVar4 = collect_vehicle_weapon_runtime_slots(param_1,&local_20);
  if ((iVar4 == 1) && (0 < local_20)) {
    piVar8 = local_1c;
    piVar5 = (int *)(iVar1 + 0x3d0);
    puVar7 = puVar7 + 0x106;
    do {
      extract_weapon_runtime_state_to_vsf_record(*piVar8,puVar7 + -0x16);
      puVar2 = (undefined4 *)*piVar5;
      iVar6 = iVar6 + 1;
      piVar8 = piVar8 + 1;
      piVar5 = piVar5 + 1;
      *puVar7 = *puVar2;
      puVar7[1] = puVar2[1];
      puVar7 = puVar7 + 0x18;
    } while (iVar6 < local_20);
  }
  return;
}


