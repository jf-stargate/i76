/*
 * Program: i76.exe
 * Function: start_or_update_ai_astar_pathfinding_state
 * Entry: 00420d30
 * Signature: undefined __cdecl start_or_update_ai_astar_pathfinding_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI helper that initializes/updates pathfinding state, locks
   global FSM context when path search succeeds, and slows vehicle while pathing. */

void __cdecl start_or_update_ai_astar_pathfinding_state(float param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  float10 fVar5;
  int local_4;
  
  get_vehicle_runtime_context((int)param_1);
  piVar1 = *(int **)(*(int *)((int)param_1 + 0x70) + 0x108);
  piVar1[0x2740] = -0x3ee00000;
  bVar3 = fsm_query_global_context_allows_object((int)param_1);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    fsm_mark_global_context_suppressed_this_frame();
  }
  else {
    piVar1[0x25] = 0;
    if (*(int *)((int)param_1 + 0x6c) == 9) {
      iVar2 = *(int *)(*(int *)(piVar1[0x22] + 0x54) + 8 + piVar1[0x28] * 0xc);
      iVar4 = *(int *)(*(int *)(piVar1[0x22] + 0x54) + piVar1[0x28] * 0xc);
      piVar1[0x2a] = 0;
      piVar1[0x2b] = 1;
      piVar1[0x2c] = iVar4;
      piVar1[0x2d] = iVar2;
      piVar1[0x2e] = 0;
      piVar1[0x21] = 0;
    }
    else {
      iVar4 = find_astar_path_between_world_positions(piVar1,&local_4);
      piVar1[0x21] = iVar4;
    }
    if (piVar1[0x21] == 1) {
      fsm_lock_global_context_to_object(param_1);
    }
    else {
      fsm_lock_global_context_to_object(0);
    }
  }
  if (piVar1[0x21] == 0) {
    piVar1[0x26] = 0;
    return;
  }
  fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
  set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)(fVar5 * (float10)_DAT_004bcc90));
  clear_vehicle_throttle_brake_command((int)param_1);
  return;
}


