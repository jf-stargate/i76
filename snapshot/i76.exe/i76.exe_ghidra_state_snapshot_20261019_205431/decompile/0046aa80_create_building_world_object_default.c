/*
 * Program: i76.exe
 * Function: create_building_world_object_default
 * Entry: 0046aa80
 * Signature: undefined __cdecl create_building_world_object_default(int param_1)
 */


/* cgpt whole-binary semantic rename v1: strings x1_bldx1/null */

void __cdecl create_building_world_object_default(int param_1)

{
  int iVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  uint local_4c;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34 [4];
  float local_24;
  float local_20;
  undefined4 local_18;
  undefined2 local_14;
  int local_4;
  
  local_4c = 0;
  local_48 = 0;
  local_40 = 0;
  local_3c = 0;
  local_44 = 0;
  puVar7 = &local_18;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  local_38 = 0;
  local_14 = 8;
  local_4 = **(int **)(param_1 + 0x70) + 1;
  dispatch_damage_context_to_world_object_class_handler(param_1,&local_18,&local_40);
  iVar6 = *(int *)(param_1 + 0x70);
  iVar3 = is_transform_composed_world_object_class(param_1);
  if (iVar3 != 0) {
    *(undefined4 *)(iVar6 + 0x28) = 1;
    create_chunk_manager_geometry_runtime(param_1);
    iVar3 = copy_world_object_orientation_or_velocity_vector(param_1,0x1000000);
    if (iVar3 != 0) {
      iVar1 = *(int *)(param_1 + 0x70);
      local_4c = 0;
      local_48 = 0;
      if (iVar1 != 0) {
        pfVar4 = (float *)compose_world_object_runtime_transform(local_34,iVar3);
        fVar2 = *pfVar4;
        local_24 = pfVar4[1];
        local_20 = pfVar4[2];
        if (*(int *)(param_1 + 0x6c) != 3) {
          iVar5 = _strnicmp((char *)(iVar1 + 0x10),s_null_004c3280,8);
          if (iVar5 == 0) {
            strncpy((char *)&local_4c,s_x1_bldx1_004f7d34,8);
            uVar8 = local_4c;
            uVar9 = local_48;
          }
          else {
            uVar8 = *(uint *)(iVar1 + 0x10);
            uVar9 = *(uint *)(iVar1 + 0x14);
          }
          spawn_cached_explosion_runtime_object(uVar8,uVar9,iVar3,fVar2,local_24,local_20,0);
          iVar5 = _stricmp((char *)(iVar1 + 0x18),s_null_004c3280);
          if (iVar5 == 0) {
            dispatch_vehicle_runtime_sound_event(7,iVar3,(undefined4 *)0x0);
          }
          else {
            play_positional_audio_for_object_or_active_player
                      ((char *)(iVar1 + 0x18),iVar3,(undefined4 *)0x0);
          }
        }
        *(undefined4 *)(iVar1 + 0x28) = 2;
      }
    }
    if ((*(uint *)(param_1 + 0x10) & 0x800) != 0) {
      release_world_object_light_runtime(param_1);
    }
    iVar3 = is_damage_side_effects_suppressed();
    if (iVar3 != 0) {
      network_vehicle_message_context_helper_00456710(*(uint *)(iVar6 + 8));
    }
  }
  return;
}


