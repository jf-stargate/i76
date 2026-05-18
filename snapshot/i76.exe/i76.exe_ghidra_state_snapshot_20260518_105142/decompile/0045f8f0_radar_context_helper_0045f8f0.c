/*
 * Program: i76.exe
 * Function: radar_context_helper_0045f8f0
 * Entry: 0045f8f0
 * Signature: undefined __cdecl radar_context_helper_0045f8f0(LPVOID param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_radar_context_helper_0045f8f0. Shorten readability
   label. */

void __cdecl radar_context_helper_0045f8f0(LPVOID param_1)

{
  HeapFree(DAT_0054b1f4,0,*(LPVOID *)((int)param_1 + 8));
  if (param_1 != (LPVOID)0x0) {
    release_bitmap_surface_context((int *)((int)param_1 + 0x80));
    HeapFree(DAT_0054b1f0,0,param_1);
  }
  return;
}


