/*
 * Program: i76.exe
 * Function: initialize_vehicle_wheel_contact_state_block
 * Entry: 00434670
 * Signature: undefined __cdecl initialize_vehicle_wheel_contact_state_block(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Initializes a vehicle wheel/contact state block and its nested
   physics/contact fields. */

void __cdecl initialize_vehicle_wheel_contact_state_block(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  effect_target_list_scan_context_helper_004382e0(param_1 + 2);
  return;
}


