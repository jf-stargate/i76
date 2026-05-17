/*
 * Program: i76.exe
 * Function: run_ai_behavior_action_004171a0
 * Entry: 0041e890
 * Signature: undefined __cdecl run_ai_behavior_action_004171a0(float param_1, uint param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Thin wrapper around FUN_004171a0 for a specific AI
   behavior table action. */

void __cdecl run_ai_behavior_action_004171a0(float param_1,uint param_2)

{
  update_ai_roadwar_path_follow_drive_control(param_1,param_2);
  return;
}


