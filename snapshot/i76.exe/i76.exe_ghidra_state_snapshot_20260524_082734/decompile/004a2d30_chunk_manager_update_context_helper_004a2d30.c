/*
 * Program: i76.exe
 * Function: chunk_manager_update_context_helper_004a2d30
 * Entry: 004a2d30
 * Signature: undefined __stdcall chunk_manager_update_context_helper_004a2d30(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: chunk manager update context helper
   based on adjacent named subsystem context. */

void chunk_manager_update_context_helper_004a2d30(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int aiStack_34 [13];
  
  DAT_004fed64 = 0xffffffff;
  puVar1 = &g_loaded_vehicle_runtime_table;
  for (iVar2 = 0x68fe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  puVar1 = &g_weapon_runtime_slot_table;
  for (iVar2 = 0x4e73; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  puVar1 = &DAT_005d88d8;
  for (iVar2 = 0x798; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  g_weapon_runtime_slot_count = 0;
  DAT_005d88d4 = 0;
  g_loaded_vehicle_runtime_count = 0;
  DAT_005da754 = 0;
  _DAT_005d88d0 = 0;
  g_player_weapon_hud_world_object = 0;
  DAT_005da798 = 0;
  DAT_005da79c = 0;
  g_player_weapon_hud_dirty = 0;
  g_player_weapon_hud_initialized = 0;
  muzzle_flash_effect_context_helper_0049f4f0();
  puVar1 = (undefined4 *)construct_bitmap_surface_context(aiStack_34,0,0,0,0);
  puVar3 = &g_player_weapon_hud_bitmap_surface;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_005da738 = &DAT_005367de;
  DAT_005da73c = &DAT_005367df;
  _DAT_005da740 = &DAT_005367e0;
  _DAT_005da744 = &DAT_005367e1;
  _DAT_005da748 = &DAT_005367e2;
  return;
}


