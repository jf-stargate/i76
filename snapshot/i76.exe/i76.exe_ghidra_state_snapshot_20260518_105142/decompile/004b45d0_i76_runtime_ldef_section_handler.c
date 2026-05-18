/*
 * Program: i76.exe
 * Function: i76_runtime_ldef_section_handler
 * Entry: 004b45d0
 * Signature: undefined __cdecl i76_runtime_ldef_section_handler(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle vdf chunk callback context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_ldef_section_handler :: LDEF
   linked-object/world-reader section wrapper; forwards callback args to 004b8f40. */

void __cdecl i76_runtime_ldef_section_handler(int *param_1,byte *param_2,int *param_3)

{
  i76_runtime_parse_ldef_linked_payload(param_1,param_2,param_3);
  return;
}


