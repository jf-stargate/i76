/*
 * Program: i76.exe
 * Function: weapon_hud_context_helper_004625c0
 * Entry: 004625c0
 * Signature: undefined __cdecl weapon_hud_context_helper_004625c0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: weapon hud context helper based on
   prior focused closure context. */

void __cdecl weapon_hud_context_helper_004625c0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = get_active_world_object_entry_object(param_1);
  puVar2 = (undefined4 *)get_active_player_or_camera_world_object_entry();
  if (puVar2 != (undefined4 *)0x0) {
    DAT_00609380 = *puVar2;
    _DAT_00609340 = 0;
  }
  puVar2 = (undefined4 *)get_vehicle_runtime_context(param_1);
  *puVar2 = puVar1;
  return;
}


