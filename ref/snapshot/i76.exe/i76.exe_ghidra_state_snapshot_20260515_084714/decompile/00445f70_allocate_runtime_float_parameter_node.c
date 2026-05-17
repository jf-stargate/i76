/*
 * Program: i76.exe
 * Function: allocate_runtime_float_parameter_node
 * Entry: 00445f70
 * Signature: undefined4 * __cdecl allocate_runtime_float_parameter_node(undefined4 * param_1)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Allocates a 0x20-byte runtime float
   parameter node from g_runtime_parameter_heap and links it into the caller-provided list head. */

undefined4 * __cdecl allocate_runtime_float_parameter_node(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  if (g_runtime_parameter_heap_ready == 0) {
    return (undefined4 *)0x0;
  }
  puVar1 = HeapAlloc(g_runtime_parameter_heap,0,0x20);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[4] = 0;
    puVar1[5] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    if (puVar1 != (undefined4 *)0x0) {
      puVar1[6] = *param_1;
      *param_1 = puVar1;
      puVar1[7] = 0;
      if (puVar1[6] != 0) {
        *(undefined4 **)(puVar1[6] + 0x1c) = puVar1;
      }
    }
  }
  return puVar1;
}


