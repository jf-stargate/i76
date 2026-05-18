/*
 * Program: i76.exe
 * Function: parse_zix_path_line
 * Entry: 004b1df0
 * Signature: undefined4 __cdecl parse_zix_path_line(FILE * param_1, int param_2)
 */


/* i76 second-pass rename
   old_name: FUN_004b1df0
   suggested_name: parse_zix_path_line
   basis: Parses zix path lines with sscanf; reports too many zix paths. */

undefined4 __cdecl parse_zix_path_line(FILE *param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  byte *pbVar9;
  char *pcVar10;
  bool bVar11;
  int local_404;
  char local_400;
  char local_3ff [255];
  byte local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  DAT_006562cc = 0;
  do {
    iVar3 = mission_resource_reference_context_helper_004b20f0(&local_400,0x100,param_1);
    if ((iVar3 == 0) || (local_400 == '-')) break;
    sscanf(&local_400,s__d__s__s_004fff4c,&local_404,local_200,local_100);
    pcVar7 = &local_400;
    cVar1 = local_400;
    while (cVar1 != '\0') {
      if (cVar1 == '\'') {
        pcVar7 = pcVar7 + 1;
        break;
      }
      pcVar8 = pcVar7 + 1;
      pcVar7 = pcVar7 + 1;
      cVar1 = *pcVar8;
    }
    if ((-1 < local_404) && (local_404 < 0x10)) {
      uVar5 = 0xffffffff;
      iVar3 = local_404 * 0x300;
      pcVar8 = local_200;
      do {
        pcVar10 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar8 = pcVar10 + -uVar5;
      pcVar10 = &g_resource_directory_roots + iVar3;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar10 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar8 = local_100;
      do {
        pcVar10 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar8 = pcVar10 + -uVar5;
      pcVar10 = &DAT_006562e0 + iVar3;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar10 = pcVar10 + 4;
      }
      cVar1 = *pcVar7;
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar10 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      }
      if (cVar1 == '\0') {
        (&DAT_006563e0)[iVar3] = 0;
      }
      else {
        uVar5 = 0xffffffff;
        do {
          pcVar8 = pcVar7;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar5 = ~uVar5;
        pcVar7 = pcVar8 + -uVar5;
        pcVar8 = &DAT_006563e0 + iVar3;
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
      }
    }
    DAT_006562cc = DAT_006562cc + 1;
  } while (DAT_006562cc < 0x10);
  do {
    g_zix_search_path_count = param_2 + 1;
    if (((0xff < g_zix_search_path_count) ||
        (iVar3 = mission_resource_reference_context_helper_004b20f0(&local_400,0x100,param_1),
        iVar3 == 0)) || (local_400 == '-')) {
      if (((g_zix_search_path_count == 0x100) &&
          (iVar3 = mission_resource_reference_context_helper_004b20f0(&local_400,0x100,param_1),
          iVar3 != 0)) && (local_400 != '-')) {
        sprintf(&g_resource_error_message,s_More_than__d_zix_paths_specified_004fff1c,0x100);
        return 0;
      }
      return 1;
    }
    sscanf(&local_400,s__s__s_004f4c80,local_300,
           &g_zix_search_path_records + g_zix_search_path_count * 0x10c);
    pbVar9 = &DAT_004fff44;
    pbVar4 = local_300;
    do {
      bVar2 = *pbVar4;
      bVar11 = bVar2 < *pbVar9;
      if (bVar2 != *pbVar9) {
LAB_004b1fea:
        iVar3 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
        goto LAB_004b1fef;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar4[1];
      bVar11 = bVar2 < pbVar9[1];
      if (bVar2 != pbVar9[1]) goto LAB_004b1fea;
      pbVar4 = pbVar4 + 2;
      pbVar9 = pbVar9 + 2;
    } while (bVar2 != 0);
    iVar3 = 0;
LAB_004b1fef:
    if (iVar3 == 0) {
      (&DAT_006593e0)[g_zix_search_path_count * 0x43] = 1;
      param_2 = g_zix_search_path_count;
    }
    else {
      iVar3 = strncmp((char *)local_300,&DAT_004fff40,2);
      param_2 = g_zix_search_path_count;
      if (iVar3 == 0) {
        (&DAT_006593e0)[g_zix_search_path_count * 0x43] = 0;
        iVar3 = atoi((char *)(local_300 + 2));
        (&DAT_006593e4)[g_zix_search_path_count * 0x43] = iVar3;
        param_2 = g_zix_search_path_count;
      }
    }
  } while( true );
}


