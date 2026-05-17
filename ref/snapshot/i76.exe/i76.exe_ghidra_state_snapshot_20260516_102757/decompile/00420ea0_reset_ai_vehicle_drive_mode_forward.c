/*
 * Program: i76.exe
 * Function: reset_ai_vehicle_drive_mode_forward
 * Entry: 00420ea0
 * Signature: undefined __cdecl reset_ai_vehicle_drive_mode_forward(int param_1)
 */


/* cgpt readability rename v13 set A: Resets vehicle runtime speed/drive fields and enters drive
   mode 3. */

void __cdecl reset_ai_vehicle_drive_mode_forward(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


