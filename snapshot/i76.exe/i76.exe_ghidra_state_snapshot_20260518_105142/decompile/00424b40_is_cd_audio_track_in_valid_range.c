/*
 * Program: i76.exe
 * Function: is_cd_audio_track_in_valid_range
 * Entry: 00424b40
 * Signature: undefined4 __cdecl is_cd_audio_track_in_valid_range(int param_1)
 */


/* cgpt rename v3: Checks whether a CD-audio track number lies inside the current valid min/max
   range. */

undefined4 __cdecl is_cd_audio_track_in_valid_range(int param_1)

{
  if ((DAT_00524588 <= param_1) && (param_1 <= DAT_0052458c)) {
    return 1;
  }
  return 0;
}


