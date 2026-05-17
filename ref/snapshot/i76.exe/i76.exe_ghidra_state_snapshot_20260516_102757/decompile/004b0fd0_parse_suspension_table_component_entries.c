/*
 * Program: i76.exe
 * Function: parse_suspension_table_component_entries
 * Entry: 004b0fd0
 * Signature: undefined4 __cdecl parse_suspension_table_component_entries(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] STBL callback in
   suspension component descriptor table. */

undefined4 __cdecl parse_suspension_table_component_entries(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(int *)(param_2 + 0x74) * 0x10 + 0xc + param_1);
  *(undefined4 *)(param_2 + 0x9e) = *puVar1;
  *(undefined4 *)(param_2 + 0xa2) = puVar1[1];
  *(undefined4 *)(param_2 + 0xa6) = puVar1[2];
  *(undefined4 *)(param_2 + 0xaa) = puVar1[3];
  return 1;
}


