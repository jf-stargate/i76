/*
 * Program: i76.exe
 * Function: texture_manager_log_or_tag
 * Entry: 0044adc0
 * Signature: undefined __cdecl texture_manager_log_or_tag(LPVOID param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: texmgr */

void __cdecl texture_manager_log_or_tag(LPVOID param_1)

{
  undefined4 *puVar1;
  
  puVar1 = get_active_world_object_entry_object((int)param_1);
  if (puVar1 != (undefined4 *)0x0) {
    has_world_object_class_damage_handler((int)puVar1);
  }
  unlink_and_release_world_object_node_refcounted(param_1,s_texmgr_004f271c);
  return;
}


