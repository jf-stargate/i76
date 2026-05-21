/*
 * Program: i76.exe
 * Function: is_ai_target_on_same_or_next_roadwar_segment
 * Entry: 00416cd0
 * Signature: bool __cdecl is_ai_target_on_same_or_next_roadwar_segment(int param_1, int param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Checks whether AI and target share the same Roadwar
   segment or a reachable next segment. */

bool __cdecl is_ai_target_on_same_or_next_roadwar_segment(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  if (*(int *)(iVar3 + 0xa96c) == 0) {
    return false;
  }
  piVar1 = *(int **)(*(int *)(*(int *)(param_2 + 0x70) + 0x108) + 0xa96c);
  if (((*(int **)(iVar3 + 0xa96c) != (int *)0x0) && (piVar1 != (int *)0x0)) &&
     (**(int **)(iVar3 + 0xa96c) == *piVar1)) {
    iVar2 = is_ai_target_not_in_vehicle_state_range_2_to_4(param_1,param_2);
    if (iVar2 != 0) {
      return true;
    }
    param_2 = *(int *)(iVar3 + 0xa96c);
    param_1 = *(int *)(iVar3 + 0xa950);
    iVar3 = roadwar_get_next_road_index(&param_2,*(int *)(iVar3 + 0xa954),&param_1);
    return iVar3 != 0;
  }
  return false;
}


