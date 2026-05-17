/*
 * Program: i76.exe
 * Function: xfree_global_heap
 * Entry: 00499d40
 * Signature: undefined4 __cdecl xfree_global_heap(LPVOID param_1)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Small allocation wrapper around
   process/global heap free path. */

undefined4 __cdecl xfree_global_heap(LPVOID param_1)

{
  if (DAT_005a7cc0 != (HANDLE)0x0) {
    HeapFree(DAT_005a7cc0,0,param_1);
  }
  return 1;
}


