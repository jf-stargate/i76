/*
 * Program: i76.exe
 * Function: process_pending_fsm_instruction_list
 * Entry: 004149f0
 * Signature: undefined __cdecl process_pending_fsm_instruction_list(undefined4 param_1, undefined4 param_2, int param_3, undefined4 param_4, int param_5, undefined4 param_6, int param_7, undefined4 param_8, int param_9, int * param_10, int * param_11, int * param_12, undefined4 param_13, undefined4 param_14, HANDLE param_15)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Processes pending FSM instruction records, advances game flow on timeout, and
   unlinks/frees completed instruction records. */

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
  
  fVar4 = mission_flow_map_context_helper_0049c7e0();
  if ((float10)_DAT_005244e0 <= fVar4) {
    set_game_flow_state(DAT_005244e4);
  }
  iVar3 = *param_11;
  if (iVar3 != 0) {
    do {
      iVar2 = assemble_fsm_instruction
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
      iVar3 = assemble_fsm_instruction
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


