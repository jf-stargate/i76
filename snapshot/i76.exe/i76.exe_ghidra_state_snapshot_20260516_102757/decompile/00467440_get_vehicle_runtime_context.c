/*
 * Program: i76.exe
 * Function: get_vehicle_runtime_context
 * Entry: 00467440
 * Signature: undefined4 __cdecl get_vehicle_runtime_context(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Returns vehicle class
   runtime context pointer from world object runtime data. */

undefined4 __cdecl get_vehicle_runtime_context(int param_1)

{
                    /* I76 semantic baseline: get_vehicle_runtime_context
                       Returns vehicle runtime context from world_object+0x70. */
  return *(undefined4 *)(param_1 + 0x70);
}


