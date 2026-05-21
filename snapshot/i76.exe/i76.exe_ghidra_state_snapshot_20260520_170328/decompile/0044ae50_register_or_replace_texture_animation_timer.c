/*
 * Program: i76.exe
 * Function: register_or_replace_texture_animation_timer
 * Entry: 0044ae50
 * Signature: undefined4 __cdecl register_or_replace_texture_animation_timer(int param_1, char * param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Registers or replaces a
   runtime texture animation timer for a texture slot binding. */

undefined4 __cdecl
register_or_replace_texture_animation_timer(int param_1,char *param_2,int param_3,int param_4)

{
  int *piVar1;
  int *lpMem;
  int iVar2;
  int *piVar3;
  
  piVar3 = g_texture_animation_timer_list_head;
  while (lpMem = piVar3, lpMem != (int *)0x0) {
    piVar3 = (int *)lpMem[8];
    if ((*lpMem == param_1) && (iVar2 = _stricmp((char *)(lpMem + 1),param_2), iVar2 == 0)) {
      finalize_released_world_object_after_damage((LPVOID)*lpMem,s_texanm_004f2724);
      piVar1 = (int *)lpMem[8];
      if (g_texture_animation_timer_list_head == lpMem) {
        g_texture_animation_timer_list_head = piVar1;
        if (lpMem[8] != 0) {
          *(undefined4 *)(lpMem[8] + 0x1c) = 0;
        }
      }
      else {
        if (piVar1 != (int *)0x0) {
          piVar1[7] = lpMem[7];
        }
        if (lpMem[7] != 0) {
          *(int *)(lpMem[7] + 0x20) = lpMem[8];
        }
      }
      lpMem[8] = 0;
      lpMem[7] = 0;
      if ((code *)lpMem[5] == update_texture_animation_timer) {
        xfree_global_heap((LPVOID)lpMem[6]);
      }
      HeapFree(g_texture_animation_timer_heap,0,lpMem);
    }
  }
  piVar3 = HeapAlloc(g_texture_animation_timer_heap,0,0x24);
  if (piVar3 == (int *)0x0) {
    return 0;
  }
  increment_refcount_recursive_for_object_tree(param_1,s_texanm_004f2724);
  *piVar3 = param_1;
  strncpy((char *)(piVar3 + 1),param_2,0xf);
  piVar3[5] = param_3;
  piVar3[6] = param_4;
  piVar3[7] = 0;
  piVar3[8] = (int)g_texture_animation_timer_list_head;
  if (g_texture_animation_timer_list_head != (int *)0x0) {
    g_texture_animation_timer_list_head[7] = (int)piVar3;
  }
  g_texture_animation_timer_list_head = piVar3;
  return 1;
}


