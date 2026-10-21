/* Decompiled retail i76.exe, Ghidra v97; 004b89b0 parse_adef_fsm_script_chunks */

/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_parse_adef_actor_fsm_payload ::
   Handler target for ADEF section. Needs deeper trace.
   [cgpt-i76-v36 high] ADEF wrapper; dispatches AREV/FSM mission behavior script.
   [I76 FSM v58] Passes the AREV/FSM/EXIT chunk table at 00500D20 to generic dispatcher 004B3DB0. */

bool __cdecl parse_adef_fsm_script_chunks(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&g_adef_descriptor_table,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


