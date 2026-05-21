/*
 * Program: i76shell.dll
 * Function: blit_glyph_to_surface
 * Entry: 1003e44c
 * Signature: int __cdecl blit_glyph_to_surface(int * param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


/* i76shell text/glyph rename
   old_name: FUN_1003e44c
   suggested_name: blit_glyph_to_surface
   basis: Blits one glyph from a glyph sheet to a destination surface/clip region, with optional
   translation table.
   
   i76shell forced text/glyph rename
   old_name: blit_glyph_to_surface
   forced_name: blit_glyph_to_surface
   basis: Blits one glyph to a destination surface/clip region. */

int __cdecl
blit_glyph_to_surface(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  byte *pbVar12;
  bool bVar13;
  int local_c;
  int local_8;
  
  piVar1 = (int *)*param_1;
  iVar7 = piVar1[1];
  iVar2 = iVar7 + 1;
  if ((iVar2 == 0 || iVar7 < -1) || (iVar10 = piVar1[2], iVar10 < 0)) {
    return -1;
  }
  iVar9 = param_1[1];
  iVar3 = iVar9;
  if (iVar9 < 1) {
    iVar3 = 0;
  }
  iVar6 = param_1[2];
  iVar4 = iVar6;
  if (iVar6 < 1) {
    iVar4 = 0;
  }
  iVar5 = param_1[3];
  if (iVar7 <= param_1[3]) {
    iVar5 = iVar7;
  }
  iVar7 = param_1[4];
  if (iVar10 <= param_1[4]) {
    iVar7 = iVar10;
  }
  if ((iVar5 < iVar3) || (iVar7 < iVar4)) {
    return -2;
  }
  param_2 = param_2 + iVar9;
  param_3 = param_3 + iVar6;
  iVar10 = *(int *)(param_4 + 8);
  piVar11 = (int *)(*(int *)(param_5 * 4 + param_4 + 0x10) + param_4);
  local_c = 0;
  local_8 = *piVar11;
  if (local_8 != 0) {
    pbVar12 = (byte *)(piVar11 + 1);
    iVar6 = ((iVar5 + 1) - local_8) - param_2;
    iVar9 = local_8;
    if ((-1 < iVar6) || (iVar9 = local_8 + iVar6, iVar9 != 0 && SCARRY4(local_8,iVar6) == iVar9 < 0)
       ) {
      iVar3 = param_2 - iVar3;
      if (iVar3 < 0) {
        bVar13 = SCARRY4(iVar9,iVar3);
        iVar9 = iVar9 + iVar3;
        if (iVar9 == 0 || bVar13 != iVar9 < 0) goto LAB_1003e5cb;
        pbVar12 = pbVar12 + -iVar3;
        param_2 = param_2 - iVar3;
      }
      iVar7 = ((iVar7 + 1) - iVar10) - param_3;
      if ((-1 < iVar7) ||
         (bVar13 = SCARRY4(iVar10,iVar7), iVar10 = iVar10 + iVar7,
         iVar10 != 0 && bVar13 == iVar10 < 0)) {
        iVar4 = param_3 - iVar4;
        if (iVar4 < 0) {
          bVar13 = SCARRY4(iVar10,iVar4);
          iVar10 = iVar10 + iVar4;
          if (iVar10 == 0 || bVar13 != iVar10 < 0) goto LAB_1003e5cb;
          param_3 = param_3 - iVar4;
          pbVar12 = pbVar12 + -(iVar4 * local_8);
        }
        pbVar8 = (byte *)(param_3 * iVar2 + *piVar1 + param_2);
        local_8 = local_8 - iVar9;
        iVar7 = iVar9;
        if (param_6 == 0) {
          do {
            for (; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pbVar8 = *pbVar12;
              pbVar12 = pbVar12 + 1;
              pbVar8 = pbVar8 + 1;
            }
            pbVar12 = pbVar12 + local_8;
            pbVar8 = pbVar8 + (iVar2 - iVar9);
            iVar10 = iVar10 + -1;
            iVar7 = iVar9;
          } while (iVar10 != 0);
          return local_8 + iVar9;
        }
        while (iVar3 = iVar9, local_c = iVar9, iVar7 != 0) {
          do {
            if (*(byte *)(param_6 + (uint)*pbVar12) != 0xff) {
              *pbVar8 = *(byte *)(param_6 + (uint)*pbVar12);
            }
            pbVar12 = pbVar12 + 1;
            pbVar8 = pbVar8 + 1;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          pbVar12 = pbVar12 + local_8;
          pbVar8 = pbVar8 + (iVar2 - iVar9);
          iVar10 = iVar10 + -1;
          iVar7 = iVar10;
        }
      }
    }
  }
LAB_1003e5cb:
  return local_8 + local_c;
}


