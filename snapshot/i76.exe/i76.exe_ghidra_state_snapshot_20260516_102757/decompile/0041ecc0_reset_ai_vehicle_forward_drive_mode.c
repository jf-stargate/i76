/*
 * Program: i76.exe
 * Function: reset_ai_vehicle_forward_drive_mode
 * Entry: 0041ecc0
 * Signature: undefined __cdecl reset_ai_vehicle_forward_drive_mode(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Clears override and enters forward drive mode 3. */

void __cdecl reset_ai_vehicle_forward_drive_mode(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


