/*
 * Program: i76.exe
 * Function: fsm_reveal_mission_objective
 * Entry: 0040be50
 * Signature: undefined __cdecl fsm_reveal_mission_objective(int * param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around reveal_mission_objective.
    */

void __cdecl fsm_reveal_mission_objective(int *param_1)

{
  reveal_mission_objective(*param_1);
  return;
}


