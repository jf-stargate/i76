/*
 * Program: i76.exe
 * Function: fire_weapon_runtime_slot_and_spawn_effects
 * Entry: 004a6e90
 * Signature: undefined __cdecl fire_weapon_runtime_slot_and_spawn_effects(int param_1, int param_2, int param_3, float param_4)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=high] Consumes ammo/cooldown state, plays
   weapon fire sound, chooses muzzle/mount object, dispatches projectile/effect helpers, and records
   weapon firing side effects. */

void __cdecl
fire_weapon_runtime_slot_and_spawn_effects(int param_1,int param_2,int param_3,float param_4)

{
  int *piVar1;
  int iVar2;
  int local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30 [2];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  LPVOID local_14;
  undefined4 local_10;
  undefined4 local_c [3];
  
  update_weapon_muzzle_flash_runtime_effect(*(LPVOID *)(param_1 + 4));
  piVar1 = (int *)get_active_player_or_camera_world_object_entry();
  if (*(int *)(param_2 + 0x5c) == 1) {
    start_weapon_muzzle_flash_texture_animation(**(int **)(param_1 + 0x18),*(int *)(param_2 + 0x58))
    ;
  }
  if (*(int *)(param_2 + 0xa0) == 0) {
    play_positional_audio_for_object_or_active_player
              ((char *)(param_2 + 0x90),*(int *)(param_1 + 4),(undefined4 *)0x0);
  }
  else {
    play_named_sound_attached_to_object_or_player
              ((char *)(param_2 + 0x90),*(int *)(param_1 + 4),(undefined4 *)0x0);
  }
  local_3c = *(int *)(param_2 + 0x80);
  local_34 = *(undefined4 *)(param_2 + 0x74);
  local_38 = **(int **)(param_1 + 0x18);
  local_28 = *(undefined4 *)(param_1 + 0x10);
  local_24 = *(undefined4 *)(param_2 + 0xa4);
  local_20 = *(undefined4 *)(param_2 + 0x68);
  local_1c = *(undefined4 *)(param_1 + 4);
  local_18 = param_3;
  if (((((DAT_005da798 != 1) || (piVar1 == (int *)0x0)) || (**(int **)(param_1 + 0x18) != *piVar1))
      || (iVar2 = is_damage_side_effects_suppressed(), iVar2 != 0)) &&
     (iVar2 = *(int *)(param_1 + 0x20) - param_3, *(int *)(param_1 + 0x20) = iVar2, iVar2 < 0)) {
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  local_14 = (LPVOID)0x0;
  switch(local_3c) {
  case 1:
  case 2:
  case 6:
  case 0x14:
    if (local_3c == 0x14) {
      *(undefined4 *)(param_1 + 0x48) = 0;
    }
    if (*(int *)(param_1 + 0x44) == 4) {
      local_14 = (LPVOID)get_primary_vehicle_weapon_target_object(local_38);
    }
    else {
      local_14 = release_vehicle_radar_or_weapon_target_object(local_38,*(int *)(param_1 + 0x44));
    }
    goto LAB_004a7057;
  case 3:
    iVar2 = **(int **)(param_1 + 0x18);
    if ((*(byte *)(iVar2 + 0x10) & 0x20) == 0) {
      local_14 = (LPVOID)raycast_weapon_fire_from_muzzle_transform(*(int *)(param_1 + 4),iVar2);
      radar_render_context_helper_00461430
                (**(int **)(param_1 + 0x18),local_14,*(int *)(param_1 + 0x44));
    }
    else {
      local_14 = (LPVOID)get_vehicle_weapon_target_object_by_slot(iVar2,*(int *)(param_1 + 0x44));
    }
    break;
  default:
    local_14 = (LPVOID)get_primary_vehicle_weapon_target_object(local_38);
    if (local_3c != 8) goto LAB_004a7057;
  }
  if (local_14 != (LPVOID)0x0) {
    noop_world_object_callback_stub();
  }
LAB_004a7057:
  if ((*(int *)(param_2 + 0x5c) == 3) && (*(int *)(param_2 + 0x58) == 3)) {
    loaded_resource_cache_find_record_helper_0046f1d0
              (**(int **)(param_1 + 0x18),*(int *)(param_1 + 4),(float)local_14,
               *(float *)(param_2 + 0x74));
  }
  local_10 = *(undefined4 *)(param_2 + 0x84);
  get_world_object_damage_or_target_vectors(local_38,local_c,local_30);
  if (0 < param_3) {
    spawn_weapon_projectile_or_ordnance_runtime_object(&local_3c,param_4);
  }
  return;
}


