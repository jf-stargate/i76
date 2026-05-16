/*
 * Program: i76.exe
 * Function: vehicle_vdf_runtime_context_helper_004b4a50
 * Entry: 004b4a50
 * Signature: bool __cdecl vehicle_vdf_runtime_context_helper_004b4a50(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle vdf runtime context helper
   based on adjacent named subsystem context. */

bool __cdecl vehicle_vdf_runtime_context_helper_004b4a50(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_005005e0,3,param_2,(byte *)0x0,1,param_3);
  return piVar1 != (int *)0x0;
}


