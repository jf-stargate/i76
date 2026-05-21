/*
 * Program: i76shell.dll
 * Function: blit_or_fill_rect_clipped
 * Entry: 1003c888
 * Signature: undefined4 __cdecl blit_or_fill_rect_clipped(int * param_1, int param_2, int param_3, int * param_4, int param_5, int param_6, uint param_7)
 */


/* i76shell text/glyph rename
   old_name: FUN_1003c888
   suggested_name: blit_or_fill_rect_clipped
   basis: Clipped rectangle primitive; fills a rect or copies pixels depending on high bits of
   parameter flags.
   
   i76shell forced text/glyph rename
   old_name: blit_or_fill_rect_clipped
   forced_name: blit_or_fill_rect_clipped
   basis: Clipped rectangle primitive; fills or copies depending on flags. */

undefined4 __cdecl
blit_or_fill_rect_clipped
          (int *param_1,int param_2,int param_3,int *param_4,int param_5,int param_6,uint param_7)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  undefined1 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  int iVar25;
  uint uVar26;
  undefined1 *puVar27;
  undefined4 *puVar28;
  undefined1 *puVar29;
  undefined4 *puVar30;
  int local_60;
  int local_54;
  int local_40;
  
  piVar1 = (int *)*param_1;
  iVar25 = piVar1[1];
  iVar9 = iVar25 + 1;
  if ((iVar9 == 0 || iVar25 < -1) || (iVar23 = piVar1[2], iVar23 < 0)) {
    return 0xffffffff;
  }
  iVar2 = param_1[1];
  iVar10 = iVar2;
  if (iVar2 < 1) {
    iVar10 = 0;
  }
  iVar3 = param_1[2];
  iVar11 = iVar3;
  if (iVar3 < 1) {
    iVar11 = 0;
  }
  iVar12 = param_1[3];
  if (iVar25 <= param_1[3]) {
    iVar12 = iVar25;
  }
  iVar25 = param_1[4];
  if (iVar23 <= param_1[4]) {
    iVar25 = iVar23;
  }
  if ((iVar12 < iVar10) || (iVar25 < iVar11)) {
    return 0xfffffffe;
  }
  iVar10 = iVar10 - iVar2;
  iVar12 = iVar12 - iVar2;
  iVar11 = iVar11 - iVar3;
  iVar25 = iVar25 - iVar3;
  piVar4 = (int *)*param_4;
  iVar23 = piVar4[1];
  iVar13 = iVar23 + 1;
  if ((iVar13 == 0 || iVar23 < -1) || (iVar18 = piVar4[2], iVar18 < 0)) {
    return 0xffffffff;
  }
  iVar5 = param_4[1];
  iVar14 = iVar5;
  if (iVar5 < 1) {
    iVar14 = 0;
  }
  iVar6 = param_4[2];
  iVar15 = iVar6;
  if (iVar6 < 1) {
    iVar15 = 0;
  }
  iVar22 = param_4[3];
  if (iVar23 <= param_4[3]) {
    iVar22 = iVar23;
  }
  iVar23 = param_4[4];
  if (iVar18 <= param_4[4]) {
    iVar23 = iVar18;
  }
  if ((iVar14 <= iVar22) && (iVar15 <= iVar23)) {
    iVar14 = iVar14 - iVar5;
    iVar22 = iVar22 - iVar5;
    iVar15 = iVar15 - iVar6;
    iVar23 = iVar23 - iVar6;
    iVar16 = param_2 - param_5;
    iVar17 = param_3 - param_6;
    iVar18 = iVar10;
    if (iVar10 <= iVar14 + iVar16) {
      iVar18 = iVar14 + iVar16;
    }
    iVar19 = iVar11;
    if (iVar11 <= iVar15 + iVar17) {
      iVar19 = iVar15 + iVar17;
    }
    iVar20 = iVar12;
    if (iVar22 + iVar16 <= iVar12) {
      iVar20 = iVar22 + iVar16;
    }
    iVar21 = iVar25;
    if (iVar23 + iVar17 <= iVar25) {
      iVar21 = iVar23 + iVar17;
    }
    if ((iVar18 <= iVar20) && (iVar19 <= iVar21)) {
      if (iVar14 <= iVar10 - iVar16) {
        iVar14 = iVar10 - iVar16;
      }
      if (iVar15 <= iVar11 - iVar17) {
        iVar15 = iVar11 - iVar17;
      }
      if (iVar12 - iVar16 <= iVar22) {
        iVar22 = iVar12 - iVar16;
      }
      if (iVar25 - iVar17 <= iVar23) {
        iVar23 = iVar25 - iVar17;
      }
      uVar24 = (iVar20 + 1) - iVar18;
      iVar25 = (iVar21 + 1) - iVar19;
      local_54 = iVar13;
      local_40 = iVar9;
      if (iVar19 <= iVar15) {
        local_54 = -iVar13;
        local_40 = -iVar9;
        iVar19 = iVar21;
        iVar15 = iVar23;
      }
      bVar7 = iVar18 <= iVar14;
      if (bVar7) {
        local_60 = 3;
        uVar26 = uVar24;
      }
      else {
        local_60 = 0;
        iVar20 = iVar18;
        iVar22 = iVar14;
        uVar26 = -uVar24;
      }
      local_40 = local_40 + uVar26;
      local_54 = local_54 + uVar26;
      puVar29 = (undefined1 *)(iVar6 * iVar13 + *piVar4 + iVar5 + iVar15 * iVar13 + iVar22);
      puVar27 = (undefined1 *)(iVar3 * iVar9 + *piVar1 + iVar2 + iVar19 * iVar9 + iVar20);
      if ((param_7 & 0xffffff00) == 0) {
        uVar8 = (undefined1)param_7;
        do {
          for (uVar26 = uVar24 & 3; uVar26 != 0; uVar26 = uVar26 - 1) {
            *puVar29 = uVar8;
            puVar29 = puVar29 + (uint)bVar7 * -2 + 1;
          }
          puVar28 = (undefined4 *)(puVar29 + -local_60);
          for (uVar26 = uVar24 >> 2; uVar26 != 0; uVar26 = uVar26 - 1) {
            *puVar28 = CONCAT22(CONCAT11(uVar8,uVar8),CONCAT11(uVar8,uVar8));
            puVar28 = puVar28 + (uint)bVar7 * -2 + 1;
          }
          puVar29 = (undefined1 *)((int)puVar28 + local_54 + local_60);
          iVar25 = iVar25 + -1;
        } while (iVar25 != 0);
      }
      else {
        do {
          for (uVar26 = uVar24 & 3; uVar26 != 0; uVar26 = uVar26 - 1) {
            *puVar29 = *puVar27;
            puVar27 = puVar27 + (uint)bVar7 * -2 + 1;
            puVar29 = puVar29 + (uint)bVar7 * -2 + 1;
          }
          puVar28 = (undefined4 *)(puVar27 + -local_60);
          puVar30 = (undefined4 *)(puVar29 + -local_60);
          for (uVar26 = uVar24 >> 2; uVar26 != 0; uVar26 = uVar26 - 1) {
            *puVar30 = *puVar28;
            puVar28 = puVar28 + (uint)bVar7 * -2 + 1;
            puVar30 = puVar30 + (uint)bVar7 * -2 + 1;
          }
          puVar27 = (undefined1 *)((int)puVar28 + local_40 + local_60);
          puVar29 = (undefined1 *)((int)puVar30 + local_54 + local_60);
          iVar25 = iVar25 + -1;
        } while (iVar25 != 0);
      }
      return 0;
    }
    return 0xfffffffd;
  }
  return 0xfffffffe;
}


