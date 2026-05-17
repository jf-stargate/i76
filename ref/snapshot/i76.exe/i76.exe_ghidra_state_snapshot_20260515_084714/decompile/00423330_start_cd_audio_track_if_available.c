/*
 * Program: i76.exe
 * Function: start_cd_audio_track_if_available
 * Entry: 00423330
 * Signature: undefined __cdecl start_cd_audio_track_if_available(int param_1, int param_2)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium-high] ShellMain callback slot +0x50.
   Starts/plays a CD-audio track if the subsystem/media state allows it. */

void __cdecl start_cd_audio_track_if_available(int param_1,int param_2)

{
  int iVar1;
  
  if (DAT_00524570 == 0) {
    close_mci_cd_audio_device();
    initialize_cd_audio_playback_state();
    if (param_1 != -1) {
      DAT_004ed800 = param_1;
    }
    iVar1 = get_current_cd_audio_track_index();
    if (((iVar1 != 0) && (iVar1 = query_mci_cd_audio_ready_state(), iVar1 != 1)) &&
       (iVar1 = is_cd_audio_track_in_valid_range(DAT_004ed800), iVar1 != 0)) {
      if (((byte)DAT_00654b90 < 2) && (param_2 == 0)) {
        return;
      }
      play_or_seek_cd_audio_track(DAT_004ed800);
      iVar1 = update_mci_cd_audio_status_state();
      if (iVar1 == 3) {
        DAT_00524570 = 1;
        iVar1 = get_game_flow_state();
        DAT_00524574 = (uint)(iVar1 == 6);
        return;
      }
    }
    DAT_004ed800 = -1;
  }
  return;
}


