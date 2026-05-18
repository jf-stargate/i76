/*
 * Program: i76.exe
 * Function: load_input_map
 * Entry: 0044d280
 * Signature: undefined4 __stdcall load_input_map(void)
 */


/* i76 second-pass rename
   old_name: FUN_0044d280
   suggested_name: load_input_map
   basis: Opens input.map and invokes parser. */

undefined4 load_input_map(void)

{
  char cVar1;
  FILE *pFVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *local_108;
  undefined4 local_104;
  char local_100 [4];
  char local_fc [252];
  
  pFVar2 = fopen(s_input_map_004f49d4,s_r_004ede60);
  if (pFVar2 == (FILE *)0x0) {
    report_chunk_parse_error();
    return 0;
  }
  parse_input_map(pFVar2);
  fclose(pFVar2);
  iVar6 = 0;
  if (g_input_device_context_count < 1) {
    return 1;
  }
  local_108 = (char *)&DAT_0053da68;
  local_104 = &DAT_0053da50;
LAB_0044d2f7:
  if (*local_104 != 0) {
    local_100[0] = s_giddi_004f4bb8[0];
    local_100[1] = s_giddi_004f4bb8[1];
    local_100[2] = s_giddi_004f4bb8[2];
    local_100[3] = s_giddi_004f4bb8[3];
    uVar3 = 0xffffffff;
    pcVar7 = s___004f4bb4;
    do {
      pcVar9 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    local_fc[0] = s_giddi_004f4bb8[4];
    local_fc[1] = s_giddi_004f4bb8[5];
    iVar4 = -1;
    pcVar7 = local_100;
    do {
      pcVar8 = pcVar7;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar3;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar7 = local_108;
    do {
      pcVar9 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar4 = -1;
    pcVar7 = local_100;
    do {
      pcVar8 = pcVar7;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar3;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    do {
      if (*(int *)__mb_cur_max_exref < 2) {
        uVar3 = 0xffffffff;
        pcVar7 = local_100;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        uVar3 = *(byte *)(*(int *)_pctype_exref + *(char *)((int)&local_104 + ~uVar3 + 2) * 2) & 4;
      }
      else {
        uVar3 = 0xffffffff;
        pcVar7 = local_100;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        uVar3 = _isctype((int)*(char *)((int)&local_104 + ~uVar3 + 2),4);
      }
      if (uVar3 == 0) goto LAB_0044d3d2;
      uVar3 = 0xffffffff;
      pcVar7 = local_100;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      *(undefined1 *)((int)&local_104 + ~uVar3 + 2) = 0;
    } while( true );
  }
  goto LAB_0044d42c;
LAB_0044d3d2:
  uVar3 = 0xffffffff;
  pcVar7 = s__std_004f4bac;
  do {
    pcVar9 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar4 = -1;
  pcVar7 = local_100;
  do {
    pcVar8 = pcVar7;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar3;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  pFVar2 = fopen(local_100,s_r_004ede60);
  if (pFVar2 != (FILE *)0x0) {
    parse_input_map(pFVar2);
    fclose(pFVar2);
  }
LAB_0044d42c:
  iVar6 = iVar6 + 1;
  local_108 = local_108 + 0x28;
  local_104 = local_104 + 1;
  if (g_input_device_context_count <= iVar6) {
    return 1;
  }
  goto LAB_0044d2f7;
}


