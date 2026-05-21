/*
 * Program: i76.exe
 * Function: set_ai_vehicle_steering_toward_heading
 * Entry: 0040fd20
 * Signature: undefined __cdecl set_ai_vehicle_steering_toward_heading(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Computes and clamps AI steering command toward a target heading using current
   heading, speed, and frame delta. */

void __cdecl set_ai_vehicle_steering_toward_heading(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  undefined4 local_10;
  undefined4 local_c [3];
  
  fVar4 = get_runtime_update_delta_seconds();
  fVar1 = (float)fVar4;
  fVar2 = _DAT_004bc760;
  if ((_DAT_004bc75c < param_2) || (fVar2 = _DAT_004bc768, param_2 < _DAT_004bc764)) {
    param_2 = param_2 - fVar2;
  }
  fVar4 = (float10)world_object_geometry_context_helper_00458920(param_1);
  if ((float10)param_2 <= fVar4) {
    fVar4 = (float10)param_2 - fVar4;
    param_2 = (float)(fVar4 - (float10)_DAT_004bc768);
  }
  else {
    param_2 = (float)((float10)param_2 - fVar4);
    fVar4 = (float10)param_2 - (float10)_DAT_004bc760;
  }
  if (ABS((float10)param_2) <= ABS(fVar4)) {
    fVar4 = (float10)param_2;
  }
  iVar3 = get_vehicle_runtime_context(param_1);
  fVar4 = (float10)fsin((float10)(float)-fVar4 * (float10)_DAT_004bc724);
  *(float *)(iVar3 + 0xe0) =
       (float)((((float10)*(float *)(iVar3 + 0xac) -
                (float10)*(float *)(iVar3 + 0xe4) * (float10)fVar1 * (float10)_DAT_004bc76c) *
                (float10)fVar1 * fVar4) / ((float10)fVar1 * (float10)fVar1 * (float10)_DAT_004bc770)
              );
  get_world_object_damage_or_target_vectors(param_1,local_c,&local_10);
  if ((float)_DAT_004bc778 <= *(float *)(iVar3 + 0xe0)) {
    if (_DAT_004bc714 < *(float *)(iVar3 + 0xe0)) {
      *(undefined4 *)(iVar3 + 0xe0) = 0x3f7fbe77;
    }
    return;
  }
  *(undefined4 *)(iVar3 + 0xe0) = 0xbf7fbe77;
  return;
}


