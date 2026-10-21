/*
 * Program: i76.exe
 * Function: allocate_class_09_vehicle_runtime
 * Entry: 0046b780
 * Signature: undefined4 * __stdcall allocate_class_09_vehicle_runtime(void)
 */


undefined4 * allocate_class_09_vehicle_runtime(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = allocate_vehicle_runtime_context_and_child_nodes();
  puVar2 = radar_context_helper_0045f3b0(0x18);
  puVar1[0x142] = puVar2;
  puVar2[5] = 0;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[1] = 600;
  *puVar2 = 600;
  puVar2[2] = 0x3ada740e;
  puVar1[0x115] = 0x81;
  return puVar1;
}


