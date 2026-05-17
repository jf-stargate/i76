/*
 * Program: i76.exe
 * Function: mission_scrounge_record_context_helper_004b8750
 * Entry: 004b8750
 * Signature: bool __cdecl mission_scrounge_record_context_helper_004b8750(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: mission scrounge record context helper
   based on adjacent named subsystem context. */

bool __cdecl
mission_scrounge_record_context_helper_004b8750(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_00500cd0,5,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


