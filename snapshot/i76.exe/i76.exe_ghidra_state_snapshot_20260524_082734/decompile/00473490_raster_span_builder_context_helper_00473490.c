/*
 * Program: i76.exe
 * Function: raster_span_builder_context_helper_00473490
 * Entry: 00473490
 * Signature: undefined __fastcall raster_span_builder_context_helper_00473490(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster span builder context helper
   based on adjacent named subsystem context. */

void __fastcall raster_span_builder_context_helper_00473490(int param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  puVar2 = *(uint **)(param_1 + 4);
  if (puVar2 != (uint *)(param_1 + 0x20)) {
    *puVar2 = *puVar2 + puVar2[6];
    uVar4 = **(uint **)(param_1 + 4);
    puVar2 = (uint *)(*(uint **)(param_1 + 4))[1];
    while (puVar5 = puVar2, puVar5 != (uint *)(param_1 + 0x20)) {
      uVar8 = *puVar5 + puVar5[6];
      *puVar5 = uVar8;
      if (uVar8 < uVar4) {
        puVar1 = puVar5 + 1;
        puVar2 = (uint *)*puVar1;
        if ((*puVar5 & 1) == 0) {
          uVar7 = puVar5[3];
          uVar3 = **(uint **)(uVar7 + 0x20);
          if ((uVar3 <= uVar8) || (uVar8 = uVar3, uVar3 != uVar4)) {
            puVar6 = (uint *)puVar5[2];
            uVar10 = puVar5[4];
            uVar3 = *puVar6;
            while (uVar8 < uVar3) {
              uVar9 = puVar6[4];
              if (uVar9 == uVar7) {
                puVar6[4] = uVar10;
              }
              else if ((uVar3 & 1) == 0) {
                if (uVar10 == uVar9) {
                  uVar10 = puVar6[3];
                }
              }
              else if (uVar10 == puVar6[3]) {
                uVar10 = uVar9;
              }
              puVar6 = (uint *)puVar6[2];
              uVar3 = *puVar6;
            }
            puVar5[4] = uVar10;
            if ((uint *)puVar6[1] != puVar5) {
              *(uint *)(*puVar1 + 8) = puVar5[2];
              *(uint *)(puVar5[2] + 4) = *puVar1;
              uVar8 = puVar6[1];
              *puVar1 = uVar8;
              puVar5[2] = (uint)puVar6;
              *(uint **)(uVar8 + 8) = puVar5;
              puVar6[1] = (uint)puVar5;
            }
          }
        }
        else {
          puVar6 = (uint *)puVar5[2];
          uVar7 = *puVar6;
          if (uVar8 < uVar7) {
            uVar3 = puVar5[3];
            uVar10 = puVar5[4];
            do {
              uVar9 = uVar10;
              if ((uVar7 & 1) == 0) {
                if ((uVar10 == puVar6[4]) &&
                   (uVar9 = puVar6[3], *(uint *)(uVar3 + 0x34) <= *(uint *)(uVar9 + 0x34))) {
                  puVar6[4] = uVar3;
                  uVar9 = uVar10;
                }
              }
              else if (uVar10 == puVar6[3]) {
                uVar9 = puVar6[4];
              }
              else if (uVar10 == puVar6[4]) {
                puVar6[4] = uVar3;
              }
              puVar6 = (uint *)puVar6[2];
              uVar7 = *puVar6;
              uVar10 = uVar9;
            } while (uVar8 < uVar7);
            *(uint *)(*puVar1 + 8) = puVar5[2];
            *(uint *)(puVar5[2] + 4) = *puVar1;
            uVar8 = puVar6[1];
            *puVar1 = uVar8;
            puVar5[2] = (uint)puVar6;
            *(uint **)(uVar8 + 8) = puVar5;
            puVar6[1] = (uint)puVar5;
            puVar5[4] = uVar9;
          }
        }
      }
      else {
        uVar4 = uVar8;
        puVar2 = (uint *)puVar5[1];
      }
    }
  }
  return;
}


