/*
 * Program: i76.exe
 * Function: parse_vdf_vehicle_definition_resource
 * Entry: 004b3650
 * Signature: undefined4 __cdecl parse_vdf_vehicle_definition_resource(int param_1, uint * param_2)
 */


/* [i76 level/static/material baseline v48]
   name: parse_vdf_vehicle_definition_resource
   confidence: high
   module: vehicle_vdf
   Parses VDF vehicle definition. Included here because ODEF class-specific VCF path still flows
   toward VDF/VTF/GEO for class 0x01/0x08/0x09.
   note: Name already matches baseline. */

undefined4 __cdecl parse_vdf_vehicle_definition_resource(int param_1,uint *param_2)

{
  byte *pbVar1;
  bool bVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  undefined3 extraout_var;
  int iVar7;
  uint *puVar8;
  char *pcVar9;
  undefined **ppuVar10;
  int *piVar11;
  int iVar12;
  uint *puVar13;
  int *local_4;
  
  bVar4 = false;
  if (DAT_005dacd4 == 0) goto LAB_004b3848;
  local_4 = (int *)(param_1 + 0x4b);
  iVar5 = _strnicmp((char *)local_4,s_null_004c3280,4);
  bVar2 = false;
  ppuVar10 = &PTR_s_wdilo_1a_wdf_005001c0;
  do {
    iVar6 = _stricmp((char *)(param_1 + 0x3e),*ppuVar10);
    if (iVar6 == 0) goto LAB_004b3833;
    ppuVar10 = ppuVar10 + 1;
  } while (ppuVar10 < &PTR_s_wftck_1a_wdf_005001e0);
  ppuVar10 = &PTR_s_vmxmarx_vdf_005001e8;
  pcVar9 = (char *)(param_1 + 0x18);
  do {
    iVar6 = _stricmp(pcVar9,*ppuVar10);
    if (iVar6 == 0) {
      bVar4 = true;
    }
    ppuVar10 = ppuVar10 + 1;
  } while (ppuVar10 < s_vmloadms_vdf_00500204);
  if (bVar4) {
LAB_004b3720:
    bVar4 = false;
    bVar2 = false;
    ppuVar10 = &PTR_s_wdilo_1a_wdf_005001c0;
    do {
      iVar6 = _stricmp((char *)(param_1 + 0x58),*ppuVar10);
      if (iVar6 == 0) goto LAB_004b3833;
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < &PTR_s_wftck_1a_wdf_005001e0);
    ppuVar10 = &PTR_s_vmxmarx_vdf_005001e8;
    do {
      iVar6 = _stricmp(pcVar9,*ppuVar10);
      if (iVar6 == 0) {
        bVar4 = true;
      }
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < s_vmloadms_vdf_00500204);
    if (!bVar4) {
      ppuVar10 = &PTR_s_wftck_1a_wdf_005001e0;
      do {
        iVar6 = _stricmp((char *)(param_1 + 0x58),*ppuVar10);
        if (iVar6 == 0) {
          bVar2 = true;
        }
        ppuVar10 = ppuVar10 + 1;
      } while (ppuVar10 < &PTR_s_vmxmarx_vdf_005001e8);
      if (bVar2) goto LAB_004b3833;
    }
    if (iVar5 == 0) goto LAB_004b3848;
    bVar4 = false;
    ppuVar10 = &PTR_s_wdilo_1a_wdf_005001c0;
    bVar2 = false;
    do {
      piVar11 = local_4;
      iVar5 = _stricmp((char *)local_4,*ppuVar10);
      if (iVar5 == 0) goto LAB_004b3833;
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < &PTR_s_wftck_1a_wdf_005001e0);
    ppuVar10 = &PTR_s_vmxmarx_vdf_005001e8;
    do {
      iVar5 = _stricmp(pcVar9,*ppuVar10);
      if (iVar5 == 0) {
        bVar4 = true;
      }
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < s_vmloadms_vdf_00500204);
    if (bVar4) goto LAB_004b3848;
    ppuVar10 = &PTR_s_wftck_1a_wdf_005001e0;
    do {
      iVar5 = _stricmp((char *)piVar11,*ppuVar10);
      if (iVar5 == 0) {
        bVar2 = true;
      }
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < &PTR_s_vmxmarx_vdf_005001e8);
    if (!bVar2) goto LAB_004b3848;
  }
  else {
    ppuVar10 = &PTR_s_wftck_1a_wdf_005001e0;
    do {
      iVar6 = _stricmp((char *)(param_1 + 0x3e),*ppuVar10);
      if (iVar6 == 0) {
        bVar2 = true;
      }
      ppuVar10 = ppuVar10 + 1;
    } while (ppuVar10 < &PTR_s_vmxmarx_vdf_005001e8);
    if (!bVar2) goto LAB_004b3720;
  }
LAB_004b3833:
  *param_2 = *param_2 | 0x1000;
  DAT_005dacd0 = 0;
LAB_004b3848:
  pbVar1 = (byte *)(param_1 + 0x18);
  local_4 = (int *)0x0;
  bVar4 = parse_bwd2_resource_with_descriptor_table(pbVar1,&DAT_00500090,0xd,(byte *)&local_4);
  if (CONCAT31(extraout_var,bVar4) == 0) {
    return 0;
  }
  if (DAT_005dacd4 != 0) {
    iVar5 = *(int *)(param_1 + 0x85);
    local_4 = (int *)(param_1 + 0x75);
    piVar11 = (int *)(param_1 + 0x65);
    bVar4 = true;
    if (DAT_005db958 == 6) {
      iVar6 = 10;
    }
    else {
      iVar6 = DAT_005db958;
      if (DAT_005db958 == 5) {
        iVar6 = 4;
      }
    }
    iVar6 = iVar6 * 0x640;
    iVar7 = (int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5;
    iVar12 = 4;
    do {
      iVar5 = iVar5 + *piVar11;
      if (*piVar11 < iVar7) {
        *param_2 = *param_2 | 0x800;
        bVar4 = false;
      }
      piVar11 = piVar11 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    iVar12 = 4;
    piVar11 = local_4;
    do {
      iVar5 = iVar5 + *piVar11;
      if (*piVar11 < iVar7) {
        *param_2 = *param_2 | 0x800;
        bVar4 = false;
      }
      piVar11 = piVar11 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    if (iVar5 != iVar6) {
      bVar4 = false;
      *param_2 = *param_2 | 0x400;
    }
    if (!bVar4) {
      DAT_005dacd0 = 0;
    }
    puVar13 = param_2 + 1;
    puVar8 = open_resource_file_into_memory((char *)pbVar1);
    if (puVar8 != (uint *)0x0) {
      for (iVar5 = get_loaded_resource_file_size((char *)pbVar1); iVar5 != 0; iVar5 = iVar5 + -1) {
        uVar3 = *puVar8;
        puVar8 = (uint *)((int)puVar8 + 1);
        *puVar13 = (&g_crc32_table_msb)[*puVar13 >> 0x18 ^ (uint)(byte)uVar3] ^ *puVar13 << 8;
      }
      release_resource_file_reference((char *)pbVar1);
    }
    pcVar9 = (char *)(param_1 + 0x3e);
    puVar8 = open_resource_file_into_memory(pcVar9);
    if (puVar8 != (uint *)0x0) {
      for (iVar5 = get_loaded_resource_file_size(pcVar9); iVar5 != 0; iVar5 = iVar5 + -1) {
        uVar3 = *puVar8;
        puVar8 = (uint *)((int)puVar8 + 1);
        *puVar13 = (&g_crc32_table_msb)[*puVar13 >> 0x18 ^ (uint)(byte)uVar3] ^ *puVar13 << 8;
      }
      release_resource_file_reference(pcVar9);
    }
    vehicle_vdf_chunk_parser_context_helper_004b3d50((char *)(param_1 + 0x4b),puVar13);
    vehicle_vdf_chunk_parser_context_helper_004b3d50((char *)(param_1 + 0x58),puVar13);
    vehicle_vdf_chunk_parser_context_helper_004b3d50(s_compnent_cdf_004ffcd0,puVar13);
  }
  return 1;
}


