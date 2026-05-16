/*
 * Program: i76.exe
 * Function: resume_cd_audio_after_cutscene_or_mode_change
 * Entry: 004234e0
 * Signature: undefined __stdcall resume_cd_audio_after_cutscene_or_mode_change(void)
 */


/* cgpt rename v3: Restores CD audio playback after a cutscene/display mode transition when playback
   was previously paused. */

void resume_cd_audio_after_cutscene_or_mode_change(void)

{
  start_pending_audio_objects();
  if ((DAT_00524570 != 0) && (DAT_0052456c != 0)) {
    if ((DAT_004ed800 != -1) && (1 < (byte)DAT_00654b90)) {
      control_cd_audio_playback(DAT_004ed800);
    }
    DAT_0052456c = 0;
  }
  return;
}


