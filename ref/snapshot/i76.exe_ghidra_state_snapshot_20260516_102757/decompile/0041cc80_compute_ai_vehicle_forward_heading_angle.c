/*
 * Program: i76.exe
 * Function: compute_ai_vehicle_forward_heading_angle
 * Entry: 0041cc80
 * Signature: float10 __cdecl compute_ai_vehicle_forward_heading_angle(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Computes the current forward/heading angle for an
   object or vehicle-adjusted forward vector using atan2. */

float10 __cdecl compute_ai_vehicle_forward_heading_angle(int param_1)

{
  float *pfVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_28 [3];
  undefined4 local_1c [3];
  float local_10;
  float local_c;
  float local_8;
  
  if ((*(float *)(param_1 + 0x30) == _DAT_004bcae8) && (*(float *)(param_1 + 0x38) == _DAT_004bcae8)
     ) {
    fVar3 = (float10)_DAT_004bcae8;
  }
  else {
    pfVar1 = (float *)copy_object_local_translation_vec3(local_1c,param_1 + 0x18);
    local_10 = *pfVar1;
    local_c = pfVar1[1];
    local_8 = pfVar1[2];
    iVar2 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar2 != 0) {
      fVar4 = local_10;
      fVar5 = local_c;
      fVar6 = local_8;
      iVar2 = get_vehicle_runtime_context(param_1);
      pfVar1 = (float *)scale_vec3_components(local_28,*(float *)(iVar2 + 0xe8),fVar4,fVar5,fVar6);
      local_10 = *pfVar1;
      local_c = pfVar1[1];
      local_8 = pfVar1[2];
    }
    fVar3 = (float10)_CIatan2();
  }
  return fVar3;
}


