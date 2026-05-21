/*
 * Program: i76shell.dll
 * Function: insert_pointer_list_item_sorted_or_append
 * Entry: 10027970
 * Signature: undefined __cdecl insert_pointer_list_item_sorted_or_append(int param_1, int param_2, undefined * param_3)
 */


void __cdecl insert_pointer_list_item_sorted_or_append(int param_1,int param_2,undefined *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    if (param_3 != (undefined *)0x0) {
      iVar3 = 0;
      if (0 < *(int *)(param_1 + 4)) {
        do {
          iVar2 = (*(code *)param_3)(*(undefined4 *)(*(int *)(param_1 + 8) + iVar3 * 4),param_2);
          if (iVar2 != 0) break;
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(param_1 + 4));
      }
      for (iVar2 = *(int *)(param_1 + 4); iVar3 < iVar2; iVar2 = iVar2 + -1) {
        puVar1 = (undefined4 *)(*(int *)(param_1 + 8) + iVar2 * 4);
        *puVar1 = puVar1[-1];
      }
      *(int *)(*(int *)(param_1 + 8) + iVar3 * 4) = param_2;
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      return;
    }
    *(int *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 4) * 4) = param_2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  }
  return;
}


