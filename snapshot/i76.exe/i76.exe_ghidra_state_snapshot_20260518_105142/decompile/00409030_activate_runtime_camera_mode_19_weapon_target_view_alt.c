/*
 * Program: i76.exe
 * Function: activate_runtime_camera_mode_19_weapon_target_view_alt
 * Entry: 00409030
 * Signature: undefined __cdecl activate_runtime_camera_mode_19_weapon_target_view_alt(int * param_1)
 */


/* cgpt rename v5 runtime camera cluster: Runtime camera mode table id 0x19; alternate weapon-target
   tracking activation using callback LAB_00409140. */

void __cdecl activate_runtime_camera_mode_19_weapon_target_view_alt(int *param_1)

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
  
  uVar1 = get_primary_vehicle_weapon_target_object(*param_1);
  if (uVar1 != 0) {
    if (g_runtime_display_mode_state != 4) {
      if (DAT_004c2988 < 1) {
        return;
      }
      DAT_004c2988 = DAT_004c2988 + -1;
      puVar3 = &g_runtime_display_mode_change_callback;
      puVar6 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
      for (iVar4 = 0x9a; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar6 = puVar6 + 1;
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
    g_runtime_display_mode_state = 4;
    DAT_004c2908 = param_1;
    g_runtime_display_mode_change_callback = &LAB_00409140;
  }
  return;
}


