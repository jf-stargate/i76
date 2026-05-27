/*
 * Program: i76.exe
 * Function: is_ai_behavior_line_of_sight_stale
 * Entry: 0041e680
 * Signature: bool __cdecl is_ai_behavior_line_of_sight_stale(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Uses gating predicates and a 5-second timer to decide
   whether line-of-sight/behavior state is stale. */

bool __cdecl is_ai_behavior_line_of_sight_stale(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  float10 fVar5;
  
  iVar2 = get_ai_vehicle_behavior_state_block(param_1);
  iVar3 = fsm_get_active_player_special_condition_flag();
  if (iVar3 == 0) {
    fVar5 = get_gameplay_runtime_seconds();
    *(float *)(iVar2 + 0xa94c) = (float)fVar5;
    bVar4 = false;
  }
  else {
    iVar3 = fsm_consume_round_robin_condition_slot();
    if ((iVar3 != 0) &&
       (iVar3 = test_weapon_projectile_path_clear_to_target(param_1,param_2), iVar3 != 0)) {
      fVar5 = get_gameplay_runtime_seconds();
      *(float *)(iVar2 + 0xa94c) = (float)fVar5;
    }
    fVar1 = *(float *)(iVar2 + 0xa94c) + _DAT_004bcb28;
    fVar5 = get_gameplay_runtime_seconds();
    bVar4 = (float10)fVar1 < fVar5;
  }
  return bVar4;
}


