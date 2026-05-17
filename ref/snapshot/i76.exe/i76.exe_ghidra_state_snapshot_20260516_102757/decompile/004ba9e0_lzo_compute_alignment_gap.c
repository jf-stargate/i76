/*
 * Program: i76.exe
 * Function: lzo_compute_alignment_gap
 * Entry: 004ba9e0
 * Signature: int __cdecl lzo_compute_alignment_gap(int param_1, uint param_2)
 */


/* [cgpt i76.exe LZO1Y labels v24; confidence=medium-high] Small LZO helper returning alignment gap
   for a pointer and alignment value. */

int __cdecl lzo_compute_alignment_gap(int param_1,uint param_2)

{
  return (((param_2 - 1) + param_1) / param_2) * param_2 - param_1;
}


