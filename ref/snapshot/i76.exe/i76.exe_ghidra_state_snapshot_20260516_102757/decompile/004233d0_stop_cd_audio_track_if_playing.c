/*
 * Program: i76.exe
 * Function: stop_cd_audio_track_if_playing
 * Entry: 004233d0
 * Signature: undefined __stdcall stop_cd_audio_track_if_playing(void)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium-high] ShellMain callback slot +0x54.
   Stops active CD-audio playback when present. */

void stop_cd_audio_track_if_playing(void)

{
  if ((DAT_00524570 != 0) && (DAT_004ed800 != -1)) {
    wait_for_mci_cd_audio_playing_state();
    DAT_00524570 = 0;
    DAT_0052456c = 0;
  }
  return;
}


