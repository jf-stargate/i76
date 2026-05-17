/*
 * Program: i76.exe
 * Function: initialize_or_refresh_player_weapon_hud_overlay
 * Entry: 004a45c0
 * Signature: undefined __cdecl initialize_or_refresh_player_weapon_hud_overlay(int * param_1)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=high] Creates/reset weapon HUD bitmap
   surface, resolves zbk map resource variant, initializes selected slots, draws HUD widgets, and
   binds texture set state. */

void __cdecl initialize_or_refresh_player_weapon_hud_overlay(int *param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  char *pcVar10;
  uint uVar11;
  int local_48;
  int *local_44;
  int *local_40;
  int *local_3c;
  int local_34 [13];
  
  release_bitmap_surface_context(&g_player_weapon_hud_bitmap_surface);
  puVar3 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar8 = &g_player_weapon_hud_bitmap_surface;
  for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar8 = puVar8 + 1;
  }
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 == (int *)0x0) {
LAB_004a463f:
    piVar4 = (int *)0x0;
  }
  else {
    iVar6 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar7 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar7 == *piVar4) goto LAB_004a4623;
        iVar6 = iVar6 + 1;
        piVar7 = piVar7 + 0xb2;
      } while (iVar6 < g_loaded_vehicle_runtime_count);
    }
    iVar6 = -1;
LAB_004a4623:
    if ((iVar6 == -1) || (g_loaded_vehicle_runtime_count <= iVar6)) goto LAB_004a463f;
    piVar4 = &g_loaded_vehicle_runtime_table + iVar6 * 0xb2;
  }
  if (piVar4 == (int *)0x0) {
    return;
  }
  if (g_display_mode_variant_index < 6) {
    iVar6 = *piVar4;
    pcVar10 = s_zbk_320_map_004fe748;
  }
  else {
    iVar6 = *piVar4;
    pcVar10 = s_zbk__map_004fe755;
  }
  uVar11 = 1;
  DAT_004fed64 = (uint)(g_display_mode_variant_index < 6);
  iVar6 = world_object_geometry_context_helper_004588b0(iVar6,pcVar10);
  get_world_object_class_id(iVar6,uVar11);
  g_player_weapon_hud_world_object =
       world_object_geometry_context_helper_004588b0
                 (*piVar4,s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd);
  world_object_geometry_context_helper_00458860(g_player_weapon_hud_world_object,1);
  if (g_player_weapon_hud_world_object == 0) {
    return;
  }
  if (*(int *)(*piVar4 + 0x70) == 0) {
    return;
  }
  *(uint *)(*(int *)(*piVar4 + 0x70) + 0x430) = g_player_weapon_hud_world_object;
  if ((g_player_weapon_hud_initialized == 0) || (param_1 != (int *)0x0)) {
    iVar6 = 0;
    bVar2 = false;
    if (0 < piVar4[0x14]) {
      piVar7 = piVar4 + 10;
      piVar9 = piVar4 + 0x2a;
      do {
        iVar1 = *piVar9;
        *piVar7 = 0;
        if ((iVar1 != -1) && (!bVar2)) {
          bVar2 = true;
          piVar4[1] = iVar6;
          *piVar7 = 1;
        }
        iVar6 = iVar6 + 1;
        piVar7 = piVar7 + 1;
        piVar9 = piVar9 + 0x16;
      } while (iVar6 < piVar4[0x14]);
    }
    g_player_weapon_hud_initialized = 1;
  }
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    iVar6 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar7 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar7 == *piVar4) goto LAB_004a4755;
        iVar6 = iVar6 + 1;
        piVar7 = piVar7 + 0xb2;
      } while (iVar6 < g_loaded_vehicle_runtime_count);
    }
    iVar6 = -1;
LAB_004a4755:
    if ((iVar6 != -1) && (iVar6 < g_loaded_vehicle_runtime_count)) {
      piVar4 = &g_loaded_vehicle_runtime_table + iVar6 * 0xb2;
      goto LAB_004a4773;
    }
  }
  piVar4 = (int *)0x0;
LAB_004a4773:
  if ((piVar4 != (int *)0x0) && (g_player_weapon_hud_world_object != 0)) {
    piVar4[9] = 0;
    iVar6 = 0;
    if (0 < piVar4[0x14]) {
      param_1 = piVar4 + 10;
      local_44 = piVar4 + 0x2a;
      local_48 = 0;
      local_3c = (int *)&DAT_004fec88;
      local_40 = (int *)&DAT_004fec70;
      do {
        iVar1 = *local_44;
        rand();
        iVar5 = ftol();
        draw_texture_widget_to_hud_surface_and_bind_object
                  (g_player_weapon_hud_world_object,
                   (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                   s_3bracket_1_004fe8c0 + local_48 + DAT_004fed64,
                   s_3housing1_004fe930 + DAT_004fed64 + iVar5 * 0x15,
                   &g_player_weapon_hud_bitmap_surface,0);
        if (iVar1 != -1) {
          if ((*(int *)(&DAT_005aab4c + iVar1 * 0x4c) == 4) ||
             (*(int *)(&DAT_005aab4c + iVar1 * 0x4c) == 1)) {
            piVar4[9] = iVar6 + 1;
          }
          update_weapon_hud_diode_indicator((int)piVar4,iVar6,iVar1,1);
          iVar5 = 0;
          piVar7 = piVar4;
          do {
            piVar7 = piVar7 + 1;
            if (*piVar7 == (&DAT_005aab24)[iVar1 * 0x13]) {
              *param_1 = 1;
              goto LAB_004a4880;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 < 5);
          *param_1 = 0;
LAB_004a4880:
          if (*param_1 == 1) {
            pcVar10 = &DAT_005d8980 + (&DAT_005aab38)[iVar1 * 0x13] * 0xd8 + DAT_004fed64;
          }
          else {
            pcVar10 = &DAT_005d8995 + (&DAT_005aab38)[iVar1 * 0x13] * 0xd8 + DAT_004fed64;
          }
          if ((pcVar10 != (char *)0x0) && (*pcVar10 != '\0')) {
            draw_texture_widget_to_hud_surface_and_bind_object
                      (g_player_weapon_hud_world_object,
                       (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                       s_3dymo_1_004fea10 + local_48 + DAT_004fed64,pcVar10,
                       &g_player_weapon_hud_bitmap_surface,1);
          }
          iVar5 = *(int *)(&DAT_005aab28 + iVar1 * 0x4c);
          (&DAT_004fec40)[iVar6] = iVar5 % 10;
          iVar5 = iVar5 / 10;
          (&DAT_004fec58)[iVar6] = iVar5 % 10;
          iVar5 = iVar5 / 10;
          *local_40 = iVar5 % 10;
          *local_3c = (iVar5 / 10) % 10;
          update_weapon_hud_ammo_digit_wheels(piVar4,iVar6,iVar1,1);
        }
        local_44 = local_44 + 0x16;
        param_1 = param_1 + 1;
        local_40 = local_40 + 1;
        local_3c = local_3c + 1;
        iVar6 = iVar6 + 1;
        local_48 = local_48 + 0x15;
      } while (iVar6 < piVar4[0x14]);
    }
    if (piVar4[9] == -1) {
      piVar4[9] = iVar6 + -1;
    }
    pcVar10 = s_Weap_004fee60;
    piVar4 = (int *)bind_or_load_texture_set_for_object
                              (g_player_weapon_hud_world_object,
                               (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),0);
    mark_texture_set_binding_dirty_or_track_special_view(piVar4,pcVar10);
  }
  return;
}


