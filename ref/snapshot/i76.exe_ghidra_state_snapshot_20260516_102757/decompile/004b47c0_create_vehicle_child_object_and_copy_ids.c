/*
 * Program: i76.exe
 * Function: create_vehicle_child_object_and_copy_ids
 * Entry: 004b47c0
 * Signature: undefined __cdecl create_vehicle_child_object_and_copy_ids(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Creates a vehicle child
   object and copies identity/name fields used by the VGEO hierarchy. */

void __cdecl create_vehicle_child_object_and_copy_ids(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = allocate_world_object_node(param_1);
  if ((puVar1 != (undefined4 *)0x0) && (param_2 != (undefined4 *)0x0)) {
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
  }
  return;
}


