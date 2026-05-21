/*
 * Program: i76shell.dll
 * Function: initialize_directplay_connection_for_mode
 * Entry: 1002e2f0
 * Signature: undefined4 __stdcall initialize_directplay_connection_for_mode(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 initialize_directplay_connection_for_mode(void)

{
  undefined4 local_80 [32];
  
  DAT_100f21cc = 0;
  _DAT_100f21dc = 0;
  DAT_100f355c = 0;
  DAT_100f2320 = 0;
  DAT_100f3548 = 0;
  _DAT_100f356c = 0;
  DAT_100f4ee4 = 0;
  DAT_100f224c = 0;
  if (DAT_100f4ee8 == 0) {
    switch(DAT_100d217c) {
    case 2:
    case 6:
      destroy_multiplayer_connection_state(local_80);
      break;
    case 3:
    case 7:
      construct_multiplayer_connection_state(local_80);
      break;
    case 4:
    case 8:
      initialize_multiplayer_connection_callbacks(local_80);
      break;
    case 5:
    case 9:
      reset_multiplayer_connection_session_state(local_80);
    }
    DAT_100f4ee8 = create_multiplayer_connection(local_80);
    if (DAT_100f4ee8 == 0) {
      return 0;
    }
  }
  return 1;
}


