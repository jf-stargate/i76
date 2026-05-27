/*
 * Program: i76.exe
 * Function: release_vehicle_runtime_context
 * Entry: 0045f3d0
 * Signature: undefined __cdecl release_vehicle_runtime_context(LPVOID param_1)
 */


/* [cgpt i76.exe world/runtime table rename v17; confidence=MEDIUM-HIGH] Shared cleanup helper
   called by vehicle class release and damaged-part cleanup paths; verify exact field layout in the
   next helper pass. */

void __cdecl release_vehicle_runtime_context(LPVOID param_1)

{
  HeapFree(DAT_0054ad38,0,param_1);
  return;
}


