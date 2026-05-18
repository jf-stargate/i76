/*
 * Program: i76.exe
 * Function: build_display_pixel_format_palette_remap_tables
 * Entry: 0042d800
 * Signature: undefined __cdecl build_display_pixel_format_palette_remap_tables(int param_1, ushort * param_2, int param_3, int param_4)
 */


/* cgpt rename v8 display/d3d cluster: Builds RGB mask lookup/remap tables for the current display
   pixel format and optionally loads/updates a 64K palette translation table resource. */

void __cdecl
build_display_pixel_format_palette_remap_tables(int param_1,ushort *param_2,int param_3,int param_4)

{
  char cVar1;
  ushort uVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  char *pcVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  byte *pbVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  uint uVar16;
  byte bVar17;
  int iVar18;
  ushort *puVar19;
  char *pcVar20;
  uint *puVar21;
  int local_c68;
  ushort local_c64;
  char local_c50 [16];
  uint local_c40 [4];
  int aiStack_c30 [268];
  int local_800 [256];
  int local_400 [256];
  
  uVar13 = *(uint *)(param_4 + 0x14);
  uVar8 = *(uint *)(param_4 + 0x10);
  uVar16 = *(uint *)(param_4 + 0x18);
  uVar2 = *(ushort *)(param_4 + 0x1c);
  iVar18 = 0;
  if (uVar2 == 0) {
    local_c64 = ((ushort)uVar16 - 1 & ~(ushort)uVar16) + 1;
  }
  else {
    local_c64 = 0;
  }
  bVar17 = 0;
  for (uVar5 = uVar8; (uVar5 & 1) == 0; uVar5 = (int)uVar5 >> 1) {
    bVar17 = bVar17 + 1;
  }
  bVar10 = 0;
  for (; uVar5 != 0; uVar5 = (int)uVar5 >> 1) {
    bVar10 = bVar10 + 1;
  }
  piVar14 = aiStack_c30 + 0xc;
  uVar5 = 0;
  local_c68 = 0x100;
  do {
    uVar5 = uVar5 + (1 << (bVar10 & 0x1f));
    *piVar14 = iVar18 << (bVar17 & 0x1f);
    if (0xff < uVar5) {
      uVar5 = uVar5 - 0x100;
      iVar18 = iVar18 + 1;
    }
    piVar14 = piVar14 + 1;
    local_c68 = local_c68 + -1;
  } while (local_c68 != 0);
  bVar17 = 0;
  for (uVar5 = uVar13; (uVar5 & 1) == 0; uVar5 = (int)uVar5 >> 1) {
    bVar17 = bVar17 + 1;
  }
  bVar10 = 0;
  for (; uVar5 != 0; uVar5 = (int)uVar5 >> 1) {
    bVar10 = bVar10 + 1;
  }
  uVar5 = 0;
  iVar18 = 0;
  piVar14 = local_800;
  local_c68 = 0x100;
  do {
    uVar5 = uVar5 + (1 << (bVar10 & 0x1f));
    *piVar14 = iVar18 << (bVar17 & 0x1f);
    if (0xff < uVar5) {
      uVar5 = uVar5 - 0x100;
      iVar18 = iVar18 + 1;
    }
    piVar14 = piVar14 + 1;
    local_c68 = local_c68 + -1;
  } while (local_c68 != 0);
  bVar17 = 0;
  for (uVar5 = uVar16; (uVar5 & 1) == 0; uVar5 = (int)uVar5 >> 1) {
    bVar17 = bVar17 + 1;
  }
  bVar10 = 0;
  for (; uVar5 != 0; uVar5 = (int)uVar5 >> 1) {
    bVar10 = bVar10 + 1;
  }
  uVar5 = 0;
  iVar18 = 0;
  piVar14 = local_400;
  local_c68 = 0x100;
  do {
    uVar5 = uVar5 + (1 << (bVar10 & 0x1f));
    *piVar14 = iVar18 << (bVar17 & 0x1f);
    if (0xff < uVar5) {
      uVar5 = uVar5 - 0x100;
      iVar18 = iVar18 + 1;
    }
    piVar14 = piVar14 + 1;
    local_c68 = local_c68 + -1;
  } while (local_c68 != 0);
  iVar18 = 0x100;
  pbVar11 = (byte *)(param_1 + 2);
  puVar19 = param_2;
  do {
    uVar4 = (short)local_400[*pbVar11] + (short)local_800[pbVar11[-1]] +
            (short)aiStack_c30[pbVar11[-2] + 0xc];
    if (uVar4 == 0) {
      uVar4 = local_c64;
    }
    pbVar11 = pbVar11 + 3;
    *puVar19 = uVar4 | uVar2;
    puVar19 = puVar19 + 1;
    iVar18 = iVar18 + -1;
  } while (iVar18 != 0);
  param_2[0xff] = 0;
  if (param_3 != 0) {
    if (DAT_00608660 == (uint *)0x0) {
      DAT_00608660 = malloc(0x20000);
    }
    copy_multiplayer_session_status_name_string(local_c50);
    iVar18 = _stricmp(local_c50,(char *)&DAT_005280b8);
    if (iVar18 != 0) {
      uVar5 = 0xffffffff;
      bVar3 = false;
      pcVar6 = local_c50;
      do {
        pcVar20 = pcVar6;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar20 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar20;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar6 = pcVar20 + -uVar5;
      pcVar20 = (char *)&DAT_005280b8;
      for (uVar12 = uVar5 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar20 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar20 = pcVar20 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar20 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar20 = pcVar20 + 1;
      }
      pcVar6 = strrchr(local_c50,0x2e);
      if (pcVar6 != (char *)0x0) {
        *(undefined4 *)pcVar6 = DAT_004edf1c;
        pcVar6[4] = DAT_004edf20;
        iVar18 = get_loaded_resource_file_size(local_c50);
        if (iVar18 == 0x20000) {
          puVar7 = open_resource_file_into_memory(local_c50);
          bVar3 = true;
          puVar21 = DAT_00608660;
          for (iVar18 = 0x8000; iVar18 != 0; iVar18 = iVar18 + -1) {
            *puVar21 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar21 = puVar21 + 1;
          }
          release_resource_file_reference(local_c50);
        }
      }
      if (!bVar3) {
        iVar18 = 0;
        do {
          *(short *)((int)DAT_00608660 + iVar18 * 2) = (short)iVar18;
          iVar18 = iVar18 + 1;
        } while (iVar18 < 0x10000);
      }
      local_c40[1] = uVar13;
      local_c40[0] = uVar8;
      local_c40[2] = uVar16;
      local_c40[3] = (uint)uVar2;
      iVar18 = 0;
      do {
        if (local_c40[iVar18] != (&DAT_004ede88)[iVar18]) break;
        iVar18 = iVar18 + 1;
      } while (iVar18 < 4);
      if (iVar18 != 4) {
        iVar18 = 0;
        do {
          iVar15 = 0;
          uVar13 = *(uint *)((int)&DAT_004ede88 + iVar18);
          for (uVar8 = uVar13; (uVar8 & 1) == 0; uVar8 = uVar8 >> 1) {
            iVar15 = iVar15 + 1;
          }
          uVar8 = *(uint *)((int)local_c40 + iVar18);
          *(int *)((int)aiStack_c30 + iVar18 + 0x18) = iVar15;
          iVar15 = 0;
          for (uVar16 = uVar8; (uVar16 & 1) == 0; uVar16 = uVar16 >> 1) {
            iVar15 = iVar15 + 1;
          }
          *(int *)((int)aiStack_c30 + iVar18 + 0x24) = iVar15;
          for (; (uVar13 & 1) == 0; uVar13 = (int)uVar13 >> 1) {
          }
          iVar15 = 8;
          for (; uVar13 != 0; uVar13 = (int)uVar13 >> 1) {
            iVar15 = iVar15 + -1;
          }
          *(int *)((int)aiStack_c30 + iVar18) = iVar15;
          for (; (uVar8 & 1) == 0; uVar8 = (int)uVar8 >> 1) {
          }
          iVar15 = 8;
          for (; uVar8 != 0; uVar8 = (int)uVar8 >> 1) {
            iVar15 = iVar15 + -1;
          }
          *(int *)((int)aiStack_c30 + iVar18 + 0xc) = iVar15;
          iVar18 = iVar18 + 4;
        } while (iVar18 < 0xc);
        iVar18 = 0;
        do {
          uVar13 = 0;
          iVar15 = 0;
          do {
            iVar9 = iVar15 + 4;
            uVar13 = uVar13 | ((((*(uint *)((int)&DAT_004ede88 + iVar15) &
                                 (uint)*(ushort *)((int)DAT_00608660 + iVar18)) >>
                                ((byte)*(undefined4 *)((int)aiStack_c30 + iVar15 + 0x18) & 0x1f)) <<
                               ((byte)*(undefined4 *)((int)aiStack_c30 + iVar15) & 0x1f)) >>
                              ((byte)*(undefined4 *)((int)aiStack_c30 + iVar15 + 0xc) & 0x1f)) <<
                              ((byte)*(undefined4 *)((int)aiStack_c30 + iVar15 + 0x24) & 0x1f);
            iVar15 = iVar9;
          } while (iVar9 < 0xc);
          uVar4 = (ushort)uVar13;
          if ((ushort)uVar13 == 0) {
            uVar4 = local_c64;
          }
          iVar15 = iVar18 + 2;
          *(ushort *)((int)DAT_00608660 + iVar18) = uVar4 | uVar2;
          iVar18 = iVar15;
        } while (iVar15 < 0x20000);
        *(undefined2 *)DAT_00608660 = 0;
      }
    }
  }
  return;
}


