/*
 * Program: i76.exe
 * Function: run_ai_combat_behavior_mode_4
 * Entry: 0041cae0
 * Signature: undefined __cdecl run_ai_combat_behavior_mode_4(float param_1, float param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Thin wrapper that invokes update_ai_combat_state with
   behavior selector 4. */

void __cdecl run_ai_combat_behavior_mode_4(float param_1,float param_2)

{
  int unaff_EBP;
  
  update_ai_combat_state(param_1,param_2,5.60519e-45,0,unaff_EBP);
  return;
}


