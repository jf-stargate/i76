/*
 * Program: i76.exe
 * Function: xalloc_global_heap
 * Entry: 00499ce0
 * Signature: undefined __cdecl xalloc_global_heap(SIZE_T param_1)
 */


/* cgpt rename v2: Thin global HeapAlloc wrapper paired with existing xfree_global_heap. */

void __cdecl xalloc_global_heap(SIZE_T param_1)

{
  HeapAlloc(DAT_005a7cc0,0,param_1);
  return;
}


