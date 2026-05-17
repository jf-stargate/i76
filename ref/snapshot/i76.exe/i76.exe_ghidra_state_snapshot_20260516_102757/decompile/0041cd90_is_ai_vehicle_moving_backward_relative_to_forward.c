/*
 * Program: i76.exe
 * Function: is_ai_vehicle_moving_backward_relative_to_forward
 * Entry: 0041cd90
 * Signature: bool __cdecl is_ai_vehicle_moving_backward_relative_to_forward(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Tests whether vehicle velocity/direction is opposite
   its forward vector. */

bool __cdecl is_ai_vehicle_moving_backward_relative_to_forward(int param_1)

{
  bool bVar1;
  float *pfVar2;
  float10 fVar3;
  undefined4 local_24 [3];
  int local_18;
  float local_10;
  float local_c;
  float local_8;
  
  local_18 = get_vehicle_runtime_context(param_1);
  if (*(float *)(local_18 + 0xe8) <= _DAT_004bcae8) {
    bVar1 = false;
  }
  else {
    pfVar2 = (float *)copy_object_local_translation_vec3(local_24,param_1 + 0x18);
    local_10 = *pfVar2;
    local_c = pfVar2[1];
    local_8 = pfVar2[2];
    fVar3 = dot_product_vec3(&local_10,(float *)(local_18 + 0xbc));
    bVar1 = fVar3 + (float10)_DAT_004bcaf0 < (float10)_DAT_004bcaf8;
  }
  return bVar1;
}


