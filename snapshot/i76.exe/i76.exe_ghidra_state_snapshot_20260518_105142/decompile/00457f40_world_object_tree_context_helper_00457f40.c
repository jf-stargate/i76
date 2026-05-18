/*
 * Program: i76.exe
 * Function: world_object_tree_context_helper_00457f40
 * Entry: 00457f40
 * Signature: int __cdecl world_object_tree_context_helper_00457f40(int * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: world object tree context helper based
   on prior focused closure context. */

int __cdecl world_object_tree_context_helper_00457f40(int *param_1,float param_2)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[0xc] == 0) {
    return 0;
  }
  if (DAT_00654b89 == '\0') {
    iVar3 = is_vehicle_or_weapon_source_world_object(*param_1);
    if ((iVar3 != 0) || (iVar3 = 2, (float)param_1[4] <= (float)param_1[9] * param_2)) {
      iVar3 = 3;
    }
  }
  else {
    iVar2 = 0;
    pfVar1 = (float *)(param_1 + 7);
    do {
      if (param_2 * *pfVar1 < (float)param_1[4]) break;
      iVar2 = iVar2 + 1;
      pfVar1 = pfVar1 + 1;
    } while (iVar2 < 3);
    iVar3 = iVar2;
    if (iVar2 < 3) {
      iVar3 = 0;
    }
    if (iVar2 == 3) {
      iVar2 = is_vehicle_or_weapon_source_world_object(*param_1);
      if ((iVar2 != 0) && ((float)param_1[4] < (float)param_1[9] * param_2 * (float)_DAT_004bdfc0))
      {
        return 0xb;
      }
    }
  }
  return iVar3;
}


