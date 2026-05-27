/*
 * Program: i76.exe
 * Function: fsm_set_helicopter_height
 * Entry: 0040bc40
 * Signature: undefined __cdecl fsm_set_helicopter_height(int param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: setHeliHeight non-helicopter */

void __cdecl fsm_set_helicopter_height(int param_1,int *param_2)

{
  if (*(int *)(param_1 + 0x6c) != 9) {
    report_error();
    return;
  }
  building_child_piece_context_helper_0046c870(param_1,(float)*param_2);
  return;
}


