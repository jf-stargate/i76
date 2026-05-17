/*
 * Program: i76.exe
 * Function: radar_context_helper_0045f3b0
 * Entry: 0045f3b0
 * Signature: LPVOID __cdecl radar_context_helper_0045f3b0(SIZE_T param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_radar_context_helper_0045f3b0. Shorten readability
   label. */

LPVOID __cdecl radar_context_helper_0045f3b0(SIZE_T param_1)

{
  LPVOID pvVar1;
  
  if (DAT_0054ad38 != (HANDLE)0x0) {
    pvVar1 = HeapAlloc(DAT_0054ad38,0,param_1);
    return pvVar1;
  }
  return (LPVOID)0x0;
}


