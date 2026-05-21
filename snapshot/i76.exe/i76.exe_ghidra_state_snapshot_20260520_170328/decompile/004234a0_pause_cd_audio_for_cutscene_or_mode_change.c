/*
 * Program: i76.exe
 * Function: pause_cd_audio_for_cutscene_or_mode_change
 * Entry: 004234a0
 * Signature: undefined __stdcall pause_cd_audio_for_cutscene_or_mode_change(void)
 */


/* cgpt rename v3: Stops/pauses CD audio when entering a cutscene/display mode transition and
   records the paused state. */

void pause_cd_audio_for_cutscene_or_mode_change(void)

{
  update_audio_object_lists_and_release_finished();
  if ((DAT_00524570 != 0) && (DAT_0052456c == 0)) {
    if ((DAT_004ed800 != -1) && (1 < (byte)DAT_00654b90)) {
      control_cd_audio_playback(0);
    }
    DAT_0052456c = 1;
  }
  return;
}


