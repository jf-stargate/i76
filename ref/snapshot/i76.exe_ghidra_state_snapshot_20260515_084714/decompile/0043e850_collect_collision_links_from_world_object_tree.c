/*
 * Program: i76.exe
 * Function: collect_collision_links_from_world_object_tree
 * Entry: 0043e850
 * Signature: undefined __cdecl collect_collision_links_from_world_object_tree(int param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Recursively scans a world-object subtree and appends qualifying
   geometry/collision links to an effect-target record. */

void __cdecl collect_collision_links_from_world_object_tree(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x60)) {
    iVar1 = *(int *)(param_1 + 0x80);
    if ((iVar1 != 0) && ((param_3 == 0 || (*(int *)(param_1 + 0x6c) == 0xd)))) {
      for (iVar2 = *(int *)(iVar1 + 8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x18)) {
        if ((_DAT_004bd21c < *(float *)(iVar2 + 8)) &&
           (piVar3 = HeapAlloc(DAT_00608be8,0,0xc), piVar3 != (int *)0x0)) {
          *piVar3 = iVar2;
          piVar3[1] = *(int *)(iVar1 + 4);
          piVar3[2] = *(int *)(param_2 + 0x18);
          *(int **)(param_2 + 0x18) = piVar3;
        }
      }
    }
    if (*(int *)(param_1 + 100) != 0) {
      collect_collision_links_from_world_object_tree(*(int *)(param_1 + 100),param_2,param_3);
    }
  }
  return;
}


