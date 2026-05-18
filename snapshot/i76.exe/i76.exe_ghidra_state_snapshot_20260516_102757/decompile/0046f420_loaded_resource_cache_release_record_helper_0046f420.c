/*
 * Program: i76.exe
 * Function: loaded_resource_cache_release_record_helper_0046f420
 * Entry: 0046f420
 * Signature: undefined __cdecl loaded_resource_cache_release_record_helper_0046f420(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache release record
   helper based on adjacent named subsystem context. */

void __cdecl loaded_resource_cache_release_record_helper_0046f420(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iVar4 = get_root_ancestor_world_object(param_1);
  iVar2 = *piVar1;
  iVar3 = *(int *)(iVar2 + 0xc);
  if (*(float *)(*(int *)(iVar4 + 0x70) + 0xe0) < _DAT_004be560) {
    iVar4 = ftol();
    *(int *)(iVar2 + 8) = iVar4 + iVar3;
    return;
  }
  iVar4 = ftol();
  *(int *)(iVar2 + 8) = iVar4 + iVar3;
  return;
}


