/*
 * Program: i76.exe
 * Function: vehicle_specials_display_texture_context_helper_004677d0
 * Entry: 004677d0
 * Signature: undefined __cdecl vehicle_specials_display_texture_context_helper_004677d0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials display texture
   context helper based on adjacent named subsystem context. */

void __cdecl vehicle_specials_display_texture_context_helper_004677d0(int param_1)

{
  int *piVar1;
  
  if (param_1 != 0) {
    piVar1 = (int *)(*(int *)(param_1 + 0x70) + 4);
    *piVar1 = *piVar1 + -1;
  }
  return;
}


