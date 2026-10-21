/*
 * Program: i76.exe
 * Function: initialize_class_09_runtime_and_player_display
 * Entry: 0046b7d0
 * Signature: undefined __cdecl initialize_class_09_runtime_and_player_display(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl initialize_class_09_runtime_and_player_display(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 extraout_ST0;
  
  puVar1 = *(undefined4 **)(param_1 + 0x70);
  puVar2 = (undefined4 *)puVar1[0x142];
  puVar4 = get_active_world_object_entry_object(param_1);
  *puVar1 = puVar4;
  uVar3 = puVar1[0x4e];
  puVar2[1] = uVar3;
  *puVar2 = uVar3;
  puVar2[2] = _DAT_004be328 / (float)(int)puVar2[1];
  start_vehicle_engine_loop_sound(param_1);
  apply_world_object_transform_to_bounds_or_geometry
            (*(double *)(param_1 + 0x40),*(double *)(param_1 + 0x50));
  if ((float10)*(double *)(param_1 + 0x48) < extraout_ST0) {
    *(double *)(param_1 + 0x48) = (double)extraout_ST0;
  }
  iVar5 = is_damage_side_effects_suppressed();
  if (iVar5 != 0) {
    puVar1[0x115] = puVar1[0x115] & 0xffffff7f;
    iVar5 = *(int *)(param_1 + 0x70);
    *(undefined4 *)(*(int *)(iVar5 + 0x508) + 0x14) = 0x41a00000;
    *(uint *)(iVar5 + 0x454) = *(uint *)(iVar5 + 0x454) & 0xffffff7f;
  }
  iVar5 = world_object_has_optional_runtime_flag(param_1);
  if (iVar5 != 0) {
    preload_cockpit_gauge_textures(param_1);
    initialize_runtime_camera_projection_matrix(1);
    initialize_or_refresh_player_weapon_hud_overlay((int *)0x1);
    load_specials_backing_texture(param_1);
    get_user_entity_or_report_missing();
  }
  return;
}


