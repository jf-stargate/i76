/*
 * Program: i76.exe
 * Function: parse_engine_table_component_entries
 * Entry: 004b0f50
 * Signature: undefined4 __cdecl parse_engine_table_component_entries(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] NTBL callback in
   engine component descriptor table. */

undefined4 __cdecl parse_engine_table_component_entries(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = parse_world_object_placement_field_helper_00469f10(*(int *)(param_2 + 4));
  iVar1 = iVar2 * 0x10 + 0xc + param_1;
  *(undefined4 *)(param_2 + 0x2a) = *(undefined4 *)(iVar2 * 0x10 + 0xc + param_1);
  *(undefined4 *)(param_2 + 0x2e) = *(undefined4 *)(iVar1 + 4);
  *(undefined4 *)(param_2 + 0x32) = *(undefined4 *)(iVar1 + 8);
  *(undefined4 *)(param_2 + 0x36) = *(undefined4 *)(iVar1 + 0xc);
  return 1;
}


