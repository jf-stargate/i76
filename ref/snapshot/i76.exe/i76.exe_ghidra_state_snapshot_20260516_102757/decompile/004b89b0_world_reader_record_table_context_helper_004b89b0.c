/*
 * Program: i76.exe
 * Function: world_reader_record_table_context_helper_004b89b0
 * Entry: 004b89b0
 * Signature: bool __cdecl world_reader_record_table_context_helper_004b89b0(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context. */

bool __cdecl
world_reader_record_table_context_helper_004b89b0(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_00500d20,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


