/*
 * Program: i76.exe
 * Function: input_action_state_clearer_helper_0044de40
 * Entry: 0044de40
 * Signature: undefined4 __stdcall input_action_state_clearer_helper_0044de40(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: input action state clearer helper
   based on prior focused closure context. */

undefined4 input_action_state_clearer_helper_0044de40(void)

{
  DAT_0053681c = 1;
  if (((byte)g_runtime_display_input_mode & 0x3e) != 0) {
    DAT_00536818 = 0;
    return 0;
  }
  if (g_pending_input_action_code != 0) {
    if ((&DAT_0053db30)[g_pending_input_action_code] == '\"') {
      DAT_00536818 = 1;
      keyboard_joystick_input_binding_context_helper_0044eca0();
      g_pending_input_action_code = 0;
      return DAT_00536818;
    }
    if ((&DAT_0053db30)[g_pending_input_action_code] == '3') {
      mission_flow_map_context_helper_0049d140();
    }
    keyboard_joystick_input_binding_context_helper_0044eca0();
    g_pending_input_action_code = 0;
  }
  return DAT_00536818;
}


