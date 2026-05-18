/*
 * Program: i76.exe
 * Function: load_tank_gdf_resources
 * Entry: 004b3aa0
 * Signature: undefined4 __cdecl load_tank_gdf_resources(int param_1, uint * param_2)
 */


/* cgpt whole-binary semantic rename v1: references gtktank.gdf/gtptank.gdf/tthowitz.gdf */

undefined4 __cdecl load_tank_gdf_resources(int param_1,uint *param_2)

{
  byte *_Str1;
  uint uVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  undefined3 extraout_var;
  uint *puVar5;
  int *piVar6;
  int iVar7;
  
  iVar7 = param_1;
  iVar4 = 0;
  param_1 = -1;
  iVar2 = param_1;
  if (0 < DAT_005db7c4) {
    piVar6 = &DAT_005db190;
    do {
      iVar2 = iVar4;
      if (*piVar6 == *(int *)(iVar7 + 8)) break;
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 0x3f;
      iVar2 = param_1;
    } while (iVar4 < DAT_005db7c4);
  }
  param_1 = iVar2;
  if (param_1 == -1) {
    return 0;
  }
  _Str1 = (byte *)(iVar7 + 0xc);
  bVar3 = parse_bwd2_resource_with_descriptor_table(_Str1,&DAT_00500160,6,(byte *)0x0);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return 0;
  }
  if (g_expected_file_crc_record_count == -1) {
LAB_004b3b5b:
    uVar1 = *param_2;
    *param_2 = ((1 << ((byte)param_1 & 0x1f) | (int)(uVar1 << 0x19) >> 0x19) ^ uVar1) & 0x7f ^ uVar1
    ;
    DAT_005dacd0 = 0;
  }
  else {
    iVar7 = 0;
    if (0 < g_expected_file_crc_record_count) {
      piVar6 = &DAT_005db7cc;
      do {
        if ((piVar6[-1] == DAT_005dacd8) && ((*piVar6 == -1 || (*piVar6 == DAT_005db978))))
        goto LAB_004b3b5b;
        iVar7 = iVar7 + 1;
        piVar6 = piVar6 + 2;
      } while (iVar7 < g_expected_file_crc_record_count);
    }
  }
  if (DAT_005dacd4 == 0) {
    return 1;
  }
  iVar7 = _stricmp((char *)_Str1,s_gtktank_gdf_0050031c);
  if (((iVar7 == 0) || (iVar7 = _stricmp((char *)_Str1,s_gtptank_gdf_00500310), iVar7 == 0)) ||
     (iVar7 = _stricmp((char *)_Str1,s_tthowitz_gdf_00500300), iVar7 == 0)) {
    *param_2 = *param_2 | 0x2000;
    DAT_005dacd0 = 0;
  }
  if (99 < DAT_005db978) {
    if (DAT_005db960 != 0) {
      *param_2 = *param_2 | 0x4000;
      DAT_005dacd0 = 0;
    }
    DAT_005db960 = 1;
  }
  if (DAT_005dacd8 == 6) {
    if (*(int *)(&DAT_005db1d4 + param_1 * 0xfc) == 4) {
LAB_004b3c31:
      if ((DAT_005db978 < 100) || (*(int *)(&DAT_005db1d4 + param_1 * 0xfc) == 1))
      goto LAB_004b3c58;
    }
  }
  else if (*(int *)(&DAT_005db1d4 + param_1 * 0xfc) != 4) goto LAB_004b3c31;
  *param_2 = *param_2 | 0x8000;
  DAT_005dacd0 = 0;
LAB_004b3c58:
  puVar5 = open_resource_file_into_memory((char *)_Str1);
  if (puVar5 != (uint *)0x0) {
    for (iVar7 = get_loaded_resource_file_size((char *)_Str1); iVar7 != 0; iVar7 = iVar7 + -1) {
      uVar1 = *puVar5;
      puVar5 = (uint *)((int)puVar5 + 1);
      param_2[1] = (&g_crc32_table_msb)[param_2[1] >> 0x18 ^ (uint)(byte)uVar1] ^ param_2[1] << 8;
    }
    release_resource_file_reference((char *)_Str1);
  }
  return 1;
}


