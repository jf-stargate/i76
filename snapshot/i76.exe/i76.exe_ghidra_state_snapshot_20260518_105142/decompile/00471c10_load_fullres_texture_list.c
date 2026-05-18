/*
 * Program: i76.exe
 * Function: load_fullres_texture_list
 * Entry: 00471c10
 * Signature: undefined4 __cdecl load_fullres_texture_list(undefined4 * param_1, byte * param_2)
 */


/* i76 second-pass rename
   old_name: FUN_00471c10
   suggested_name: load_fullres_texture_list
   basis: References FULLRES.LST and add_texture_to_cache. */

undefined4 __cdecl load_fullres_texture_list(undefined4 *param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  bool bVar3;
  uint *puVar4;
  undefined3 extraout_var;
  char *pcVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  char *pcVar11;
  byte *pbVar12;
  char local_d9;
  byte local_d8 [16];
  byte local_c8;
  byte local_c7 [199];
  
  param_1[1] = 0;
  puVar4 = load_texture_resource_resolving_vqm_cbk_to_cache(param_2);
  *param_1 = puVar4;
  if (puVar4 == (uint *)0x0) {
    return 0;
  }
  bVar3 = is_miss16_high_color_resource_mode();
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return 1;
  }
  if (param_1[1] == 0) {
    uVar7 = 0xffffffff;
    do {
      pbVar10 = param_2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pbVar10 = param_2 + 1;
      bVar1 = *param_2;
      param_2 = pbVar10;
    } while (bVar1 != 0);
    uVar7 = ~uVar7;
    pbVar10 = pbVar10 + -uVar7;
    pbVar12 = local_d8;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pbVar12 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar12 = pbVar12 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar12 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar12 = pbVar12 + 1;
    }
    pcVar5 = strrchr((char *)local_d8,0x2e);
    if (pcVar5 != (char *)0x0) {
      *pcVar5 = '\0';
    }
    uVar7 = 0xffffffff;
    pcVar5 = s__m16_004f8ca4;
    do {
      pcVar11 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar11 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar11;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    iVar9 = -1;
    pbVar10 = local_d8;
    do {
      pbVar12 = pbVar10;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      pbVar12 = pbVar10 + 1;
      bVar1 = *pbVar10;
      pbVar10 = pbVar12;
    } while (bVar1 != 0);
    pbVar10 = (byte *)(pcVar11 + -uVar7);
    pbVar12 = pbVar12 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pbVar12 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar12 = pbVar12 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar12 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar12 = pbVar12 + 1;
    }
    iVar9 = get_loaded_resource_file_size((char *)local_d8);
    if (iVar9 != 0) {
      puVar4 = open_resource_file_into_memory((char *)local_d8);
      param_1[1] = puVar4;
      if ((puVar4 != (uint *)0x0) && ((puVar4[1] & 0x40000000) == 0)) {
        if (g_fullres_resource_bitset_initialized == 0) {
          puVar6 = open_resource_file_into_memory(s_FULLRES_LST_004f8c98);
          if (puVar6 != (uint *)0x0) {
            iVar9 = get_loaded_resource_file_size(s_FULLRES_LST_004f8c98);
            for (pcVar5 = parse_fullres_lst_line
                                    (&local_d9,(char *)&local_c8,(char *)puVar6,
                                     (char *)(iVar9 + (int)puVar6)); pcVar5 != (char *)0x0;
                pcVar5 = parse_fullres_lst_line
                                   (&local_d9,(char *)&local_c8,pcVar5,(char *)(iVar9 + (int)puVar6)
                                   )) {
              uVar7 = 0;
              pbVar10 = &local_c8;
              bVar1 = local_c8;
              while (bVar1 != 0) {
                uVar7 = uVar7 * 2 ^ bVar1 & 0xdf;
                pbVar12 = pbVar10 + 1;
                pbVar10 = pbVar10 + 1;
                bVar1 = *pbVar12;
              }
              (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar7 % 0x6cd) >> 3] =
                   (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar7 % 0x6cd) >> 3] |
                   '\x01' << ((byte)((ulonglong)uVar7 % 0x6cd) & 7);
            }
            release_resource_file_reference(s_FULLRES_LST_004f8c98);
          }
          g_fullres_resource_bitset_initialized = 1;
        }
        uVar7 = 0;
        pbVar10 = local_d8;
        while (local_d8[0] != 0) {
          uVar7 = uVar7 * 2 ^ local_d8[0] & 0xdf;
          pbVar12 = pbVar10 + 1;
          pbVar10 = pbVar10 + 1;
          local_d8[0] = *pbVar12;
        }
        puVar4[1] = (uint)(('\x01' << ((byte)((ulonglong)uVar7 % 0x6cd) & 7) &
                           (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar7 % 0x6cd) >> 3])
                           != 0U | 2) << 0x1d | puVar4[1] & 0xdfffffff;
      }
    }
    if (param_1[1] == 0) {
      return 1;
    }
  }
  return 2;
}


