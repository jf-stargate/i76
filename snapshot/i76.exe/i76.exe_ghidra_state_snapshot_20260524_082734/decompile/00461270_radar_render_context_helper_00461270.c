/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00461270
 * Entry: 00461270
 * Signature: undefined4 __cdecl radar_render_context_helper_00461270(uint param_1, uint param_2)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00461270. Shorten
   readability label. */

undefined4 __cdecl radar_render_context_helper_00461270(uint param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    puVar6 = *(uint **)(iVar1 + 4);
    if ((*(byte *)(param_1 + 0x10) & 0x20) == 0) {
      if (puVar6 != (uint *)0x0) {
        do {
          if (*puVar6 == param_2) break;
          puVar6 = (uint *)puVar6[8];
        } while (puVar6 != (uint *)0x0);
        if (puVar6 != (uint *)0x0) {
          if (*(int *)(iVar1 + 0x54) != 0) {
            *(undefined1 *)(*(int *)(iVar1 + 0x54) + 0x1c) = 0x69;
          }
          *(undefined4 *)(iVar1 + 0x54) = 0;
          uVar7 = *(uint *)(iVar1 + 0xc) & 0xffffffed;
          *(uint *)(iVar1 + 0xc) = uVar7;
          puVar9 = &DAT_004faed8;
          puVar10 = (undefined4 *)(iVar1 + 0x10);
          for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
            *puVar10 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar10 = puVar10 + 1;
          }
          *(uint **)(iVar1 + 0x54) = puVar6;
          *(undefined4 *)(iVar1 + 0x50) = 0;
          *(uint *)(iVar1 + 0xc) = uVar7 | 0x10;
          return 1;
        }
      }
      iVar8 = *(int *)(iVar1 + 0x54);
    }
    else {
      while (puVar6 != (uint *)0x0) {
        *(uint *)(iVar1 + 4) = puVar6[8];
        HeapFree(DAT_0054b1f8,0,puVar6);
        puVar6 = *(uint **)(iVar1 + 4);
      }
      if (param_2 != 0) {
        puVar6 = *(uint **)(iVar1 + 4);
        puVar5 = HeapAlloc(DAT_0054b1f8,0,0x24);
        if (puVar5 != (uint *)0x0) {
          *puVar5 = param_2;
          radar_render_context_helper_00460c80(puVar5,param_1);
          *(undefined1 *)(puVar5 + 7) = 0x69;
          puVar4 = puVar6;
          puVar3 = (uint *)0x0;
          while ((puVar2 = puVar4, puVar2 != (uint *)0x0 && ((float)puVar2[5] <= (float)puVar5[5])))
          {
            puVar3 = puVar2;
            puVar4 = (uint *)puVar2[8];
          }
          if (puVar3 == (uint *)0x0) {
            puVar5[8] = (uint)puVar6;
            puVar6 = puVar5;
          }
          else {
            puVar5[8] = puVar3[8];
            puVar3[8] = (uint)puVar5;
          }
        }
        *(uint **)(iVar1 + 4) = puVar6;
        *(uint **)(iVar1 + 0x54) = puVar6;
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x10;
        return 1;
      }
      iVar8 = *(int *)(iVar1 + 0x54);
    }
    if (iVar8 != 0) {
      *(undefined1 *)(iVar8 + 0x1c) = 0x69;
    }
    *(undefined4 *)(iVar1 + 0x54) = 0;
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffed;
    puVar9 = &DAT_004faed8;
    puVar10 = (undefined4 *)(iVar1 + 0x10);
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
  }
  return 0;
}


