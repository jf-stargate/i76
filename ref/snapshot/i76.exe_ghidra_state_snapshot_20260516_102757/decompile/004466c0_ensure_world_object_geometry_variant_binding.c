/*
 * Program: i76.exe
 * Function: ensure_world_object_geometry_variant_binding
 * Entry: 004466c0
 * Signature: bool __cdecl ensure_world_object_geometry_variant_binding(int param_1, int param_2)
 */


/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Ensures the requested geometry
   variant is loaded/bound on a world object before bounds/render traversal. */

bool __cdecl ensure_world_object_geometry_variant_binding(int param_1,int param_2)

{
  int *_Str1;
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint *_Str2;
  undefined1 local_10 [16];
  
  for (piVar5 = (int *)(&g_geometry_binding_hash)[(param_1 * 0x6cd + 0xaabU) % 0x7ed];
      piVar5 != (int *)0x0; piVar5 = (int *)piVar5[0xe]) {
    if (*piVar5 == param_1) goto LAB_00446702;
  }
  piVar5 = (int *)0x0;
LAB_00446702:
  if (piVar5 == (int *)0x0) {
    return false;
  }
  iVar1 = piVar5[3];
  if (iVar1 != param_2) {
    if (piVar5[4] == param_2) {
      _Str2 = (uint *)(piVar5 + 9);
    }
    else {
      iVar3 = piVar5[2];
      iVar2 = piVar5[0xd];
      if (0 < iVar3) {
        do {
          iVar2 = *(int *)(iVar2 + 0x70);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      _Str2 = (uint *)(param_2 * 0x10 + iVar2);
    }
    _Str1 = piVar5 + 5;
    piVar5[3] = param_2;
    iVar3 = _stricmp((char *)_Str1,(char *)_Str2);
    if (iVar3 != 0) {
      if (piVar5[1] != 0) {
        release_geometry_cache_reference(piVar5[1]);
      }
      memmove(local_10,_Str1,0x10);
      strncpy((char *)_Str1,(char *)_Str2,0xf);
      uVar4 = load_geometry_resource_into_cache(_Str2);
      piVar5[1] = uVar4;
      piVar5[4] = iVar1;
      memmove(piVar5 + 9,local_10,0x10);
      *(int *)(param_1 + 0x5c) = piVar5[1];
      refresh_object_texture_bindings_after_geometry_change(param_1);
    }
  }
  return *(int *)(param_1 + 0x5c) != 0;
}


