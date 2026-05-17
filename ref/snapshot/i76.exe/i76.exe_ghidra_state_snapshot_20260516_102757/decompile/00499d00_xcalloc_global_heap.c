/*
 * Program: i76.exe
 * Function: xcalloc_global_heap
 * Entry: 00499d00
 * Signature: undefined __cdecl xcalloc_global_heap(int param_1, int param_2)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Small allocation wrapper around
   process/global heap calloc-like path. */

void __cdecl xcalloc_global_heap(int param_1,int param_2)

{
  HeapAlloc(DAT_005a7cc0,0,param_2 * param_1);
  return;
}


