/*
 * Program: i76shell.dll
 * Function: blit_mw2_image_subresource_rle_unclipped
 * Entry: 1003ad68
 * Signature: undefined4 __cdecl blit_mw2_image_subresource_rle_unclipped(int * param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl
blit_mw2_image_subresource_rle_unclipped(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  byte *pbVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  bool bVar14;
  
  iVar1 = ((int *)*param_1)[1];
  iVar3 = iVar1 + 1;
  if (iVar3 != 0 && -2 < iVar1) {
    iVar1 = *(int *)(param_2 + 0xc);
    puVar12 = (uint *)(*(int *)*param_1 + *(int *)(param_2 + 8) + param_3 + param_1[1] +
                      (iVar1 + param_4 + param_1[2]) * iVar3);
    iVar4 = *(int *)(param_2 + 0x14) + 1;
    iVar5 = iVar4 - iVar1;
    if (iVar5 != 0 && iVar1 <= iVar4) {
      puVar9 = (uint *)(param_2 + 0x18);
      do {
        uVar8 = *puVar9;
        puVar9 = (uint *)((int)puVar9 + 1);
        bVar14 = (bool)((byte)uVar8 & 1);
        bVar2 = (byte)uVar8 >> 1;
        uVar8 = (uint)bVar2;
        puVar13 = puVar12;
        if (!bVar14 && bVar2 != 0) goto LAB_1003ade4;
        if (bVar2 != 0) goto LAB_1003ae23;
joined_r0x1003adc9:
        if (bVar14) {
          do {
            while( true ) {
              pbVar10 = (byte *)((int)puVar9 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)(byte)*puVar9);
              puVar9 = (uint *)((int)puVar9 + 2);
              bVar14 = (bool)(*pbVar10 & 1);
              bVar2 = *pbVar10 >> 1;
              uVar8 = (uint)bVar2;
              if (!bVar14 && bVar2 != 0) goto LAB_1003ade4;
              if (bVar2 == 0) break;
LAB_1003ae23:
              do {
                while( true ) {
                  puVar11 = puVar9;
                  if (4 < uVar8) {
                    uVar6 = -(int)puVar13 & 3;
                    uVar7 = uVar8 - uVar6;
                    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(byte *)puVar13 = (byte)*puVar9;
                      puVar9 = (uint *)((int)puVar9 + 1);
                      puVar13 = (uint *)((int)puVar13 + 1);
                    }
                    uVar8 = uVar7 & 3;
                    puVar11 = puVar9;
                    for (uVar7 = uVar7 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *puVar13 = *puVar11;
                      puVar11 = puVar11 + 1;
                      puVar13 = puVar13 + 1;
                    }
                  }
                  for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(byte *)puVar13 = (byte)*puVar11;
                    puVar11 = (uint *)((int)puVar11 + 1);
                    puVar13 = (uint *)((int)puVar13 + 1);
                  }
                  puVar9 = (uint *)((int)puVar11 + 1);
                  bVar14 = (bool)((byte)*puVar11 & 1);
                  bVar2 = (byte)*puVar11 >> 1;
                  uVar8 = (uint)bVar2;
                  if (!bVar14 && bVar2 != 0) break;
                  if (bVar2 == 0) goto joined_r0x1003adc9;
                }
LAB_1003ade4:
                do {
                  bVar2 = (byte)*puVar9;
                  uVar6 = (uint)bVar2;
                  pbVar10 = (byte *)((int)puVar9 + 1);
                  if (4 < uVar8) {
                    uVar6 = -(int)puVar13 & 3;
                    uVar7 = uVar8 - uVar6;
                    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(byte *)puVar13 = bVar2;
                      puVar13 = (uint *)((int)puVar13 + 1);
                    }
                    uVar6 = CONCAT31(CONCAT21(CONCAT11(bVar2,bVar2),bVar2),bVar2);
                    uVar8 = uVar7 & 3;
                    for (uVar7 = uVar7 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *puVar13 = uVar6;
                      puVar13 = puVar13 + 1;
                    }
                  }
                  for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(byte *)puVar13 = (byte)uVar6;
                    puVar13 = (uint *)((int)puVar13 + 1);
                  }
                  puVar9 = (uint *)((int)puVar9 + 2);
                  bVar14 = (bool)(*pbVar10 & 1);
                  bVar2 = *pbVar10 >> 1;
                  uVar8 = (uint)bVar2;
                } while (!bVar14 && bVar2 != 0);
                if (!bVar14) goto LAB_1003ae57;
              } while (bVar2 != 0);
            }
          } while (bVar14);
        }
LAB_1003ae57:
        puVar12 = (uint *)((int)puVar12 + iVar3);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return 0;
}


