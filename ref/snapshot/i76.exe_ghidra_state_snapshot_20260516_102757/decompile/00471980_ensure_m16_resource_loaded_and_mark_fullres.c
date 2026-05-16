/*
 * Program: i76.exe
 * Function: ensure_m16_resource_loaded_and_mark_fullres
 * Entry: 00471980
 * Signature: int __cdecl ensure_m16_resource_loaded_and_mark_fullres(int * param_1, char * param_2)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Lazily loads basename.m16,
   initializes FULLRES.LST bitset if needed, and marks loaded M16 resource flags for full-resolution
   handling. */

int __cdecl ensure_m16_resource_loaded_and_mark_fullres(int *param_1,char *param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  char *pcVar10;
  byte *pbVar11;
  char local_d9;
  byte local_d8 [16];
  byte local_c8;
  byte local_c7 [199];
  
  if (*param_1 == 0) {
    uVar6 = 0xffffffff;
    do {
      pcVar3 = param_2;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar3 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar3;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pbVar9 = (byte *)(pcVar3 + -uVar6);
    pbVar11 = local_d8;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar11 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar11 = pbVar11 + 1;
    }
    pcVar3 = strrchr((char *)local_d8,0x2e);
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    uVar6 = 0xffffffff;
    pcVar3 = s__m16_004f8ca4;
    do {
      pcVar10 = pcVar3;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar10;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    iVar8 = -1;
    pbVar9 = local_d8;
    do {
      pbVar11 = pbVar9;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pbVar11 = pbVar9 + 1;
      bVar2 = *pbVar9;
      pbVar9 = pbVar11;
    } while (bVar2 != 0);
    pbVar9 = (byte *)(pcVar10 + -uVar6);
    pbVar11 = pbVar11 + -1;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar11 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar11 = pbVar11 + 1;
    }
    iVar8 = get_loaded_resource_file_size((char *)local_d8);
    if (iVar8 != 0) {
      puVar4 = open_resource_file_into_memory((char *)local_d8);
      *param_1 = (int)puVar4;
      if ((puVar4 != (uint *)0x0) && ((puVar4[1] & 0x40000000) == 0)) {
        if (g_fullres_resource_bitset_initialized == 0) {
          puVar5 = open_resource_file_into_memory(s_FULLRES_LST_004f8c98);
          if (puVar5 != (uint *)0x0) {
            iVar8 = get_loaded_resource_file_size(s_FULLRES_LST_004f8c98);
            for (pcVar3 = parse_fullres_lst_line
                                    (&local_d9,(char *)&local_c8,(char *)puVar5,
                                     (char *)(iVar8 + (int)puVar5)); pcVar3 != (char *)0x0;
                pcVar3 = parse_fullres_lst_line
                                   (&local_d9,(char *)&local_c8,pcVar3,(char *)(iVar8 + (int)puVar5)
                                   )) {
              uVar6 = 0;
              pbVar9 = &local_c8;
              bVar2 = local_c8;
              while (bVar2 != 0) {
                uVar6 = uVar6 * 2 ^ bVar2 & 0xdf;
                pbVar11 = pbVar9 + 1;
                pbVar9 = pbVar9 + 1;
                bVar2 = *pbVar11;
              }
              (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar6 % 0x6cd) >> 3] =
                   (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar6 % 0x6cd) >> 3] |
                   '\x01' << ((byte)((ulonglong)uVar6 % 0x6cd) & 7);
            }
            release_resource_file_reference(s_FULLRES_LST_004f8c98);
          }
          g_fullres_resource_bitset_initialized = 1;
        }
        uVar6 = 0;
        pbVar9 = local_d8;
        while (local_d8[0] != 0) {
          uVar6 = uVar6 * 2 ^ local_d8[0] & 0xdf;
          pbVar11 = pbVar9 + 1;
          pbVar9 = pbVar9 + 1;
          local_d8[0] = *pbVar11;
        }
        puVar4[1] = (uint)(('\x01' << ((byte)((ulonglong)uVar6 % 0x6cd) & 7) &
                           (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar6 % 0x6cd) >> 3])
                           != 0U | 2) << 0x1d | puVar4[1] & 0xdfffffff;
      }
    }
  }
  return *param_1;
}


