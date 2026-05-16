/*
 * Program: i76.exe
 * Function: destroy_texture_animation_list
 * Entry: 0044b100
 * Signature: undefined __stdcall destroy_texture_animation_list(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: texanm and HeapFree */

void destroy_texture_animation_list(void)

{
  undefined4 *puVar1;
  undefined4 *lpMem;
  
  lpMem = g_texture_animation_timer_list_head;
  while (lpMem != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)lpMem[8];
    finalize_released_world_object_after_damage((LPVOID)*lpMem,s_texanm_004f2724);
    if (g_texture_animation_timer_list_head == lpMem) {
      g_texture_animation_timer_list_head = (undefined4 *)lpMem[8];
      if (lpMem[8] != 0) {
        *(undefined4 *)(lpMem[8] + 0x1c) = 0;
      }
    }
    else {
      if (lpMem[8] != 0) {
        *(undefined4 *)(lpMem[8] + 0x1c) = lpMem[7];
      }
      if (lpMem[7] != 0) {
        *(undefined4 *)(lpMem[7] + 0x20) = lpMem[8];
      }
    }
    lpMem[8] = 0;
    lpMem[7] = 0;
    if ((code *)lpMem[5] == update_texture_animation_timer) {
      xfree_global_heap((LPVOID)lpMem[6]);
    }
    HeapFree(g_texture_animation_timer_heap,0,lpMem);
    lpMem = puVar1;
  }
  g_texture_animation_timer_list_head = (undefined4 *)0x0;
  HeapDestroy(g_texture_animation_timer_heap);
  return;
}


