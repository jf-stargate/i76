/*
 * Program: i76.exe
 * Function: load_serialized_fsm_runtime_tables
 * Entry: 00410720
 * Signature: undefined __cdecl load_serialized_fsm_runtime_tables(undefined4 param_1, int param_2, int * param_3, int * param_4, int * param_5, int * param_6, int * param_7, int * param_8, int * param_9, int * param_10, undefined4 * param_11, int * param_12, int * param_13, int * param_14, undefined4 * param_15, int * param_16, HANDLE param_17)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Top-level serialized FSM/AI table loader; allocates
   multiple record arrays, index tables, and auxiliary pointer tables from the shared stream.
   
   I76 rename v43: load_serialized_fsm_runtime_tables
   Loads serialized FSM runtime tables. */

void __cdecl
load_serialized_fsm_runtime_tables
          (undefined4 param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6,
          int *param_7,int *param_8,int *param_9,int *param_10,undefined4 *param_11,int *param_12,
          int *param_13,int *param_14,undefined4 *param_15,int *param_16,HANDLE param_17)

{
  undefined4 uVar1;
  LPVOID pvVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  int iVar7;
  
  pcVar6 = HeapAlloc_exref;
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  g_fsm_serialized_stream_cursor = param_2;
  iVar4 = *(int *)(param_2 + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_4 = iVar4;
  if (iVar4 == 0) {
    *param_3 = 0;
  }
  else {
    pvVar2 = HeapAlloc(param_17,0,iVar4 * 0x54);
    iVar4 = 0;
    *param_3 = (int)pvVar2;
    if (0 < *param_4) {
      iVar5 = 0;
      do {
        puVar3 = (undefined1 *)(*param_3 + iVar5);
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        uVar1 = *(undefined4 *)
                 (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
        iVar7 = 9;
        *puVar3 = (char)uVar1;
        puVar3[3] = (char)((uint)uVar1 >> 0x18);
        puVar3[2] = (char)((uint)uVar1 >> 0x10);
        puVar3[1] = (char)((uint)uVar1 >> 8);
        puVar3 = puVar3 + 6;
        do {
          g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
          uVar1 = *(undefined4 *)
                   (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4)
          ;
          puVar3[1] = (char)((uint)uVar1 >> 0x18);
          *puVar3 = (char)((uint)uVar1 >> 0x10);
          puVar3[-1] = (char)((uint)uVar1 >> 8);
          puVar3[-2] = (char)uVar1;
          iVar7 = iVar7 + -1;
          puVar3 = puVar3 + 4;
        } while (iVar7 != 0);
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x54;
        pcVar6 = HeapAlloc_exref;
      } while (iVar4 < *param_4);
    }
  }
  load_serialized_fsm_record_array_with_bitfields(param_9,param_10,param_17);
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  iVar4 = *(int *)(g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_6 = iVar4;
  if (iVar4 == 0) {
    *param_5 = 0;
  }
  else {
    iVar4 = (*pcVar6)(param_17,0,iVar4 * 0x54);
    iVar5 = 0;
    *param_5 = iVar4;
    if (0 < *param_6) {
      iVar4 = 0;
      do {
        puVar3 = (undefined1 *)(*param_5 + iVar4);
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        uVar1 = *(undefined4 *)
                 (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
        iVar7 = 9;
        *puVar3 = (char)uVar1;
        puVar3[3] = (char)((uint)uVar1 >> 0x18);
        puVar3[2] = (char)((uint)uVar1 >> 0x10);
        puVar3[1] = (char)((uint)uVar1 >> 8);
        puVar3 = puVar3 + 6;
        do {
          g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
          uVar1 = *(undefined4 *)
                   (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4)
          ;
          puVar3[1] = (char)((uint)uVar1 >> 0x18);
          *puVar3 = (char)((uint)uVar1 >> 0x10);
          puVar3[-1] = (char)((uint)uVar1 >> 8);
          puVar3[-2] = (char)uVar1;
          iVar7 = iVar7 + -1;
          puVar3 = puVar3 + 4;
        } while (iVar7 != 0);
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0x54;
        pcVar6 = HeapAlloc_exref;
      } while (iVar5 < *param_6);
    }
  }
  load_serialized_fsm_record_array_with_vec3_lists(param_7,param_8,param_17);
  load_serialized_fsm_linked_state_blocks(param_11,param_12,param_17);
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  iVar4 = *(int *)(g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_14 = iVar4;
  if (iVar4 == 0) {
    *param_13 = 0;
  }
  else {
    iVar4 = (*pcVar6)(param_17,0,iVar4 << 2);
    *param_13 = iVar4;
    iVar4 = 0;
    if (0 < *param_14) {
      do {
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        iVar4 = iVar4 + 1;
        *(undefined4 *)(*param_13 + -4 + iVar4 * 4) =
             *(undefined4 *)
              (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
      } while (iVar4 < *param_14);
    }
  }
  g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
  iVar4 = *(int *)(g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
  *param_16 = iVar4;
  if (iVar4 != 0) {
    iVar4 = (*pcVar6)(param_17,0,iVar4 << 3);
    *param_12 = iVar4;
    iVar4 = 0;
    if (0 < *param_16 << 1) {
      do {
        g_fsm_serialized_stream_limit_or_base = g_fsm_serialized_stream_limit_or_base + 1;
        iVar4 = iVar4 + 1;
        *(undefined4 *)(*param_12 + -4 + iVar4 * 4) =
             *(undefined4 *)
              (g_fsm_serialized_stream_cursor + -4 + g_fsm_serialized_stream_limit_or_base * 4);
      } while (iVar4 < *param_16 * 2);
    }
    return;
  }
  *param_15 = 0;
  return;
}


