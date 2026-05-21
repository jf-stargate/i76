/*
 * Program: i76.exe
 * Function: unlink_and_free_linked_list_node_3field
 * Entry: 0049c360
 * Signature: undefined __cdecl unlink_and_free_linked_list_node_3field(int * param_1, int * param_2)
 */


/* cgpt rename v4: Unlinks a generic three-field linked-list node and frees it from the associated
   heap. */

void __cdecl unlink_and_free_linked_list_node_3field(int *param_1,int *param_2)

{
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  if ((int *)param_2[1] != (int *)0x0) {
    *(int *)param_2[1] = *param_2;
    HeapFree(DAT_005a7da0,0,param_2);
    return;
  }
  *param_1 = *param_2;
  HeapFree(DAT_005a7da0,0,param_2);
  return;
}


