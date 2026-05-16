/*
 * Program: i76.exe
 * Function: bind_ai_path_state_to_path_record
 * Entry: 004151f0
 * Signature: undefined __cdecl bind_ai_path_state_to_path_record(int param_1, int param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Binds an AI path-state block to a path/route record and
   initializes path progress fields from the route header. */

void __cdecl bind_ai_path_state_to_path_record(int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(int *)(param_1 + 0x88) = param_2;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  uVar1 = *(undefined4 *)(param_2 + 0x50);
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  return;
}


