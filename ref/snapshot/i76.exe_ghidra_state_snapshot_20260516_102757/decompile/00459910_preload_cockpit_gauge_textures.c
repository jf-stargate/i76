/*
 * Program: i76.exe
 * Function: preload_cockpit_gauge_textures
 * Entry: 00459910
 * Signature: undefined __cdecl preload_cockpit_gauge_textures(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00459910
   suggested_name: preload_cockpit_gauge_textures
   basis: References gauge/reticle/speedometer/tachometer .map/.tmt assets and calls
   add_texture_to_cache. */

void __cdecl preload_cockpit_gauge_textures(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  char *pcVar7;
  int local_34 [13];
  
  iVar4 = *(int *)(param_1 + 0x70);
  reset_vehicle_weapon_target_transform_state(param_1);
  load_reticle_crosshair_textures(param_1);
  if (g_display_mode_variant_index < 6) {
    uVar6 = 1;
    DAT_004f67ec = 1;
    iVar2 = world_object_geometry_context_helper_004588b0(param_1,s_zsy_320_map_004f64c0);
    get_world_object_class_id(iVar2,uVar6);
    uVar6 = 1;
    iVar2 = world_object_geometry_context_helper_004588b0(param_1,s_zcm_320_map_004f64f4);
    get_world_object_class_id(iVar2,uVar6);
    if (DAT_0054ab94 == (uint *)0x0) goto LAB_004599d6;
    pcVar7 = s_ztarg901_map_004f66c8;
  }
  else {
    uVar6 = 1;
    DAT_004f67ec = 0;
    iVar2 = world_object_geometry_context_helper_004588b0(param_1,s_zsy__map_004f64cd);
    get_world_object_class_id(iVar2,uVar6);
    uVar6 = 1;
    iVar2 = world_object_geometry_context_helper_004588b0(param_1,s_zcm__map_004f6501);
    get_world_object_class_id(iVar2,uVar6);
    if (DAT_0054ab94 == (uint *)0x0) goto LAB_004599d6;
    pcVar7 = s_ztarg902_map_004f66d5;
  }
  release_vqm_texture_cache_reference_by_name(pcVar7);
LAB_004599d6:
  DAT_0054ab94 = (uint *)0x0;
  iVar2 = world_object_geometry_context_helper_004588b0
                    (param_1,s_zsy_320_map_004f64c0 + DAT_004f67ec * 0xd);
  *(int *)(iVar4 + 0x420) = iVar2;
  iVar2 = world_object_geometry_context_helper_004588b0
                    (param_1,s_zcm_320_map_004f64f4 + DAT_004f67ec * 0xd);
  *(int *)(iVar4 + 0x428) = iVar2;
  iVar2 = world_object_geometry_context_helper_004588b0
                    (param_1,s_zgear101_map_004f650e + DAT_004f67ec * 0xd);
  *(int *)(iVar4 + 0x438) = iVar2;
  world_object_geometry_context_helper_00458860(*(int *)(iVar4 + 0x420),1);
  world_object_geometry_context_helper_00458860(*(int *)(iVar4 + 0x428),1);
  puVar3 = &DAT_0054a418;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  DAT_0054a338 = 0xffffffff;
  puVar3 = &DAT_0054abd0;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  _DAT_0054abf0 = 0xc3fa0000;
  if (DAT_0054ab94 == (uint *)0x0) {
    DAT_0054ab94 = load_texture_resource_resolving_vqm_cbk_to_cache
                             ((byte *)(s_ztarg901_map_004f66c8 + DAT_004f67ec * 0xd));
    if (DAT_0054ab94 != (uint *)0x0) {
      release_bitmap_surface_context(&DAT_0054a2b0);
      puVar3 = (undefined4 *)
               construct_bitmap_surface_context
                         (local_34,*DAT_0054ab94,(int)(DAT_0054ab94[1] << 3) >> 3,
                          (int)(DAT_0054ab94 + 2),0);
      puVar5 = &DAT_0054a2b0;
      for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
    }
  }
  if (DAT_0054a3c8 == (uint *)0x0) {
    DAT_0054a3c8 = load_texture_resource_resolving_vqm_cbk_to_cache
                             ((byte *)(s_zretc_1_map_004f66e8 + DAT_004f67ec * 0xd));
    if (DAT_0054a3c8 != (uint *)0x0) {
      release_bitmap_surface_context(&DAT_0054a270);
      puVar3 = (undefined4 *)
               construct_bitmap_surface_context
                         (local_34,*DAT_0054a3c8,(int)(DAT_0054a3c8[1] << 3) >> 3,
                          (int)(DAT_0054a3c8 + 2),0);
      puVar5 = &DAT_0054a270;
      for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
    }
  }
  if (DAT_0054ab90 == (uint *)0x0) {
    DAT_0054ab90 = load_texture_resource_resolving_vqm_cbk_to_cache
                             ((byte *)(s_zretc_1_map_004f6708 + DAT_004f67ec * 0xd));
    if (DAT_0054ab90 != (uint *)0x0) {
      release_bitmap_surface_context(&DAT_0054ab58);
      puVar3 = (undefined4 *)
               construct_bitmap_surface_context
                         (local_34,*DAT_0054ab90,(int)(DAT_0054ab90[1] << 3) >> 3,
                          (int)(DAT_0054ab90 + 2),0);
      puVar5 = &DAT_0054ab58;
      for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
    }
  }
  if (DAT_00609504 != (LPVOID)0x0) {
    release_world_object_texture_bindings((int)DAT_00609504);
    DAT_00609504 = (LPVOID)0x0;
  }
  if (DAT_00609500 != (LPVOID)0x0) {
    release_world_object_texture_bindings((int)DAT_00609500);
    DAT_00609500 = (LPVOID)0x0;
  }
  if (DAT_00609508 != (LPVOID)0x0) {
    release_world_object_texture_bindings((int)DAT_00609508);
    DAT_00609508 = (LPVOID)0x0;
  }
  iVar4 = mission_flow_map_context_helper_0049ccc0();
  DAT_00609508 = load_texture_set_and_create_binding_list
                           ((byte *)(s_zcbh3101_tmt_004f6728 + (DAT_004f67ec + -2 + iVar4 * 2) * 0xd
                                    ));
  DAT_00609504 = load_texture_set_and_create_binding_list
                           ((byte *)(s_ztach3_map_004f67b0 + DAT_004f67ec * 0xd));
  DAT_00609500 = load_texture_set_and_create_binding_list
                           ((byte *)(s_zspeedo3_map_004f67d0 + DAT_004f67ec * 0xd));
  DAT_0054ac64 = 0;
  DAT_004f67f0 = 0xffffffff;
  uVar1 = convert_rgb_floats_to_nearest_palette_index();
  DAT_0054a44c = CONCAT31(extraout_var,uVar1);
  uVar1 = convert_rgb_floats_to_nearest_palette_index();
  _DAT_0054a448 = CONCAT31(extraout_var_00,uVar1);
  uVar1 = convert_rgb_floats_to_nearest_palette_index();
  _DAT_0054a444 = CONCAT31(extraout_var_01,uVar1);
  uVar1 = convert_rgb_floats_to_nearest_palette_index();
  _DAT_0054a440 = CONCAT31(extraout_var_02,uVar1);
  DAT_0054ac6c = 1;
  release_bitmap_surface_context(&DAT_0054a340);
  release_bitmap_surface_context(&DAT_0054a2f0);
  puVar3 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar5 = &DAT_0054a340;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar3 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar5 = &DAT_0054a2f0;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}


