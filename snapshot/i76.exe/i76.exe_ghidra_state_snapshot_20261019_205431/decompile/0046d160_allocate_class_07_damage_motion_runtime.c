/*
 * Program: i76.exe
 * Function: allocate_class_07_damage_motion_runtime
 * Entry: 0046d160
 * Signature: undefined4 * __stdcall allocate_class_07_damage_motion_runtime(void)
 */


undefined4 * allocate_class_07_damage_motion_runtime(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0xa0);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  initialize_vehicle_wheel_contact_state_block(puVar1);
  puVar1[0x1e] = 0;
  puVar1[0x1f] = 0;
  puVar1[0x25] = 0x3f800000;
  puVar1[0x24] = 1;
  puVar1[0x20] = 0;
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0;
  puVar1[0x1b] = 0;
  puVar1[0x26] = 400;
  puVar1[0x27] = 400;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = 0;
  return puVar1;
}


