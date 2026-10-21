/*
 * Program: i76.exe
 * Function: vehicle_specials_display_render_context_helper_00467760
 * Entry: 00467760
 * Signature: undefined __cdecl vehicle_specials_display_render_context_helper_00467760(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials display render
   context helper based on adjacent named subsystem context. */

void __cdecl vehicle_specials_display_render_context_helper_00467760(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x70);
  *piVar1 = param_2;
  if (param_2 == 2) {
    piVar1[1] = 3;
    return;
  }
  if (param_2 == 1) {
    piVar1[1] = 5;
    return;
  }
  piVar1[1] = 1;
  return;
}


