/*
 * Program: i76.exe
 * Function: find_loaded_vehicle_runtime_index_by_world_object
 * Entry: 004a5170
 * Signature: int __cdecl find_loaded_vehicle_runtime_index_by_world_object(int param_1)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Scans loaded vehicle runtime
   table for a matching world object pointer and returns index or -1. */

int __cdecl find_loaded_vehicle_runtime_index_by_world_object(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar2 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar2 == param_1) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  return -1;
}


