/*
 * Program: i76.exe
 * Function: start_ai_vehicle_reverse_from_current_forward_state
 * Entry: 0041e8b0
 * Signature: undefined __cdecl start_ai_vehicle_reverse_from_current_forward_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Starts reverse-mode AI state using current forward
   vector as stored position/direction baseline. */

void __cdecl start_ai_vehicle_reverse_from_current_forward_state(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined4 local_1c [3];
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_10 = get_vehicle_runtime_context(param_1);
  local_8 = *(int *)(local_10 + 0x108);
  fVar2 = get_runtime_time_seconds();
  *(float *)(local_8 + 0xa82c) = (float)(fVar2 + (float10)_DAT_004bcab0);
  *(undefined4 *)(local_8 + 0xa998) = param_2;
  puVar1 = (undefined4 *)copy_object_local_translation_vec3(local_1c,param_1 + 0x18);
  *(undefined4 *)(local_8 + 0xa970) = *puVar1;
  *(undefined4 *)(local_8 + 0xa974) = puVar1[1];
  *(undefined4 *)(local_8 + 0xa978) = puVar1[2];
  *(undefined4 *)(local_8 + 0xa97c) = 0;
  *(undefined4 *)(local_10 + 0xf0) = 0;
  *(undefined4 *)(local_10 + 0xe8) = 0xbf800000;
  vehicle_specials_state_getter_helper_00467370(param_1,1);
  return;
}


