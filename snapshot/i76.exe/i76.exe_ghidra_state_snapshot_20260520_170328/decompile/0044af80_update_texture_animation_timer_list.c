/*
 * Program: i76.exe
 * Function: update_texture_animation_timer_list
 * Entry: 0044af80
 * Signature: undefined __stdcall update_texture_animation_timer_list(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Per-frame texanm timer list walker.
   Releases invalid object references, invokes animation callbacks, and frees expired timer records.
    */

void update_texture_animation_timer_list(void)

{
  undefined4 *puVar1;
  undefined4 *lpMem;
  LPVOID pvVar2;
  
  lpMem = g_texture_animation_timer_list_head;
  while (lpMem != (undefined4 *)0x0) {
    pvVar2 = release_world_object_tree_reference((LPVOID)*lpMem,s_texanm_004f2724);
    *lpMem = pvVar2;
    puVar1 = (undefined4 *)lpMem[8];
    if (pvVar2 == (LPVOID)0x0) {
      if (g_texture_animation_timer_list_head == lpMem) {
        g_texture_animation_timer_list_head = puVar1;
        if (lpMem[8] != 0) {
          *(undefined4 *)(lpMem[8] + 0x1c) = 0;
        }
      }
      else {
        if (puVar1 != (undefined4 *)0x0) {
          puVar1[7] = lpMem[7];
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
    else {
      (*(code *)lpMem[5])(pvVar2,lpMem + 1,lpMem[6]);
      lpMem = puVar1;
    }
  }
  return;
}


