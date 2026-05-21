/*
 * Program: i76.exe
 * Function: reload_texture_binding_current_frame_pixels
 * Entry: 0044a930
 * Signature: undefined __cdecl reload_texture_binding_current_frame_pixels(uint param_1, byte * param_2, int param_3)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Texture binding update helper:
   locates object+slot binding and reloads/copies current frame pixels through the VQM/direct
   texture cache loader. */

void __cdecl reload_texture_binding_current_frame_pixels(uint param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  byte bVar2;
  int *_Dst;
  uint uVar3;
  int iVar4;
  uint *_Src;
  byte *pbVar5;
  uint *puVar6;
  
  if ((param_1 != 0) && (param_2 != (byte *)0x0)) {
    uVar3 = 0;
    bVar2 = *param_2;
    pbVar5 = param_2;
    while (bVar2 != 0) {
      uVar3 = uVar3 * 2 ^ bVar2 & 0xdf;
      pbVar1 = pbVar5 + 1;
      pbVar5 = pbVar5 + 1;
      bVar2 = *pbVar1;
    }
    puVar6 = (uint *)(&g_texture_slot_binding_hash)[((uVar3 ^ param_1) * 0x6cd + 0xaab) % 0x7ed];
    if (puVar6 != (uint *)0x0) {
      do {
        if ((*puVar6 == param_1) &&
           (iVar4 = _stricmp((char *)(puVar6 + 5),(char *)param_2), iVar4 == 0)) break;
        puVar6 = (uint *)puVar6[0x10];
      } while (puVar6 != (uint *)0x0);
      if ((puVar6 != (uint *)0x0) && ((puVar6[0xf] & 1) != 0)) {
        _Src = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)(puVar6 + 1));
        if (param_3 != 0) {
          _Dst = (int *)puVar6[0xd];
          memmove(_Dst,_Src,((_Dst[1] << 3) >> 3) * *_Dst + 8);
          release_vqm_texture_cache_reference_by_name((char *)(puVar6 + 1));
          return;
        }
        xfree_global_heap((LPVOID)puVar6[0xd]);
        puVar6[0xd] = (uint)_Src;
        puVar6[0xf] = puVar6[0xf] & 0xfffffffe;
      }
    }
  }
  return;
}


