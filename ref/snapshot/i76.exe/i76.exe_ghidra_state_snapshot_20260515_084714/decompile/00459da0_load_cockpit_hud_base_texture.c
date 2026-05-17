/*
 * Program: i76.exe
 * Function: load_cockpit_hud_base_texture
 * Entry: 00459da0
 * Signature: undefined __stdcall load_cockpit_hud_base_texture(void)
 */


/* cgpt whole-binary semantic rename v1: references zcbh3101.tmt */

void load_cockpit_hud_base_texture(void)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_34 [13];
  
  iVar2 = DAT_0054a3c4;
  if (DAT_0054a414 == 1) {
    iVar7 = 2;
    piVar1 = (int *)get_active_player_or_camera_world_object_entry();
    iVar7 = is_vehicle_weapon_fire_gate_clear(*piVar1,iVar7);
    if (iVar7 != 0) {
      iVar7 = 1;
      piVar1 = (int *)get_active_player_or_camera_world_object_entry();
      iVar7 = is_vehicle_weapon_fire_gate_clear(*piVar1,iVar7);
      if (iVar7 != 0) {
        if (DAT_0054a3c4 == -1) {
          return;
        }
        iVar8 = 1;
        iVar6 = 0;
        iVar2 = DAT_0054a3c4;
        iVar7 = mission_flow_map_context_helper_0049ccc0();
        iVar2 = set_texture_binding_frame_and_reload
                          (DAT_00609508,
                           (byte *)(s_zcbh3101_tmt_004f6728 + (DAT_004f67ec + -2 + iVar7 * 2) * 0xd)
                           ,iVar6,iVar2,iVar8);
        if (iVar2 != 1) {
          return;
        }
        iVar7 = 0;
        iVar2 = mission_flow_map_context_helper_0049ccc0();
        DAT_0054a2e4 = (int *)bind_or_load_texture_set_for_object
                                        (DAT_00609508,
                                         (byte *)(s_zcbh3101_tmt_004f6728 +
                                                 (DAT_004f67ec + -2 + iVar2 * 2) * 0xd),iVar7);
        if (DAT_0054a2e4 != (int *)0x0) {
          puVar3 = (undefined4 *)
                   construct_bitmap_surface_context
                             (local_34,*DAT_0054a2e4,(DAT_0054a2e4[1] << 3) >> 3,
                              (int)(DAT_0054a2e4 + 2),0);
          puVar5 = &DAT_0054abf8;
          for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
        }
        if (0 < DAT_0054a3c4) {
          return;
        }
        DAT_0054a3c4 = DAT_0054a3c4 + 1;
        return;
      }
    }
  }
  if ((DAT_0054a3c4 < 0) || (DAT_0054a3c4 = DAT_0054a3c4 + -1, DAT_0054a3c4 < 0)) {
    if (iVar2 == DAT_0054a3c4) {
      return;
    }
    release_bitmap_surface_context(&DAT_0054abf8);
    DAT_0054a2e4 = (int *)0x0;
    piVar1 = (int *)0x0;
    uVar4 = 0;
    iVar2 = 0;
  }
  else {
    iVar8 = 1;
    iVar6 = 0;
    iVar2 = DAT_0054a3c4;
    iVar7 = mission_flow_map_context_helper_0049ccc0();
    iVar2 = set_texture_binding_frame_and_reload
                      (DAT_00609508,
                       (byte *)(s_zcbh3101_tmt_004f6728 + (DAT_004f67ec + -2 + iVar7 * 2) * 0xd),
                       iVar6,iVar2,iVar8);
    if (iVar2 != 1) {
      return;
    }
    iVar7 = 0;
    iVar2 = mission_flow_map_context_helper_0049ccc0();
    DAT_0054a2e4 = (int *)bind_or_load_texture_set_for_object
                                    (DAT_00609508,
                                     (byte *)(s_zcbh3101_tmt_004f6728 +
                                             (DAT_004f67ec + -2 + iVar2 * 2) * 0xd),iVar7);
    if (DAT_0054a2e4 == (int *)0x0) {
      return;
    }
    piVar1 = DAT_0054a2e4 + 2;
    iVar2 = *DAT_0054a2e4;
    uVar4 = (DAT_0054a2e4[1] << 3) >> 3;
  }
  puVar3 = (undefined4 *)construct_bitmap_surface_context(local_34,iVar2,uVar4,(int)piVar1,0);
  puVar5 = &DAT_0054abf8;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}


