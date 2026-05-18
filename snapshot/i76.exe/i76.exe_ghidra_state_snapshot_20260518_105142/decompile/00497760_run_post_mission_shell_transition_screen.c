/*
 * Program: i76.exe
 * Function: run_post_mission_shell_transition_screen
 * Entry: 00497760
 * Signature: undefined4 __stdcall run_post_mission_shell_transition_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM] Called after runtime for state
   0/0xb before returning to shell or changing flow state.
   old_name: FUN_00497760 */

undefined4 run_post_mission_shell_transition_screen(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_005a60b8 == 0) {
    DAT_005a60b8 = 1;
    show_in_game_pause_menu();
  }
  if (((DAT_00504c10 == 0) && (((byte)DAT_00654b98 & 2) == 0)) && (DAT_005dd2f4 == 0)) {
    DAT_004fd360 = &DAT_004fd0b0;
    _DAT_004fd364 = 6;
  }
  else {
    DAT_004fd360 = &DAT_004fd218;
    _DAT_004fd364 = 5;
  }
  _DAT_004fcec0 = &DAT_004fd348;
  iVar1 = get_game_flow_state();
  if (iVar1 == 0xb) {
    set_game_flow_state(0);
    uVar2 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                          s_Congratulations__You_won__Not_to_004fd920);
    *(undefined4 *)(DAT_004fd360 + 4) = uVar2;
    uVar2 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                          s_Turn_off_Cheater_Options_004fd904);
    *(undefined4 *)(DAT_004fd360 + 0x40) = uVar2;
    *(undefined4 *)(DAT_004fd360 + 0x3c) = 0x200;
    *(undefined1 **)(DAT_004fd360 + 0x44) = &LAB_004976a0;
    _DAT_004fd368 = 1;
  }
  else {
    iVar1 = mission_objective_notepad_context_helper_0045eb40();
    *(int *)(DAT_004fd360 + 4) = iVar1;
    *(undefined4 *)(DAT_004fd360 + 0x40) = 0;
    *(undefined4 *)(DAT_004fd360 + 0x3c) = 0;
    *(undefined4 *)(DAT_004fd360 + 0x44) = 0;
    _DAT_004fd368 = 2;
  }
  iVar1 = initialize_mission_loading_screen(&DAT_004fd348,&LAB_004978b0);
  if (iVar1 != 0) {
    update_audio_object_lists_and_release_finished();
    mission_flow_map_context_helper_0049cdd0(0x10);
    return 1;
  }
  return 0;
}


