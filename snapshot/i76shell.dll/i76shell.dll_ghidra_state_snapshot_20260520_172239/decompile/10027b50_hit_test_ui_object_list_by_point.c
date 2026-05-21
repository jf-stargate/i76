/*
 * Program: i76shell.dll
 * Function: hit_test_ui_object_list_by_point
 * Entry: 10027b50
 * Signature: undefined4 __cdecl hit_test_ui_object_list_by_point(int param_1, int param_2, int param_3)
 */


undefined4 __cdecl hit_test_ui_object_list_by_point(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(int *)(param_1 + 4)) {
    piVar2 = *(int **)(param_1 + 8);
    do {
      puVar1 = (undefined4 *)*piVar2;
      if (((((int)puVar1[1] < param_2) && (param_2 < (int)puVar1[2])) && ((int)puVar1[3] < param_3))
         && (param_3 < (int)puVar1[4])) {
        return *puVar1;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *(int *)(param_1 + 4));
  }
  return 0xffffffff;
}


