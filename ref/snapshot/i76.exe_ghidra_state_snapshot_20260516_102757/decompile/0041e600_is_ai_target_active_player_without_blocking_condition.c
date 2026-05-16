/*
 * Program: i76.exe
 * Function: is_ai_target_active_player_without_blocking_condition
 * Entry: 0041e600
 * Signature: bool __cdecl is_ai_target_active_player_without_blocking_condition(int param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Checks whether target is the active player object and
   no blocking AI condition is present. */

bool __cdecl is_ai_target_active_player_without_blocking_condition(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar2 == (int *)0x0) {
    cVar1 = '\0';
  }
  else if (*piVar2 == param_2) {
    iVar3 = fsm_query_target_not_over_subscribed(param_1,param_2);
    cVar1 = '\x01' - (iVar3 != 0);
  }
  else {
    cVar1 = '\0';
  }
  return (bool)cVar1;
}


