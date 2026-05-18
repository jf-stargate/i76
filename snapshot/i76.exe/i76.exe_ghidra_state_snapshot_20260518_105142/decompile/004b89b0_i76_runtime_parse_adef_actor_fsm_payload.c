/*
 * Program: i76.exe
 * Function: i76_runtime_parse_adef_actor_fsm_payload
 * Entry: 004b89b0
 * Signature: bool __cdecl i76_runtime_parse_adef_actor_fsm_payload(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_parse_adef_actor_fsm_payload ::
   Handler target for ADEF section. Needs deeper trace. */

bool __cdecl i76_runtime_parse_adef_actor_fsm_payload(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_00500d20,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


