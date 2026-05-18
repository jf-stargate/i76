/*
 * Program: i76.exe
 * Function: preload_asset_caches
 * Entry: 004026c0
 * Signature: undefined __cdecl preload_asset_caches(char * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_004026c0
   suggested_name: preload_asset_caches
   basis: Cache preload candidate; clustered with geometry/texture/video cache preload diagnostics.
    */

void __cdecl preload_asset_caches(char *param_1)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char *pcVar5;
  undefined3 extraout_var;
  uint *puVar6;
  int iVar7;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  char *_Format;
  char local_1a9;
  int local_1a8;
  char *local_1a4;
  int local_1a0;
  int local_19c;
  int local_198;
  uint *local_194;
  uint local_190 [49];
  char cStack_c9;
  undefined4 local_c8 [50];
  
  uVar8 = 0xffffffff;
  do {
    pcVar5 = param_1;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar5 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar5;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  pcVar5 = pcVar5 + -uVar8;
  pcVar10 = (char *)local_c8;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar10 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar10 = pcVar10 + 1;
  }
  pcVar5 = strchr((char *)local_c8,0x2e);
  bVar2 = false;
  if (pcVar5 == (char *)0x0) {
    uVar8 = 0xffffffff;
    pcVar5 = (char *)local_c8;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5 = (char *)((int)local_c8 + (~uVar8 - 1));
  }
  local_1a4 = pcVar5;
  bVar3 = is_miss16_high_color_resource_mode();
  if (CONCAT31(extraout_var,bVar3) == 0) {
    *(undefined4 *)pcVar5 = DAT_004c2340;
    pcVar5[4] = DAT_004c2344;
  }
  else {
    *(undefined4 *)pcVar5 = DAT_004c2348;
    *(undefined **)(pcVar5 + 4) = PTR_DAT_004c234c;
  }
  loaded_resource_cache_cleanup_context_helper_0046fa80();
  texture_cache_record_touch_helper_00447db0();
  purge_queued_geometry_cache_records();
  if (DAT_00504bfc == 0) {
    puVar6 = open_resource_file_into_memory((char *)local_c8);
    if (((byte)DAT_00504c08 & 2) != 0) {
      g_resource_debug_log_file = DAT_005a7c90;
    }
    local_194 = puVar6;
    if (g_resource_debug_log_file != 0) {
      fprintf((FILE *)DAT_005a7c90,s_cache_geom_tex_video_free___d__d_004c2314,
              g_loaded_resource_cache_budget_bytes,DAT_00608e5c,g_vqm_texture_cache_bytes_remaining,
              DAT_0052b914);
    }
    if (puVar6 != (uint *)0x0) {
      local_1a8 = 0;
      iVar7 = get_loaded_resource_file_size((char *)local_c8);
      pcVar10 = (char *)(iVar7 + (int)puVar6);
      bVar3 = false;
      local_19c = 0;
      local_1a0 = 0;
      local_198 = 0;
      for (pcVar5 = parse_fullres_lst_line(&local_1a9,(char *)local_190,(char *)puVar6,pcVar10);
          pcVar5 != (char *)0x0;
          pcVar5 = parse_fullres_lst_line(&local_1a9,(char *)local_190,pcVar5,pcVar10)) {
        if (local_1a9 == 'p') {
          puVar6 = open_resource_file_into_memory((char *)local_190);
          if (puVar6 != (uint *)0x0) {
            if (local_19c == 0) {
              local_1a8 = local_1a8 + 1;
              if ((g_loaded_resource_cache_budget_bytes < 1700000) &&
                 (local_19c = 1, g_resource_debug_log_file != 0)) {
                _Format = s_cache_preloaded__004c2300;
LAB_004028e3:
                fprintf((FILE *)DAT_005a7c90,_Format);
              }
            }
            else {
              release_resource_file_reference((char *)local_190);
            }
          }
        }
        else if (local_1a9 == 't') {
          if (local_1a0 == 0) {
            puVar6 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)local_190);
            if (puVar6 != (uint *)0x0) {
              release_vqm_texture_cache_reference_by_name((char *)local_190);
            }
            if ((g_vqm_texture_cache_bytes_remaining < 500000) &&
               (local_1a0 = 1, g_resource_debug_log_file != 0)) {
              _Format = s_texture_cache_preloaded__004c22e4;
              goto LAB_004028e3;
            }
          }
        }
        else if (((local_1a9 == 'x') || (local_1a9 == 'v')) || (local_1a9 == 'a')) {
          if (((!bVar3) &&
              (bVar4 = is_miss16_high_color_resource_mode(), CONCAT31(extraout_var_00,bVar4) != 0))
             && ((iVar7 = strncmp((char *)local_190,s_ZSWL_004c22c4,4), iVar7 != 0 ||
                 (local_198 = local_198 + 1, local_198 < 6)))) {
            puVar6 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)local_190);
            if (puVar6 != (uint *)0x0) {
              if (local_1a9 == 'a') {
                uVar8 = 2;
              }
              else {
                uVar8 = (uint)(local_1a9 == 'x');
              }
              bVar4 = register_video_memory_texture_cache_entry(puVar6,uVar8);
              if (((CONCAT31(extraout_var_01,bVar4) == 0) || (DAT_0052b914 < 700000)) &&
                 (bVar3 = true, g_resource_debug_log_file != 0)) {
                fprintf((FILE *)DAT_005a7c90,s_D3D_cache_preloaded__004c22ac);
              }
            }
            release_vqm_texture_cache_reference_by_name((char *)local_190);
          }
        }
        else if ((local_1a9 == 'g') && (!bVar2)) {
          uVar8 = load_geometry_resource_into_cache(local_190);
          if (uVar8 != 0) {
            release_geometry_cache_reference(uVar8);
          }
          if ((DAT_00608e5c < 200000) && (bVar2 = true, g_resource_debug_log_file != 0)) {
            fprintf((FILE *)DAT_005a7c90,s_geom_cache_preloaded__004c22cc);
          }
        }
      }
      for (pcVar5 = parse_fullres_lst_line(&local_1a9,(char *)local_190,(char *)local_194,pcVar10);
          pcVar5 != (char *)0x0;
          pcVar5 = parse_fullres_lst_line(&local_1a9,(char *)local_190,pcVar5,pcVar10)) {
        if ((local_1a9 == 'p') && (local_1a8 = local_1a8 + -1, -1 < local_1a8)) {
          release_resource_file_reference((char *)local_190);
        }
      }
      release_resource_file_reference((char *)local_c8);
      pcVar5 = local_1a4;
      if (g_resource_debug_log_file != 0) {
        fprintf((FILE *)DAT_005a7c90,s_preload_done__004c229c);
        pcVar5 = local_1a4;
      }
    }
  }
  if ((DAT_00654b88 != '\0') &&
     (((DAT_004c2908 != (int *)0x0 ||
       (DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry(),
       DAT_004c2908 != (int *)0x0)) && (*DAT_004c2908 != 0)))) {
    hud_bitmap_render_context_helper_0045dc10(*(uint *)(*DAT_004c2908 + 100),4);
  }
  if (DAT_00504bfc != 0) {
    pcVar10 = s_w_004c2298;
    pcVar5[3] = 'o';
    g_resource_debug_log_file = (int)fopen((char *)local_c8,pcVar10);
  }
  return;
}


