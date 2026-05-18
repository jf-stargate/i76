/*
 * Program: i76.exe
 * Function: vehicle_specials_state_getter_helper_00467370
 * Entry: 00467370
 * Signature: undefined __cdecl vehicle_specials_state_getter_helper_00467370(int param_1, undefined4 param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials state getter helper
   based on adjacent named subsystem context. */

void __cdecl vehicle_specials_state_getter_helper_00467370(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0x6c) == 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x104) = param_2;
  }
  return;
}


