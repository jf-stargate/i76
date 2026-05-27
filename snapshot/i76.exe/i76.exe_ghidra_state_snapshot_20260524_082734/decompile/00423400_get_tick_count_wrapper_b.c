/*
 * Program: i76.exe
 * Function: get_tick_count_wrapper_b
 * Entry: 00423400
 * Signature: undefined __stdcall get_tick_count_wrapper_b(void)
 */


/* i76 first-pass rename
   old_name: FUN_00423400
   suggested_name: get_tick_count_wrapper_b
   basis: Small GetTickCount timing wrapper. */

void get_tick_count_wrapper_b(void)

{
  DWORD DVar1;
  int iVar2;
  
  if ((DAT_00524570 != 0) && (DVar1 = GetTickCount(), DAT_00524578 < (int)DVar1)) {
    if (DAT_00524574 == 0) {
      DAT_00524578 = DVar1 + 60000;
    }
    else {
      DAT_00524578 = DVar1 + 5000;
    }
    iVar2 = query_mci_cd_audio_ready_state();
    if ((iVar2 == 1) || (iVar2 == 5)) {
      DAT_0052456c = 0;
      DAT_00524570 = 0;
    }
    else if ((((DAT_0052456c == 0) && (1 < (byte)DAT_00654b90)) &&
             (iVar2 = poll_mci_cd_audio_state_change(), iVar2 != 0)) && (DAT_004ed800 != -1)) {
      iVar2 = DAT_004ed800;
      if (DAT_00524574 == 0) {
        iVar2 = 2;
      }
      play_or_seek_cd_audio_track(iVar2);
      update_mci_cd_audio_status_state();
      return;
    }
  }
  return;
}


