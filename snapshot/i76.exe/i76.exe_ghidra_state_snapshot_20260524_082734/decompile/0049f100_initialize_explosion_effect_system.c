/*
 * Program: i76.exe
 * Function: initialize_explosion_effect_system
 * Entry: 0049f100
 * Signature: undefined __stdcall initialize_explosion_effect_system(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence explsn */

void initialize_explosion_effect_system(void)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID lpMem;
  undefined4 *local_4;
  
  local_4 = &g_explosion_runtime_state;
  do {
    lpMem = (LPVOID)*local_4;
    while (lpMem != (LPVOID)0x0) {
      draw_classifier_display(*(LPVOID *)((int)lpMem + 8));
      unlink_and_release_world_object_node_refcounted(*(LPVOID *)((int)lpMem + 8),s_explsn_004fe6e0)
      ;
      pvVar2 = *(LPVOID *)((int)lpMem + 0x1c);
      while (pvVar2 != (LPVOID)0x0) {
        pvVar1 = *(LPVOID *)((int)pvVar2 + 0x60);
        *(undefined4 *)((int)pvVar2 + 0x60) = 0;
        *(undefined4 *)((int)pvVar2 + 0x68) = 0;
        draw_classifier_display(pvVar2);
        unlink_and_release_world_object_node_refcounted(pvVar2,s_explsn_004fe6e0);
        pvVar2 = pvVar1;
      }
      *(undefined4 *)((int)lpMem + 0x1c) = 0;
      pvVar2 = *(LPVOID *)((int)lpMem + 0x20);
      HeapFree(DAT_005a80f8,0,lpMem);
      lpMem = pvVar2;
    }
    local_4 = local_4 + 1;
  } while ((int)local_4 < 0x5a80f4);
  HeapDestroy(DAT_005a80f4);
  HeapDestroy(DAT_005a80f8);
  return;
}


