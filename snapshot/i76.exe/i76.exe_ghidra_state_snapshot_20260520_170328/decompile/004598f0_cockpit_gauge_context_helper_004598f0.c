/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_004598f0
 * Entry: 004598f0
 * Signature: undefined __cdecl cockpit_gauge_context_helper_004598f0(LPVOID param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_004598f0. Remove duplicated
   cockpit wording. */

void __cdecl cockpit_gauge_context_helper_004598f0(LPVOID param_1)

{
  if (param_1 != (LPVOID)0x0) {
    xfree_global_heap(param_1);
  }
  return;
}


