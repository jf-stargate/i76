/*
 * Program: i76.exe
 * Function: xrealloc_global_heap
 * Entry: 00499d20
 * Signature: undefined __cdecl xrealloc_global_heap(LPVOID param_1, SIZE_T param_2)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Small allocation wrapper around
   process/global heap realloc-like path. */

void __cdecl xrealloc_global_heap(LPVOID param_1,SIZE_T param_2)

{
  HeapReAlloc(DAT_005a7cc0,0,param_1,param_2);
  return;
}


