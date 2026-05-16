/*
 * Program: i76.exe
 * Function: muzzle_flash_effect_context_helper_0049f4f0
 * Entry: 0049f4f0
 * Signature: undefined __stdcall muzzle_flash_effect_context_helper_0049f4f0(void)
 */


/* cgpt readability rename set D v16: Readability pass set D: muzzle flash effect context helper
   based on adjacent named subsystem context. */

void muzzle_flash_effect_context_helper_0049f4f0(void)

{
  undefined4 *puVar1;
  
  DAT_005a8108 = 0;
  if (0 < DAT_005a810c) {
    puVar1 = &DAT_00655284;
    do {
      puVar1[-1] = 0;
      *puVar1 = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[6] = 0x32;
      puVar1[7] = 0;
      puVar1[8] = 0;
      puVar1[9] = 0;
      puVar1[10] = 0;
      puVar1[0xb] = 0;
      puVar1[0xc] = 0;
      puVar1[0xd] = 0x3f800000;
      puVar1[0x15] = 0;
      puVar1[0x16] = 0;
      puVar1[0x18] = 0;
      puVar1[0x17] = 0;
      puVar1[0x19] = 0;
      puVar1[0x1b] = 0;
      puVar1[0x1c] = 0;
      puVar1[0x21] = 0;
      puVar1[0x22] = 0;
      puVar1[0x27] = 0;
      puVar1[0x28] = 0;
      puVar1[0x2d] = 0;
      puVar1[0x2e] = 0;
      puVar1[0x11] = 0;
      DAT_005a810c = DAT_005a810c + -1;
      puVar1[0x12] = 0;
      puVar1[0x13] = 0;
      puVar1[0x14] = 0;
      puVar1[0xe] = 0;
      puVar1[0x10] = 0;
      puVar1[0xf] = 0;
      puVar1 = puVar1 + 0x34;
    } while (DAT_005a810c != 0);
  }
  DAT_005a810c = 0;
  reset_pending_mission_vehicle_effect_spawn_heap();
  return;
}


