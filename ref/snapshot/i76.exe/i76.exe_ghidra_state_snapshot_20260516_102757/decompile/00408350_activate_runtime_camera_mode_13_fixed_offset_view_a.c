/*
 * Program: i76.exe
 * Function: activate_runtime_camera_mode_13_fixed_offset_view_a
 * Entry: 00408350
 * Signature: undefined __cdecl activate_runtime_camera_mode_13_fixed_offset_view_a(undefined4 param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v5 runtime camera cluster: Runtime camera mode table id 0x13; initializes a fixed
   offset object view and installs update_runtime_camera_orbit_offset_callback. */

void __cdecl activate_runtime_camera_mode_13_fixed_offset_view_a(undefined4 param_1)

{
  uint uVar1;
  float *pfVar2;
  undefined4 *puVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float local_258 [16];
  float local_218 [16];
  float local_1d8 [118];
  
  if ((g_runtime_display_mode_state == 4) && (DAT_004c2988 < 8)) {
    puVar3 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
    puVar6 = &g_runtime_display_mode_change_callback;
    DAT_004c2988 = DAT_004c2988 + 1;
    for (iVar4 = 0x9a; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    if ((g_runtime_display_mode_state == 2) &&
       (iVar4 = weapon_hud_display_context_helper_004621a0(), iVar4 == 0)) {
      uVar1 = reticle_crosshair_context_helper_00462130();
      while (uVar1 == 0) {
        uVar1 = reticle_crosshair_context_helper_00462130();
      }
    }
  }
  pfVar2 = (float *)&DAT_004c2770;
  pfVar5 = local_258;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  pfVar2 = (float *)compose_matrix_or_transform_b(local_258,local_218);
  pfVar5 = local_258;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  puVar3 = (undefined4 *)
           software_raster_command_context_helper_00472220
                     (local_1d8,DAT_004c276c,1.5707963,DAT_004c2760,DAT_004c2740,DAT_004c2764);
  puVar6 = &DAT_004c2730;
  for (iVar4 = 0x76; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_258);
  DAT_004c2724 = 0;
  g_runtime_display_mode_state = 1;
  DAT_004c2908 = param_1;
  DAT_004c2928 = 0;
  DAT_004c292c = 0;
  _DAT_004c2920 = 0;
  DAT_004c2938 = 0xbfc00000;
  DAT_004c293c = 0;
  DAT_004c2940 = 0x3e4ccccd;
  g_runtime_display_mode_change_callback = update_runtime_camera_orbit_offset_callback;
  return;
}


