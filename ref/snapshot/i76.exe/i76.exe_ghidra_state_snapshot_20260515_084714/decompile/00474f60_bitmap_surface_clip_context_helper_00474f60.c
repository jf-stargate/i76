/*
 * Program: i76.exe
 * Function: bitmap_surface_clip_context_helper_00474f60
 * Entry: 00474f60
 * Signature: undefined __cdecl bitmap_surface_clip_context_helper_00474f60(uint * param_1, uint param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: bitmap surface clip context helper
   based on adjacent named subsystem context. */

void __cdecl bitmap_surface_clip_context_helper_00474f60(uint *param_1,uint param_2)

{
  undefined2 uVar1;
  uint uVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  uint *puVar13;
  
  if (param_1[0xb] != 0) {
    if (param_1[2] == 1) {
      uVar2 = *param_1;
      uVar4 = param_1[8];
      uVar7 = param_1[7];
      uVar10 = param_1[5];
      uVar5 = param_2 & 0xff;
      param_2 = (param_1[10] - uVar4) + 1;
      uVar1 = (&DAT_00608460)[uVar5];
      if (0 < (int)param_2) {
        do {
          if (0 < (int)uVar2) {
            puVar12 = (undefined4 *)(uVar10 + (uVar2 * uVar4 + uVar7) * 2);
            for (uVar5 = uVar2 >> 1; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar12 = CONCAT22(uVar1,uVar1);
              puVar12 = puVar12 + 1;
            }
            for (uVar5 = (uint)((uVar2 & 1) != 0); uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined2 *)puVar12 = uVar1;
              puVar12 = (undefined4 *)((int)puVar12 + 2);
            }
          }
          param_2 = param_2 - 1;
        } while (param_2 != 0);
        return;
      }
    }
    else {
      uVar2 = *param_1;
      puVar9 = (uint *)(uVar2 * param_1[8] + param_1[5] + param_1[7]);
      iVar6 = (param_1[9] - param_1[7]) + 1;
      uVar4 = param_2 | param_2 << 8;
      iVar11 = (param_1[10] - param_1[8]) + 1;
      uVar3 = (undefined1)param_2;
      iVar8 = iVar6;
      puVar13 = puVar9;
      if (7 < iVar6) {
        do {
          uVar7 = -(int)puVar9 & 3;
          uVar10 = iVar6 - uVar7;
          puVar13 = puVar9;
          for (; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar13 = uVar3;
            puVar13 = (uint *)((int)puVar13 + 1);
          }
          uVar7 = uVar10 & 3;
          for (uVar10 = uVar10 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *puVar13 = uVar4 | uVar4 << 0x10;
            puVar13 = puVar13 + 1;
          }
          for (; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar13 = uVar3;
            puVar13 = (uint *)((int)puVar13 + 1);
          }
          puVar9 = (uint *)((int)puVar9 + uVar2);
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        return;
      }
      do {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined1 *)puVar9 = uVar3;
          puVar9 = (uint *)((int)puVar9 + 1);
        }
        puVar9 = (uint *)((int)puVar13 + uVar2);
        iVar11 = iVar11 + -1;
        iVar8 = iVar6;
        puVar13 = puVar9;
      } while (iVar11 != 0);
    }
  }
  return;
}


