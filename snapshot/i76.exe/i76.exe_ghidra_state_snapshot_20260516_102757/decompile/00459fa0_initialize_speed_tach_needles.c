/*
 * Program: i76.exe
 * Function: initialize_speed_tach_needles
 * Entry: 00459fa0
 * Signature: undefined __cdecl initialize_speed_tach_needles(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings speedneedleloc/tachneedleloc/needle maps */

void __cdecl initialize_speed_tach_needles(int param_1)

{
  float *pfVar1;
  uint uVar2;
  float10 fVar3;
  float *pfVar4;
  int *piVar5;
  int iVar6;
  float fVar7;
  undefined4 *puVar8;
  int iVar9;
  float *pfVar10;
  undefined4 *puVar11;
  float10 fVar12;
  undefined8 uVar13;
  float local_90;
  undefined8 local_8c;
  float local_80 [6];
  float local_68;
  float local_60;
  float local_40 [16];
  
  if (DAT_005dd360 != (_g_display_mode_variant_index & 0xff)) {
    DAT_005dd360 = _g_display_mode_variant_index & 0xff;
    preload_cockpit_gauge_textures(param_1);
  }
  if (DAT_0054a40c == 0) {
    target_reticle_context_helper_00459330(param_1);
    DAT_0054a40c = 1;
  }
  if ((DAT_004c2724 != 0) || (DAT_00654b8c._2_1_ != '\0')) {
    iVar6 = *(int *)(*(int *)(param_1 + 0x70) + 0x3f8);
    iVar9 = *(int *)(*(int *)(param_1 + 0x70) + 0x3c4);
    if ((iVar6 != 0) && (iVar9 != 0)) {
      pfVar1 = *(float **)(iVar6 + 0x70);
      fVar12 = building_child_piece_context_helper_0046a7b0(*(int *)(iVar9 + 0x70));
      local_90 = (float)fVar12;
      if ((float10)_DAT_004bdfe4 < fVar12) {
        local_90 = 150.0;
      }
      if (local_90 < _DAT_004bdfe8) {
        local_90 = 0.0;
      }
      local_90 = local_90 * _DAT_004bdfec;
      if (_DAT_004bdff0 < local_90) {
        local_90 = local_90 - _DAT_004bdff4;
      }
      pfVar1[0x11] = local_90 * _DAT_004bdff8;
      pfVar4 = (float *)&DAT_004faed8;
      pfVar10 = local_80;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar10 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar10 = pfVar10 + 1;
      }
      uVar13 = mission_flow_map_context_helper_0049d400(pfVar1[0x11]);
      local_68 = (float)uVar13;
      local_8c._4_4_ = (float)((ulonglong)uVar13 >> 0x20);
      local_60 = local_8c._4_4_;
      local_80[2] = -local_68;
      local_80[0] = local_8c._4_4_;
      local_8c = uVar13;
      pfVar4 = compose_matrix_or_transform_a(local_40,local_80,pfVar1);
      pfVar10 = (float *)(iVar6 + 0x18);
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar10 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar10 = pfVar10 + 1;
      }
      if ((DAT_00654b88 == '\0') &&
         (piVar5 = (int *)get_active_player_or_camera_world_object_entry(), param_1 == *piVar5)) {
        pfVar1[0x13] = pfVar1[0x12];
        iVar6 = ftol();
        pfVar1[0x12] = (float)(9 - iVar6);
        if (0x26 < 9 - iVar6) {
          pfVar1[0x12] = 5.32493e-44;
        }
        if ((pfVar1[0x13] != pfVar1[0x12]) || (DAT_0054ac6c != 0)) {
          sprintf((char *)&local_8c,s_3needle__d_004f7124,pfVar1[0x12]);
          reload_texture_binding_current_frame_pixels
                    (DAT_00609500,(byte *)(s_zspeedo3_map_004f67d0 + DAT_004f67ec * 0xd),0);
          draw_texture_widget_to_hud_surface_and_bind_object
                    (DAT_00609500,(byte *)(s_zspeedo3_map_004f67d0 + DAT_004f67ec * 0xd),
                     s_speedneedleloc_004f7114,(char *)((int)&local_8c + DAT_004f67ec),&DAT_0054a340
                     ,1);
        }
      }
    }
    iVar6 = *(int *)(param_1 + 0x70);
    iVar9 = *(int *)(iVar6 + 0x3fc);
    if (((iVar6 != 0) && (iVar9 != 0)) && (*(int *)(iVar6 + 0x3c4) != 0)) {
      iVar6 = *(int *)(*(int *)(iVar6 + 0x3c4) + 0x70);
      pfVar1 = *(float **)(iVar9 + 0x70);
      if ((iVar6 != 0) && (pfVar1 != (float *)0x0)) {
        local_90 = *(float *)(iVar6 + 0x1c);
        if (_DAT_004be000 < local_90) {
          local_90 = 8400.0;
        }
        local_90 = local_90 * _DAT_004be004;
        if (_DAT_004bdff0 < local_90) {
          local_90 = local_90 - _DAT_004bdff4;
        }
        pfVar1[0x11] = local_90 * _DAT_004bdff8;
        pfVar4 = (float *)&DAT_004faed8;
        pfVar10 = local_80;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *pfVar10 = *pfVar4;
          pfVar4 = pfVar4 + 1;
          pfVar10 = pfVar10 + 1;
        }
        local_8c = mission_flow_map_context_helper_0049d400(pfVar1[0x11]);
        local_80[0] = (float)((ulonglong)local_8c >> 0x20);
        local_68 = (float)local_8c;
        local_80[2] = -local_68;
        local_60 = local_80[0];
        pfVar4 = compose_matrix_or_transform_a(local_40,local_80,pfVar1);
        pfVar10 = (float *)(iVar9 + 0x18);
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *pfVar10 = *pfVar4;
          pfVar4 = pfVar4 + 1;
          pfVar10 = pfVar10 + 1;
        }
        if ((DAT_00654b88 == '\0') &&
           (piVar5 = (int *)get_active_player_or_camera_world_object_entry(), param_1 == *piVar5)) {
          pfVar1[0x13] = pfVar1[0x12];
          fVar7 = (float)ftol();
          pfVar1[0x12] = fVar7;
          if (0x19 < (int)fVar7) {
            pfVar1[0x12] = 3.50325e-44;
          }
          if ((pfVar1[0x13] != pfVar1[0x12]) || (DAT_0054ac6c != 0)) {
            sprintf((char *)&local_8c,s_3needle__d_004f7124,pfVar1[0x12]);
            reload_texture_binding_current_frame_pixels
                      (DAT_00609504,(byte *)(s_ztach3_map_004f67b0 + DAT_004f67ec * 0xd),0);
            draw_texture_widget_to_hud_surface_and_bind_object
                      (DAT_00609504,(byte *)(s_ztach3_map_004f67b0 + DAT_004f67ec * 0xd),
                       s_tachneedleloc_004f7104,(char *)((int)&local_8c + DAT_004f67ec),
                       &DAT_0054a2f0,1);
          }
        }
      }
    }
    iVar6 = DAT_004f67ec * 0xd;
    uVar2 = *(uint *)(*(int *)(param_1 + 0x70) + 0x428);
    if (uVar2 != 0) {
      fVar12 = (float10)world_object_geometry_context_helper_00458970(param_1);
      if (fVar12 < (float10)_DAT_004bdfe8) {
        fVar12 = fVar12 - (float10)_DAT_004be010;
      }
      fVar3 = (float10)_DAT_004be014;
      if (fVar12 * fVar3 != (float10)_DAT_0054abf0) {
        puVar8 = (undefined4 *)
                 definition_record_parser_context_helper_00449220
                           ((int *)local_80,uVar2,s_zcm_320_map_004f64f4 + iVar6,
                            s_3compass_window_004f5e90 + DAT_004f67ec,
                            s_3left_004f5f00 + DAT_004f67ec,s_3right_004f5f10 + DAT_004f67ec);
        puVar11 = &DAT_0054a3d0;
        for (iVar6 = 0xd; _DAT_0054abf0 = (float)(fVar12 * fVar3), iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar11 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar11 = puVar11 + 1;
        }
      }
    }
    update_cockpit_status_warning_indicators(param_1);
    initialize_gear_selector_indicator(param_1);
    initialize_specials_empty_indicator(param_1);
    load_cockpit_hud_base_texture();
  }
  return;
}


