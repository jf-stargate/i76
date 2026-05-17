/*
 * Program: i76.exe
 * Function: close_zfsf_archive
 * Entry: 004b9af0
 * Signature: undefined4 __cdecl close_zfsf_archive(undefined4 * param_1)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Closes the archive FILE pointer and
   releases directory-offset and live-record arrays from a ZFSF archive handle. */

undefined4 __cdecl close_zfsf_archive(undefined4 *param_1)

{
  fclose((FILE *)*param_1);
  HeapFree(g_process_heap,0,(LPVOID)param_1[9]);
  HeapFree(g_process_heap,0,(LPVOID)param_1[10]);
  HeapFree(g_process_heap,0,param_1);
  return 1;
}


