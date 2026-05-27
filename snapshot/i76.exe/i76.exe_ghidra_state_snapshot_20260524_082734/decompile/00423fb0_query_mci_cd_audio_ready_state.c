/*
 * Program: i76.exe
 * Function: query_mci_cd_audio_ready_state
 * Entry: 00423fb0
 * Signature: undefined4 __stdcall query_mci_cd_audio_ready_state(void)
 */


/* cgpt whole-binary semantic rename v1: queries MCI status and closes on error */

undefined4 query_mci_cd_audio_ready_state(void)

{
  MCIERROR MVar1;
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  undefined4 local_8;
  
  if (DAT_00524674 != 0) {
    local_8 = 4;
    MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
    if (MVar1 == 0) {
      return 2;
    }
    if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
      return 5;
    }
  }
  return 5;
}


