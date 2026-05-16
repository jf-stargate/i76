/*
 * Program: i76.exe
 * Function: vehicle_config_loader_context_helper_004ad600
 * Entry: 004ad600
 * Signature: undefined __cdecl vehicle_config_loader_context_helper_004ad600(undefined4 * param_1)
 */


/* cgpt label refinement v20: was vehicle_config_loading_context_helper_004ad600. Shorten
   readability label. */

void __cdecl vehicle_config_loader_context_helper_004ad600(undefined4 *param_1)

{
  if ((LPVOID)param_1[1] != (LPVOID)0x0) {
    HeapFree((HANDLE)*param_1,0,(LPVOID)param_1[1]);
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  HeapDestroy((HANDLE)*param_1);
  return;
}


