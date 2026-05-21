/*
 * Program: i76.exe
 * Function: parse_rdef_route_segment_chunks
 * Entry: 004b8750
 * Signature: bool __cdecl parse_rdef_route_segment_chunks(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: mission scrounge record context helper
   based on adjacent named subsystem context.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_parse_rdef_road_payload :: Handler
   target for RDEF section. Existing label references scrounge/mission records; needs deeper trace.
   [cgpt-i76-v36 high] RDEF wrapper for RSEG/ISEG/TSEG route/corridor records. */

bool __cdecl parse_rdef_route_segment_chunks(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&g_rdef_descriptor_table,5,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


