/*
 * Program: i76.exe
 * Function: release_or_detach_object_geometry_variant
 * Entry: 004465b0
 * Signature: bool __cdecl release_or_detach_object_geometry_variant(int param_1, int param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Geometry/cache helper called by
   vehicle destruction and object release paths. */

bool __cdecl release_or_detach_object_geometry_variant(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  for (piVar3 = (int *)(&g_geometry_binding_hash)[(param_1 * 0x6cd + 0xaabU) % 0x7ed];
      piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0xe]) {
    if (*piVar3 == param_1) goto LAB_004465ef;
  }
  piVar3 = (int *)0x0;
LAB_004465ef:
  if (piVar3 == (int *)0x0) {
    return false;
  }
  if (piVar3[2] == param_2) {
    return true;
  }
  iVar4 = piVar3[0xd];
  iVar1 = param_2;
  if (0 < param_2) {
    do {
      iVar4 = *(int *)(iVar4 + 0x70);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  piVar3[2] = param_2;
  if (piVar3[3] == -1) {
    return true;
  }
  piVar3[4] = -1;
  iVar1 = _stricmp((char *)(piVar3 + 5),(char *)(piVar3[3] * 0x10 + iVar4));
  if (iVar1 == 0) {
    return true;
  }
  if (piVar3[1] != 0) {
    release_geometry_cache_reference(piVar3[1]);
    piVar3[1] = 0;
  }
  strncpy((char *)(piVar3 + 5),(char *)(piVar3[3] * 0x10 + iVar4),0xf);
  uVar2 = load_geometry_resource_into_cache((uint *)(piVar3[3] * 0x10 + iVar4));
  piVar3[1] = uVar2;
  *(uint *)(param_1 + 0x5c) = uVar2;
  refresh_object_texture_bindings_after_geometry_change(param_1);
  return *(int *)(param_1 + 0x5c) != 0;
}


