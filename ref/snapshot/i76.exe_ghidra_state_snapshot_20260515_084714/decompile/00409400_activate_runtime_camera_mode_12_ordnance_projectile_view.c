/*
 * Program: i76.exe
 * Function: activate_runtime_camera_mode_12_ordnance_projectile_view
 * Entry: 00409400
 * Signature: undefined __stdcall activate_runtime_camera_mode_12_ordnance_projectile_view(void)
 */


/* cgpt rename v5 runtime camera cluster: Runtime camera mode table id 0x12; switches to
   ordnance/effect-source camera view when the current ordnance parent object is valid and flagged.
    */

void activate_runtime_camera_mode_12_ordnance_projectile_view(void)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float local_258 [16];
  float local_218 [16];
  float local_1d8 [118];
  
  iVar1 = ordnance_runtime_flag_set_context_helper_004a7150();
  if ((iVar1 != 0) && (g_runtime_display_mode_state != 5)) {
    iVar2 = get_effect_source_parent_world_object(iVar1);
    iVar2 = world_object_has_optional_runtime_flag(iVar2);
    if ((iVar2 != 0) && ((g_runtime_display_mode_state != 8 && (0 < DAT_004c2988)))) {
      DAT_004c2988 = DAT_004c2988 + -1;
      puVar4 = &g_runtime_display_mode_change_callback;
      puVar6 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
      for (iVar2 = 0x9a; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      DAT_004c2724 = 0;
      g_runtime_display_mode_state = 8;
      software_raster_command_context_helper_00472400((float *)&DAT_004c2730,1.0);
      pfVar3 = (float *)&DAT_004c2770;
      pfVar5 = local_258;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *pfVar5 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar5 = pfVar5 + 1;
      }
      pfVar3 = (float *)compose_matrix_or_transform_b(local_258,local_218);
      pfVar5 = local_258;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *pfVar5 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar5 = pfVar5 + 1;
      }
      puVar4 = (undefined4 *)
               software_raster_command_context_helper_00472220
                         (local_1d8,DAT_004c276c,1.5707963,DAT_004c2760,DAT_004c2740,DAT_004c2764);
      puVar6 = &DAT_004c2730;
      for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      software_raster_queue_context_helper_00472990(0x4c2730,local_258);
      g_runtime_display_mode_change_callback = &LAB_00409540;
      DAT_004c2908 = iVar1;
    }
  }
  return;
}


