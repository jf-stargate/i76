/*
 * Program: i76.exe
 * Function: release_audio_object_if_present
 * Entry: 00421e70
 * Signature: undefined __cdecl release_audio_object_if_present(undefined4 * param_1)
 */


/* cgpt rename v2: Null-safe wrapper that releases an audio object through the audio-object release
   path. */

void __cdecl release_audio_object_if_present(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    release_audio_object_resource_and_buffers(param_1);
  }
  return;
}


