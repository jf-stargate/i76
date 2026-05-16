/*
 * Program: i76.exe
 * Function: update_runtime_camera_object_relative_callback
 * Entry: 004061b0
 * Signature: undefined __stdcall update_runtime_camera_object_relative_callback(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Runtime camera callback used by object-relative camera modes;
   updates tracked object transform and active camera matrix. */

void update_runtime_camera_object_relative_callback(void)

{
  float fVar1;
  int *piVar2;
  float fVar3;
  float *pfVar4;
  undefined4 *puVar5;
  int iVar6;
  float *pfVar7;
  float10 fVar8;
  float10 extraout_ST0;
  undefined8 uVar9;
  float local_100 [16];
  float local_c0 [4];
  float local_b0 [10];
  undefined4 local_88;
  undefined4 local_84;
  double local_80;
  double local_78;
  float local_70 [4];
  undefined4 local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  double local_48;
  double local_40;
  double local_38;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined8 local_14;
  float local_c;
  float local_8;
  
  if (DAT_004c2908 == (int *)0x0) {
    DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry();
  }
  piVar2 = DAT_004c2908;
  fVar8 = get_runtime_frame_delta_seconds();
  local_30 = (float)(fVar8 + fVar8);
  DAT_004c2918 = DAT_004c2918 - (float)_DAT_00536794 * _DAT_004bc528;
  if (DAT_004c2918 < _DAT_004bc52c) {
    DAT_004c2918 = 0.017453292;
  }
  if (_DAT_004bc530 < DAT_004c2918) {
    DAT_004c2918 = 1.5707963;
  }
  DAT_004c291c = DAT_004c291c - (float)_DAT_0053679c * _DAT_004bc528;
  if ((_DAT_004bc534 < ABS(DAT_004c291c)) &&
     (DAT_004c291c = DAT_004c292c - (DAT_004c292c / 6.2831855) * 6.2831855,
     DAT_004c291c < _DAT_004bc518)) {
    DAT_004c291c = DAT_004c291c - _DAT_004bc53c;
  }
  DAT_004c2924 = (float)_DAT_0053678c;
  if (DAT_004c2924 < _DAT_004bc508) {
    DAT_004c2924 = 1.0;
  }
  if (_DAT_004bc540 < DAT_004c2924) {
    DAT_004c2924 = 10.0;
  }
  local_14 = CONCAT44(DAT_004c2934,(float)local_14);
  fVar3 = DAT_004c2924;
  if (((_DAT_004bc518 <= local_30) && (fVar3 = DAT_004c2924, local_30 <= _DAT_004bc544)) &&
     (fVar3 = DAT_004c2924, (float)_DAT_004bc548 <= ABS(DAT_004c2924 - DAT_004c2934))) {
    fVar3 = local_30 * (DAT_004c2924 - DAT_004c2934) + DAT_004c2934;
  }
  DAT_004c2934 = fVar3;
  fVar3 = DAT_004c2918;
  if ((_DAT_004bc518 <= local_30) && (fVar3 = DAT_004c2918, local_30 <= _DAT_004bc544)) {
    fVar1 = DAT_004c2918 - DAT_004c2928;
    local_14 = CONCAT44(fVar1,(float)local_14);
    fVar3 = DAT_004c2918;
    if ((float)_DAT_004bc548 <= ABS(fVar1)) {
      fVar3 = local_30 * fVar1 + DAT_004c2928;
    }
  }
  DAT_004c2928 = fVar3;
  local_c = DAT_004c292c;
  fVar3 = DAT_004c291c;
  if ((_DAT_004bc518 <= local_30) && (fVar3 = DAT_004c291c, local_30 <= _DAT_004bc544)) {
    fVar1 = DAT_004c291c - DAT_004c292c;
    local_14 = CONCAT44(fVar1,(float)local_14);
    fVar3 = DAT_004c291c;
    if ((float)_DAT_004bc548 <= ABS(fVar1)) {
      fVar3 = local_30 * fVar1 + DAT_004c292c;
    }
  }
  DAT_004c292c = fVar3;
  pfVar4 = (float *)&DAT_004faed8;
  pfVar7 = local_b0;
  local_20 = local_30;
  local_8 = DAT_004c2928;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  fVar3 = DAT_004c2934 * (float)piVar2[4];
  if (_DAT_004bc514 < DAT_004c2934 * (float)piVar2[4]) {
    fVar3 = _DAT_004bc514;
  }
  pfVar4 = (float *)&DAT_004faed8;
  pfVar7 = local_70;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  local_78 = (double)-fVar3;
  uVar9 = mission_flow_map_context_helper_0049d400(local_8);
  local_60 = (undefined4)((ulonglong)uVar9 >> 0x20);
  local_5c = (float)local_14;
  local_54 = -(float)local_14;
  local_50 = (float)local_60;
  local_14 = uVar9;
  pfVar4 = compose_matrix_or_transform_a(local_100,local_b0,local_70);
  pfVar7 = local_b0;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  pfVar4 = (float *)&DAT_004faed8;
  pfVar7 = local_70;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  uVar9 = mission_flow_map_context_helper_0049d400(DAT_004c292c);
  local_70[0] = (float)((ulonglong)uVar9 >> 0x20);
  local_58 = (float)local_14;
  local_14._0_4_ = (float)uVar9;
  local_70[2] = (float)local_14;
  local_58 = -local_58;
  local_50 = local_70[0];
  local_14 = uVar9;
  pfVar4 = compose_matrix_or_transform_a(local_100,local_b0,local_70);
  pfVar7 = local_b0;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  pfVar4 = (float *)compute_audio_listener_orientation_from_world_object(local_c0,piVar2);
  local_1c = *pfVar4;
  local_18 = pfVar4[1];
  local_14._0_4_ = pfVar4[2];
  local_14._4_4_ = pfVar4[3];
  if ((float)local_14 * _DAT_004c294c +
      local_18 * _DAT_004c2948 + local_1c * _DAT_004c2944 + local_14._4_4_ * _DAT_004c2950 <
      (float)_DAT_004bc550) {
    local_14._4_4_ = -local_14._4_4_;
    local_1c = -local_1c;
    local_18 = -local_18;
    local_14._0_4_ = -(float)local_14;
  }
  _DAT_004c2948 = local_18;
  _DAT_004c294c = (float)local_14;
  _DAT_004c2944 = local_1c;
  _DAT_004c2950 = local_14._4_4_;
  puVar5 = (undefined4 *)
           zone_satellite_map_context_helper_004944d0
                     (local_c0,(float *)&DAT_004c2954,(float *)&DAT_004c2944,local_30);
  _DAT_004c2954 = *puVar5;
  _DAT_004c2958 = puVar5[1];
  _DAT_004c295c = puVar5[2];
  _DAT_004c2960 = puVar5[3];
  pfVar4 = (float *)zone_satellite_map_context_helper_00494170(&DAT_004c2954,local_100);
  pfVar7 = local_70;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  transform_vec3_array_by_matrix(&local_2c,(float *)(piVar2 + 1),1,(float *)(*piVar2 + 0x18));
  local_48 = (double)local_2c;
  local_40 = (double)local_28;
  local_38 = (double)local_24;
  pfVar4 = compose_matrix_or_transform_a(local_100,local_b0,local_70);
  pfVar7 = local_b0;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar7 = pfVar7 + 1;
  }
  apply_world_object_transform_to_bounds_or_geometry((double)CONCAT44(local_84,local_88),local_78);
  if ((float10)local_80 - (float10)_DAT_004bc560 < extraout_ST0 - (float10)_DAT_004bc558) {
    local_80 = (double)((extraout_ST0 - (float10)_DAT_004bc558) - (float10)_DAT_004bc568);
  }
  software_raster_queue_context_helper_00472990(0x4c2730,local_b0);
  return;
}


