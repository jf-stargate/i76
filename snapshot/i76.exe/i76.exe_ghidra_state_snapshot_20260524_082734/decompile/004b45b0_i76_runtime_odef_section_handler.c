/*
 * Program: i76.exe
 * Function: i76_runtime_odef_section_handler
 * Entry: 004b45b0
 * Signature: undefined __cdecl i76_runtime_odef_section_handler(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle vdf chunk callback context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_odef_section_handler :: ODEF object
   section wrapper; forwards callback args to 004b7a90. */

void __cdecl i76_runtime_odef_section_handler(int *param_1,byte *param_2,int *param_3)

{
  parse_odef_object_placement_chunks(param_1,param_2,param_3);
  return;
}


