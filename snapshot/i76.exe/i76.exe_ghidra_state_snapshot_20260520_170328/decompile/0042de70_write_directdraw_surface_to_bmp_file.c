/*
 * Program: i76.exe
 * Function: write_directdraw_surface_to_bmp_file
 * Entry: 0042de70
 * Signature: undefined __stdcall write_directdraw_surface_to_bmp_file(void)
 */


/* cgpt rename v2: Captures/serializes a DirectDraw surface-like buffer to a BMP-style file using
   fwrite and surface masks. */

void write_directdraw_surface_to_bmp_file(void)

{
  ushort *puVar1;
  int iVar2;
  FILE *_File;
  size_t sVar3;
  uint uVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  ushort *puVar10;
  int *piVar11;
  undefined4 *puVar12;
  undefined4 uStack_104;
  int iVar13;
  byte bStack_f0;
  byte bStack_ec;
  int *piStack_e8;
  byte bStack_e4;
  undefined2 uStack_e0;
  undefined4 uStack_de;
  undefined2 uStack_da;
  undefined2 uStack_d8;
  undefined2 uStack_d6;
  undefined4 local_d4;
  int iStack_d0;
  int iStack_cc;
  int aiStack_c8 [3];
  undefined2 uStack_bc;
  undefined2 uStack_ba;
  undefined4 uStack_b8;
  undefined4 auStack_a0 [4];
  uint uStack_90;
  uint uStack_8c;
  uint uStack_88;
  int iStack_70;
  undefined4 auStack_6c [4];
  int iStack_5c;
  undefined4 auStack_38 [4];
  uint uStack_28;
  uint uStack_24;
  uint uStack_20;
  char *pcStack_10;
  
  piVar8 = DAT_006080c4;
  if ((DAT_005fff34 == 0) && (local_d4 = DAT_006080c4, (DAT_005fff14 & 0x40) != 0)) {
    while (DAT_005280d8 != 0) {
      uStack_104 = 0;
      iVar2 = (**(code **)(*DAT_006080c0 + 0x2c))(DAT_006080c0,0);
      if (iVar2 != -0x7789fde4) {
        DAT_005280d8 = 0;
      }
    }
    if (DAT_005280cc != 0) {
      DAT_005280cc = 0;
      uStack_104 = 0;
      (**(code **)(*piVar8 + 0x80))(piVar8);
    }
    uStack_104 = 0;
    puVar9 = auStack_6c;
    for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    auStack_6c[0] = 0x6c;
    iVar2 = (**(code **)(*piVar8 + 100))(piVar8,0,auStack_6c,1);
    if (iVar2 == 0) {
      _File = fopen(pcStack_10,s_wb_004edf28);
      if (_File != (FILE *)0x0) {
        uStack_e0 = 0;
        uStack_de._0_2_ = 0;
        uStack_de._2_2_ = 0;
        uStack_da = 0;
        uStack_d8 = 0;
        uStack_d6 = 0;
        piVar11 = aiStack_c8;
        for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar11 = 0;
          piVar11 = piVar11 + 1;
        }
        local_d4._0_2_ = 0;
        strncpy((char *)&uStack_e0,&DAT_004edf24,2);
        aiStack_c8[1] = DAT_00608400;
        uStack_b8 = 0;
        uStack_de = (DAT_00608400 * DAT_00608404 + 0x12) * 3;
        aiStack_c8[2] = DAT_00608404;
        uStack_d6 = 0x36;
        local_d4._0_2_ = 0;
        aiStack_c8[0] = 0x28;
        uStack_bc = 1;
        uStack_ba = 0x18;
        sVar3 = fwrite(&uStack_e0,0xe,1,_File);
        if (sVar3 == 1) {
          sVar3 = fwrite(aiStack_c8,0x28,1,_File);
          uVar4 = uStack_28;
          if (sVar3 == 1) {
            puVar9 = auStack_38;
            puVar12 = auStack_a0;
            for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar12 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar12 = puVar12 + 1;
            }
            bStack_f0 = 0;
            for (; (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
              bStack_f0 = bStack_f0 + 1;
            }
            bStack_e4 = 0;
            for (uVar4 = uStack_24; (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
              bStack_e4 = bStack_e4 + 1;
            }
            bStack_ec = 0;
            for (uVar4 = uStack_20; (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
              bStack_ec = bStack_ec + 1;
            }
            iStack_d0 = 0;
            for (; uStack_28 != 0; uStack_28 = uStack_28 >> 1) {
              if ((uStack_28 & 1) != 0) {
                iStack_d0 = iStack_d0 + 1;
              }
            }
            iStack_d0 = 8 - iStack_d0;
            cVar5 = '\0';
            for (; uStack_24 != 0; uStack_24 = uStack_24 >> 1) {
              if ((uStack_24 & 1) != 0) {
                cVar5 = cVar5 + '\x01';
              }
            }
            cVar6 = '\0';
            for (; uStack_20 != 0; uStack_20 = uStack_20 >> 1) {
              if ((uStack_20 & 1) != 0) {
                cVar6 = cVar6 + '\x01';
              }
            }
            iStack_70 = iStack_70 >> 1;
            puVar1 = (ushort *)(iStack_5c + (DAT_00608404 + -1) * iStack_70 * 2);
            iStack_cc = iStack_70;
            iVar7 = DAT_00608400;
            iVar2 = DAT_00608404;
            while (iVar2 = iVar2 + -1, piVar8 = piStack_e8, -1 < iVar2) {
              iVar13 = 0;
              puVar10 = puVar1;
              if (0 < iVar7) {
                do {
                  uVar4 = (uint)*puVar10;
                  uStack_104 = CONCAT31(CONCAT21(CONCAT11(uStack_104._3_1_,
                                                          (char)((uStack_90 & uVar4) >>
                                                                (bStack_f0 & 0x1f)) <<
                                                          ((byte)iStack_d0 & 0x1f)),
                                                 (char)((uStack_8c & uVar4) >> (bStack_e4 & 0x1f))
                                                 << (8U - cVar5 & 0x1f)),
                                        (char)((uStack_88 & uVar4) >> (bStack_ec & 0x1f)) <<
                                        (8U - cVar6 & 0x1f));
                  sVar3 = fwrite(&uStack_104,3,1,_File);
                  if (sVar3 != 1) goto LAB_0042e1ae;
                  iVar13 = iVar13 + 1;
                  iStack_70 = iStack_cc;
                  iVar7 = DAT_00608400;
                  puVar10 = puVar10 + 1;
                } while (iVar13 < DAT_00608400);
              }
              puVar1 = puVar1 + -iStack_70;
            }
          }
        }
LAB_0042e1ae:
        fclose(_File);
      }
      (**(code **)(*piVar8 + 0x80))(piVar8,0);
    }
  }
  return;
}


