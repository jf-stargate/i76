/*
 * Program: i76.exe
 * Function: parse_odef_object_placement_chunks
 * Entry: 004b7a90
 * Signature: bool __cdecl parse_odef_object_placement_chunks(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt label refinement v20: was vehicle_vdf_geometry_part_context_helper_004b7a90. Shorten
   readability label.
   
   [cgpt_i76exe_runtime_section_names_v2] proposed=i76_runtime_parse_odef_object_payload :: Handler
   target for ODEF section. Existing label references geometry/object context; needs deeper trace.
   [cgpt-i76-v36 high] ODEF wrapper for mission object placement OBJ records.
   
   I76 rename v43: parse_odef_object_definition_section
   ODEF top-level descriptor-table section handler. */

bool __cdecl parse_odef_object_placement_chunks(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&g_odef_descriptor_table,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


