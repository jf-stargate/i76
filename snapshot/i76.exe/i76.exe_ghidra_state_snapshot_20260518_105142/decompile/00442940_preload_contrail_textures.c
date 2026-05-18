/*
 * Program: i76.exe
 * Function: preload_contrail_textures
 * Entry: 00442940
 * Signature: undefined __cdecl preload_contrail_textures(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00442940
   suggested_name: preload_contrail_textures
   basis: References contrail start frame maps and calls add_texture_to_cache. */

void __cdecl preload_contrail_textures(int param_1)

{
  float fVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined1 uVar4;
  uint *puVar5;
  int *piVar6;
  undefined3 extraout_var;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  
  puVar9 = &DAT_004f1d08;
  do {
    iVar8 = 1;
    pbVar10 = (byte *)(puVar9 + -4);
    bVar3 = true;
    puVar11 = puVar9;
    do {
      puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar10);
      *puVar11 = puVar5;
      if (puVar5 == (uint *)0x0) {
        report_chunk_parse_error();
        bVar3 = false;
      }
      puVar11 = puVar11 + 1;
      pbVar10 = pbVar10 + 0xd;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    pbVar10 = (byte *)(puVar9 + 1);
    puVar11 = puVar9 + 5;
    iVar8 = 1;
    do {
      puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar10);
      *puVar11 = puVar5;
      if (puVar5 == (uint *)0x0) {
        report_chunk_parse_error();
        bVar3 = false;
      }
      puVar11 = puVar11 + 1;
      pbVar10 = pbVar10 + 0xd;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    pbVar10 = (byte *)(puVar9 + 6);
    puVar11 = puVar9 + 10;
    iVar8 = 1;
    do {
      puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar10);
      *puVar11 = puVar5;
      if (puVar5 == (uint *)0x0) {
        report_chunk_parse_error();
        bVar3 = false;
      }
      puVar11 = puVar11 + 1;
      pbVar10 = pbVar10 + 0xd;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    if (bVar3) {
      puVar9[0xb] = 0x94;
    }
    else {
      puVar9[0xb] = 0;
    }
    puVar9 = puVar9 + 0x10;
  } while ((int)puVar9 < 0x4f1ec8);
  if (0 < param_1) {
    do {
      puVar9 = (undefined4 *)xalloc_global_heap(0x398);
      if (puVar9 != (undefined4 *)0x0) {
        puVar11 = puVar9;
        for (iVar8 = 0xe6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar11 = 0;
          puVar11 = puVar11 + 1;
        }
        *puVar9 = DAT_0052bae8;
        DAT_0052bae8 = puVar9;
      }
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  puVar11 = (undefined4 *)*DAT_0052bae8;
  puVar9 = DAT_0052bae8;
  while (puVar2 = puVar11, puVar2 != (undefined4 *)0x0) {
    puVar9 = puVar2;
    puVar11 = (undefined4 *)*puVar2;
  }
  *puVar9 = DAT_0052bae8;
  iVar8 = 0;
  piVar6 = &DAT_0052ba88;
  do {
    iVar8 = iVar8 + 1;
    *piVar6 = iVar8;
    fVar1 = _DAT_004bd2c0;
    piVar6 = piVar6 + 1;
  } while ((int)piVar6 < 0x52bae4);
  *(undefined4 *)(iVar8 * 4 + 0x52ba84) = 0;
  piVar6 = &DAT_0052ba58;
  iVar8 = 0;
  do {
    iVar7 = iVar8;
    piVar6[1] = (int)fVar1;
    fVar1 = fVar1 - _DAT_004bd2c4;
    iVar8 = iVar7 + 1;
    *piVar6 = iVar8;
    piVar6 = piVar6 + 2;
  } while ((int)piVar6 < 0x52ba88);
  (&DAT_0052ba50)[iVar8 * 2] = iVar7;
  uVar4 = convert_rgb_floats_to_nearest_palette_index();
  _DAT_0052bae4 = CONCAT31(extraout_var,uVar4);
  return;
}


