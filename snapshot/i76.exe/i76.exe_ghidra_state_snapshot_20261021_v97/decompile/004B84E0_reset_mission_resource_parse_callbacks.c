/* Decompiled retail i76.exe, Ghidra v97; 004b84e0 reset_mission_resource_parse_callbacks */

/* [cgpt i76.exe mission/runtime rename v14; confidence=medium_high] Registers/reset mission
   resource parse callback state through FUN_00457290 before selected mission parse. */

undefined4 reset_mission_resource_parse_callbacks(void)

{
  register_world_object_tree_callback(clear_mission_parse_object_callback_state);
  return 1;
}


