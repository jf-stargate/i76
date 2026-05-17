/*
 * Program: i76.exe
 * Function: chunk_manager_update_log_tag
 * Entry: 004a2cd0
 * Signature: undefined __stdcall chunk_manager_update_log_tag(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence chnkmgr */

void chunk_manager_update_log_tag(void)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005aaad0;
  do {
    lpMem = (LPVOID)*puVar2;
    while (lpMem != (LPVOID)0x0) {
      unlink_and_release_world_object_node_refcounted
                (*(LPVOID *)((int)lpMem + 8),s_chnkmgr_004fe71c);
      pvVar1 = *(LPVOID *)((int)lpMem + 0x10);
      HeapFree(DAT_005aab04,0,lpMem);
      lpMem = pvVar1;
    }
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < 0x5aab04);
  HeapDestroy(DAT_005aab04);
  return;
}


