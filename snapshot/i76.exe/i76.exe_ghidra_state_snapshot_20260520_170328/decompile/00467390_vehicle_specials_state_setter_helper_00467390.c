/*
 * Program: i76.exe
 * Function: vehicle_specials_state_setter_helper_00467390
 * Entry: 00467390
 * Signature: undefined __cdecl vehicle_specials_state_setter_helper_00467390(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials state setter helper
   based on adjacent named subsystem context. */

void __cdecl vehicle_specials_state_setter_helper_00467390(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x104);
  if (iVar1 < 5) {
    *(int *)(*(int *)(param_1 + 0x70) + 0x104) = iVar1 + 1;
  }
  return;
}


