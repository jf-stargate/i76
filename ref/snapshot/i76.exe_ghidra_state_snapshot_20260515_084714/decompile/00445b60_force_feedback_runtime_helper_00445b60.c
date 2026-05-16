/*
 * Program: i76.exe
 * Function: force_feedback_runtime_helper_00445b60
 * Entry: 00445b60
 * Signature: undefined __stdcall force_feedback_runtime_helper_00445b60(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was player_force_feedback_force_feedback_helper_00445b60. Remove
   duplicated force_feedback wording. */

void force_feedback_runtime_helper_00445b60(void)

{
  if (g_runtime_parameter_heap_ready != 0) {
    _DAT_0052bbd8 = 0;
    _DAT_004f2330 = 0;
    dispatch_force_feedback_effect();
    return;
  }
  return;
}


