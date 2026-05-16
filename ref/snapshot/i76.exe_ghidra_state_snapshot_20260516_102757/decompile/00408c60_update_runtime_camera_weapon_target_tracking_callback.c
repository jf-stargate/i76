/*
 * Program: i76.exe
 * Function: update_runtime_camera_weapon_target_tracking_callback
 * Entry: 00408c60
 * Signature: undefined __stdcall update_runtime_camera_weapon_target_tracking_callback(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v5 runtime camera cluster: Runtime camera callback for weapon-target tracking;
   updates source/target transforms, times out if target disappears, and calls the two-position
   camera solver. */

void update_runtime_camera_weapon_target_tracking_callback(void)

{
  float10 fVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  
  if (DAT_004c2908 == (int *)0x0) {
    DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
  }
  iVar3 = *DAT_004c2908;
  _DAT_00507d10 = *(undefined4 *)(iVar3 + 0x40);
  _DAT_00507d14 = *(undefined4 *)(iVar3 + 0x44);
  _DAT_00507d18 = *(undefined4 *)(iVar3 + 0x48);
  _DAT_00507d1c = *(undefined4 *)(iVar3 + 0x4c);
  _DAT_00507d20 = *(undefined4 *)(iVar3 + 0x50);
  _DAT_00507d24 = *(undefined4 *)(iVar3 + 0x54);
  uVar2 = get_primary_vehicle_weapon_target_object(iVar3);
  if (uVar2 == 0) {
    fVar6 = get_runtime_frame_delta_seconds();
    fVar1 = (float10)_DAT_00507d0c;
    _DAT_00507d0c = (float)(fVar1 - fVar6);
    if (fVar1 - fVar6 <= (float10)_DAT_004bc518) {
      if (DAT_004c2988 < 8) {
        puVar4 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
        puVar5 = &g_runtime_display_mode_change_callback;
        DAT_004c2988 = DAT_004c2988 + 1;
        for (iVar3 = 0x9a; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        if ((g_runtime_display_mode_state == 2) &&
           (iVar3 = weapon_hud_display_context_helper_004621a0(), iVar3 == 0)) {
          uVar2 = reticle_crosshair_context_helper_00462130();
          while (uVar2 == 0) {
            uVar2 = reticle_crosshair_context_helper_00462130();
          }
        }
      }
      (*g_runtime_display_mode_change_callback)();
      return;
    }
  }
  else {
    _DAT_00507d0c = 3.0;
    _DAT_00507d28 = *(undefined4 *)(uVar2 + 0x40);
    _DAT_00507d2c = *(undefined4 *)(uVar2 + 0x44);
    _DAT_00507d30 = *(undefined4 *)(uVar2 + 0x48);
    _DAT_00507d34 = *(undefined4 *)(uVar2 + 0x4c);
    _DAT_00507d38 = *(undefined4 *)(uVar2 + 0x50);
    _DAT_00507d3c = *(undefined4 *)(uVar2 + 0x54);
  }
  solve_runtime_camera_between_source_and_target_positions
            ((double *)&DAT_00507d28,(double *)&DAT_00507d10);
  return;
}


