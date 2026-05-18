/*
 * Program: I76EDIT.EXE
 * Function: i76edit_find_next_enabled_path_node
 * Entry: 00411520
 * Signature: undefined4 * __cdecl i76edit_find_next_enabled_path_node(undefined4 * param_1)
 */


/* [cgpt_i76edit_level_renames_v4:medium] Walks a linked list and returns the next node whose
   payload flags at +0x50 have bit 0 set. */

undefined4 * __cdecl i76edit_find_next_enabled_path_node(undefined4 *param_1)

{
  while( true ) {
    if (param_1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if ((*(uint *)(param_1[2] + 0x50) & 1) != 0) break;
    param_1 = (undefined4 *)*param_1;
  }
  return param_1;
}


