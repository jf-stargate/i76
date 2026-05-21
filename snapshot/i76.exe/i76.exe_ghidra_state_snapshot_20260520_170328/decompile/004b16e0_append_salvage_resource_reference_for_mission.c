/*
 * Program: i76.exe
 * Function: append_salvage_resource_reference_for_mission
 * Entry: 004b16e0
 * Signature: undefined4 __cdecl append_salvage_resource_reference_for_mission(char * param_1, undefined4 param_2, undefined4 param_3)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Classifies salvage/resource path by
   extension/stem (.wdf/.gdf/.vcf and eng/sus/brk/tir prefixes), gates by selected mission
   number/family, appends linked salvage item record. */

undefined4 __cdecl
append_salvage_resource_reference_for_mission(char *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 *puVar12;
  char *pcVar13;
  char local_214 [16];
  char local_204 [4];
  char local_200 [256];
  char local_100 [256];
  
  iVar9 = 2;
  if (((byte)DAT_00654b98 & 2) != 0) {
    return 0;
  }
  _splitpath(param_1,local_204,local_100,local_214,local_200);
  iVar4 = _stricmp(local_200,&DAT_004ffec8);
  if (iVar4 == 0) {
    iVar9 = 0;
  }
  else {
    iVar4 = _stricmp(local_200,s__gdf_004ffec0);
    if (iVar4 == 0) {
      iVar9 = 1;
    }
    else {
      iVar4 = _stricmp(local_200,&DAT_00504c28);
      if (iVar4 != 0) {
LAB_004b19b0:
        report_error();
        return 0;
      }
      iVar4 = _strnicmp(local_214,s_eng_004ffebc,3);
      if (iVar4 != 0) {
        iVar9 = _strnicmp(local_214,s_sus_004ffeb0,3);
        if (iVar9 == 0) {
          iVar9 = 3;
        }
        else {
          iVar9 = _strnicmp(local_214,(char *)&PTR_DAT_004ffeac,3);
          if (iVar9 == 0) {
            iVar9 = 4;
          }
          else {
            iVar9 = _strnicmp(local_214,(char *)&PTR_DAT_004ffea8,3);
            if (iVar9 != 0) goto LAB_004b19b0;
            iVar9 = 5;
          }
        }
      }
    }
  }
  uVar7 = 0xffffffff;
  do {
    pcVar10 = param_1;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar10 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar10;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar10 = pcVar10 + -uVar7;
  pcVar11 = local_214;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar11 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar11 = pcVar11 + 1;
  }
  if (iVar9 == 0) {
    strncpy(local_214,s_wauto_0_004fff08,7);
  }
  iVar4 = is_salvage_resource_available_for_mission
                    (local_214,iVar9,g_selected_mission_number + 1,g_selected_mission_family);
  puVar3 = g_mission_salvage_resource_list;
  puVar12 = g_mission_salvage_resource_list;
  if (iVar4 == 0) {
    return 1;
  }
  while ((puVar5 = puVar3, puVar5 != (undefined4 *)0x0 &&
         ((puVar5[2] != iVar9 || (iVar4 = _stricmp((char *)(puVar5[1] + 4),local_214), iVar4 != 0)))
         )) {
    puVar3 = (undefined4 *)*puVar5;
    puVar12 = puVar5;
  }
  puVar3 = g_mission_salvage_resource_list;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)xalloc_global_heap(0xc);
    if (puVar5 == (undefined4 *)0x0) {
      report_error();
      return 0;
    }
    *puVar5 = 0;
    puVar5[1] = 0;
    puVar5[2] = 0;
    puVar5[2] = iVar9;
    puVar3 = puVar5;
    if (puVar12 != (undefined4 *)0x0) {
      *puVar12 = puVar5;
      puVar3 = g_mission_salvage_resource_list;
    }
  }
  g_mission_salvage_resource_list = puVar3;
  puVar6 = (undefined4 *)puVar5[1];
  puVar3 = (undefined4 *)puVar5[1];
  while (puVar2 = puVar6, puVar2 != (undefined4 *)0x0) {
    puVar3 = puVar2;
    puVar6 = (undefined4 *)*puVar2;
  }
  puVar6 = (undefined4 *)xalloc_global_heap(0x1c);
  if (puVar6 == (undefined4 *)0x0) {
    report_error();
    if (puVar3 != (undefined4 *)0x0) {
      return 0;
    }
    xfree_global_heap(puVar5);
    *puVar12 = 0;
    return 0;
  }
  puVar12 = puVar6;
  for (iVar9 = 7; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  if (puVar3 == (undefined4 *)0x0) {
    puVar5[1] = puVar6;
  }
  else {
    *puVar3 = puVar6;
  }
  puVar6[5] = param_2;
  puVar6[6] = param_3;
  uVar7 = 0xffffffff;
  pcVar10 = (char *)(puVar6 + 1);
  pcVar11 = local_214;
  do {
    pcVar13 = pcVar11;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar13 = pcVar11 + 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar13;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar11 = pcVar13 + -uVar7;
  pcVar13 = pcVar10;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar13 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar13 = pcVar13 + 1;
  }
  iVar9 = -1;
  uVar7 = 0;
  pcVar11 = pcVar10;
  do {
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  if (iVar9 != -2) {
    do {
      tolower((int)pcVar10[uVar7]);
      uVar8 = 0xffffffff;
      uVar7 = uVar7 + 1;
      pcVar11 = pcVar10;
      do {
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
    } while (uVar7 < ~uVar8 - 1);
  }
  return 1;
}


