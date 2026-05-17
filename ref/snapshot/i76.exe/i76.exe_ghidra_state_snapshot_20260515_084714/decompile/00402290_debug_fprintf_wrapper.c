/*
 * Program: i76.exe
 * Function: debug_fprintf_wrapper
 * Entry: 00402290
 * Signature: undefined __cdecl debug_fprintf_wrapper(char param_1)
 */


/* i76 second-pass rename
   old_name: FUN_00402290
   suggested_name: debug_fprintf_wrapper
   basis: Tiny fprintf wrapper called by diagnostics/cache/resource paths. */

void __cdecl debug_fprintf_wrapper(char param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < g_resource_nested_load_depth) {
    do {
      fprintf(g_resource_debug_log_file,s__004c2224);
      iVar1 = iVar1 + 1;
    } while (iVar1 < g_resource_nested_load_depth);
  }
  fprintf(g_resource_debug_log_file,s__c_004c2220,(int)param_1);
  return;
}


