/*
 * Program: i76.exe
 * Function: load_speedometer_textures
 * Entry: 0045be20
 * Signature: undefined __cdecl load_speedometer_textures(float * param_1)
 */


/* cgpt whole-binary semantic rename v1: references zspeedo3/6 maps */

void __cdecl load_speedometer_textures(float *param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  ushort uVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  undefined3 extraout_var;
  uint uVar11;
  undefined3 extraout_var_00;
  int iVar12;
  int iVar13;
  undefined3 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  int *piVar14;
  int iVar15;
  uint *puVar16;
  uint *puVar17;
  int local_8;
  
  iVar8 = is_damage_side_effects_suppressed();
  if (((iVar8 == 0) || (g_runtime_display_input_mode != 0x10)) &&
     (iVar8 = can_pop_runtime_camera_state_stack(), iVar8 == 0)) {
    if (DAT_004c2908 == (int *)0x0) {
      DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
    }
    piVar14 = DAT_004c2908;
    if (((DAT_004c2908 != (int *)0x0) && (iVar8 = *DAT_004c2908, iVar8 != 0)) &&
       (((*(uint *)(iVar8 + 0x10) & 0x200) == 0 && (fVar1 = param_1[0xf], fVar1 != 0.0)))) {
      iVar2 = *(int *)((int)fVar1 + 0x1c);
      iVar3 = *(int *)((int)fVar1 + 0x20);
      iVar4 = *(int *)((int)fVar1 + 0x24);
      iVar5 = *(int *)((int)fVar1 + 0x28);
      if (g_runtime_display_mode_state != 2) {
        if (DAT_0054ac64 == 0) {
          local_8 = 9;
          piVar9 = radar_display_update_context_helper_004615f0(iVar8);
          iVar8 = DAT_005dd360;
          *(int **)(s_zspeedo3_map_004f67d0 + DAT_005dd360 * 0x20 + 8) = piVar9;
          if (DAT_0054abac == 0) {
            puVar10 = (undefined4 *)0x0;
          }
          else {
            if (DAT_004f67ec == 0) {
              iVar15 = 0x3d;
              iVar8 = 0x78;
            }
            else {
              iVar15 = 0x7a;
              iVar8 = 0xf0;
            }
            set_bitmap_surface_clip_rect(&DAT_0054ab98,0,0,iVar8,iVar15);
            puVar10 = &DAT_0054ab98;
            iVar8 = DAT_005dd360;
          }
          *(undefined4 **)(&DAT_004f68d8 + iVar8 * 0x20) = puVar10;
          *(undefined4 **)(&DAT_004f69d8 + iVar8 * 0x20) = &DAT_0054a3d0;
          bVar6 = is_miss16_high_color_resource_mode();
          if ((CONCAT31(extraout_var,bVar6) == 0) || (DAT_0054ac68 == 0)) {
            puVar10 = weapon_state_validation_context_helper_004a4a00();
            iVar8 = DAT_005dd360;
            *(undefined4 **)(&DAT_004f6fd8 + DAT_005dd360 * 0x20) = puVar10;
            if (DAT_0054a354 == 0) {
              puVar10 = (undefined4 *)0x0;
            }
            else {
              if (DAT_004f67ec == 0) {
                iVar15 = 0x28;
                iVar8 = 0x28;
              }
              else {
                iVar15 = 0x4f;
                iVar8 = 0x4f;
              }
              set_bitmap_surface_clip_rect(&DAT_0054a340,0,0,iVar8,iVar15);
              puVar10 = &DAT_0054a340;
              iVar8 = DAT_005dd360;
            }
            *(undefined4 **)(&DAT_004f6ad8 + iVar8 * 0x20) = puVar10;
            if (DAT_0054a304 == 0) {
              puVar10 = (undefined4 *)0x0;
            }
            else {
              if (DAT_004f67ec == 0) {
                iVar15 = 0x28;
                iVar8 = 0x28;
              }
              else {
                iVar15 = 0x4f;
                iVar8 = 0x4f;
              }
              set_bitmap_surface_clip_rect(&DAT_0054a2f0,0,0,iVar8,iVar15);
              puVar10 = &DAT_0054a2f0;
              iVar8 = DAT_005dd360;
            }
            *(undefined4 **)(&DAT_004f6bd8 + iVar8 * 0x20) = puVar10;
            if (DAT_0054ac44 == 0) {
              puVar10 = (undefined4 *)0x0;
            }
            else {
              set_bitmap_surface_clip_rect(&DAT_0054ac30,0,0,0xd4,0x1d);
              puVar10 = &DAT_0054ac30;
              iVar8 = DAT_005dd360;
            }
            *(undefined4 **)(&DAT_004f6cd8 + iVar8 * 0x20) = puVar10;
            if (DAT_004c2724 == 0) {
              *(undefined4 *)(&DAT_004f6ed8 + iVar8 * 0x20) = 0;
            }
            else {
              uVar11 = get_user_entity_context_helper_00445370();
              *(uint *)(&DAT_004f6ed8 + DAT_005dd360 * 0x20) = uVar11;
            }
            puVar10 = vehicle_specials_display_cleanup_helper_00467810();
            *(undefined4 **)(&DAT_004f6dd8 + DAT_005dd360 * 0x20) = puVar10;
          }
          else {
            local_8 = 3;
          }
          iVar8 = 0;
          if (local_8 != 0) {
            do {
              iVar15 = (DAT_005dd360 + iVar8 * 8) * 0x20;
              piVar9 = *(int **)(s_zspeedo3_map_004f67d0 + iVar15 + 8);
              if ((piVar9 != (int *)0x0) &&
                 ((piVar9[0xb] != 0 ||
                  (bVar6 = is_miss16_high_color_resource_mode(),
                  CONCAT31(extraout_var_00,bVar6) == 0)))) {
                puVar16 = (uint *)0x5;
                iVar12 = ftol();
                iVar13 = ftol();
                draw_bitmap_context_or_textured_quad
                          (param_1,piVar9,*(int *)(s_zspeedo6_map_004f67dd + iVar15 + 3),
                           *(uint **)(s_zspeedo6_map_004f67dd + iVar15 + 7),iVar13,iVar12,puVar16);
              }
              iVar8 = iVar8 + 1;
            } while (iVar8 < local_8);
          }
          bVar6 = is_miss16_high_color_resource_mode();
          if ((CONCAT31(extraout_var_01,bVar6) != 0) && (DAT_0054ac68 != 0)) {
            render_queued_hud_marker_quads
                      (param_1,(float)*(int *)(s_zspeedo6_map_004f67dd + DAT_005dd360 * 0x20 + 3),
                       (float)*(int *)(s_zspeedo6_map_004f67dd + DAT_005dd360 * 0x20 + 7));
          }
        }
        set_bitmap_surface_clip_rect(&DAT_0054a270,0,0,0x20,0x20);
        iVar8 = is_vehicle_weapon_fire_gate_locked_ready(*piVar14,1);
        if (((iVar8 != 0) || (iVar8 = get_vehicle_weapon_fire_gate_state(*piVar14,1), iVar8 != 0))
           && (uVar7 = compare_runtime_camera_distance_threshold(1.5358897),
              CONCAT22(extraout_var_02,uVar7) == 1)) {
          puVar17 = (uint *)0x5;
          iVar12 = 0;
          iVar15 = 0;
          puVar16 = (uint *)ftol();
          iVar8 = ftol();
          draw_bitmap_context_or_textured_quad
                    (param_1,&DAT_0054a270,iVar8,puVar16,iVar15,iVar12,puVar17);
        }
        iVar8 = is_vehicle_weapon_fire_gate_locked_ready(*piVar14,2);
        if (((iVar8 != 0) || (iVar8 = get_vehicle_weapon_fire_gate_state(*piVar14,2), iVar8 != 0))
           && (uVar7 = compare_runtime_camera_distance_threshold(-1.4486233),
              CONCAT22(extraout_var_03,uVar7) == -1)) {
          puVar17 = (uint *)0x5;
          iVar12 = 0;
          iVar15 = 0;
          puVar16 = (uint *)ftol();
          iVar8 = ftol();
          draw_bitmap_context_or_textured_quad
                    (param_1,&DAT_0054a270,iVar8,puVar16,iVar15,iVar12,puVar17);
        }
        set_bitmap_surface_clip_rect(&DAT_0054ab58,0,0,0x20,0x20);
        if (((DAT_004c2724 != 0) &&
            (iVar8 = is_vehicle_weapon_fire_gate_clear(*piVar14,1), iVar8 != 0)) &&
           ((iVar8 = is_vehicle_weapon_fire_gate_clear(*piVar14,2), iVar8 != 0 &&
            ((uVar7 = compare_runtime_camera_distance_threshold(-0.06981317),
             CONCAT22(extraout_var_04,uVar7) == 1 &&
             (uVar7 = compare_runtime_camera_distance_threshold(0.06981317),
             CONCAT22(extraout_var_05,uVar7) == -1)))))) {
          iVar8 = ftol();
          puVar16 = (uint *)ftol();
          draw_bitmap_context_or_textured_quad(param_1,&DAT_0054ab58,iVar8,puVar16,0,0,(uint *)0x5);
        }
      }
      piVar14 = (int *)(-(uint)(DAT_0054a2e4 != 0) & 0x54abf8);
      if (((DAT_004c2724 != 0) && (piVar14 != (int *)0x0)) && (param_1[0xf] != 0.0)) {
        draw_bitmap_context_or_textured_quad
                  (param_1,piVar14,((iVar4 - iVar2) + 1 >> 1) - (*piVar14 >> 1),
                   (uint *)(((iVar5 - iVar3) + 1) - ((piVar14[1] << 3) >> 3)),0,0,(uint *)0x5);
      }
      DAT_0054ac6c = 0;
    }
  }
  return;
}


