/*
 * Program: i76.exe
 * Function: world_object_placement_class_helper_00469fb0
 * Entry: 00469fb0
 * Signature: undefined4 __cdecl world_object_placement_class_helper_00469fb0(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: world object placement class helper
   based on adjacent named subsystem context. */

undefined4 __cdecl world_object_placement_class_helper_00469fb0(int param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iVar3 = is_damage_side_effects_suppressed();
  fVar2 = _DAT_004be268;
  if (iVar3 == 0) {
    iVar3 = get_root_ancestor_world_object(param_1);
    iVar3 = world_object_has_optional_runtime_flag(iVar3);
    fVar2 = _DAT_004be268;
    if (iVar3 == 0) {
      fVar2 = _DAT_004be264;
    }
  }
  iVar3 = 0;
  piVar4 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar3 & 0x1f)) != 0) {
      if (*piVar1 < *piVar4) {
        *(int *)(param_2 + 8 + iVar3 * 4) = *(int *)(param_2 + 8 + iVar3 * 4) - *piVar1;
        *piVar1 = 0;
        piVar1[6] = (int)fVar2;
        return 1;
      }
      *piVar1 = *piVar1 - *piVar4;
      *piVar4 = 0;
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar3 < 4);
  piVar1[6] = (int)((float)*piVar1 / (float)piVar1[1]);
  if (fVar2 <= (float)*piVar1 / (float)piVar1[1]) {
    return 0;
  }
  piVar1[6] = (int)fVar2;
  return 0;
}


