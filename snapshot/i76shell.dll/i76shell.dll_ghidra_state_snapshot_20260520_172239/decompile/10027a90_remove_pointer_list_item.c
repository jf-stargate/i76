/*
 * Program: i76shell.dll
 * Function: remove_pointer_list_item
 * Entry: 10027a90
 * Signature: undefined __cdecl remove_pointer_list_item(int param_1, int param_2)
 */


void __cdecl remove_pointer_list_item(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  bVar1 = false;
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 4)) {
    piVar3 = *(int **)(param_1 + 8);
    do {
      if (*piVar3 == param_2) {
        (*(int **)(param_1 + 8))[iVar2] = 0;
        bVar1 = true;
        break;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < *(int *)(param_1 + 4));
  }
  if (bVar1) {
    if (iVar2 < *(int *)(param_1 + 4) + -1) {
      do {
        iVar2 = iVar2 + 1;
        *(undefined4 *)(*(int *)(param_1 + 8) + -4 + iVar2 * 4) =
             *(undefined4 *)(*(int *)(param_1 + 8) + iVar2 * 4);
      } while (iVar2 < *(int *)(param_1 + 4) + -1);
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return;
}


