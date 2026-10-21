/*
 * Program: i76.exe
 * Function: allocate_class_08_vehicle_runtime_and_aux_state
 * Entry: 00462580
 * Signature: undefined4 * __stdcall allocate_class_08_vehicle_runtime_and_aux_state(void)
 */


undefined4 * allocate_class_08_vehicle_runtime_and_aux_state(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = allocate_vehicle_runtime_context_and_child_nodes();
  puVar2 = radar_context_helper_0045f3b0(0x54);
  puVar1[0x142] = puVar2;
  puVar2[1] = 600;
  *puVar2 = 600;
  puVar2[2] = 0x3ada740e;
  puVar2[0x13] = 1;
  puVar2[0x14] = 5;
  return puVar1;
}


