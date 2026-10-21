/*
 * Program: i76.exe
 * Function: allocate_class_0a_damage_motion_runtime
 * Entry: 0046f650
 * Signature: undefined __stdcall allocate_class_0a_damage_motion_runtime(void)
 */


void allocate_class_0a_damage_motion_runtime(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x14);
  if (puVar1 == (undefined4 *)0x0) {
    return;
  }
  *puVar1 = 0;
  puVar1[1] = 0x3f490fdb;
  puVar1[2] = 0;
  puVar1[3] = 400;
  puVar1[4] = 400;
  return;
}


