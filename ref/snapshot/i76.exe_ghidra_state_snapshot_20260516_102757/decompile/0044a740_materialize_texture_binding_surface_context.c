/*
 * Program: i76.exe
 * Function: materialize_texture_binding_surface_context
 * Entry: 0044a740
 * Signature: undefined __cdecl materialize_texture_binding_surface_context(undefined4 * param_1, uint param_2, byte * param_3)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Materializes an object texture
   binding into a bitmap/surface context from the current texture frame resource. */

void __cdecl
materialize_texture_binding_surface_context(undefined4 *param_1,uint param_2,byte *param_3)

{
  byte *pbVar1;
  byte bVar2;
  int *_Src;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  void *_Dst;
  undefined4 *puVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  uint *puVar9;
  SIZE_T _Size;
  undefined4 *puVar10;
  int local_34 [13];
  
  if ((param_2 == 0) || (param_3 == (byte *)0x0)) goto LAB_0044a910;
  uVar3 = 0;
  bVar2 = *param_3;
  pbVar7 = param_3;
  while (bVar2 != 0) {
    uVar3 = uVar3 * 2 ^ bVar2 & 0xdf;
    pbVar1 = pbVar7 + 1;
    pbVar7 = pbVar7 + 1;
    bVar2 = *pbVar1;
  }
  puVar9 = (uint *)(&g_texture_slot_binding_hash)[((uVar3 ^ param_2) * 0x6cd + 0xaab) % 0x7ed];
  while ((puVar9 != (uint *)0x0 &&
         ((*puVar9 != param_2 ||
          (iVar4 = _stricmp((char *)(puVar9 + 5),(char *)param_3), iVar4 != 0))))) {
    puVar9 = (uint *)puVar9[0x10];
  }
  if (puVar9 == (uint *)0x0) {
    bind_or_load_texture_set_for_object(param_2,param_3,0);
    uVar3 = 0;
    bVar2 = *param_3;
    pbVar7 = param_3;
    while (bVar2 != 0) {
      uVar3 = uVar3 * 2 ^ bVar2 & 0xdf;
      pbVar1 = pbVar7 + 1;
      pbVar7 = pbVar7 + 1;
      bVar2 = *pbVar1;
    }
    puVar9 = (uint *)(&g_texture_slot_binding_hash)[((uVar3 ^ param_2) * 0x6cd + 0xaab) % 0x7ed];
    if (puVar9 != (uint *)0x0) {
      do {
        if ((*puVar9 == param_2) &&
           (iVar4 = _stricmp((char *)(puVar9 + 5),(char *)param_3), iVar4 == 0)) break;
        puVar9 = (uint *)puVar9[0x10];
      } while (puVar9 != (uint *)0x0);
      if (puVar9 != (uint *)0x0) goto LAB_0044a844;
    }
    puVar10 = (undefined4 *)0x0;
    puVar8 = (undefined4 *)0x0;
    puVar6 = (undefined4 *)0x0;
    goto LAB_0044a911;
  }
LAB_0044a844:
  if ((puVar9[0xf] & 1) == 0) {
    if ((puVar9[0xf] & 2) != 0) {
      puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)(puVar9 + 1));
      puVar9[0xd] = (uint)puVar5;
      puVar9[0xf] = puVar9[0xf] & 0xfffffffd;
    }
    _Src = (int *)puVar9[0xd];
    if (_Src != (int *)0x0) {
      _Size = ((_Src[1] << 3) >> 3) * *_Src + 8;
      _Dst = (void *)xalloc_global_heap(_Size);
      puVar9[0xd] = (uint)_Dst;
      if (_Dst != (void *)0x0) {
        memmove(_Dst,_Src,_Size);
        puVar9[0xf] = puVar9[0xf] | 1;
        release_vqm_texture_cache_reference_by_name((char *)(puVar9 + 1));
        release_m16_resource_handle((int *)(puVar9 + 0xe),(char *)(puVar9 + 1));
        goto LAB_0044a8c7;
      }
      puVar9[0xd] = (uint)_Src;
    }
LAB_0044a910:
    puVar10 = (undefined4 *)0x0;
    puVar8 = puVar10;
    puVar6 = puVar10;
  }
  else {
LAB_0044a8c7:
    puVar10 = (undefined4 *)puVar9[0xd];
    uVar3 = puVar10[1];
    puVar6 = puVar10 + 2;
    puVar10[1] = uVar3 | 0x60000000;
    puVar10 = (undefined4 *)*puVar10;
    puVar8 = (undefined4 *)((int)(uVar3 * 8) >> 3);
  }
LAB_0044a911:
  puVar6 = (undefined4 *)
           construct_bitmap_surface_context(local_34,(int)puVar10,(uint)puVar8,(int)puVar6,0);
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *param_1 = *puVar6;
    puVar6 = puVar6 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


