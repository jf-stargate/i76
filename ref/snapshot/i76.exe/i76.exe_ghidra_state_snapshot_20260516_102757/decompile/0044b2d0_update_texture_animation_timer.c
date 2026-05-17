/*
 * Program: i76.exe
 * Function: update_texture_animation_timer
 * Entry: 0044b2d0
 * Signature: undefined __cdecl update_texture_animation_timer(uint param_1, byte * param_2, float * param_3)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Advances texture animation
   timer state, supports ping-pong/reverse/one-shot behavior, updates binding frame, and removes
   expired timers. */

void __cdecl update_texture_animation_timer(uint param_1,byte *param_2,float *param_3)

{
  uint *puVar1;
  float fVar2;
  int iVar3;
  uint *lpMem;
  float10 fVar4;
  
  fVar4 = get_network_or_session_runtime_seconds();
  if ((float10)*param_3 < fVar4) {
    fVar4 = get_network_or_session_runtime_seconds();
    if ((float10)*param_3 < fVar4) {
      do {
        *param_3 = *param_3 + param_3[1];
        if (param_3[5] == 2.8026e-45) {
          if ((int)param_3[2] + -1 <= (int)param_3[3]) {
            if ((code *)param_3[6] != (code *)0x0) {
              (*(code *)param_3[6])(param_1);
            }
            lpMem = g_texture_animation_timer_list_head;
            if (g_texture_animation_timer_list_head == (uint *)0x0) {
              return;
            }
            while ((*lpMem != param_1 ||
                   (iVar3 = _stricmp((char *)(lpMem + 1),(char *)param_2), iVar3 != 0))) {
              puVar1 = lpMem + 8;
              lpMem = (uint *)*puVar1;
              if ((uint *)*puVar1 == (uint *)0x0) {
                return;
              }
            }
            finalize_released_world_object_after_damage((LPVOID)*lpMem,s_texanm_004f2724);
            if (g_texture_animation_timer_list_head == lpMem) {
              g_texture_animation_timer_list_head = (uint *)lpMem[8];
              if (lpMem[8] != 0) {
                *(undefined4 *)(lpMem[8] + 0x1c) = 0;
              }
              lpMem[8] = 0;
              lpMem[7] = 0;
            }
            else {
              if (lpMem[8] != 0) {
                *(uint *)(lpMem[8] + 0x1c) = lpMem[7];
              }
              if (lpMem[7] != 0) {
                *(uint *)(lpMem[7] + 0x20) = lpMem[8];
              }
              lpMem[8] = 0;
              lpMem[7] = 0;
            }
            if ((code *)lpMem[5] == update_texture_animation_timer) {
              xfree_global_heap((LPVOID)lpMem[6]);
            }
            HeapFree(g_texture_animation_timer_heap,0,lpMem);
            return;
          }
          fVar2 = (float)((int)param_3[3] + 1);
        }
        else {
          fVar2 = param_3[3];
          if (param_3[5] == 1.4013e-45) {
            if (fVar2 == 0.0) {
              fVar2 = param_3[2];
            }
            fVar2 = (float)((int)fVar2 + -1);
          }
          else if ((int)fVar2 < (int)param_3[2] + -1) {
            fVar2 = (float)((int)fVar2 + 1);
          }
          else {
            fVar2 = 0.0;
          }
        }
        param_3[3] = fVar2;
        fVar4 = get_network_or_session_runtime_seconds();
      } while ((float10)*param_3 < fVar4);
    }
    set_texture_binding_frame_and_reload(param_1,param_2,0,(int)param_3[3],1);
  }
  return;
}


