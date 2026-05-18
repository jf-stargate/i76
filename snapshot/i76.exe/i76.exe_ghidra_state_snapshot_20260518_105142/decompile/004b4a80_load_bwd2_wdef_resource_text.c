/*
 * Program: i76.exe
 * Function: load_bwd2_wdef_resource_text
 * Entry: 004b4a80
 * Signature: undefined4 __cdecl load_bwd2_wdef_resource_text(byte * param_1, char * param_2, size_t param_3)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Shell callback +0x58. Opens a
   resource, parses BWD2/WDEF chunks, copies the WDEF text/name payload to caller buffer, and
   NUL-terminates it. */

undefined4 __cdecl load_bwd2_wdef_resource_text(byte *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  bool bVar2;
  byte local_100 [256];
  
  if (param_1 == (byte *)0x0) {
    bVar2 = false;
  }
  else {
    iVar1 = _strnicmp((char *)param_1,s_null_004c3280,4);
    if (iVar1 == 0) {
      bVar2 = true;
    }
    else {
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
                                 ((int *)g_current_bwd2_parse_cursor,&DAT_00500610,1,local_100,
                                  param_1,1,g_current_bwd2_parse_end);
        }
        release_resource_file_reference((char *)param_1);
      }
      bVar2 = g_current_bwd2_parse_cursor != (uint *)0x0;
    }
  }
  if (bVar2) {
    strncpy(param_2,(char *)local_100,param_3);
    param_2[param_3 - 1] = '\0';
    return 1;
  }
  return 0;
}


