/*
 * Program: i76.exe
 * Function: select_matching_player_weapon_group
 * Entry: 004a6170
 * Signature: undefined __cdecl select_matching_player_weapon_group(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=medium] Weapon selection/HUD update
   path for matching group/category. Needs one more focused pass for exact binding semantics. */

void __cdecl select_matching_player_weapon_group(undefined4 *param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  int *piVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  int iVar12;
  bool bVar14;
  int *local_24;
  int iVar13;
  
  piVar8 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar8 == (int *)0x0) {
LAB_004a61c1:
    puVar10 = (undefined4 *)0x0;
  }
  else {
    iVar9 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar11 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar11 == *piVar8) goto LAB_004a61a5;
        iVar9 = iVar9 + 1;
        piVar11 = piVar11 + 0xb2;
      } while (iVar9 < g_loaded_vehicle_runtime_count);
    }
    iVar9 = -1;
LAB_004a61a5:
    if ((iVar9 == -1) || (g_loaded_vehicle_runtime_count <= iVar9)) goto LAB_004a61c1;
    puVar10 = &g_loaded_vehicle_runtime_table + iVar9 * 0xb2;
  }
  if (puVar10 == (undefined4 *)0x0) {
    return;
  }
  iVar9 = param_1[1];
  if (iVar9 == -1) {
    return;
  }
  iVar2 = param_1[iVar9 * 0x16 + 0x2a];
  if (iVar2 == -1) {
    return;
  }
  local_24 = param_1 + 2;
  if (param_1[2] == -1) {
    iVar3 = (&DAT_005aab38)[iVar2 * 0x13];
    iVar2 = *(int *)(&DAT_005aab4c + iVar2 * 0x4c);
    iVar13 = iVar9;
    do {
      iVar12 = iVar13 + 1;
      iVar4 = param_1[iVar12 * 0x16 + 0x2a];
      if ((iVar4 != -1) && (iVar12 != iVar9)) {
        iVar5 = (&DAT_005aab38)[iVar4 * 0x13];
        bVar14 = *(int *)(&DAT_005aab4c + iVar4 * 0x4c) == iVar2;
        iVar6 = (&DAT_005d8934)[iVar5 * 0x36];
        if ((iVar6 == 3) && ((&DAT_005d8930)[iVar5 * 0x36] == 4)) {
          bVar14 = false;
        }
        if ((iVar6 == 4) && ((&DAT_005d8930)[iVar5 * 0x36] == 4)) {
          bVar14 = false;
        }
        if ((iVar6 == (&DAT_005d8934)[iVar3 * 0x36]) && (bVar14)) {
          fVar7 = _DAT_004beab8;
          if (iVar4 * 0x4c != -0x5aab08) {
            fVar7 = (float)(uint)(&DAT_005aab14)[iVar4 * 0x13] /
                    (float)*(int *)(&DAT_005d893c + (&DAT_005aab38)[iVar4 * 0x13] * 0xd8);
          }
          if (_DAT_004beab8 < fVar7) {
            *local_24 = iVar12;
            local_24 = local_24 + 1;
            if (param_1 == puVar10) {
              play_sound_if_object_tree_is_audible
                        (s_CAMMO_WAV_004feec0,g_player_weapon_hud_world_object,(undefined4 *)0x0);
              pcVar1 = &DAT_005d8980 + iVar5 * 0xd8 + DAT_004fed64;
              _g_weapon_hud_group_select_feedback_flag = 1;
              if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
                puVar10[iVar13 + 0xb] = 1;
                draw_texture_widget_to_hud_surface_and_bind_object
                          (g_player_weapon_hud_world_object,
                           (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                           s_3dymo_1_004fea10 + DAT_004fed64 + iVar12 * 0x15,pcVar1,
                           &g_player_weapon_hud_bitmap_surface,1);
              }
            }
          }
        }
      }
      if (iVar12 == 5) {
        iVar12 = -1;
      }
      iVar13 = iVar12;
    } while (iVar12 != iVar9);
    param_1[1] = iVar9;
  }
  piVar8 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar8 != (int *)0x0) {
    iVar9 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar11 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar11 == *piVar8) goto LAB_004a63e4;
        iVar9 = iVar9 + 1;
        piVar11 = piVar11 + 0xb2;
      } while (iVar9 < g_loaded_vehicle_runtime_count);
    }
    iVar9 = -1;
LAB_004a63e4:
    if ((iVar9 != -1) && (iVar9 < g_loaded_vehicle_runtime_count)) {
      puVar10 = &g_loaded_vehicle_runtime_table + iVar9 * 0xb2;
      goto LAB_004a6402;
    }
  }
  puVar10 = (undefined4 *)0x0;
LAB_004a6402:
  if (((puVar10 != (undefined4 *)0x0) && (g_player_weapon_hud_world_object != 0)) &&
     (puVar10[9] != -1)) {
    draw_texture_widget_to_hud_surface_and_bind_object
              (g_player_weapon_hud_world_object,
               (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
               s_3separator_1_004fe850 + DAT_004fed64 + puVar10[9] * 0x15,
               s_3sepbar_004fe838 + DAT_004fed64,&g_player_weapon_hud_bitmap_surface,0);
  }
  g_player_weapon_hud_dirty = 1;
  return;
}


