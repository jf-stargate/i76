/*
 * Program: i76.exe
 * Function: collect_effect_target_collision_links
 * Entry: 0043e3f0
 * Signature: undefined __cdecl collect_effect_target_collision_links(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Scans a world-object subtree for collision links and attaches qualifying links to
   an effect-target record. */

void __cdecl collect_effect_target_collision_links(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = *param_1;
  iVar2 = *(int *)(iVar1 + 0x6c);
  if ((10 < iVar2) && (iVar2 < 0xe)) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      iVar3 = *(int *)(iVar1 + 0x80);
      if ((iVar3 != 0) && (((iVar2 == 0xc) == 0 || (*(int *)(iVar1 + 0x6c) == 0xd)))) {
        for (iVar4 = *(int *)(iVar3 + 8); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x18)) {
          if ((_DAT_004bd21c < *(float *)(iVar4 + 8)) &&
             (piVar5 = HeapAlloc(DAT_00608be8,0,0xc), piVar5 != (int *)0x0)) {
            *piVar5 = iVar4;
            piVar5[1] = *(int *)(iVar3 + 4);
            piVar5[2] = param_1[6];
            param_1[6] = (int)piVar5;
          }
        }
      }
      if (*(int *)(iVar1 + 100) != 0) {
        collect_collision_links_from_world_object_tree
                  (*(int *)(iVar1 + 100),(int)param_1,(uint)(iVar2 == 0xc));
      }
    }
    if (param_1[6] != 0) {
      DAT_0052b94c = allocate_linked_list_node_3field(DAT_0052b94c,(undefined4 *)0x0,(int)param_1);
    }
  }
  return;
}


