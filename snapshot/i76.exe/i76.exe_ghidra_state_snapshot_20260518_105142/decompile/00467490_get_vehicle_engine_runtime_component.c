/*
 * Program: i76.exe
 * Function: get_vehicle_engine_runtime_component
 * Entry: 00467490
 * Signature: undefined4 __cdecl get_vehicle_engine_runtime_component(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Returns vehicle engine
   runtime component from vehicle context object. */

undefined4 __cdecl get_vehicle_engine_runtime_component(int param_1)

{
                    /* I76 semantic baseline: get_vehicle_engine_runtime_component
                       Returns engine runtime component. */
  return *(undefined4 *)(*(int *)(param_1 + 0x3c4) + 0x70);
}


