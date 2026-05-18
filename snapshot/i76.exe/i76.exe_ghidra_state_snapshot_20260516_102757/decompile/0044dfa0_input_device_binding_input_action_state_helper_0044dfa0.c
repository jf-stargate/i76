/*
 * Program: i76.exe
 * Function: input_device_binding_input_action_state_helper_0044dfa0
 * Entry: 0044dfa0
 * Signature: undefined __cdecl input_device_binding_input_action_state_helper_0044dfa0(undefined4 param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely input_device_binding /
   input_action_state_helper based on address neighborhood and prior focused closure context. */

void __cdecl input_device_binding_input_action_state_helper_0044dfa0(undefined4 param_1)

{
  if (DAT_0053eb30 == 0) {
    dispatch_runtime_camera_mode_activation_by_id(param_1,0xe);
    DAT_0053eb30 = 1;
    return;
  }
  dispatch_runtime_camera_mode_activation_by_id(param_1,DAT_0053eb34);
  DAT_0053eb30 = 0;
  return;
}


