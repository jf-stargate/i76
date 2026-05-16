/*
 * Program: i76.exe
 * Function: compare_roadwar_path_tree_node_order
 * Entry: 00416600
 * Signature: int __cdecl compare_roadwar_path_tree_node_order(int param_1, int param_2, int param_3, int param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Compares Roadwar/path tree node ordering while walking
   child links and side selectors. */

int __cdecl compare_roadwar_path_tree_node_order(int param_1,int param_2,int param_3,int param_4)

{
  if (param_1 == param_3) {
    return ((param_4 <= param_2) - 1 & 2) - 1;
  }
  if (*(int *)(param_1 + 0xc) == 0) {
    do {
      if (param_1 == param_3) {
        return 1;
      }
      param_1 = *(int *)(param_1 + 4);
    } while (*(int *)(param_1 + 0xc) == 0);
    return (-(uint)(param_1 != param_3) & 0xfffffffe) + 1;
  }
  return (-(uint)(param_1 != param_3) & 0xfffffffe) + 1;
}


