/*
 * Program: i76.exe
 * Function: draw_clipped_line_to_bitmap_surface
 * Entry: 0048d2e0
 * Signature: undefined __cdecl draw_clipped_line_to_bitmap_surface(int * param_1, int param_2, int param_3, int param_4, int param_5, undefined1 param_6, int param_7)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] General clipped Bresenham-style 8bpp
   line drawer for bitmap/surface contexts. */

void __cdecl
draw_clipped_line_to_bitmap_surface
          (int *param_1,int param_2,int param_3,int param_4,int param_5,undefined1 param_6,
          int param_7)

{
  byte bVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte bVar10;
  undefined1 *puVar11;
  int local_30 [11];
  
  if (param_1[0xb] != 0) {
    local_30[1] = *param_1;
    piVar3 = param_1 + 7;
    uVar8 = (param_2 + -1) - param_1[9];
    uVar9 = (param_3 + -1) - param_1[10];
    bVar1 = ((CARRY4(param_2 - *piVar3,param_2 - *piVar3) * '\x02' + CARRY4(uVar8,uVar8)) * '\x02' +
            CARRY4(param_3 - param_1[8],param_3 - param_1[8])) * '\x02' + CARRY4(uVar9,uVar9) ^ 5;
    uVar8 = (param_4 + -1) - param_1[9];
    uVar9 = (param_5 + -1) - param_1[10];
    bVar2 = ((CARRY4(param_4 - *piVar3,param_4 - *piVar3) * '\x02' + CARRY4(uVar8,uVar8)) * '\x02' +
            CARRY4(param_5 - param_1[8],param_5 - param_1[8])) * '\x02' + CARRY4(uVar9,uVar9) ^ 5;
    if (bVar2 != 0 || bVar1 != 0) {
      do {
        if ((bVar1 & bVar2) != 0) {
          return;
        }
        bVar10 = bVar1;
        if (bVar1 == 0) {
          bVar10 = bVar2;
        }
        if ((bVar10 & 8) == 0) {
          if ((bVar10 & 4) == 0) {
            if ((bVar10 & 2) == 0) {
              iVar4 = (int)(((longlong)(param_4 - param_2) * (longlong)(param_1[10] - param_3)) /
                           (longlong)(param_5 - param_3)) + param_2;
              iVar5 = param_1[10];
            }
            else {
              iVar4 = (int)(((longlong)(param_4 - param_2) * (longlong)(param_1[8] - param_3)) /
                           (longlong)(param_5 - param_3)) + param_2;
              iVar5 = param_1[8];
            }
          }
          else {
            iVar5 = param_3 + (int)(((longlong)(param_5 - param_3) *
                                    (longlong)(param_1[9] - param_2)) /
                                   (longlong)(param_4 - param_2));
            iVar4 = param_1[9];
          }
        }
        else {
          iVar5 = param_3 + (int)(((longlong)(param_5 - param_3) * (longlong)(*piVar3 - param_2)) /
                                 (longlong)(param_4 - param_2));
          iVar4 = *piVar3;
        }
        if (bVar10 == bVar1) {
          uVar8 = (iVar4 + -1) - param_1[9];
          uVar9 = (iVar5 + -1) - param_1[10];
          bVar1 = ((CARRY4(iVar4 - *piVar3,iVar4 - *piVar3) * '\x02' + CARRY4(uVar8,uVar8)) * '\x02'
                  + CARRY4(iVar5 - param_1[8],iVar5 - param_1[8])) * '\x02' + CARRY4(uVar9,uVar9) ^
                  5;
          param_2 = iVar4;
          param_3 = iVar5;
        }
        else {
          uVar8 = (iVar4 + -1) - param_1[9];
          uVar9 = (iVar5 + -1) - param_1[10];
          bVar2 = ((CARRY4(iVar4 - *piVar3,iVar4 - *piVar3) * '\x02' + CARRY4(uVar8,uVar8)) * '\x02'
                  + CARRY4(iVar5 - param_1[8],iVar5 - param_1[8])) * '\x02' + CARRY4(uVar9,uVar9) ^
                  5;
          param_4 = iVar4;
          param_5 = iVar5;
        }
      } while (bVar2 != 0 || bVar1 != 0);
    }
    iVar5 = param_4 - param_2;
    iVar4 = param_5 - param_3;
    puVar11 = (undefined1 *)((param_1[8] + param_3) * local_30[1] + param_1[5] + param_2 + *piVar3);
    if (param_7 == 0) {
      if (-1 < iVar4) {
        if (-1 < iVar5) {
          if (iVar5 < iVar4) {
            iVar6 = iVar5 * 2 - iVar4;
            local_30[0] = local_30[1] + 1;
            local_30[3] = iVar5 * 2;
            local_30[2] = iVar6 - iVar4;
          }
          else {
            iVar6 = iVar4 * 2 - iVar5;
            local_30[0] = local_30[1] + 1;
            local_30[1] = 1;
            local_30[3] = iVar4 * 2;
            local_30[2] = iVar6 - iVar5;
            iVar4 = iVar5;
          }
          iVar4 = iVar4 + 1;
          while( true ) {
            iVar5 = iVar6 >> 0x1f;
            iVar4 = iVar4 + -1;
            if (iVar4 == 0) break;
            iVar6 = iVar6 + local_30[2 - iVar5];
            iVar5 = local_30[-iVar5];
            *puVar11 = param_6;
            puVar11 = puVar11 + iVar5;
          }
          return;
        }
        if (-iVar5 < iVar4) {
          iVar6 = iVar5 * -2 - iVar4;
          local_30[0] = local_30[1] + -1;
          local_30[3] = iVar5 * -2;
          local_30[2] = iVar6 - iVar4;
        }
        else {
          iVar6 = iVar4 * 2 + iVar5;
          local_30[0] = local_30[1] + -1;
          local_30[1] = 0xffffffff;
          local_30[3] = iVar4 * 2;
          local_30[2] = iVar6 + iVar5;
          iVar4 = -iVar5;
        }
        iVar4 = iVar4 + 1;
        while( true ) {
          iVar5 = iVar6 >> 0x1f;
          iVar4 = iVar4 + -1;
          if (iVar4 == 0) break;
          iVar6 = iVar6 + local_30[2 - iVar5];
          iVar5 = local_30[-iVar5];
          *puVar11 = param_6;
          puVar11 = puVar11 + iVar5;
        }
        return;
      }
      if (-1 < iVar5) {
        local_30[1] = -local_30[1];
        iVar6 = -iVar4;
        if (iVar5 < iVar6) {
          iVar7 = iVar5 * 2 + iVar4;
          local_30[0] = local_30[1] + 1;
          local_30[3] = iVar5 * 2;
          local_30[2] = iVar7 + iVar4;
        }
        else {
          iVar7 = iVar4 * -2 - iVar5;
          local_30[0] = local_30[1] + 1;
          local_30[1] = 1;
          local_30[3] = iVar4 * -2;
          local_30[2] = iVar7 - iVar5;
          iVar6 = iVar5;
        }
        iVar6 = iVar6 + 1;
        while( true ) {
          iVar4 = iVar7 >> 0x1f;
          iVar6 = iVar6 + -1;
          if (iVar6 == 0) break;
          iVar7 = iVar7 + local_30[2 - iVar4];
          iVar4 = local_30[-iVar4];
          *puVar11 = param_6;
          puVar11 = puVar11 + iVar4;
        }
        return;
      }
      local_30[1] = -local_30[1];
      iVar6 = -iVar4;
      if (-iVar5 < iVar6) {
        iVar7 = iVar5 * -2 + iVar4;
        local_30[0] = local_30[1] + -1;
        local_30[3] = iVar5 * -2;
        local_30[2] = iVar7 + iVar4;
      }
      else {
        iVar7 = iVar4 * -2 + iVar5;
        local_30[0] = local_30[1] + -1;
        local_30[1] = 0xffffffff;
        local_30[3] = iVar4 * -2;
        local_30[2] = iVar7 + iVar5;
        iVar6 = -iVar5;
      }
      iVar6 = iVar6 + 1;
      while( true ) {
        iVar4 = iVar7 >> 0x1f;
        iVar6 = iVar6 + -1;
        if (iVar6 == 0) break;
        iVar7 = iVar7 + local_30[2 - iVar4];
        iVar4 = local_30[-iVar4];
        *puVar11 = param_6;
        puVar11 = puVar11 + iVar4;
      }
    }
  }
  return;
}


