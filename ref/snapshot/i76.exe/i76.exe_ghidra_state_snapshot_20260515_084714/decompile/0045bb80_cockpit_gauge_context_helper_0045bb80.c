/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_0045bb80
 * Entry: 0045bb80
 * Signature: undefined __cdecl cockpit_gauge_context_helper_0045bb80(int param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_0045bb80. Remove duplicated
   cockpit wording. */

void __cdecl cockpit_gauge_context_helper_0045bb80(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_0054a438 == 0) {
    piVar1 = (int *)get_active_player_or_camera_world_object_entry();
    if ((((piVar1 != (int *)0x0) &&
         (iVar3 = is_vehicle_or_actor_runtime_world_object(*piVar1), iVar3 != 0)) &&
        (uVar2 = get_primary_vehicle_weapon_target_object(*piVar1), uVar2 != 0)) &&
       (iVar3 = is_vehicle_or_actor_runtime_world_object(uVar2), iVar3 != 0)) {
      piVar1 = get_active_world_object_entry_object(uVar2);
      cockpit_gauge_context_helper_0045bc20(param_1,piVar1);
    }
  }
  else {
    multiplayer_network_scoreboard_table_helper_00451970();
    piVar1 = (int *)multiplayer_network_scoreboard_table_helper_004519b0();
    if (piVar1 != (int *)0x0) {
      do {
        uVar2 = vehicle_damage_component_runtime_context_helper_00466de0(*piVar1);
        if (uVar2 != 0) {
          cockpit_gauge_context_helper_0045bc20(param_1,piVar1);
        }
        piVar1 = (int *)multiplayer_network_scoreboard_table_helper_004519b0();
      } while (piVar1 != (int *)0x0);
      return;
    }
  }
  return;
}


