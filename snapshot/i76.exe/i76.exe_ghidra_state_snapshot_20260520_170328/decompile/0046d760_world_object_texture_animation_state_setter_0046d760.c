/*
 * Program: i76.exe
 * Function: world_object_texture_animation_state_setter_0046d760
 * Entry: 0046d760
 * Signature: undefined4 * __stdcall world_object_texture_animation_state_setter_0046d760(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object texture animation state
   setter based on adjacent named subsystem context. */

undefined4 * world_object_texture_animation_state_setter_0046d760(void)

{
  undefined4 *puVar1;
  
  puVar1 = radar_context_helper_0045f3b0(0x88);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[1] = 100;
    puVar1[2] = 100;
    puVar1[3] = 0x3f800000;
    puVar1[4] = 0x3f800000;
    puVar1[5] = 0x3f800000;
    puVar1[6] = 0x3f800000;
    puVar1[0xb] = 0x42800000;
    puVar1[0xc] = 0x42800000;
    *puVar1 = 0;
    puVar1[7] = 0x3f1100e7;
    puVar1[0x13] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0x14] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0x3e1100e7;
    puVar1[0xf] = 0xbe1100e7;
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
    puVar1[0x15] = 0;
    mission_flow_map_context_helper_0049e0f0((double *)(puVar1 + 0x16),0.7,15.0);
    puVar1[0x20] = 0x40400000;
    puVar1[0x21] = 0;
  }
  return puVar1;
}


