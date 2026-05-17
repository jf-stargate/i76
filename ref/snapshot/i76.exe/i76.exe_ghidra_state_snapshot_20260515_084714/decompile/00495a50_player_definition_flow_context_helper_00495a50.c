/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495a50
 * Entry: 00495a50
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495a50(undefined4 param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495a50. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495a50(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (param_2 == 4) {
    iVar1 = is_damage_side_effects_suppressed();
    if (iVar1 != 0) {
      piVar2 = (int *)get_active_player_or_camera_world_object_entry();
      if (piVar2 != (int *)0x0) {
        iVar1 = *(int *)(*piVar2 + 0x70);
        if ((*(uint *)(iVar1 + 0x454) & 0x4020) == 0) {
          *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x100000;
          DAT_005367f9 = 1;
        }
        else {
          iVar3 = multiplayer_respawn_state_context_helper_00451570(1);
          if ((iVar3 == 0) && ((*(uint *)(iVar1 + 0x454) & 0x8000) != 0)) {
            *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x100000;
            load_selected_loading_screen_bitmap((undefined *)0x0);
            return 0;
          }
        }
      }
      load_selected_loading_screen_bitmap((undefined *)0x0);
      return 0;
    }
    set_game_flow_state(7);
    if (DAT_00654b18 != (code *)0x0) {
      (*DAT_00654b18)();
    }
  }
  return 0;
}


