/*
 * Program: i76shell.dll
 * Function: find_pointer_list_item_index
 * Entry: 10027af0
 * Signature: int __cdecl find_pointer_list_item_index(int * param_1, int param_2)
 */


int __cdecl find_pointer_list_item_index(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < *param_1) {
    piVar2 = (int *)param_1[2];
    do {
      if (*piVar2 == param_2) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < *param_1);
  }
  return -1;
}


