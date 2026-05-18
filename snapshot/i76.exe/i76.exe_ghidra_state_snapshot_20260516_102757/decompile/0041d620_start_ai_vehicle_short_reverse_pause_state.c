/*
 * Program: i76.exe
 * Function: start_ai_vehicle_short_reverse_pause_state
 * Entry: 0041d620
 * Signature: undefined __cdecl start_ai_vehicle_short_reverse_pause_state(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Toggles forward/reverse mode, clears drive input, and
   starts a 1.5-second secondary timer. */

void __cdecl start_ai_vehicle_short_reverse_pause_state(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = get_ai_vehicle_behavior_state_block(param_1);
  iVar3 = is_float_nearly_zero_1e_minus4(*(float *)(iVar1 + 0xe8) - _DAT_004bcae4);
  if (iVar3 == 0) {
    *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
    vehicle_specials_state_getter_helper_00467370(param_1,3);
  }
  else {
    *(undefined4 *)(iVar1 + 0xe8) = 0xbf800000;
    vehicle_specials_state_getter_helper_00467370(param_1,1);
  }
  clear_vehicle_throttle_brake_command(param_1);
  fVar4 = get_gameplay_runtime_seconds();
  *(float *)(iVar2 + 0x9d34) = (float)(fVar4 + (float10)_DAT_004bcb04);
  return;
}


