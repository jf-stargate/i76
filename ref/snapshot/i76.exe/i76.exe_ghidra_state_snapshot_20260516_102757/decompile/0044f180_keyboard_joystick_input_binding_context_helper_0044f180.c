/*
 * Program: i76.exe
 * Function: keyboard_joystick_input_binding_context_helper_0044f180
 * Entry: 0044f180
 * Signature: float10 __cdecl keyboard_joystick_input_binding_context_helper_0044f180(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was input_device_binding_keyboard_joystick_input_helper_0044f180.
   Shorten readability label while preserving keyboard/joystick input binding context. */

float10 __cdecl keyboard_joystick_input_binding_context_helper_0044f180(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)param_2 - (float10)param_1;
  if ((float10)_DAT_004bd8bc < fVar1) {
    return fVar1 - (float10)_DAT_004bd8c0;
  }
  if (fVar1 < (float10)_DAT_004bd8c4) {
    fVar1 = fVar1 - (float10)_DAT_004bd8c8;
  }
  return fVar1;
}


