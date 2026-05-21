/*
 * Program: i76.exe
 * Function: preload_flamer_textures
 * Entry: 00443a90
 * Signature: undefined __cdecl preload_flamer_textures(int param_1)
 */


/* i76 second-pass rename
   old_name: FUN_00443a90
   suggested_name: preload_flamer_textures
   basis: References flamer start/mid/end/endcap frame maps and missing-frame diagnostics. */

void __cdecl preload_flamer_textures(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  bool bVar3;
  uint *puVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  
  puVar7 = &DAT_004f1fe4;
  do {
    bVar3 = true;
    pbVar8 = (byte *)(puVar7 + -0xd);
    iVar6 = 4;
    puVar9 = puVar7;
    do {
      puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar8);
      *puVar9 = puVar4;
      if (puVar4 == (uint *)0x0) {
        report_error();
        bVar3 = false;
      }
      puVar9 = puVar9 + 1;
      pbVar8 = pbVar8 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    pbVar8 = (byte *)(puVar7 + 4);
    puVar9 = puVar7 + 0x11;
    iVar6 = 4;
    do {
      puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar8);
      *puVar9 = puVar4;
      if (puVar4 == (uint *)0x0) {
        report_error();
        bVar3 = false;
      }
      puVar9 = puVar9 + 1;
      pbVar8 = pbVar8 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    pbVar8 = (byte *)(puVar7 + 0x15);
    puVar9 = puVar7 + 0x22;
    iVar6 = 4;
    do {
      puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar8);
      *puVar9 = puVar4;
      if (puVar4 == (uint *)0x0) {
        report_error();
        bVar3 = false;
      }
      puVar9 = puVar9 + 1;
      pbVar8 = pbVar8 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    pbVar8 = (byte *)(puVar7 + 0x26);
    puVar9 = puVar7 + 0x2a;
    iVar6 = 1;
    do {
      puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar8);
      *puVar9 = puVar4;
      if (puVar4 == (uint *)0x0) {
        report_error();
        bVar3 = false;
      }
      puVar9 = puVar9 + 1;
      pbVar8 = pbVar8 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    if (bVar3) {
      puVar7[0x2b] = 0x54;
    }
    else {
      puVar7[0x2b] = 0xe3;
    }
    puVar7 = puVar7 + 0x39;
  } while ((int)puVar7 < 0x4f2290);
  if (0 < param_1) {
    do {
      puVar7 = (undefined4 *)xalloc_global_heap(0x360);
      if (puVar7 != (undefined4 *)0x0) {
        puVar9 = puVar7;
        for (iVar6 = 0xd8; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar9 = 0;
          puVar9 = puVar9 + 1;
        }
        *puVar7 = DAT_0052bb90;
        DAT_0052bb90 = puVar7;
      }
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  puVar9 = (undefined4 *)*DAT_0052bb90;
  puVar7 = DAT_0052bb90;
  while (puVar2 = puVar9, puVar2 != (undefined4 *)0x0) {
    puVar7 = puVar2;
    puVar9 = (undefined4 *)*puVar2;
  }
  *puVar7 = DAT_0052bb90;
  iVar6 = 0;
  piVar5 = &DAT_0052bb40;
  do {
    iVar6 = iVar6 + 1;
    *piVar5 = iVar6;
    piVar5 = piVar5 + 1;
  } while ((int)piVar5 < 0x52bb90);
  *(undefined4 *)(iVar6 * 4 + 0x52bb3c) = 0;
  iVar6 = 0;
  piVar5 = &DAT_0052baf0;
  do {
    iVar1 = iVar6 + -1;
    iVar6 = iVar6 + 1;
    *piVar5 = iVar1;
    piVar5 = piVar5 + 1;
  } while ((int)piVar5 < 0x52bb40);
  DAT_0052baf0 = 0x13;
  return;
}


