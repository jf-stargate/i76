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
  return *(undefined4 *)(param_1 + 0x70);
}


