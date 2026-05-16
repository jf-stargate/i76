/*
 * Program: i76.exe
 * Function: world_reader_parser_context_helper_004b8f40
 * Entry: 004b8f40
 * Signature: bool __cdecl world_reader_parser_context_helper_004b8f40(int * param_1, byte * param_2, int * param_3)
 */


/* cgpt label refinement v20: was world_reader_parse_context_helper_004b8f40. Normalize parser
   wording. */

bool __cdecl world_reader_parser_context_helper_004b8f40(int *param_1,byte *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = parse_tagged_chunk_descriptor_table
                     (param_1,&DAT_00500d80,3,(byte *)0x0,param_2,1,param_3);
  return piVar1 != (int *)0x0;
}


