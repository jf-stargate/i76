/*
 * Program: i76shell.dll
 * Function: directplay_session_enum_callback
 * Entry: 1002d260
 * Signature: undefined __cdecl directplay_session_enum_callback(char * param_1)
 */


void __cdecl directplay_session_enum_callback(char *param_1)

{
  strncpy((char *)&DAT_100d4050,param_1,0x20);
  DAT_100d406f = 0;
  return;
}


