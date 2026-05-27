/*
 * Program: i76.exe
 * Function: decode_vqm_cbk_4x4_blocks_to_indexed_pixels
 * Entry: 0044b430
 * Signature: undefined4 __cdecl decode_vqm_cbk_4x4_blocks_to_indexed_pixels(uint * param_1, int param_2, uint * param_3, uint param_4)
 */


/* [i76 level/static/material baseline v48]
   name: decode_vqm_cbk_4x4_blocks_to_indexed_pixels
   confidence: high
   module: material_vqm_cbk
   Decodes VQM/CBK 4x4 indexed blocks. Static material pass v41+ shows VQM-first is generally
   correct for M06 building/static texture families; road/junction details remain type-specific.
   note: Name already matches baseline. */

undefined4 __cdecl
decode_vqm_cbk_4x4_blocks_to_indexed_pixels(uint *param_1,int param_2,uint *param_3,uint param_4)

{
  uint *puVar1;
  ushort uVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  int local_1c;
  uint *local_14;
  uint local_10;
  
  if (*param_1 * param_1[1] + 0x18 <= param_4) {
    puVar9 = param_1 + 6;
    *param_3 = *param_1;
    uVar6 = param_1[1];
    puVar3 = (uint *)*param_3;
    param_3[1] = uVar6;
    uVar6 = (int)(uVar6 << 3) >> 3;
    puVar1 = param_3 + 2;
    local_1c = 0;
    param_1 = puVar9;
    if (3 < uVar6) {
      local_10 = 3;
      param_3 = puVar1;
      do {
        uVar7 = 0;
        param_4 = 0;
        if ((uint *)0x3 < puVar3) {
          local_14 = (uint *)0x3;
          do {
            uVar2 = (ushort)*puVar9;
            uVar7 = 0;
            iVar8 = param_4 + (int)param_3;
            do {
              uVar4 = 0;
              do {
                if ((uVar2 & 0x8000) == 0) {
                  *(undefined1 *)(uVar4 + iVar8) =
                       *(undefined1 *)(param_2 + 4 + (uVar7 + (uint)uVar2 * 4) * 4 + uVar4);
                }
                else {
                  *(char *)(uVar4 + iVar8) = (char)uVar2;
                }
                uVar4 = uVar4 + 1;
              } while (uVar4 < 4);
              uVar7 = uVar7 + 1;
              iVar8 = iVar8 + (int)puVar3;
            } while (uVar7 < 4);
            local_14 = local_14 + 1;
            puVar9 = (uint *)((int)param_1 + 2);
            uVar7 = param_4 + 4;
            param_1 = puVar9;
            param_4 = uVar7;
          } while (local_14 < puVar3);
        }
        uVar4 = (uint)puVar3 & 3;
        if (uVar4 != 0) {
          uVar2 = (ushort)*puVar9;
          iVar8 = uVar7 + (int)param_3;
          uVar7 = 0;
          do {
            uVar5 = 0;
            if (uVar4 != 0) {
              do {
                if ((uVar2 & 0x8000) == 0) {
                  *(undefined1 *)(uVar5 + iVar8) =
                       *(undefined1 *)(param_2 + 4 + (uVar7 + (uint)uVar2 * 4) * 4 + uVar5);
                }
                else {
                  *(char *)(uVar5 + iVar8) = (char)uVar2;
                }
                uVar5 = uVar5 + 1;
              } while (uVar5 < uVar4);
            }
            uVar7 = uVar7 + 1;
            iVar8 = iVar8 + (int)puVar3;
          } while (uVar7 < 4);
          puVar9 = (uint *)((int)param_1 + 2);
          param_1 = puVar9;
        }
        local_1c = local_1c + 4;
        param_3 = param_3 + (int)puVar3;
        local_10 = local_10 + 4;
      } while (local_10 < uVar6);
    }
    uVar6 = uVar6 & 3;
    if (uVar6 != 0) {
      uVar7 = 0;
      param_4 = 0;
      if ((uint *)0x3 < puVar3) {
        param_3 = (uint *)0x3;
        do {
          uVar2 = (ushort)*puVar9;
          uVar7 = 0;
          if (uVar6 != 0) {
            iVar8 = (int)puVar1 + param_4 + (int)puVar3 * local_1c;
            do {
              uVar4 = 0;
              do {
                if ((uVar2 & 0x8000) == 0) {
                  *(undefined1 *)(uVar4 + iVar8) =
                       *(undefined1 *)(param_2 + 4 + (uVar7 + (uint)uVar2 * 4) * 4 + uVar4);
                }
                else {
                  *(char *)(uVar4 + iVar8) = (char)uVar2;
                }
                uVar4 = uVar4 + 1;
              } while (uVar4 < 4);
              uVar7 = uVar7 + 1;
              iVar8 = iVar8 + (int)puVar3;
            } while (uVar7 < uVar6);
          }
          param_3 = param_3 + 1;
          puVar9 = (uint *)((int)param_1 + 2);
          uVar7 = param_4 + 4;
          param_1 = puVar9;
          param_4 = uVar7;
        } while (param_3 < puVar3);
      }
      uVar4 = (uint)puVar3 & 3;
      if (uVar4 != 0) {
        uVar2 = (ushort)*puVar9;
        uVar5 = 0;
        iVar8 = (int)puVar1 + uVar7 + (int)puVar3 * local_1c;
        if (uVar6 != 0) {
          do {
            uVar7 = 0;
            if (uVar4 != 0) {
              do {
                if ((uVar2 & 0x8000) == 0) {
                  *(undefined1 *)(uVar7 + iVar8) =
                       *(undefined1 *)(param_2 + 4 + (uVar5 + (uint)uVar2 * 4) * 4 + uVar7);
                }
                else {
                  *(char *)(uVar7 + iVar8) = (char)uVar2;
                }
                uVar7 = uVar7 + 1;
              } while (uVar7 < uVar4);
            }
            uVar5 = uVar5 + 1;
            iVar8 = iVar8 + (int)puVar3;
          } while (uVar5 < uVar6);
        }
      }
    }
    return 1;
  }
  return 0;
}


