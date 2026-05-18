/*
 * Program: i76.exe
 * Function: terrain_reverse_tag_handler
 * Entry: 00493910
 * Signature: bool __cdecl terrain_reverse_tag_handler(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence TREV
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=i76_runtime_parse_tdef_terrain_chunks :: TDEF
   handler. Clears runtime zone map/page tables, then parses nested terrain descriptor table at
   004fae18. */

bool __cdecl terrain_reverse_tag_handler(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &g_runtime_zmap_80x80_u8;
  for (iVar2 = 0x640; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  puVar3 = &g_runtime_active_zone_page_ptrs;
  for (iVar2 = 0x50; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,(byte *)g_tdef_terrain_descriptor_table,4,(byte *)0x0,param_2,1,
                      param_3);
  return piVar1 != (int *)0x0;
}


