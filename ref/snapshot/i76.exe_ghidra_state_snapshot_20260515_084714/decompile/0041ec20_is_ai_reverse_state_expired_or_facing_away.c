/*
 * Program: i76.exe
 * Function: is_ai_reverse_state_expired_or_facing_away
 * Entry: 0041ec20
 * Signature: bool __cdecl is_ai_reverse_state_expired_or_facing_away(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Checks reverse-state timer and forward-vector dot
   product against stored direction. */

bool __cdecl is_ai_reverse_state_expired_or_facing_away(int param_1)

{
  bool bVar1;
  float *pfVar2;
  float10 fVar3;
  undefined4 local_20 [3];
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  local_8 = 0;
  local_8 = get_ai_vehicle_behavior_state_block(param_1);
  fVar3 = get_runtime_time_seconds();
  if (fVar3 <= (float10)*(float *)(local_8 + 0xa82c)) {
    pfVar2 = (float *)copy_object_local_translation_vec3(local_20,param_1 + 0x18);
    local_14 = *pfVar2;
    local_10 = pfVar2[1];
    local_c = pfVar2[2];
    fVar3 = dot_product_vec3(&local_14,(float *)(local_8 + 0xa970));
    bVar1 = fVar3 < (float10)_DAT_004bcb60;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}


