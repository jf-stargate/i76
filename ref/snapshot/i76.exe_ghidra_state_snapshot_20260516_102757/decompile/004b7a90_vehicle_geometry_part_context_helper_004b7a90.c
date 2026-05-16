/*
 * Program: i76.exe
 * Function: vehicle_geometry_part_context_helper_004b7a90
 * Entry: 004b7a90
 * Signature: bool __cdecl vehicle_geometry_part_context_helper_004b7a90(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt label refinement v20: was vehicle_vdf_geometry_part_context_helper_004b7a90. Shorten
   readability label. */

bool __cdecl vehicle_geometry_part_context_helper_004b7a90(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_00500ae8,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


