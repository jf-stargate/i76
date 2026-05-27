/*
 * Program: i76.exe
 * Function: mark_asset_fullres_flag_from_fullres_list
 * Entry: 00471840
 * Signature: undefined __cdecl mark_asset_fullres_flag_from_fullres_list(int param_1, byte * param_2)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium-high] Initializes/checks
   FULLRES.LST-derived hash bitset and marks asset/resource flags for full-resolution handling. */

void __cdecl mark_asset_fullres_flag_from_fullres_list(int param_1,byte *param_2)

{
  byte *pbVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  byte *pbVar7;
  char local_c9;
  byte local_c8;
  byte local_c7 [199];
  
  if (g_fullres_resource_bitset_initialized == 0) {
    puVar3 = open_resource_file_into_memory(s_FULLRES_LST_004f8c98);
    if (puVar3 != (uint *)0x0) {
      iVar4 = get_loaded_resource_file_size(s_FULLRES_LST_004f8c98);
      for (pcVar5 = parse_fullres_lst_line
                              (&local_c9,(char *)&local_c8,(char *)puVar3,
                               (char *)(iVar4 + (int)puVar3)); pcVar5 != (char *)0x0;
          pcVar5 = parse_fullres_lst_line
                             (&local_c9,(char *)&local_c8,pcVar5,(char *)(iVar4 + (int)puVar3))) {
        uVar6 = 0;
        pbVar7 = &local_c8;
        bVar2 = local_c8;
        while (bVar2 != 0) {
          uVar6 = uVar6 * 2 ^ bVar2 & 0xdf;
          pbVar1 = pbVar7 + 1;
          pbVar7 = pbVar7 + 1;
          bVar2 = *pbVar1;
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
  bVar2 = *param_2;
  while (bVar2 != 0) {
    uVar6 = uVar6 * 2 ^ bVar2 & 0xdf;
    pbVar7 = param_2 + 1;
    param_2 = param_2 + 1;
    bVar2 = *pbVar7;
  }
  *(uint *)(param_1 + 4) =
       (uint)(('\x01' << ((byte)((ulonglong)uVar6 % 0x6cd) & 7) &
              (&g_fullres_resource_hash_bitset)[(int)((ulonglong)uVar6 % 0x6cd) >> 3]) != 0U | 2) <<
       0x1d | *(uint *)(param_1 + 4) & 0xdfffffff;
  return;
}


