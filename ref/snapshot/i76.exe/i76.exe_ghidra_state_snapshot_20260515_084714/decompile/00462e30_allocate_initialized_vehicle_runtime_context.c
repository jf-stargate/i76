/*
 * Program: i76.exe
 * Function: allocate_initialized_vehicle_runtime_context
 * Entry: 00462e30
 * Signature: undefined4 * __stdcall allocate_initialized_vehicle_runtime_context(void)
 */


/* cgpt rename v2: Allocates and initializes the large vehicle runtime context with default damage,
   wheel, lighting, and headlight state. */

undefined4 * allocate_initialized_vehicle_runtime_context(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = radar_context_helper_0045f3b0(0x50c);
  puVar2 = puVar1;
  for (iVar3 = 0x143; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  initialize_vehicle_wheel_contact_state_block(puVar1 + 0xe);
  puVar1[1] = 0xbf800000;
  puVar1[2] = 0x3f800000;
  puVar1[3] = 0xc0000000;
  puVar1[4] = 0x3f800000;
  puVar1[5] = 0x3f800000;
  puVar1[6] = 0xc0000000;
  puVar1[7] = 0x3f800000;
  puVar1[8] = 0x3f800000;
  puVar1[9] = 0x40000000;
  puVar1[10] = 0xbf800000;
  puVar1[0xb] = 0x3f800000;
  puVar1[0xd] = 0x3fc00000;
  puVar1[0xc] = 0x40000000;
  effect_target_list_scan_context_helper_004382e0(puVar1 + 0x29);
  puVar1[0x38] = 0;
  puVar1[0x39] = 0;
  puVar1[0x3a] = 0x3f800000;
  puVar1[0x3b] = 0;
  puVar1[0x40] = 0;
  puVar1[0x3c] = 0;
  puVar1[0x3d] = 0;
  puVar1[0x3e] = 0;
  puVar1[0x3f] = 0;
  puVar1[0x41] = 3;
  iVar3 = allocate_initialized_ai_fsm_behavior_state_block();
  puVar1[0x42] = iVar3;
  puVar1[0x43] = 0;
  puVar1[0x44] = 0x3e4ccccd;
  puVar1[0x45] = 0x3faf5c29;
  puVar1[0x46] = 0x402f5c29;
  puVar1[0x48] = 0;
  puVar1[0x49] = 0;
  effect_target_list_scan_context_helper_00438340((float *)(puVar1 + 0x29),1500.0,1500.0);
  puVar1[0x4b] = 0;
  puVar1[0x4c] = 0;
  puVar1[0x4a] = 0x3f800000;
  iVar3 = 4;
  puVar1[0x4d] = 0;
  puVar2 = puVar1 + 0x56;
  do {
    puVar2[-8] = 400;
    *puVar2 = 400;
    puVar2[-4] = 400;
    puVar2[4] = 400;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar2 = puVar1 + 0x5e;
  iVar3 = 5;
  do {
    puVar2[5] = 400;
    *puVar2 = 400;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar1[0x67] = 100;
  puVar1[0x62] = 100;
  puVar2 = puVar1 + 0x68;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = puVar1 + 0x6f;
  for (iVar3 = 0x77; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = puVar1 + 0xea;
  for (iVar3 = 0x18; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = puVar1 + 0x108;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar1[0xe6] = 0;
  puVar1[0xe7] = 0;
  puVar1[0x110] = 0;
  puVar1[0x114] = 0;
  iVar3 = get_current_headlight_runtime_state();
  puVar1[0x115] = (-(uint)(iVar3 != 0) & 0xffffffc0) + 0x40;
  puVar1[0x118] = 0;
  puVar1[0x116] = 0;
  *(undefined2 *)(puVar1 + 0x120) = 0;
  puVar1[0x119] = 0x3f800000;
  *(undefined2 *)((int)puVar1 + 0x482) = 0;
  puVar1[0x117] = 2;
  puVar1[0x11b] = 0x411ccccd;
  puVar1[0x11a] = 0;
  puVar1[0x11c] = 0;
  puVar1[0x11d] = 0;
  puVar1[0x11e] = 0x3dcccccd;
  puVar1[0x142] = 0;
  return puVar1;
}


