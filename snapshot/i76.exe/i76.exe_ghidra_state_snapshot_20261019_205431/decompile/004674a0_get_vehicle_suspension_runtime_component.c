/*
 * Program: i76.exe
 * Function: get_vehicle_suspension_runtime_component
 * Entry: 004674a0
 * Signature: undefined4 __cdecl get_vehicle_suspension_runtime_component(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Returns vehicle suspension
   runtime component from vehicle context object. */

undefined4 __cdecl get_vehicle_suspension_runtime_component(int param_1)

{
                    /* I76 semantic baseline: get_vehicle_suspension_runtime_component
                       Returns suspension runtime component. */
  return *(undefined4 *)(*(int *)(param_1 + 0x3c8) + 0x70);
}


