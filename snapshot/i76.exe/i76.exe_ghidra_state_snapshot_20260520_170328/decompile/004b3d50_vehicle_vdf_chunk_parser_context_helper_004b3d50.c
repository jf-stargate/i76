/*
 * Program: i76.exe
 * Function: vehicle_vdf_chunk_parser_context_helper_004b3d50
 * Entry: 004b3d50
 * Signature: undefined __cdecl vehicle_vdf_chunk_parser_context_helper_004b3d50(char * param_1, uint * param_2)
 */


/* cgpt label refinement v20: was vehicle_vdf_chunk_parse_context_helper_004b3d50. Normalize parser
   wording. */

void __cdecl vehicle_vdf_chunk_parser_context_helper_004b3d50(char *param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  puVar2 = open_resource_file_into_memory(param_1);
  if (puVar2 != (uint *)0x0) {
    for (iVar3 = get_loaded_resource_file_size(param_1); iVar3 != 0; iVar3 = iVar3 + -1) {
      uVar1 = *puVar2;
      puVar2 = (uint *)((int)puVar2 + 1);
      *param_2 = (&g_crc32_table_msb)[*param_2 >> 0x18 ^ (uint)(byte)uVar1] ^ *param_2 << 8;
    }
    release_resource_file_reference(param_1);
  }
  return;
}


