/*
 * Program: i76.exe
 * Function: load_vtfc_vehicle_texture_map_sets
 * Entry: 004af8f0
 * Signature: undefined4 __cdecl load_vtfc_vehicle_texture_map_sets(int param_1, int * param_2)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Loads/binds VTFC vehicle texture
   map/TMT sets, including repeated six-face groups and body-map slots. */

undefined4 __cdecl load_vtfc_vehicle_texture_map_sets(int param_1,int *param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  byte *pbVar10;
  char *pcVar11;
  char **ppcVar12;
  byte *pbVar13;
  char *pcVar14;
  byte *pbVar15;
  char *pcVar16;
  int local_e0;
  char *local_d8 [4];
  char *local_c8;
  char *local_c4;
  byte local_c0 [16];
  int local_b0;
  char local_ac [156];
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  local_b0 = *(int *)(*param_2 + 0x70);
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  uVar8 = *(uint *)(local_b0 + 0x408);
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x25);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffdfc;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x177);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffdf4;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x2c9);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffdec;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  uVar8 = *(uint *)(local_b0 + 0x40c);
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x73);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffde4;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x1c5);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffddc;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0x317);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffdd4;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  local_d8[0] = &DAT_004ffe2c;
  local_d8[1] = s_BK_map_004ffe24;
  uVar8 = *(uint *)(local_b0 + 0x410);
  local_d8[2] = s_RT_map_004ffe1c;
  local_d8[3] = s_LF_map_004ffe14;
  local_c8 = s_TP_map_004ffe0c;
  local_c4 = s_UN_map_004ffe04;
  pbVar10 = (byte *)(param_1 + 0xc1);
  local_e0 = 0;
  ppcVar12 = local_d8;
  do {
    iVar3 = _strnicmp((char *)pbVar10,s_null_004c3280,4);
    if (iVar3 != 0) {
      uVar6 = 0xffffffff;
      pcVar9 = &DAT_004ffdcc;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = local_c0;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar9 = *ppcVar12;
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      iVar3 = -1;
      pbVar13 = local_c0;
      do {
        pbVar15 = pbVar13;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pbVar15 = pbVar13 + 1;
        bVar2 = *pbVar13;
        pbVar13 = pbVar15;
      } while (bVar2 != 0);
      pbVar13 = (byte *)(pcVar11 + -uVar6);
      pbVar15 = pbVar15 + -1;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
        pbVar13 = pbVar13 + 4;
        pbVar15 = pbVar15 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar15 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        pbVar15 = pbVar15 + 1;
      }
      iVar3 = bind_texture_resource_to_object_slot(uVar8,local_c0,pbVar10);
      if (iVar3 == 0) {
        return 0;
      }
    }
    ppcVar12 = ppcVar12 + 1;
    local_e0 = local_e0 + 1;
    pbVar10 = pbVar10 + 0xd;
  } while (local_e0 < 6);
  iVar3 = bind_vtfc_six_face_map_slots(uVar8,s_V3_BK_004ffdc4,(byte *)(param_1 + 0x213));
  if ((iVar3 != 0) &&
     (iVar4 = bind_vtfc_six_face_map_slots(uVar8,s_V5_BK_004ffdbc,(byte *)(param_1 + 0x365)),
     iVar3 = local_b0, iVar4 != 0)) {
    uVar8 = *(uint *)(local_b0 + 0x414);
    iVar4 = bind_vtfc_six_face_map_slots(uVar8,s_V1_TP_004ffdb4,(byte *)(param_1 + 0x10f));
    if ((iVar4 != 0) &&
       ((iVar4 = bind_vtfc_six_face_map_slots(uVar8,s_V3_TP_004ffdac,(byte *)(param_1 + 0x261)),
        iVar4 != 0 &&
        (iVar4 = bind_vtfc_six_face_map_slots(uVar8,s_V5_TP_004ffda4,(byte *)(param_1 + 0x3b3)),
        iVar4 != 0)))) {
      uVar8 = *(uint *)(iVar3 + 0x418);
      pbVar10 = (byte *)(param_1 + 0x15d);
      iVar4 = bind_optional_vtfc_texture_map_slot(uVar8,(byte *)s_V1_FB_FT_map_004ffd94,pbVar10);
      if ((iVar4 != 0) &&
         ((iVar4 = bind_optional_vtfc_texture_map_slot
                             (uVar8,(byte *)s_V3_FB_FT_map_004ffd84,pbVar10), iVar4 != 0 &&
          (iVar4 = bind_optional_vtfc_texture_map_slot
                             (uVar8,(byte *)s_V5_FB_FT_map_004ffd74,pbVar10), iVar4 != 0)))) {
        uVar8 = *(uint *)(iVar3 + 0x41c);
        pbVar10 = (byte *)(param_1 + 0x16a);
        iVar3 = bind_optional_vtfc_texture_map_slot(uVar8,(byte *)s_V1_BB_BK_map_004ffd64,pbVar10);
        if ((iVar3 != 0) &&
           ((iVar3 = bind_optional_vtfc_texture_map_slot
                               (uVar8,(byte *)s_V3_BB_BK_map_004ffd54,pbVar10), iVar3 != 0 &&
            (iVar3 = bind_optional_vtfc_texture_map_slot
                               (uVar8,(byte *)s_V5_BB_BK_map_004ffd44,pbVar10), iVar3 != 0)))) {
          iVar3 = 0xc;
          pcVar9 = (char *)(param_1 + 0x41b);
          pcVar11 = local_ac;
          do {
            uVar8 = 0xffffffff;
            pcVar14 = pcVar9;
            do {
              pcVar16 = pcVar14;
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              pcVar16 = pcVar14 + 1;
              cVar1 = *pcVar14;
              pcVar14 = pcVar16;
            } while (cVar1 != '\0');
            uVar8 = ~uVar8;
            pcVar14 = pcVar16 + -uVar8;
            pcVar16 = pcVar11;
            for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
              pcVar14 = pcVar14 + 4;
              pcVar16 = pcVar16 + 4;
            }
            iVar3 = iVar3 + -1;
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar16 = *pcVar14;
              pcVar14 = pcVar14 + 1;
              pcVar16 = pcVar16 + 1;
            }
            pcVar9 = pcVar9 + 0xd;
            pcVar11 = pcVar11 + 0xd;
            if (iVar3 == 0) {
              local_10 = *(undefined4 *)(param_1 + 0x4b7);
              local_c = *(undefined4 *)(param_1 + 0x4bb);
              local_8 = *(undefined4 *)(param_1 + 0x4bf);
              local_4 = *(undefined1 *)(param_1 + 0x4c3);
              uVar5 = bind_vtfc_body_map_to_object_tree
                                (*(uint *)(*param_2 + 100),local_ac,(byte *)(param_1 + 0x4b7));
              return uVar5;
            }
          } while( true );
        }
      }
    }
  }
  return 0;
}


