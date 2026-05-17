/*
 * Program: i76.exe
 * Function: allocate_vehicle_runtime_context_and_child_nodes
 * Entry: 00462d90
 * Signature: undefined4 * __stdcall allocate_vehicle_runtime_context_and_child_nodes(void)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Class-id 1 constructor callback.
   Allocates vehicle runtime context and child world objects with classes 0x14, 0x15, 0x16, and
   0x17. */

undefined4 * allocate_vehicle_runtime_context_and_child_nodes(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  puVar1 = allocate_initialized_vehicle_runtime_context();
  if (puVar1 != (undefined4 *)0x0) {
    pvVar2 = allocate_world_object_node(0);
    puVar1[0xf1] = pvVar2;
    set_world_object_class_and_register_runtime((int)pvVar2,0x15);
    pvVar2 = allocate_world_object_node(0);
    puVar1[0xf3] = pvVar2;
    set_world_object_class_and_register_runtime((int)pvVar2,0x16);
    pvVar2 = allocate_world_object_node(0);
    puVar1[0xf2] = pvVar2;
    set_world_object_class_and_register_runtime((int)pvVar2,0x17);
    pvVar2 = allocate_world_object_node(0);
    puVar1[0xf0] = pvVar2;
    set_world_object_class_and_register_runtime((int)pvVar2,0x14);
  }
  return puVar1;
}


