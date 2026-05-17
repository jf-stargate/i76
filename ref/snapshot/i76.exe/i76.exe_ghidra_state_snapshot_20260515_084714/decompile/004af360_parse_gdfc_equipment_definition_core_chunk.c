/*
 * Program: i76.exe
 * Function: parse_gdfc_equipment_definition_core_chunk
 * Entry: 004af360
 * Signature: undefined4 __cdecl parse_gdfc_equipment_definition_core_chunk(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=high] GDFC callback for
   equipment/gadget definition core fields. */

undefined4 __cdecl parse_gdfc_equipment_definition_core_chunk(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = create_vehicle_child_object_and_copy_ids(*(int *)*param_2,param_2 + 2);
  param_2[0x51] = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  set_world_object_class_and_register_runtime(iVar1,0x32);
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = param_2 + 5;
  for (iVar1 = 0x29; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 1;
}


