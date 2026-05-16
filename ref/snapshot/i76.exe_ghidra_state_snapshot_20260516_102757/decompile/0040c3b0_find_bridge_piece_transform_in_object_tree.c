/*
 * Program: i76.exe
 * Function: find_bridge_piece_transform_in_object_tree
 * Entry: 0040c3b0
 * Signature: undefined4 __cdecl find_bridge_piece_transform_in_object_tree(int param_1, float * param_2, int * param_3, float * param_4)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: Recursively searches an object tree for child
   class/type 0x0d, composing transforms and returning the matching bridge piece transform. */

undefined4 __cdecl
find_bridge_piece_transform_in_object_tree(int param_1,float *param_2,int *param_3,float *param_4)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float local_80 [16];
  float local_40 [16];
  
  if (param_1 == 0) {
    return 0;
  }
  while( true ) {
    pfVar1 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 0x18),param_2);
    pfVar3 = pfVar1;
    pfVar4 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar4 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar4 = pfVar4 + 1;
    }
    if (*(int *)(param_1 + 0x6c) == 0xd) break;
    if ((*(int *)(param_1 + 100) != 0) &&
       (iVar2 = find_bridge_piece_transform_in_object_tree
                          (*(int *)(param_1 + 100),local_80,param_3,param_4), iVar2 != 0)) {
      return 1;
    }
    param_1 = *(int *)(param_1 + 0x60);
    if (param_1 == 0) {
      return 0;
    }
  }
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_4 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    param_4 = param_4 + 1;
  }
  *param_3 = param_1;
  return 1;
}


