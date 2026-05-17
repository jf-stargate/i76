/*
 * Program: i76.exe
 * Function: vehicle_specials_display_counter_helper_004676b0
 * Entry: 004676b0
 * Signature: undefined __stdcall vehicle_specials_display_counter_helper_004676b0(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials display counter
   helper based on adjacent named subsystem context. */

void vehicle_specials_display_counter_helper_004676b0(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x18);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 10;
    puVar1[3] = 10;
    puVar1[4] = 0;
  }
  return;
}


