/*
 * Program: i76.exe
 * Function: load_gear_indicator_texture
 * Entry: 0045adf0
 * Signature: undefined __cdecl load_gear_indicator_texture(float * param_1)
 */


/* cgpt whole-binary semantic rename v1: references zgear101.map */

void __cdecl load_gear_indicator_texture(float *param_1)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_00;
  int iVar4;
  int local_28 [5];
  undefined4 local_14;
  undefined4 local_10;
  int *local_4;
  
  bVar2 = get_global_heap_handle();
  if ((CONCAT31(extraout_var,bVar2) != 0) && (DAT_0054ac68 != 0)) {
    load_speedometer_textures(param_1);
    return;
  }
  iVar3 = is_damage_side_effects_suppressed();
  if ((iVar3 == 0) || (g_runtime_display_input_mode != 0x10)) {
    if (DAT_004c2908 == (int *)0x0) {
      DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
    }
    piVar1 = DAT_004c2908;
    if ((DAT_004c2908 != (int *)0x0) && (*DAT_004c2908 != 0)) {
      local_28[0] = *DAT_004c2908;
      local_14 = 4;
      local_10 = 0;
      local_4 = DAT_004c2908;
      bVar2 = get_global_heap_handle();
      if (CONCAT31(extraout_var_00,bVar2) == 1) {
        iVar3 = get_current_texture_cache_generation();
        iVar3 = iVar3 - DAT_004f70f8;
        DAT_004f70f8 = get_current_texture_cache_generation();
        if ((((iVar3 != 1) && (*piVar1 != 0)) && (iVar3 = *(int *)(*piVar1 + 0x70), iVar3 != 0)) &&
           (iVar3 = *(int *)(iVar3 + 0x438), iVar3 != 0)) {
          ensure_world_object_geometry_variant_binding(iVar3,4);
          iVar3 = *(int *)(*(int *)(iVar3 + 0x5c) + 0x14);
          if (iVar3 != 0) {
            if (iVar3 == 0) goto LAB_0045aee7;
            do {
              iVar4 = _strnicmp((char *)(iVar3 + 0x20),s_zgear101_map_004f716c,0x10);
              if (iVar4 == 0) {
                *(byte *)(iVar3 + 0x1d) = *(byte *)(iVar3 + 0x1d) | 4;
              }
LAB_0045aee7:
              iVar3 = *(int *)(iVar3 + 0x30);
            } while (iVar3 != 0);
          }
        }
      }
      hud_bitmap_render_context_helper_0045dcc0(local_28,param_1);
    }
  }
  return;
}


