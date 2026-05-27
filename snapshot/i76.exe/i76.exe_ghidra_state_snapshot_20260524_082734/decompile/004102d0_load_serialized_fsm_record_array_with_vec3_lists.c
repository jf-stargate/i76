/*
 * Program: i76.exe
 * Function: load_serialized_fsm_record_array_with_vec3_lists
 * Entry: 004102d0
 * Signature: undefined __cdecl load_serialized_fsm_record_array_with_vec3_lists(int * param_1, int * param_2, HANDLE param_3)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Loads a serialized FSM/AI record array with
   0x58-byte records and per-record vector/list payloads from the shared table stream.
   
   I76 rename v43: fsm_load_record_array_with_vec3_lists
   FSM serialized array loader with vec3 lists. */

void __cdecl
load_serialized_fsm_record_array_with_vec3_lists(int *param_1,int *param_2,HANDLE param_3)

{
  LPVOID pvVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  iVar5 = *(int *)(g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_2 = iVar5;
  if (iVar5 == 0) {
    *param_1 = 0;
    return;
  }
  pvVar1 = HeapAlloc(param_3,0,iVar5 * 0x58);
  iVar5 = 0;
  *param_1 = (int)pvVar1;
  if (0 < *param_2) {
    iVar7 = 0;
    do {
      puVar2 = (undefined1 *)(*param_1 + iVar7);
      g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
      iVar6 = 9;
      uVar3 = *(undefined4 *)
               (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
      *puVar2 = (char)uVar3;
      puVar2[3] = (char)((uint)uVar3 >> 0x18);
      puVar2[2] = (char)((uint)uVar3 >> 0x10);
      puVar2[1] = (char)((uint)uVar3 >> 8);
      puVar2 = puVar2 + 6;
      do {
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        uVar3 = *(undefined4 *)
                 (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
        puVar2[1] = (char)((uint)uVar3 >> 0x18);
        *puVar2 = (char)((uint)uVar3 >> 0x10);
        puVar2[-1] = (char)((uint)uVar3 >> 8);
        puVar2[-2] = (char)uVar3;
        iVar6 = iVar6 + -1;
        puVar2 = puVar2 + 4;
      } while (iVar6 != 0);
      g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
      *(undefined4 *)(*param_1 + 0x50 + iVar7) =
           *(undefined4 *)
            (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
      uVar3 = xalloc_global_heap(*(int *)(*param_1 + 0x50 + iVar7) * 0xc);
      *(undefined4 *)(*param_1 + 0x54 + iVar7) = uVar3;
      iVar6 = 0;
      if (0 < *(int *)(*param_1 + 0x50 + iVar7)) {
        iVar4 = 0;
        do {
          g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
          iVar4 = iVar4 + 0xc;
          *(undefined4 *)(*(int *)(*param_1 + 0x54 + iVar7) + -0xc + iVar4) =
               *(undefined4 *)
                (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
          g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
          *(undefined4 *)(*(int *)(*param_1 + 0x54 + iVar7) + -8 + iVar4) =
               *(undefined4 *)
                (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
          g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
          iVar6 = iVar6 + 1;
          *(undefined4 *)(*(int *)(*param_1 + 0x54 + iVar7) + -4 + iVar4) =
               *(undefined4 *)
                (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
        } while (iVar6 < *(int *)(*param_1 + 0x50 + iVar7));
      }
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 0x58;
    } while (iVar5 < *param_2);
  }
  return;
}


