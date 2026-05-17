/*
 * Program: i76.exe
 * Function: parse_brake_table_component_entries
 * Entry: 004b0f90
 * Signature: undefined4 __cdecl parse_brake_table_component_entries(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] BTBL callback in
   brake component descriptor table. */

undefined4 __cdecl parse_brake_table_component_entries(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(int *)(param_2 + 0x3c) * 0x10 + 0xc + param_1);
  *(undefined4 *)(param_2 + 0x62) = *puVar1;
  *(undefined4 *)(param_2 + 0x66) = puVar1[1];
  *(undefined4 *)(param_2 + 0x6a) = puVar1[2];
  *(undefined4 *)(param_2 + 0x6e) = puVar1[3];
  return 1;
}


