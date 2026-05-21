/*
 * Program: i76shell.dll
 * Function: remove_pointer_list_items_present_in_other_list
 * Entry: 10035f30
 * Signature: undefined __cdecl remove_pointer_list_items_present_in_other_list(int param_1, int * param_2)
 */


void __cdecl remove_pointer_list_items_present_in_other_list(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    iVar2 = *(int *)(*(int *)(param_1 + 8) + iVar1 * 4);
    iVar3 = find_pointer_list_item_index(param_2,iVar2);
    if (iVar3 != -1) {
      remove_pointer_list_item(param_1,iVar2);
    }
  }
  return;
}


