/*
 * Program: i76.exe
 * Function: probe_ai_vehicle_forward_ground_clearance
 * Entry: 0041d450
 * Signature: undefined4 __cdecl probe_ai_vehicle_forward_ground_clearance(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Projects points ahead of the vehicle and tests for
   ground/height clearance changes. */

undefined4 __cdecl probe_ai_vehicle_forward_ground_clearance(int param_1)

{
  float *pfVar1;
  int iVar2;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float local_6c [3];
  undefined4 local_60 [3];
  float local_54 [3];
  float local_48;
  int local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_44 = 0;
  local_24 = 5.1;
  local_44 = get_vehicle_runtime_context(param_1);
  pfVar1 = (float *)copy_transform_position_vec3(local_54,param_1 + 0x18);
  local_1c = *pfVar1;
  local_18 = pfVar1[1];
  local_14 = pfVar1[2];
  iVar2 = probe_ai_vehicle_path_clearance_along_heading
                    ((float *)(param_1 + 0x18),&local_1c,local_44 + 0xbc,*(float *)(local_44 + 0xac)
                     ,&local_8,*(float *)(local_44 + 0xe8),1,&local_28);
  if (iVar2 != 0) {
    pfVar1 = (float *)copy_object_local_translation_vec3(local_60,param_1 + 0x18);
    local_34 = *pfVar1;
    local_30 = pfVar1[1];
    local_2c = pfVar1[2];
    apply_world_object_transform_to_bounds_or_geometry((double)local_1c,(double)local_14);
    local_48 = (float)extraout_ST0;
    for (local_10 = 5.0; local_10 <= local_24; local_10 = local_10 + _DAT_004bcb28) {
      pfVar1 = (float *)vec3_madd_xyz(local_6c,local_1c,local_18,local_14,local_10,local_34,local_30
                                      ,local_2c);
      local_40 = *pfVar1;
      local_3c = pfVar1[1];
      local_38 = pfVar1[2];
      apply_world_object_transform_to_bounds_or_geometry((double)local_40,(double)local_38);
      local_20 = (float)extraout_ST0_00;
      local_c = (float)(extraout_ST0_00 - (float10)local_48);
      if (extraout_ST0_00 - (float10)local_48 < (float10)_DAT_004bcadc) {
        return 1;
      }
      local_48 = local_20;
    }
  }
  return 0;
}


