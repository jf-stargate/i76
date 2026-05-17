/*
 * Program: i76.exe
 * Function: shutdown_audio_runtime_directsound_cd
 * Entry: 004216e0
 * Signature: undefined4 __stdcall shutdown_audio_runtime_directsound_cd(void)
 */


/* cgpt rename v3: Stops CD audio, closes MCI CD device, shuts down DirectSound, destroys the audio
   heap, and clears audio runtime state. */

undefined4 shutdown_audio_runtime_directsound_cd(void)

{
  stop_cd_audio_track_if_playing();
  close_mci_cd_audio_device();
  if (DAT_00524564 == (int *)0x0) {
    return 0;
  }
  shutdown_directsound(DAT_00524564);
  HeapDestroy(DAT_005fcc00);
  DAT_005fcbf4 = 0;
  return 1;
}


