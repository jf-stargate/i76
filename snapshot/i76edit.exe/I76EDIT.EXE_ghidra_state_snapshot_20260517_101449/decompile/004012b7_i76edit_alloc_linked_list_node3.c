/*
 * Program: I76EDIT.EXE
 * Function: i76edit_alloc_linked_list_node3
 * Entry: 004012b7
 * Signature: undefined __cdecl i76edit_alloc_linked_list_node3(int param_1, undefined4 * param_2, int param_3)
 */


void __cdecl i76edit_alloc_linked_list_node3(int param_1,undefined4 *param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = HeapAlloc(DAT_00436994,0,0xc);
  if (piVar1 != (int *)0x0) {
    *piVar1 = param_1;
    piVar1[1] = (int)param_2;
    piVar1[2] = param_3;
    if (param_1 != 0) {
      *(int **)(param_1 + 4) = piVar1;
    }
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = piVar1;
    }
  }
  return;
}


