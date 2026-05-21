/*
 * Program: i76shell.dll
 * Function: blit_mw2_image_subresource_rle_transparent_remap_unclipped
 * Entry: 1003b2f0
 * Signature: undefined4 __cdecl blit_mw2_image_subresource_rle_transparent_remap_unclipped(int * param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl
blit_mw2_image_subresource_rle_transparent_remap_unclipped
          (int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  uint *puVar11;
  uint *puVar12;
  bool bVar13;
  
  iVar1 = ((int *)*param_1)[1];
  iVar3 = iVar1 + 1;
  if (iVar3 != 0 && -2 < iVar1) {
    iVar1 = *(int *)(param_2 + 0xc);
    puVar11 = (uint *)(*(int *)*param_1 + *(int *)(param_2 + 8) + param_3 + param_1[1] +
                      (iVar1 + param_4 + param_1[2]) * iVar3);
    iVar4 = *(int *)(param_2 + 0x14) + 1;
    iVar5 = iVar4 - iVar1;
    if (iVar5 != 0 && iVar1 <= iVar4) {
      pbVar9 = (byte *)(param_2 + 0x18);
      do {
        bVar2 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        bVar13 = (bool)(bVar2 & 1);
        bVar2 = bVar2 >> 1;
        uVar8 = (uint)bVar2;
        puVar12 = puVar11;
        if (!bVar13 && bVar2 != 0) goto LAB_1003b368;
        if (bVar2 != 0) goto joined_r0x1003b3b6;
joined_r0x1003b351:
        if (bVar13) {
          do {
            while( true ) {
              pbVar10 = pbVar9 + 1;
              puVar12 = (uint *)((int)puVar12 + (uint)*pbVar9);
              pbVar9 = pbVar9 + 2;
              bVar13 = (bool)(*pbVar10 & 1);
              bVar2 = *pbVar10 >> 1;
              uVar8 = (uint)bVar2;
              if (!bVar13 && bVar2 != 0) goto LAB_1003b368;
              if (bVar2 == 0) break;
joined_r0x1003b3b6:
              do {
                while( true ) {
                  for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                    bVar2 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    *(byte *)puVar12 = *(byte *)((int)&DAT_1004ee3c + (uint)bVar2);
                    puVar12 = (uint *)((int)puVar12 + 1);
                  }
                  bVar2 = *pbVar9;
                  pbVar9 = pbVar9 + 1;
                  bVar13 = (bool)(bVar2 & 1);
                  bVar2 = bVar2 >> 1;
                  uVar8 = (uint)bVar2;
                  if (!bVar13 && bVar2 != 0) break;
                  if (bVar2 == 0) goto joined_r0x1003b351;
                }
LAB_1003b368:
                do {
                  pbVar10 = pbVar9 + 1;
                  bVar2 = *(byte *)((int)&DAT_1004ee3c + (uint)*pbVar9);
                  uVar6 = (uint)bVar2;
                  if (4 < uVar8) {
                    uVar6 = -(int)puVar12 & 3;
                    uVar7 = uVar8 - uVar6;
                    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(byte *)puVar12 = bVar2;
                      puVar12 = (uint *)((int)puVar12 + 1);
                    }
                    uVar6 = CONCAT31(CONCAT21(CONCAT11(bVar2,bVar2),bVar2),bVar2);
                    uVar8 = uVar7 & 3;
                    for (uVar7 = uVar7 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *puVar12 = uVar6;
                      puVar12 = puVar12 + 1;
                    }
                  }
                  for (; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(byte *)puVar12 = (byte)uVar6;
                    puVar12 = (uint *)((int)puVar12 + 1);
                  }
                  pbVar9 = pbVar9 + 2;
                  bVar13 = (bool)(*pbVar10 & 1);
                  bVar2 = *pbVar10 >> 1;
                  uVar8 = (uint)bVar2;
                } while (!bVar13 && bVar2 != 0);
                if (!bVar13) goto LAB_1003b3d2;
              } while (bVar2 != 0);
            }
          } while (bVar13);
        }
LAB_1003b3d2:
        puVar11 = (uint *)((int)puVar11 + iVar3);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return 0;
}


