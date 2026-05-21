/*
 * Program: i76.exe
 * Function: release_texture_animation_record
 * Entry: 0044b030
 * Signature: undefined4 __cdecl release_texture_animation_record(int param_1, char * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: texanm and HeapFree */

undefined4 __cdecl release_texture_animation_record(int param_1,char *param_2)

{
  int *piVar1;
  int iVar2;
  int *lpMem;
  
  lpMem = g_texture_animation_timer_list_head;
  if (g_texture_animation_timer_list_head == (int *)0x0) {
    return 0;
  }
  while ((*lpMem != param_1 || (iVar2 = _stricmp((char *)(lpMem + 1),param_2), iVar2 != 0))) {
    piVar1 = lpMem + 8;
    lpMem = (int *)*piVar1;
    if ((int *)*piVar1 == (int *)0x0) {
      return 0;
    }
  }
  finalize_released_world_object_after_damage((LPVOID)*lpMem,s_texanm_004f2724);
  if (g_texture_animation_timer_list_head == lpMem) {
    g_texture_animation_timer_list_head = (int *)lpMem[8];
    if (lpMem[8] != 0) {
      *(undefined4 *)(lpMem[8] + 0x1c) = 0;
    }
    lpMem[8] = 0;
    lpMem[7] = 0;
  }
  else {
    if (lpMem[8] != 0) {
      *(int *)(lpMem[8] + 0x1c) = lpMem[7];
    }
    if (lpMem[7] != 0) {
      *(int *)(lpMem[7] + 0x20) = lpMem[8];
    }
    lpMem[8] = 0;
    lpMem[7] = 0;
  }
  if ((code *)lpMem[5] == update_texture_animation_timer) {
    xfree_global_heap((LPVOID)lpMem[6]);
  }
  HeapFree(g_texture_animation_timer_heap,0,lpMem);
  return 1;
}


