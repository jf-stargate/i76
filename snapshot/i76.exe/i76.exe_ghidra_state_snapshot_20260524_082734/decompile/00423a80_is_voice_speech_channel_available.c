/*
 * Program: i76.exe
 * Function: is_voice_speech_channel_available
 * Entry: 00423a80
 * Signature: bool __stdcall is_voice_speech_channel_available(void)
 */


/* cgpt readability rename v13 set A: Returns true when the voice/speech channel busy flag
   DAT_0052457c is clear. */

bool is_voice_speech_channel_available(void)

{
  return DAT_0052457c == 0;
}


