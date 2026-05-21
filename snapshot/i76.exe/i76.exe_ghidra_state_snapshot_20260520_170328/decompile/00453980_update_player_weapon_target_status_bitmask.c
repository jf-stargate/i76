/*
 * Program: i76.exe
 * Function: update_player_weapon_target_status_bitmask
 * Entry: 00453980
 * Signature: undefined __stdcall update_player_weapon_target_status_bitmask(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium_high] Updates global weapon/target
   status bitmask and small HUD status fields from active player weapon mounts and current target
   objects. */

void update_player_weapon_target_status_bitmask(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  
  piVar1 = (int *)get_active_player_or_camera_world_object_entry();
  iVar5 = 0;
  _g_player_secondary_target_status_a = 0;
  _g_player_secondary_target_status_b = 0;
  g_player_primary_target_status = 0;
  if (piVar1 != (int *)0x0) {
    uVar2 = get_primary_vehicle_weapon_target_object(*piVar1);
    if (uVar2 != 0) {
      iVar3 = is_vehicle_or_actor_runtime_world_object(uVar2);
      if (iVar3 == 0) {
        g_player_primary_target_status = *(short *)(*(int *)(uVar2 + 0x70) + 8) + 1;
        g_player_weapon_status_bitmask = g_player_weapon_status_bitmask | 0x40000000;
      }
      else {
        g_player_primary_target_status = *(short *)(*(int *)(uVar2 + 0x70) + 0x480);
      }
    }
    psVar6 = &g_player_secondary_target_status_a;
    do {
      iVar3 = get_vehicle_weapon_target_object_by_slot(*piVar1,*(int *)((int)&DAT_004f5c38 + iVar5))
      ;
      if (iVar3 != 0) {
        iVar4 = is_vehicle_or_actor_runtime_world_object(iVar3);
        if (iVar4 == 0) {
          *psVar6 = *(short *)(*(int *)(iVar3 + 0x70) + 8) + 1;
          g_player_weapon_status_bitmask =
               g_player_weapon_status_bitmask | *(uint *)((int)&DAT_004f5c48 + iVar5);
        }
        else {
          *psVar6 = *(short *)(*(int *)(iVar3 + 0x70) + 0x480);
        }
      }
      psVar6 = psVar6 + 1;
      iVar5 = iVar5 + 4;
    } while ((int)psVar6 < 0x54100e);
  }
  return;
}


