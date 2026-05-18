/*
 * Program: i76.exe
 * Function: release_geometry_variant_recursive
 * Entry: 004ba5f0
 * Signature: bool __cdecl release_geometry_variant_recursive(int param_1, int param_2)
 */


/* cgpt rename v2: Recursively releases/detaches a geometry variant for a world-object subtree. */

bool __cdecl release_geometry_variant_recursive(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  if (param_1 != 0) {
    bVar2 = release_or_detach_object_geometry_variant(param_1,param_2);
    bVar2 = CONCAT31(extraout_var,bVar2) != 0;
    for (iVar1 = *(int *)(param_1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      bVar3 = release_geometry_variant_recursive(iVar1,param_2);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
        bVar2 = true;
      }
    }
    return bVar2;
  }
  return false;
}


