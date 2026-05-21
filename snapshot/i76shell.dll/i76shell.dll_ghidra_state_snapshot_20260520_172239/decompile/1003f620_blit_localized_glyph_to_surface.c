/*
 * Program: i76shell.dll
 * Function: blit_localized_glyph_to_surface
 * Entry: 1003f620
 * Signature: int __cdecl blit_localized_glyph_to_surface(int * param_1, int param_2, int param_3, int param_4, uint param_5, int param_6)
 */


/* i76shell locale/rich-text rename
   old_name: FUN_1003f620
   forced_name: set_character_stride_or_locale_mode
   basis: Writes DAT_1004efa0; likely switches between single-byte and two-byte text modes.
   
   i76shell localized glyph rename
   old_name: set_character_stride_or_locale_mode
   forced_name: blit_localized_glyph_to_surface
   basis: Maps localized/DBCS glyph code, reads record-65 1bpp bit-packed glyph payload, and blits
   to destination surface. */

int __cdecl
blit_localized_glyph_to_surface
          (int *param_1,int param_2,int param_3,int param_4,uint param_5,int param_6)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined2 uVar12;
  int iVar10;
  byte *pbVar11;
  uint uVar13;
  undefined3 uVar15;
  uint uVar14;
  char cVar16;
  char cVar19;
  int iVar17;
  uint uVar18;
  byte bVar21;
  uint uVar20;
  uint *puVar23;
  bool bVar24;
  uint local_c;
  uint local_8;
  byte bVar22;
  
  piVar2 = (int *)*param_1;
  iVar10 = piVar2[1];
  iVar5 = iVar10 + 1;
  if ((iVar5 == 0 || iVar10 < -1) || (iVar17 = piVar2[2], iVar17 < 0)) {
    return -1;
  }
  iVar9 = param_1[1];
  iVar6 = iVar9;
  if (iVar9 < 1) {
    iVar6 = 0;
  }
  iVar3 = param_1[2];
  iVar7 = iVar3;
  if (iVar3 < 1) {
    iVar7 = 0;
  }
  iVar8 = param_1[3];
  if (iVar10 <= param_1[3]) {
    iVar8 = iVar10;
  }
  iVar10 = param_1[4];
  if (iVar17 <= param_1[4]) {
    iVar10 = iVar17;
  }
  if ((iVar8 < iVar6) || (iVar10 < iVar7)) {
    return -1;
  }
  param_2 = param_2 + iVar9;
  param_3 = param_3 + iVar3;
  iVar17 = *(int *)(param_4 + 8);
  iVar9 = (param_5 & 0xffff00ff) * 2;
  DAT_1004efa0 = 2;
  sVar1 = *(short *)(DAT_1004ef9c + iVar9);
  uVar12 = (undefined2)((uint)iVar9 >> 0x10);
  if (sVar1 == 0) {
    iVar9 = CONCAT31((int3)(CONCAT22(uVar12,sVar1) >> 8),(char)param_5);
    DAT_1004efa0 = 1;
  }
  else {
    iVar9 = CONCAT22(uVar12,sVar1 + ((ushort)param_5 >> 8));
  }
  puVar23 = (uint *)(*(int *)(iVar9 * 4 + param_4 + 0x10) + param_4);
  local_c = 0;
  local_8 = *puVar23;
  if (local_8 != 0) {
    puVar23 = puVar23 + 1;
    iVar9 = ((iVar8 + 1) - local_8) - param_2;
    uVar13 = local_8;
    if ((-1 < iVar9) ||
       (uVar13 = local_8 + iVar9, uVar13 != 0 && SCARRY4(local_8,iVar9) == (int)uVar13 < 0)) {
      iVar6 = param_2 - iVar6;
      if (iVar6 < 0) {
        bVar24 = SCARRY4(uVar13,iVar6);
        uVar13 = uVar13 + iVar6;
        if (uVar13 == 0 || bVar24 != (int)uVar13 < 0) goto LAB_1003f7d9;
        puVar23 = (uint *)((int)puVar23 - iVar6);
        param_2 = param_2 - iVar6;
      }
      iVar10 = ((iVar10 + 1) - iVar17) - param_3;
      if ((-1 < iVar10) ||
         (bVar24 = SCARRY4(iVar17,iVar10), iVar17 = iVar17 + iVar10,
         iVar17 != 0 && bVar24 == iVar17 < 0)) {
        iVar7 = param_3 - iVar7;
        if (iVar7 < 0) {
          bVar24 = SCARRY4(iVar17,iVar7);
          iVar17 = iVar17 + iVar7;
          if (iVar17 == 0 || bVar24 != iVar17 < 0) goto LAB_1003f7d9;
          param_3 = param_3 - iVar7;
          puVar23 = (uint *)((int)puVar23 - iVar7 * local_8);
        }
        bVar21 = (byte)iVar17;
        pbVar11 = (byte *)(param_3 * iVar5 + *piVar2 + param_2);
        local_8 = local_8 - uVar13;
        local_c = uVar13;
        if (uVar13 != 0) {
          bVar4 = DAT_1004efa4;
          if (param_6 != 0) {
            bVar4 = *(byte *)(param_6 + (uint)DAT_1004efa4);
          }
          if (bVar4 != 0xff) {
            uVar20 = uVar13 & 0xff;
            do {
              uVar18 = (uint)bVar21;
              uVar15 = (undefined3)(uVar13 >> 8);
              cVar16 = (char)uVar20;
              uVar14 = CONCAT31(uVar15,cVar16);
              uVar20 = (uint)CONCAT11(cVar16,cVar16);
              if ('\b' < cVar16) {
                uVar14 = CONCAT31(uVar15,8);
              }
              do {
                uVar18 = (uint)CONCAT11((char)*puVar23,(char)uVar18);
                do {
                  cVar19 = (char)(uVar18 >> 8);
                  cVar16 = (char)uVar18;
                  uVar18 = (uint)CONCAT11(cVar19 << 1,cVar16);
                  if (cVar19 < '\0') {
                    *pbVar11 = bVar4;
                  }
                  pbVar11 = pbVar11 + 1;
                  uVar14 = uVar14 - 1;
                } while (uVar14 != 0);
                puVar23 = (uint *)((int)puVar23 + 1);
                bVar22 = (byte)(uVar20 >> 8);
                bVar21 = bVar22 - 8;
                uVar20 = (uint)CONCAT11(bVar21,(char)uVar20);
              } while ((7 < bVar22 && bVar21 != 0) && (uVar14 = (uint)bVar21, 7 < bVar22));
              puVar23 = (uint *)((int)puVar23 + local_8);
              pbVar11 = pbVar11 + (iVar5 - uVar13);
              bVar21 = cVar16 - 1;
            } while (bVar21 != 0);
          }
        }
      }
    }
  }
LAB_1003f7d9:
  return local_8 + local_c;
}


