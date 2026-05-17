/*
 * Program: i76.exe
 * Function: update_local_player_vehicle_weapons_and_hud
 * Entry: 004a4130
 * Signature: undefined __stdcall update_local_player_vehicle_weapons_and_hud(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Local player weapon/HUD control
   loop: targeting pre-pass, fire gating, selected weapon/HUD updates, cooldown/ammo/fire effects,
   texture refresh. */

void update_local_player_vehicle_weapons_and_hud(void)

{
  bool bVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  float10 fVar8;
  char *pcVar9;
  float local_3c;
  int local_38;
  int local_20;
  int local_1c [7];
  
  update_player_weapon_targeting_lock_and_reticle_state();
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if (((piVar3 == (int *)0x0) ||
      (iVar4 = find_loaded_vehicle_runtime_index_by_world_object(*piVar3), iVar4 == -1)) ||
     (g_loaded_vehicle_runtime_count <= iVar4)) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = &g_loaded_vehicle_runtime_table + iVar4 * 0xb2;
  }
  iVar4 = is_damage_side_effects_suppressed();
  if (((iVar4 == 0) || (piVar3 != (int *)0x0)) && (piVar3 != (int *)0x0)) {
    if (((byte)DAT_00654b98 & 4) == 0) {
LAB_004a41a7:
      DAT_005da798 = 0;
    }
    else {
      iVar4 = is_damage_side_effects_suppressed();
      DAT_005da798 = 1;
      if (iVar4 != 0) goto LAB_004a41a7;
    }
    iVar4 = get_pending_active_player_ai_control_change_flag();
    if (iVar4 == 0) {
      update_player_weapon_fire_enable_flags(piVar3);
    }
    bVar1 = true;
    piVar6 = piVar3 + 0x2a;
    iVar4 = 5;
    do {
      if ((*piVar6 != -1) &&
         (fVar8 = get_weapon_ammo_fraction_remaining(*piVar6), (float10)_DAT_004beab8 < fVar8)) {
        bVar1 = false;
      }
      piVar6 = piVar6 + 0x16;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    if (!bVar1) {
      iVar4 = is_selected_weapon_empty((int)piVar3);
      if (iVar4 != 0) {
        DAT_005367dc = '\x01';
      }
      if (DAT_005367dc != '\0') {
        select_next_player_weapon_slot(piVar3);
      }
      if (DAT_005367dd != '\0') {
        DAT_005da79c = (uint)(DAT_005da79c == 0);
      }
      if (DAT_005da79c == 1) {
        select_matching_player_weapon_group(piVar3);
      }
      else {
        select_previous_player_weapon_slot(piVar3);
      }
    }
  }
  iVar4 = is_damage_side_effects_suppressed();
  if (iVar4 != 0) {
    piVar3 = (int *)get_active_player_or_camera_world_object_entry();
    if (((piVar3 != (int *)0x0) &&
        (iVar4 = collect_vehicle_weapon_runtime_slots(*piVar3,&local_20), iVar4 == 1)) &&
       (local_38 = 0, 0 < local_20)) {
      piVar3 = local_1c;
      do {
        iVar4 = *piVar3 * 0x4c;
        if ((*(int *)(&DAT_005aab44 + iVar4) != 0) &&
           ((DAT_005da798 != 1 || (iVar5 = is_damage_side_effects_suppressed(), iVar5 != 0)))) {
          if (*(int *)(&DAT_005aab28 + iVar4) == 0) {
            *(undefined4 *)(&DAT_005aab44 + iVar4) = 0;
          }
          else {
            iVar5 = *piVar3;
            fVar2 = _DAT_004beab8;
            if (iVar5 * 0x4c != -0x5aab08) {
              fVar2 = (float)(uint)(&DAT_005aab14)[iVar5 * 0x13] /
                      (float)*(int *)(&DAT_005d893c + (&DAT_005aab38)[iVar5 * 0x13] * 0xd8);
            }
            local_3c = (_DAT_004beac0 - fVar2) - _DAT_004beb10;
            if (_DAT_004beb14 < local_3c) {
              local_3c = 0.5;
            }
            if ((_DAT_004beab8 < local_3c) &&
               (iVar5 = rand(), (float)iVar5 < local_3c * _DAT_004beb18)) {
              *(undefined4 *)(&DAT_005aab44 + iVar4) = 0;
              get_runtime_frame_delta_seconds();
              iVar5 = ftol();
              *(int *)(&DAT_005aab28 + iVar4) = *(int *)(&DAT_005aab28 + iVar4) - iVar5;
            }
          }
        }
        local_38 = local_38 + 1;
        piVar3 = piVar3 + 1;
      } while (local_38 < local_20);
    }
    update_weapon_available_bitmask_from_vsf_state();
  }
  update_weapon_cooldowns_ammo_and_fire_effects();
  iVar4 = is_damage_side_effects_suppressed();
  if (iVar4 != 0) {
    update_player_weapon_target_status_bitmask();
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar3 == (int *)0x0) {
LAB_004a4429:
    puVar7 = (undefined4 *)0x0;
  }
  else {
    iVar4 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar6 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar6 == *piVar3) goto LAB_004a440d;
        iVar4 = iVar4 + 1;
        piVar6 = piVar6 + 0xb2;
      } while (iVar4 < g_loaded_vehicle_runtime_count);
    }
    iVar4 = -1;
LAB_004a440d:
    if ((iVar4 == -1) || (g_loaded_vehicle_runtime_count <= iVar4)) goto LAB_004a4429;
    puVar7 = &g_loaded_vehicle_runtime_table + iVar4 * 0xb2;
  }
  if ((puVar7 != (undefined4 *)0x0) && (iVar4 = 0, 0 < (int)puVar7[0x14])) {
    piVar3 = puVar7 + 0x2a;
    do {
      if (*piVar3 != -1) {
        update_weapon_hud_diode_indicator((int)puVar7,iVar4,*piVar3,0);
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 0x16;
    } while (iVar4 < (int)puVar7[0x14]);
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar3 != (int *)0x0) {
    iVar4 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar6 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar6 == *piVar3) goto LAB_004a448c;
        iVar4 = iVar4 + 1;
        piVar6 = piVar6 + 0xb2;
      } while (iVar4 < g_loaded_vehicle_runtime_count);
    }
    iVar4 = -1;
LAB_004a448c:
    if ((iVar4 != -1) && (iVar4 < g_loaded_vehicle_runtime_count)) {
      puVar7 = &g_loaded_vehicle_runtime_table + iVar4 * 0xb2;
      goto LAB_004a44aa;
    }
  }
  puVar7 = (undefined4 *)0x0;
LAB_004a44aa:
  if ((puVar7 != (undefined4 *)0x0) && (iVar4 = 0, 0 < (int)puVar7[0x14])) {
    piVar3 = puVar7 + 0x2a;
    do {
      if (*piVar3 != -1) {
        update_weapon_hud_ammo_digit_wheels(puVar7,iVar4,*piVar3,0);
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 0x16;
    } while (iVar4 < (int)puVar7[0x14]);
  }
  if (g_player_weapon_hud_dirty == 1) {
    pcVar9 = s_Weap_004fee60;
    piVar3 = (int *)bind_or_load_texture_set_for_object
                              (g_player_weapon_hud_world_object,
                               (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),0);
    mark_texture_set_binding_dirty_or_track_special_view(piVar3,pcVar9);
  }
  g_player_weapon_hud_dirty = 0;
  return;
}


