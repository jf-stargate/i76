/*
 * Program: i76.exe
 * Function: clear_effect_target_collision_link_lists
 * Entry: 0043e390
 * Signature: undefined __stdcall clear_effect_target_collision_link_lists(void)
 */


/* cgpt rename v3: Frees all collision/geometry link nodes for registered effect targets and clears
   the global target list. */

void clear_effect_target_collision_link_lists(void)

{
  int iVar1;
  LPVOID pvVar2;
  LPVOID lpMem;
  
  while (DAT_0052b94c != (int *)0x0) {
    iVar1 = DAT_0052b94c[2];
    lpMem = *(LPVOID *)(iVar1 + 0x18);
    while (lpMem != (LPVOID)0x0) {
      pvVar2 = *(LPVOID *)((int)lpMem + 8);
      HeapFree(DAT_00608be8,0,lpMem);
      lpMem = pvVar2;
    }
    *(undefined4 *)(iVar1 + 0x18) = 0;
    unlink_and_free_linked_list_node_3field((int *)&DAT_0052b94c,DAT_0052b94c);
  }
  return;
}


