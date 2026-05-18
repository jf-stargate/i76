/*
 * Program: i76.exe
 * Function: select_previous_player_weapon_slot
 * Entry: 004a5f50
 * Signature: undefined __cdecl select_previous_player_weapon_slot(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=medium] Weapon selection/HUD update
   path, likely previous-slot input binding. Needs one more focused pass for exact binding
   semantics. */

void __cdecl select_previous_player_weapon_slot(undefined4 *param_1)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *local_4;
  
  puVar4 = param_1;
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar2 == (int *)0x0) {
LAB_004a5fa5:
    local_4 = (undefined4 *)0x0;
  }
  else {
    iVar3 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar5 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar5 == *piVar2) goto LAB_004a5f85;
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 0xb2;
      } while (iVar3 < g_loaded_vehicle_runtime_count);
    }
    iVar3 = -1;
LAB_004a5f85:
    if ((iVar3 == -1) || (g_loaded_vehicle_runtime_count <= iVar3)) goto LAB_004a5fa5;
    local_4 = &g_loaded_vehicle_runtime_table + iVar3 * 0xb2;
  }
  if (local_4 == (undefined4 *)0x0) {
    return;
  }
  if (param_1[1] == -1) {
    return;
  }
  if (param_1[param_1[1] * 0x16 + 0x2a] == -1) {
    return;
  }
  piVar2 = param_1 + 2;
  if (param_1[2] != -1) {
    puVar6 = local_4 + 0xb;
    param_1 = (undefined4 *)0x6;
    do {
      if (*piVar2 != -1) {
        iVar3 = puVar4[*piVar2 * 0x16 + 0x2a];
        if (puVar4 == local_4) {
          play_sound_if_object_tree_is_audible
                    (s_CAMMO_WAV_004feec0,g_player_weapon_hud_world_object,(undefined4 *)0x0);
          _g_weapon_hud_clear_selection_feedback_flag = 1;
          pcVar1 = &DAT_005d8995 + (&DAT_005aab38)[iVar3 * 0x13] * 0xd8 + DAT_004fed64;
          if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
            *puVar6 = 0;
            draw_texture_widget_to_hud_surface_and_bind_object
                      (g_player_weapon_hud_world_object,
                       (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                       s_3dymo_1_004fea10 + DAT_004fed64 + *piVar2 * 0x15,pcVar1,
                       &g_player_weapon_hud_bitmap_surface,1);
          }
        }
        *piVar2 = -1;
      }
      puVar6 = puVar6 + 1;
      piVar2 = piVar2 + 1;
      param_1 = (undefined4 *)((int)param_1 + -1);
    } while (param_1 != (undefined4 *)0x0);
  }
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar2 != (int *)0x0) {
    iVar3 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar5 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar5 == *piVar2) goto LAB_004a60eb;
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 0xb2;
      } while (iVar3 < g_loaded_vehicle_runtime_count);
    }
    iVar3 = -1;
LAB_004a60eb:
    if ((iVar3 != -1) && (iVar3 < g_loaded_vehicle_runtime_count)) {
      puVar4 = &g_loaded_vehicle_runtime_table + iVar3 * 0xb2;
      goto LAB_004a6109;
    }
  }
  puVar4 = (undefined4 *)0x0;
LAB_004a6109:
  if (((puVar4 != (undefined4 *)0x0) && (g_player_weapon_hud_world_object != 0)) &&
     (puVar4[9] != -1)) {
    draw_texture_widget_to_hud_surface_and_bind_object
              (g_player_weapon_hud_world_object,
               (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
               s_3separator_1_004fe850 + DAT_004fed64 + puVar4[9] * 0x15,
               s_3sepbar_004fe838 + DAT_004fed64,&g_player_weapon_hud_bitmap_surface,0);
  }
  g_player_weapon_hud_dirty = 1;
  return;
}


