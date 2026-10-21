/* Decompiled retail i76.exe, Ghidra v97; 004149f0 process_pending_fsm_instruction_list */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Processes pending FSM instruction records, advances game flow on timeout, and
   unlinks/frees completed instruction records.
   [v57 FSM] Consumes linked pending command blocks; calls 00414670; frees completed nodes
   [FSM v60, i76.exe verified] Pending node scheduler; calls token VM, removes only when VM returns
   completion. Yield retains node. */

void __cdecl
process_pending_fsm_instruction_list
          (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
          undefined4 param_6,int param_7,undefined4 param_8,int param_9,int *param_10,int *param_11,
          int *param_12,undefined4 param_13,undefined4 param_14,HANDLE param_15)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  int iVar2;
  int iVar3;
  float10 fVar4;
  
                    /* I76 semantic baseline: process_pending_fsm_instruction_list
                       Processes pending FSM instruction list/context. */
  fVar4 = get_mission_elapsed_clock_seconds();
  if ((float10)_g_fsm_game_flow_timeout_seconds <= fVar4) {
    set_game_flow_state(g_fsm_game_flow_timeout_next_state);
  }
  iVar3 = *param_11;
  if (iVar3 != 0) {
    do {
      iVar2 = execute_fsm_vm_token_stream
                        (iVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
      if (iVar2 != 0) {
        *param_12 = *param_12 + -1;
        pvVar1 = (LPVOID)*param_11;
        *param_11 = *(int *)((int)pvVar1 + 0x10b8);
        HeapFree(param_15,0,pvVar1);
      }
      iVar3 = *param_11;
      if (iVar3 == 0) {
        return;
      }
    } while (iVar2 != 0);
    pvVar1 = (LPVOID)*param_11;
    lpMem = (LPVOID)0x0;
    if (pvVar1 != (LPVOID)0x0) {
      lpMem = *(LPVOID *)((int)pvVar1 + 0x10b8);
    }
    while (lpMem != (LPVOID)0x0) {
      iVar3 = execute_fsm_vm_token_stream
                        ((int)lpMem,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
      if (iVar3 == 0) {
        pvVar1 = lpMem;
        lpMem = *(LPVOID *)((int)lpMem + 0x10b8);
      }
      else {
        *param_12 = *param_12 + -1;
        *(undefined4 *)((int)pvVar1 + 0x10b8) = *(undefined4 *)((int)lpMem + 0x10b8);
        HeapFree(param_15,0,lpMem);
        if (pvVar1 == (LPVOID)0x0) {
          lpMem = (LPVOID)0x0;
        }
        else {
          lpMem = *(LPVOID *)((int)pvVar1 + 0x10b8);
        }
      }
    }
  }
  return;
}


