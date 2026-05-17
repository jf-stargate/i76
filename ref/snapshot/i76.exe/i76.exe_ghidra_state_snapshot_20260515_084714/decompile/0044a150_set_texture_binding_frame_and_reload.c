/*
 * Program: i76.exe
 * Function: set_texture_binding_frame_and_reload
 * Entry: 0044a150
 * Signature: undefined4 __cdecl set_texture_binding_frame_and_reload(uint param_1, byte * param_2, int param_3, int param_4, int param_5)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Updates an animated texture
   binding frame and reloads/rebinds the corresponding texture resource. */

undefined4 __cdecl
set_texture_binding_frame_and_reload(uint param_1,byte *param_2,int param_3,int param_4,int param_5)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  byte *pbVar8;
  uint *puVar9;
  
  if ((param_1 != 0) && (param_2 != (byte *)0x0)) {
    uVar4 = 0;
    bVar2 = *param_2;
    pbVar8 = param_2;
    while (bVar2 != 0) {
      uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
      pbVar1 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar2 = *pbVar1;
    }
    puVar9 = (uint *)(&g_texture_slot_binding_hash)[((uVar4 ^ param_1) * 0x6cd + 0xaab) % 0x7ed];
    if (puVar9 != (uint *)0x0) {
      do {
        if ((*puVar9 == param_1) &&
           (iVar5 = _stricmp((char *)(puVar9 + 5),(char *)param_2), iVar5 == 0)) break;
        puVar9 = (uint *)puVar9[0x10];
      } while (puVar9 != (uint *)0x0);
      if (puVar9 != (uint *)0x0) {
        uVar4 = puVar9[0xc];
        iVar5 = 1;
        if (param_3 != 0) {
          iVar5 = *(int *)(uVar4 + 0x1c + param_3 * 4);
        }
        puVar9[param_3 + 9] = iVar5 * param_4;
        if (param_5 != 0) {
          iVar5 = 0;
          if ((puVar9[0xf] & 1) == 0) {
            if ((puVar9[0xf] & 2) == 0) {
              release_vqm_texture_cache_reference_by_name((char *)(puVar9 + 1));
            }
          }
          else {
            xfree_global_heap((LPVOID)puVar9[0xd]);
            puVar9[0xf] = puVar9[0xf] & 0xfffffffe;
          }
          release_m16_resource_handle((int *)(puVar9 + 0xe),(char *)(puVar9 + 1));
          iVar7 = *(int *)(uVar4 + 0x1c);
          if (0 < iVar7) {
            puVar6 = puVar9 + 9;
            do {
              uVar3 = *puVar6;
              puVar6 = puVar6 + 1;
              iVar5 = iVar5 + uVar3;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
          }
          strncpy((char *)(puVar9 + 1),(char *)(*(int *)(uVar4 + 0x2c) + iVar5 * 0x10),0xf);
          puVar9[0xd] = 0;
          puVar9[0xf] = puVar9[0xf] | 2;
        }
        return 1;
      }
    }
  }
  return 0;
}


