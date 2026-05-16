/*
 * Program: i76.exe
 * Function: select_next_player_weapon_slot
 * Entry: 004a5be0
 * Signature: undefined __cdecl select_next_player_weapon_slot(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=medium] Weapon selection/HUD update
   path, likely next-slot input binding. Needs one more focused pass for exact binding semantics. */

void __cdecl select_next_player_weapon_slot(int *param_1)

{
  char *pcVar1;
  bool bVar2;
  float fVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *local_1c;
  
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 == (int *)0x0) {
LAB_004a5c37:
    local_1c = (int *)0x0;
  }
  else {
    iVar5 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar7 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar7 == *piVar4) goto LAB_004a5c17;
        iVar5 = iVar5 + 1;
        piVar7 = piVar7 + 0xb2;
      } while (iVar5 < g_loaded_vehicle_runtime_count);
    }
    iVar5 = -1;
LAB_004a5c17:
    if ((iVar5 == -1) || (g_loaded_vehicle_runtime_count <= iVar5)) goto LAB_004a5c37;
    local_1c = &g_loaded_vehicle_runtime_table + iVar5 * 0xb2;
  }
  if (local_1c == (int *)0x0) {
    return;
  }
  iVar5 = param_1[1];
  piVar4 = param_1 + 1;
  iVar11 = iVar5;
  if (iVar5 == -1) {
    return;
  }
  do {
    bVar2 = false;
    iVar11 = iVar11 + 1;
    iVar9 = -1;
    if (iVar11 == 5) {
      iVar11 = -1;
    }
    else if (iVar11 == iVar5) {
      iVar9 = param_1[iVar11 * 0x16 + 0x2a];
    }
    else {
      iVar8 = 5;
      piVar7 = piVar4;
      do {
        if (*piVar7 == iVar11) {
          bVar2 = true;
        }
        piVar7 = piVar7 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      if ((!bVar2) && (iVar8 = param_1[iVar11 * 0x16 + 0x2a], iVar8 != -1)) {
        fVar3 = _DAT_004beab8;
        if (iVar8 * 0x4c != -0x5aab08) {
          fVar3 = (float)(uint)(&DAT_005aab14)[iVar8 * 0x13] /
                  (float)*(int *)(&DAT_005d893c + (&DAT_005aab38)[iVar8 * 0x13] * 0xd8);
        }
        if (_DAT_004beab8 < fVar3) {
          iVar9 = iVar8;
        }
      }
    }
  } while ((iVar9 == -1) && ((iVar11 != iVar5 || (bVar2))));
  if (iVar11 == iVar5) {
    return;
  }
  iVar5 = 7;
  piVar7 = local_1c + 10;
  piVar10 = piVar4;
  do {
    if ((param_1 == local_1c) && (iVar9 = *piVar10, iVar9 != -1)) {
      iVar8 = local_1c[iVar9 * 0x16 + 0x2a];
      *piVar7 = 0;
      pcVar1 = &DAT_005d8995 + (&DAT_005aab38)[iVar8 * 0x13] * 0xd8 + DAT_004fed64;
      if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (g_player_weapon_hud_world_object,
                   (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                   s_3dymo_1_004fea10 + DAT_004fed64 + iVar9 * 0x15,pcVar1,
                   &g_player_weapon_hud_bitmap_surface,1);
      }
    }
    *piVar10 = -1;
    piVar7 = piVar7 + 1;
    piVar10 = piVar10 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  *piVar4 = iVar11;
  if (param_1 == local_1c) {
    play_sound_if_object_tree_is_audible
              (s_CAMMO_WAV_004feec0,g_player_weapon_hud_world_object,(undefined4 *)0x0);
    _g_weapon_hud_selected_next_feedback_flag = 1;
    pcVar1 = &DAT_005d8980 +
             (&DAT_005aab38)[local_1c[iVar11 * 0x16 + 0x2a] * 0x13] * 0xd8 + DAT_004fed64;
    if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
      local_1c[iVar11 + 10] = 1;
      draw_texture_widget_to_hud_surface_and_bind_object
                (g_player_weapon_hud_world_object,
                 (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                 s_3dymo_1_004fea10 + DAT_004fed64 + iVar11 * 0x15,pcVar1,
                 &g_player_weapon_hud_bitmap_surface,1);
    }
    reset_vehicle_weapon_target_transform_state(*param_1);
  }
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    iVar5 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar7 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar7 == *piVar4) goto LAB_004a5ecc;
        iVar5 = iVar5 + 1;
        piVar7 = piVar7 + 0xb2;
      } while (iVar5 < g_loaded_vehicle_runtime_count);
    }
    iVar5 = -1;
LAB_004a5ecc:
    if ((iVar5 != -1) && (iVar5 < g_loaded_vehicle_runtime_count)) {
      puVar6 = &g_loaded_vehicle_runtime_table + iVar5 * 0xb2;
      goto LAB_004a5eea;
    }
  }
  puVar6 = (undefined4 *)0x0;
LAB_004a5eea:
  if (((puVar6 != (undefined4 *)0x0) && (g_player_weapon_hud_world_object != 0)) &&
     (puVar6[9] != -1)) {
    draw_texture_widget_to_hud_surface_and_bind_object
              (g_player_weapon_hud_world_object,
               (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
               s_3separator_1_004fe850 + DAT_004fed64 + puVar6[9] * 0x15,
               s_3sepbar_004fe838 + DAT_004fed64,&g_player_weapon_hud_bitmap_surface,0);
  }
  g_player_weapon_hud_dirty = 1;
  return;
}


