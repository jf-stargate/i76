/*
 * Program: i76.exe
 * Function: i76_runtime_adef_section_handler
 * Entry: 004b45f0
 * Signature: undefined __cdecl i76_runtime_adef_section_handler(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle vdf chunk callback context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_adef_section_handler :: ADEF
   actor/FSM section wrapper; forwards callback args to 004b89b0. */

void __cdecl i76_runtime_adef_section_handler(int *param_1,byte *param_2,int *param_3)

{
  parse_adef_fsm_script_chunks(param_1,param_2,param_3);
  return;
}


