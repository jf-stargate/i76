/*
 * Program: i76shell.dll
 * Function: decode_iff_ilbm_to_shell_surface
 * Entry: 1003e75f
 * Signature: uint __cdecl decode_iff_ilbm_to_shell_surface(int * param_1, int param_2)
 */


uint __cdecl decode_iff_ilbm_to_shell_surface(int *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  undefined2 uVar5;
  char cVar11;
  undefined1 *puVar6;
  uint uVar7;
  ushort *puVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  byte bVar12;
  uint uVar13;
  byte bVar14;
  int iVar15;
  int iVar16;
  byte *pbVar17;
  byte *pbVar18;
  undefined1 *puVar19;
  uint local_3c;
  int local_2c;
  int local_1c;
  undefined1 *local_18;
  byte *local_14;
  uint local_c;
  
  puVar6 = (undefined1 *)((param_1[3] - param_1[1]) + 1);
  uVar7 = (param_1[4] - param_1[2]) + 1;
  local_2c = 0;
  iVar2 = *(int *)(param_2 + 8);
  puVar8 = (ushort *)find_iff_chunk_by_fourcc((short *)&DAT_1003e711,param_2);
  uVar1 = *puVar8;
  uVar3 = CONCAT11((char)uVar1,(char)(uVar1 >> 8));
  puVar9 = (undefined1 *)(uint)uVar3;
  local_c = (uint)CONCAT11((char)puVar8[1],(char)(puVar8[1] >> 8));
  if ((int)uVar7 <= (int)local_c) {
    local_c = uVar7;
  }
  if (*(char *)((int)puVar8 + 9) != '\x01') {
    uVar4 = puVar8[5];
    local_3c = (uint)*(byte *)((int)puVar8 + 0xd);
    uVar7 = ((uVar3 >> 3) + 1) - (uint)((uVar1 & 0x700) == 0);
    iVar15 = uVar7 + (uVar7 & 1);
    puVar10 = puVar9;
    if ((int)puVar6 <= (int)puVar9) {
      puVar10 = puVar6;
    }
    local_14 = (byte *)find_iff_chunk_by_fourcc((short *)&DAT_1003e719,param_2);
    do {
      if ((char)uVar4 == '\x01') {
        pbVar18 = (byte *)&DAT_1004e825;
        while (pbVar17 = local_14, pbVar18 < puVar9 + ((uint)puVar9 & 1) + 0x1004e825) {
          local_14 = pbVar17 + 1;
          uVar7 = (uint)*pbVar17;
          if (uVar7 != 0x80) {
            if (uVar7 < 0x81) {
              for (uVar13 = uVar7 + 1 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                *pbVar18 = *local_14;
                local_14 = local_14 + 1;
                pbVar18 = pbVar18 + 1;
              }
              for (uVar7 = uVar7 + 1 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(undefined4 *)pbVar18 = *(undefined4 *)local_14;
                local_14 = local_14 + 4;
                pbVar18 = pbVar18 + 4;
              }
            }
            else {
              bVar14 = *local_14;
              bVar12 = 1 - *pbVar17;
              for (uVar7 = bVar12 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *pbVar18 = bVar14;
                pbVar18 = pbVar18 + 1;
              }
              for (uVar7 = (uint)(bVar12 >> 2); local_14 = pbVar17 + 2, uVar7 != 0;
                  uVar7 = uVar7 - 1) {
                *(uint *)pbVar18 = CONCAT22(CONCAT11(bVar14,bVar14),CONCAT11(bVar14,bVar14));
                pbVar18 = pbVar18 + 4;
              }
            }
          }
        }
        pbVar18 = (byte *)&DAT_1004e825;
        local_14 = pbVar17;
      }
      else {
        pbVar18 = local_14;
        local_14 = local_14 + (int)(puVar9 + ((uint)puVar9 & 1));
      }
      if (iVar2 == 0x4d424c49) {
        puVar6 = &DAT_1004db25;
        local_1c = iVar15;
        local_18 = puVar10;
        do {
          bVar14 = 0x80;
          puVar19 = puVar6;
          do {
            iVar16 = 0;
            uVar7 = 0x100;
            do {
              uVar5 = (undefined2)uVar7;
              if ((pbVar18[iVar16] & bVar14) != 0) {
                uVar5 = (undefined2)CONCAT31((int3)(uVar7 >> 8),(byte)uVar7 | (byte)(uVar7 >> 8));
              }
              iVar16 = iVar16 + iVar15;
              cVar11 = (char)((ushort)uVar5 >> 8) << 1;
              uVar7 = (uint)CONCAT11(cVar11,(char)uVar5);
            } while (cVar11 != '\0');
            puVar6 = puVar19 + 1;
            *puVar19 = (char)uVar5;
            local_18 = local_18 + -1;
            if (local_18 == (undefined1 *)0x0) goto LAB_1003e8e7;
            bVar14 = bVar14 >> 1;
            puVar19 = puVar6;
          } while (bVar14 != 0);
          pbVar18 = pbVar18 + 1;
          local_1c = local_1c + -1;
        } while (local_1c != 0);
LAB_1003e8e7:
        write_decoded_image_scanline_to_shell_surface
                  (param_1,local_2c,(undefined4 *)&DAT_1004db25,puVar10);
      }
      else {
        write_decoded_image_scanline_to_shell_surface
                  (param_1,local_2c,(undefined4 *)pbVar18,puVar10);
      }
      local_2c = local_2c + 1;
      local_c = local_c - 1;
    } while (local_c != 0);
  }
  return local_3c;
}


