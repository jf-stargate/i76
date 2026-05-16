/*
 * Program: i76.exe
 * Function: lzo_runtime_config_selftest
 * Entry: 004ba6d0
 * Signature: int __stdcall lzo_runtime_config_selftest(void)
 */


/* WARNING: Type propagation algorithm not settling */
/* [cgpt i76.exe LZO1Y labels v24; confidence=medium-high] LZO runtime configuration/self-test
   helper for byte order, unaligned access, pointer behavior, and embedded identity-string checksum.
    */

int lzo_runtime_config_selftest(void)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  undefined2 *puVar8;
  undefined4 *puVar9;
  int *piVar10;
  int *piVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  undefined1 local_4c [2];
  short sStack_4a;
  undefined1 local_48 [2];
  short sStack_46;
  int local_44;
  int local_40;
  int local_3c [4];
  int local_2c [9];
  int aiStack_8 [2];
  
  iVar3 = 0;
  do {
    *(char *)((int)local_3c + iVar3) = (char)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x10);
  bVar15 = (short)local_3c[0] == 0x100;
  bVar16 = local_3c[0] == 0x3020100 && bVar15;
  if (local_3c[0] == 0x3020100 && bVar15) {
    iVar3 = 0;
    puVar8 = (undefined2 *)local_4c;
    do {
      puVar1 = (undefined2 *)((int)local_3c + iVar3);
      iVar3 = iVar3 + 1;
      *puVar8 = *puVar1;
      puVar8 = puVar8 + 1;
    } while (iVar3 < 4);
    bVar16 = ((sStack_46 == 0x403 && local_4c == (undefined1  [2])0x100) &&
             local_48 == (undefined1  [2])0x302) && sStack_4a == 0x201;
  }
  bVar15 = false;
  if (bVar16) {
    iVar3 = 0;
    puVar9 = (undefined4 *)local_4c;
    do {
      puVar2 = (undefined4 *)((int)local_3c + iVar3);
      iVar3 = iVar3 + 1;
      *puVar9 = *puVar2;
      puVar9 = puVar9 + 1;
    } while (iVar3 < 4);
    bVar15 = ((local_44 == 0x5040302 && _local_48 == 0x4030201) && local_40 == 0x6050403) &&
             _local_4c == 0x3020100;
    if (((local_44 == 0x5040302 && _local_48 == 0x4030201) && local_40 == 0x6050403) &&
        _local_4c == 0x3020100) {
      uVar4 = lzo_adler32(0,(byte *)0x0,0);
      uVar5 = lzo_adler32(uVar4,(byte *)
                                "\n\n\nLZO real-time data compression library.\nCopyright (C) 1996, 1997 Markus Franz Xaver Johannes Oberhumer\n<markus.oberhumer@jk.uni-linz.ac.at>\nhttp://www.infosys.tuwien.ac.at/Staff/lux/marco/lzo.html\n\nLZO version: v1.00, Jul 13 1997\nLZO build date: Feb 12 1998 20:22:39\n\nLZO special compilation options:\n LZO_BYTE_ORDER=1234\n LZO_UNALIGNED_OK_2\n LZO_UNALIGNED_OK_4\n LZO_DICT_USE_PTR\n\n\n$Id: LZO 1.00 built Feb 12 1998 20:22:39 by Microsoft C 1100 $\n$Copyright: LZO (C) 1996, 1997 Markus Franz Xaver Johannes Oberhumer $\n"
                          ,200);
      uVar4 = DAT_00501774;
      bVar15 = false;
      if (uVar5 == 0x918c45aa) {
        uVar5 = 0;
        if (DAT_00501774 != 0) {
          piVar10 = &DAT_005dbab0;
          do {
            iVar3 = uVar5 - 3;
            uVar5 = uVar5 + 1;
            *piVar10 = iVar3;
            piVar10 = piVar10 + 1;
          } while (uVar5 < uVar4);
        }
        if (((DAT_005dbab0 == -3) && (DAT_005dbab4 == -2)) && (DAT_005dbab8 == -1)) {
          bVar16 = false;
        }
        else {
          bVar16 = true;
        }
        bVar15 = false;
        if (!bVar16) {
          iVar3 = 0;
          do {
            local_4c[iVar3] = (char)iVar3;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x10);
          iVar3 = lzo_compute_alignment_gap((int)local_2c,4);
          piVar10 = (int *)((int)local_2c + iVar3);
          if ((uint)((int)piVar10 - (int)local_2c) < 4) {
            iVar6 = 8;
            do {
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
          }
          bVar15 = false;
          if ((uint)((int)piVar10 - (int)local_2c) < 4) {
            piVar7 = (int *)((int)local_2c + iVar3 + 4);
            piVar11 = piVar10;
            for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
              *piVar11 = (int)piVar10;
              piVar11 = piVar11 + 1;
            }
            piVar11 = piVar7;
            for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
              *piVar11 = 0;
              piVar11 = piVar11 + 1;
            }
            bVar16 = (int *)*piVar10 == piVar10;
            iVar6 = 8;
            do {
              bVar16 = (bool)(bVar16 & *piVar7 == 0);
              piVar7 = piVar7 + 1;
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
            bVar15 = false;
            if ((bool)(bVar16 & (int *)*(int *)((int)aiStack_8 + iVar3) == piVar10)) {
              iVar3 = lzo_compute_alignment_gap((int)local_4c + 1,4);
              piVar10 = (int *)(local_4c + iVar3 + 1);
              bVar16 = piVar10 < (uint)((int)local_48 + 1U);
              bVar12 = (uint)((int)local_4c + 1U) <= piVar10;
              bVar13 = ((uint)piVar10 & 3) == 0;
              bVar14 = iVar3 + 1U < 5;
              bVar15 = (((bVar16 && bVar12) && bVar13) && iVar3 != -1) && bVar14;
              if ((((bVar16 && bVar12) && bVar13) && iVar3 != -1) && bVar14) {
                bVar15 = bVar15 && (*(int *)(local_48 + iVar3 + 1) != 0 && *piVar10 != 0);
              }
            }
          }
        }
      }
    }
  }
  return -(uint)!bVar15;
}


