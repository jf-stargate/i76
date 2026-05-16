/*
 * Program: i76.exe
 * Function: get_tire_compression_visual_offset
 * Entry: 0046dd70
 * Signature: float10 __cdecl get_tire_compression_visual_offset(int param_1)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Tire child accessor for
   visual compression/contact offset. */

float10 __cdecl get_tire_compression_visual_offset(int param_1)

{
  return (float10)*(float *)(*(int *)(param_1 + 0x70) + 0x24);
}


