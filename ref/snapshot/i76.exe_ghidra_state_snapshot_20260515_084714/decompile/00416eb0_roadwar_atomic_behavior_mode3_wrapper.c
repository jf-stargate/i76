/*
 * Program: i76.exe
 * Function: roadwar_atomic_behavior_mode3_wrapper
 * Entry: 00416eb0
 * Signature: undefined __cdecl roadwar_atomic_behavior_mode3_wrapper(int * param_1, int * param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Thin wrapper around handle_roadwar_atomic_behavior with
   mode 3. */

void __cdecl roadwar_atomic_behavior_mode3_wrapper(int *param_1,int *param_2)

{
  handle_roadwar_atomic_behavior(param_1,param_2,3);
  return;
}


