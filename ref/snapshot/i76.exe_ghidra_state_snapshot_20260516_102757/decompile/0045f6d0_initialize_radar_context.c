/*
 * Program: i76.exe
 * Function: initialize_radar_context
 * Entry: 0045f6d0
 * Signature: undefined __cdecl initialize_radar_context(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: radar */

void __cdecl initialize_radar_context(int *param_1)

{
  int iVar1;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    iVar1 = is_world_object_class_root_actor_or_weapon_range(*param_1);
    if ((iVar1 != 0) && (iVar1 = *param_1, iVar1 != 0)) {
      DAT_0054b1ec = allocate_linked_list_node_3field(DAT_0054b1ec,(undefined4 *)0x0,iVar1);
      increment_refcount_recursive_for_object_tree(iVar1,s_radar_004f7694);
    }
  }
  return;
}


