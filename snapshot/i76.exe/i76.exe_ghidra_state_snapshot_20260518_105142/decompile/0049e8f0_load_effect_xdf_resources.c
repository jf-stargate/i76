/*
 * Program: i76.exe
 * Function: load_effect_xdf_resources
 * Entry: 0049e8f0
 * Signature: undefined __stdcall load_effect_xdf_resources(void)
 */


/* cgpt whole-binary semantic rename v1: references xcarx1/xbldx1/xcars1.xdf */

void load_effect_xdf_resources(void)

{
  int iVar1;
  undefined4 *puVar2;
  char local_8 [8];
  
  DAT_005a80f4 = HeapCreate(0,0,0);
  DAT_005a80f8 = HeapCreate(0,0,0);
  puVar2 = &g_explosion_runtime_state;
  for (iVar1 = 0x71; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_005a80fc = 0;
  world_reader_null_handler((byte *)s_xcarx1_xdf_004fe6d4,local_8,0);
  world_reader_null_handler((byte *)s_xbldx1_xdf_004fe6c8,local_8,0);
  world_reader_null_handler((byte *)s_xcars1_xdf_004fe6bc,local_8,0);
  return;
}


