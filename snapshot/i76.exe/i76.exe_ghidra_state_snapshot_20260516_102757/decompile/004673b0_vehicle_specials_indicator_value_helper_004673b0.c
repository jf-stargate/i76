/*
 * Program: i76.exe
 * Function: vehicle_specials_indicator_value_helper_004673b0
 * Entry: 004673b0
 * Signature: undefined __cdecl vehicle_specials_indicator_value_helper_004673b0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials indicator value
   helper based on adjacent named subsystem context. */

void __cdecl vehicle_specials_indicator_value_helper_004673b0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x104);
  if (0 < iVar1) {
    *(int *)(*(int *)(param_1 + 0x70) + 0x104) = iVar1 + -1;
  }
  return;
}


