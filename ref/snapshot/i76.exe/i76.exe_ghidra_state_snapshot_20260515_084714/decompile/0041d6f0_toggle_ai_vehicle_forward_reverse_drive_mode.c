/*
 * Program: i76.exe
 * Function: toggle_ai_vehicle_forward_reverse_drive_mode
 * Entry: 0041d6f0
 * Signature: undefined __cdecl toggle_ai_vehicle_forward_reverse_drive_mode(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Toggles vehicle drive direction flag and updates
   drive mode animation/state. */

void __cdecl toggle_ai_vehicle_forward_reverse_drive_mode(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = is_float_nearly_zero_1e_minus4(*(float *)(iVar1 + 0xe8) - _DAT_004bcae4);
  if (iVar2 == 0) {
    *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
    vehicle_specials_state_getter_helper_00467370(param_1,3);
  }
  else {
    *(undefined4 *)(iVar1 + 0xe8) = 0xbf800000;
    vehicle_specials_state_getter_helper_00467370(param_1,1);
  }
  return;
}


