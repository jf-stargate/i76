/*
 * Program: i76.exe
 * Function: release_world_object_texture_bindings
 * Entry: 00449e60
 * Signature: undefined4 __cdecl release_world_object_texture_bindings(int param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Releases all texture-slot
   bindings owned by a world object. */

undefined4 __cdecl release_world_object_texture_bindings(int param_1)

{
  uint *_Str2;
  byte *pbVar1;
  byte bVar2;
  uint *puVar3;
  char *_Str1;
  int *piVar4;
  uint *lpMem;
  uint *puVar5;
  char *_Str1_00;
  int *lpMem_00;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  char local_10 [16];
  
  uVar8 = (param_1 * 0x6cd + 0xaabU) % 0x71;
  lpMem_00 = (int *)(&g_texture_bindings_by_object_hash)[uVar8];
  if (lpMem_00 != (int *)0x0) {
    if (*lpMem_00 == param_1) {
      (&g_texture_bindings_by_object_hash)[uVar8] = lpMem_00[2];
    }
    else {
      piVar4 = lpMem_00;
      for (lpMem_00 = (int *)lpMem_00[2]; lpMem_00 != (int *)0x0; lpMem_00 = (int *)lpMem_00[2]) {
        if (*lpMem_00 == param_1) {
          piVar4[2] = lpMem_00[2];
          break;
        }
        piVar4 = lpMem_00;
      }
    }
  }
  if (lpMem_00 == (int *)0x0) {
    return 0;
  }
  lpMem = (uint *)lpMem_00[1];
  do {
    do {
      if (lpMem == (uint *)0x0) {
        HeapFree(g_texture_object_binding_list_heap,0,lpMem_00);
        return 1;
      }
      puVar3 = (uint *)lpMem[0x11];
      uVar8 = *lpMem;
      _Str2 = lpMem + 5;
      uVar7 = 0;
      bVar2 = (byte)lpMem[5];
      puVar9 = _Str2;
      while (bVar2 != 0) {
        uVar7 = uVar7 * 2 ^ bVar2 & 0xdf;
        pbVar1 = (byte *)((int)puVar9 + 1);
        puVar9 = (uint *)((int)puVar9 + 1);
        bVar2 = *pbVar1;
      }
      uVar7 = ((uVar8 ^ uVar7) * 0x6cd + 0xaab) % 0x7ed;
      puVar9 = (uint *)(&g_texture_slot_binding_hash)[uVar7];
      if (puVar9 != (uint *)0x0) {
        if ((*puVar9 == uVar8) && (iVar6 = _stricmp((char *)(puVar9 + 5),(char *)_Str2), iVar6 == 0)
           ) {
          (&g_texture_slot_binding_hash)[uVar7] = puVar9[0x10];
        }
        else {
          for (puVar5 = (uint *)puVar9[0x10]; puVar5 != (uint *)0x0; puVar5 = (uint *)puVar5[0x10])
          {
            if ((*puVar5 == uVar8) &&
               (iVar6 = _stricmp((char *)(puVar5 + 5),(char *)_Str2), iVar6 == 0)) {
              puVar9[0x10] = puVar5[0x10];
              break;
            }
            puVar9 = puVar5;
          }
        }
      }
      strncpy(local_10,(char *)(lpMem + 1),0xf);
      if ((lpMem[0xf] & 1) == 0) {
        if ((lpMem[0xf] & 2) == 0) {
          release_vqm_texture_cache_reference_by_name(local_10);
        }
      }
      else {
        xfree_global_heap((LPVOID)lpMem[0xd]);
      }
      release_m16_resource_handle((int *)(lpMem + 0xe),(char *)(lpMem + 1));
      pbVar1 = (byte *)lpMem[0xc];
      HeapFree(g_texture_slot_binding_heap,0,lpMem);
      lpMem = puVar3;
    } while ((pbVar1 == (byte *)0x0) ||
            (iVar6 = *(int *)(pbVar1 + 0x10), *(int *)(pbVar1 + 0x10) = iVar6 + -1, iVar6 + -1 != 0)
            );
    uVar8 = hash_texture_set_name_mod_0x7ed(pbVar1);
    _Str1 = (char *)(&g_texture_set_cache_hash)[uVar8];
    if (_Str1 != (char *)0x0) {
      iVar6 = _stricmp(_Str1,(char *)pbVar1);
      if (iVar6 == 0) {
        (&g_texture_set_cache_hash)[uVar8] = *(undefined4 *)(_Str1 + 0x30);
      }
      else {
        for (_Str1_00 = *(char **)(_Str1 + 0x30); _Str1_00 != (char *)0x0;
            _Str1_00 = *(char **)(_Str1_00 + 0x30)) {
          iVar6 = _stricmp(_Str1_00,(char *)pbVar1);
          if (iVar6 == 0) {
            *(undefined4 *)(_Str1 + 0x30) = *(undefined4 *)(_Str1_00 + 0x30);
            break;
          }
          _Str1 = _Str1_00;
        }
      }
    }
    HeapFree(g_texture_name_array_heap,0,*(LPVOID *)(pbVar1 + 0x2c));
    HeapFree(g_texture_set_cache_heap,0,pbVar1);
  } while( true );
}


