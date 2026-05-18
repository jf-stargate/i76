/*
 * Program: i76.exe
 * Function: parse_bwd2_resource_with_descriptor_table
 * Entry: 004b41e0
 * Signature: bool __cdecl parse_bwd2_resource_with_descriptor_table(byte * param_1, byte * param_2, int param_3, byte * param_4)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Opens a named resource,
   validates the generic BWD2 descriptor, then parses a caller-supplied tagged chunk descriptor
   table.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=parse_bwd2_resource_with_descriptor_table ::
   Generic named-resource BWD2 loader that validates BWD2 then parses a caller-supplied descriptor
   table. */

bool __cdecl
parse_bwd2_resource_with_descriptor_table(byte *param_1,byte *param_2,int param_3,byte *param_4)

{
  int iVar1;
  
  if (param_1 == (byte *)0x0) {
    return false;
  }
  iVar1 = _strnicmp((char *)param_1,s_null_004c3280,4);
  if (iVar1 == 0) {
    return true;
  }
  g_current_bwd2_parse_cursor = open_resource_file_into_memory((char *)param_1);
  if (g_current_bwd2_parse_cursor != (uint *)0x0) {
    iVar1 = get_loaded_resource_file_size((char *)param_1);
    g_current_bwd2_parse_end = (int *)(iVar1 + (int)g_current_bwd2_parse_cursor);
    g_current_bwd2_parse_cursor =
         (uint *)parse_tagged_chunk_descriptor_table
                           ((int *)g_current_bwd2_parse_cursor,&g_bwd2_descriptor_table,2,
                            (byte *)0x0,param_1,1,g_current_bwd2_parse_end);
    if (g_current_bwd2_parse_cursor != (uint *)0x0) {
      g_current_bwd2_parse_cursor =
           (uint *)parse_tagged_chunk_descriptor_table
                             ((int *)g_current_bwd2_parse_cursor,param_2,param_3,param_4,param_1,1,
                              g_current_bwd2_parse_end);
    }
    release_resource_file_reference((char *)param_1);
  }
  return g_current_bwd2_parse_cursor != (uint *)0x0;
}


