/* Decompiled retail i76.exe, Ghidra v97; 00457610 register_world_object_instance_key */

/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457610. Remove
   duplicated network/entity wording. */

void __cdecl register_world_object_instance_key(int param_1,int param_2,undefined4 param_3)

{
  append_world_object_instance_key_record
            ((undefined4 *)&g_world_object_instance_key_registry,param_1,param_2,param_3);
  return;
}


