/*
 * Program: i76.exe
 * Function: release_effect_target_collision_links
 * Entry: 0043e4c0
 * Signature: undefined __cdecl release_effect_target_collision_links(int * param_1)
 */


/* cgpt rename v3: Frees collision link nodes for a single effect-target record and removes it from
   the global effect-target list. */

void __cdecl release_effect_target_collision_links(int *param_1)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  int *piVar2;
  
  if (((10 < *(int *)(*param_1 + 0x6c)) && (*(int *)(*param_1 + 0x6c) < 0xe)) &&
     (piVar2 = DAT_0052b94c, DAT_0052b94c != (int *)0x0)) {
    while ((int *)piVar2[2] != param_1) {
      piVar2 = (int *)*piVar2;
      if (piVar2 == (int *)0x0) {
        return;
      }
    }
    lpMem = (LPVOID)param_1[6];
    while (lpMem != (LPVOID)0x0) {
      pvVar1 = *(LPVOID *)((int)lpMem + 8);
      HeapFree(DAT_00608be8,0,lpMem);
      lpMem = pvVar1;
    }
    param_1[6] = 0;
    unlink_and_free_linked_list_node_3field((int *)&DAT_0052b94c,piVar2);
  }
  return;
}


