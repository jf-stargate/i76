/*
 * Program: i76.exe
 * Function: update_runtime_camera_orbit_offset_callback
 * Entry: 00408240
 * Signature: undefined __stdcall update_runtime_camera_orbit_offset_callback(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v5 runtime camera cluster: Runtime camera callback that composes orbit/offset
   parameters with the tracked object's transform and writes the active camera matrix. */

void update_runtime_camera_orbit_offset_callback(void)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  float10 extraout_ST0;
  float local_80 [10];
  double local_58;
  double local_50;
  double local_48;
  float local_40 [16];
  
  if (DAT_004c2908 == (int *)0x0) {
    DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
  }
  piVar1 = DAT_004c2908;
  pfVar2 = (float *)zone_satellite_map_context_helper_00493e60
                              (local_40,DAT_004c2928,DAT_004c292c,DAT_004c2930,DAT_004c2938,
                               DAT_004c293c,DAT_004c2940);
  pfVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  local_58 = (double)((float)piVar1[1] + (float)local_58);
  local_50 = (double)((float)piVar1[2] + (float)local_50);
  local_48 = (double)((float)piVar1[3] + (float)local_48);
  pfVar2 = compose_matrix_or_transform_a(local_40,local_80,(float *)(*piVar1 + 0x18));
  pfVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  apply_world_object_transform_to_bounds_or_geometry(local_58,local_48);
  if ((float10)local_50 - (float10)_DAT_004bc560 < extraout_ST0 - (float10)_DAT_004bc558) {
    local_50 = (double)((extraout_ST0 - (float10)_DAT_004bc558) - (float10)_DAT_004bc568);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_80);
  return;
}


