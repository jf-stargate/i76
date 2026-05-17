/*
 * Program: i76.exe
 * Function: keyboard_joystick_input_binding_context_helper_0044ece0
 * Entry: 0044ece0
 * Signature: undefined __cdecl keyboard_joystick_input_binding_context_helper_0044ece0(int param_1)
 */


/* cgpt label refinement v18: was input_device_binding_keyboard_joystick_input_helper_0044ece0.
   Shorten readability label while preserving keyboard/joystick input binding context. */

void __cdecl keyboard_joystick_input_binding_context_helper_0044ece0(int param_1)

{
  if (param_1 == 1) {
    DAT_0053eb4c = ImmAssociateContext(DAT_005dcf7c,(HIMC)0x0);
    return;
  }
  if (DAT_0053eb4c != (HIMC)0x0) {
    ImmAssociateContext(DAT_005dcf7c,DAT_0053eb4c);
    DAT_0053eb4c = (HIMC)0x0;
  }
  return;
}


