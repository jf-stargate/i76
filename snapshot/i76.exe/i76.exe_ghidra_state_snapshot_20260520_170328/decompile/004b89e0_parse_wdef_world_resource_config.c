/*
 * Program: i76.exe
 * Function: parse_wdef_world_resource_config
 * Entry: 004b89e0
 * Signature: bool __cdecl parse_wdef_world_resource_config(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_parse_wdef_world_payload :: Handler
   target for WDEF section. Needs deeper trace; name is wrapper-derived.
   [cgpt-i76-v36 high] WDEF wrapper; dispatches WREV/WRLD resource config. */

bool __cdecl parse_wdef_world_resource_config(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&g_wdef_descriptor_table,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


