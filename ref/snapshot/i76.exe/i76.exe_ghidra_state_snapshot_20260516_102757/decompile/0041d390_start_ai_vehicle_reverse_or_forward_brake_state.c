/*
 * Program: i76.exe
 * Function: start_ai_vehicle_reverse_or_forward_brake_state
 * Entry: 0041d390
 * Signature: undefined __cdecl start_ai_vehicle_reverse_or_forward_brake_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Starts braking and toggles forward/reverse drive mode
   based on current reverse flag. */

void __cdecl start_ai_vehicle_reverse_or_forward_brake_state(float param_1)

{
  int iVar1;
  int iVar2;
  
  reset_ai_tactics_weight_scalars_to_one((int)param_1);
  iVar1 = get_vehicle_runtime_context((int)param_1);
  set_vehicle_brake_to_max_safe_value(param_1);
  iVar2 = is_float_nearly_zero_1e_minus4(*(float *)(iVar1 + 0xe8) - _DAT_004bcae4);
  if (iVar2 == 0) {
    *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
    vehicle_specials_state_getter_helper_00467370((int)param_1,3);
  }
  else {
    *(undefined4 *)(iVar1 + 0xe8) = 0xbf800000;
    vehicle_specials_state_getter_helper_00467370((int)param_1,1);
  }
  return;
}


