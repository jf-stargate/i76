/*
 * Program: i76.exe
 * Function: fsm_set_tactics_tag_from_index
 * Entry: 0040bf60
 * Signature: undefined __cdecl fsm_set_tactics_tag_from_index(int param_1, int * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: stores tactic index - 1 and parses the
   corresponding tactics tag into AI/FSM state +0xa82c. */

void __cdecl fsm_set_tactics_tag_from_index(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  iVar2 = *param_2;
  *(int *)(iVar1 + 0xa818) = iVar2 + -1;
  parse_fsm_tactics_tag(iVar2 + -1,iVar1 + 0xa82c);
  return;
}


