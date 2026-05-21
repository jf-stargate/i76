/*
 * Program: i76shell.dll
 * Function: poll_directplay_session_enumeration
 * Entry: 1002e3d0
 * Signature: undefined4 __stdcall poll_directplay_session_enumeration(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 poll_directplay_session_enumeration(void)

{
  undefined4 uVar1;
  DWORD DVar2;
  
  validate_joined_multiplayer_session_and_fill_launch_config();
  if (DAT_100f21cc == 3) {
    uVar1 = 1;
  }
  else {
    DVar2 = GetTickCount();
    if (((DAT_100f21cc != 2) && (1000 < DVar2 - _DAT_100f21dc)) && (DAT_100f355c == 0)) {
      _DAT_100f4ed8 = DAT_100f4ee8;
      _DAT_100f4edc = &DAT_100f4770;
      _DAT_100f4ee0 = &DAT_100f3570;
      if (DAT_100f4ee8 != 0) {
        DAT_100f355c = 1;
        create_or_open_directplay_interface((undefined4 *)&DAT_100f4ed8);
      }
      _DAT_100f21dc = GetTickCount();
    }
    if (DAT_100f355c == 2) {
      DAT_100f355c = 0;
      FUN_1002ce70();
      compact_or_update_directplay_player_records();
    }
    FUN_1002cec0();
    uVar1 = 0;
  }
  return uVar1;
}


