/*
 * Program: i76.exe
 * Function: get_global_heap_handle
 * Entry: 00495060
 * Signature: bool __stdcall get_global_heap_handle(void)
 */


/* i76 second-pass rename
   old_name: FUN_00495060
   suggested_name: get_global_heap_handle
   basis: Tiny helper called before HeapAlloc/cache operations; likely returns global heap/context.
    */

bool get_global_heap_handle(void)

{
  return DAT_005dd2a8 == 1;
}


