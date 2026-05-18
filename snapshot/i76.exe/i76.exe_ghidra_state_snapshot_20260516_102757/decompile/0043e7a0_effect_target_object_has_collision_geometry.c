/*
 * Program: i76.exe
 * Function: effect_target_object_has_collision_geometry
 * Entry: 0043e7a0
 * Signature: bool __cdecl effect_target_object_has_collision_geometry(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Checks whether an effect target object
   has qualifying collision geometry/child class links. */

bool __cdecl effect_target_object_has_collision_geometry(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  iVar1 = *param_1;
  uVar5 = (uint)(*(int *)(iVar1 + 0x6c) == 0xc);
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
    iVar2 = *(int *)(iVar1 + 0x80);
    if ((iVar2 != 0) && ((uVar5 == 0 || (*(int *)(iVar1 + 0x6c) == 0xd)))) {
      for (iVar3 = *(int *)(iVar2 + 8); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x18)) {
        if ((_DAT_004bd21c < *(float *)(iVar3 + 8)) &&
           (piVar4 = HeapAlloc(DAT_00608be8,0,0xc), piVar4 != (int *)0x0)) {
          *piVar4 = iVar3;
          piVar4[1] = *(int *)(iVar2 + 4);
          piVar4[2] = param_1[6];
          param_1[6] = (int)piVar4;
        }
      }
    }
    if (*(int *)(iVar1 + 100) != 0) {
      collect_collision_links_from_world_object_tree(*(int *)(iVar1 + 100),(int)param_1,uVar5);
    }
  }
  return param_1[6] != 0;
}


