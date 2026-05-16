/*
 * Program: i76.exe
 * Function: activate_runtime_camera_mode_1b_effect_target_orbit_view
 * Entry: 00408030
 * Signature: undefined __cdecl activate_runtime_camera_mode_1b_effect_target_orbit_view(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v5 runtime camera cluster: Runtime camera mode table id 0x1b; initializes an
   effect-target orbit view using transformed target radius and callback FUN_00408240. */

void __cdecl activate_runtime_camera_mode_1b_effect_target_orbit_view(int *param_1)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float local_268 [4];
  float local_258 [16];
  float local_218 [16];
  float local_1d8 [118];
  
  if ((((g_runtime_display_mode_state != 5) && (g_runtime_display_mode_state != 0)) &&
      (g_runtime_display_mode_state != 2)) && (0 < DAT_004c2988)) {
    DAT_004c2988 = DAT_004c2988 + -1;
    puVar2 = &g_runtime_display_mode_change_callback;
    puVar5 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
    for (iVar3 = 0x9a; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    pfVar1 = (float *)&DAT_004c2770;
    pfVar4 = local_258;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    pfVar1 = (float *)compose_matrix_or_transform_b(local_258,local_218);
    pfVar4 = local_258;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
    puVar2 = (undefined4 *)
             software_raster_command_context_helper_00472220
                       (local_1d8,DAT_004c276c,1.5707963,DAT_004c2760,DAT_004c2740,DAT_004c2764);
    puVar5 = &DAT_004c2730;
    for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    software_raster_queue_context_helper_00472990(0x4c2730,local_258);
    DAT_004c2724 = 0;
    g_runtime_display_mode_state = 9;
    DAT_004c2908 = param_1;
    iVar3 = get_effect_target_transformed_position_radius(local_268,param_1);
    DAT_004c2924 = *(float *)(iVar3 + 0xc);
    DAT_004c2938 = 0;
    DAT_004c2940 = -DAT_004c2924;
    DAT_004c293c = 0x40000000;
    DAT_004c291c = 0;
    DAT_004c2918 = 0;
    _DAT_004c2920 = 0;
    DAT_004c292c = 0;
    DAT_004c2928 = 0;
    DAT_004c2930 = 0;
    DAT_004c2934 = DAT_004c2924;
    _DAT_0053678c = ftol();
    puVar2 = (undefined4 *)compute_audio_listener_orientation_from_world_object(local_268,param_1);
    _DAT_004c2954 = *puVar2;
    _DAT_004c2958 = puVar2[1];
    _DAT_004c295c = puVar2[2];
    _DAT_004c2960 = puVar2[3];
    _DAT_004c2944 = *puVar2;
    _DAT_004c2948 = puVar2[1];
    _DAT_004c294c = puVar2[2];
    _DAT_004c2950 = puVar2[3];
    g_runtime_display_mode_change_callback = update_runtime_camera_orbit_offset_callback;
    update_runtime_camera_orbit_offset_callback();
  }
  return;
}


