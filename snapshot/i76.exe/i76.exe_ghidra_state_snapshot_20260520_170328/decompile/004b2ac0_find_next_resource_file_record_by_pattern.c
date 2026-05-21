/*
 * Program: i76.exe
 * Function: find_next_resource_file_record_by_pattern
 * Entry: 004b2ac0
 * Signature: int __cdecl find_next_resource_file_record_by_pattern(char * param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Iterates registered resource-file
   records matching wildcard patterns such as *.wdf, *.gdf, *.vtf.
   
   I76 rename v43: find_next_resource_file_record_by_pattern
   Resource file record pattern iterator/helper. */

int __cdecl find_next_resource_file_record_by_pattern(char *param_1,int *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  if (param_1 != (char *)0x0) {
    if ((-1 < *param_2) && (*param_2 < g_resource_key_table_count)) {
      do {
        bVar1 = zfsf_payload_wrapper_context_helper_004b9e10
                          ((char *)(*param_2 * 0x30 + g_resource_key_table_entries),param_1);
        if (CONCAT31(extraout_var,bVar1) != 0) {
          iVar2 = *param_2 * 0x30 + g_resource_key_table_entries;
          *param_2 = *param_2 + 1;
          return iVar2;
        }
        iVar2 = *param_2;
        *param_2 = iVar2 + 1;
      } while (iVar2 + 1 < g_resource_key_table_count);
      return 0;
    }
  }
  return 0;
}


