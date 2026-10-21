/*
 * Program: i76.exe
 * Function: allocate_class_16_damage_runtime
 * Entry: 0046a7c0
 * Signature: undefined __stdcall allocate_class_16_damage_runtime(void)
 */


void allocate_class_16_damage_runtime(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x18);
  puVar1[1] = 0x96;
  puVar1[2] = 0x96;
  *puVar1 = 0;
  puVar1[3] = 0x3f800000;
  puVar1[4] = 0x3f800000;
  return;
}


