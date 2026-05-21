/*
 * Program: i76.exe
 * Function: runtime_library_string_scan_helper_004bb370
 * Entry: 004bb370
 * Signature: undefined4 __cdecl runtime_library_string_scan_helper_004bb370(float * param_1, int param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: runtime library string scan helper
   based on adjacent named subsystem context. */

undefined4 __cdecl
runtime_library_string_scan_helper_004bb370(float *param_1,int param_2,float *param_3)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78 [2];
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50 [4];
  float local_40 [16];
  
  transform_vec3_array_by_matrix(&local_90,(float *)(param_2 + 0x84),1,param_3);
  local_84 = local_90 - _DAT_005dbb08 * _DAT_004bff9c;
  local_80 = local_8c - _DAT_005dbb0c * _DAT_004bff9c;
  local_7c = local_88 - _DAT_005dbb10 * _DAT_004bff9c;
  iVar1 = runtime_library_memory_fill_helper_004bb080
                    (local_78,local_90,local_8c,local_88,local_84,local_80,local_7c);
  if (iVar1 == 0) {
    return 0;
  }
  local_88 = local_70 - _DAT_004bffa0;
  local_7c = local_70 - _DAT_004bffa4;
  local_84 = local_78[0] - _DAT_004bffa4;
  local_6c = local_78[0] - _DAT_004bffa0;
  local_90 = local_78[0];
  local_64 = local_7c;
  apply_world_object_transform_to_bounds_or_geometry((double)local_78[0],(double)local_88);
  local_8c = (float)extraout_ST0;
  apply_world_object_transform_to_bounds_or_geometry((double)local_84,(double)local_7c);
  local_80 = (float)extraout_ST0_00;
  apply_world_object_transform_to_bounds_or_geometry((double)local_6c,(double)local_64);
  local_68 = (float)extraout_ST0_01;
  pfVar2 = (float *)compute_polygon_plane_or_normal_from_three_points
                              (local_50,&local_90,&local_6c,&local_84);
  local_60 = *pfVar2;
  local_5c = pfVar2[1];
  local_58 = pfVar2[2];
  local_54 = pfVar2[3];
  iVar1 = zone_satellite_map_context_helper_00493fc0(param_1,&local_60,(float *)&DAT_005dbb08);
  if (iVar1 == 0) {
    return 0;
  }
  pfVar2 = compose_matrix_or_transform_a(local_40,param_1,(float *)(DAT_005dbac4 + 0x40));
  pfVar3 = param_1;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar2 = compose_matrix_or_transform_a(local_40,param_3,param_1);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  noop_world_object_callback_stub();
  return 1;
}


