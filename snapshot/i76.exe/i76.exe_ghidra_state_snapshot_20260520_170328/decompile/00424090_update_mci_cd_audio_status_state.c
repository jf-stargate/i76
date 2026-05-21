/*
 * Program: i76.exe
 * Function: update_mci_cd_audio_status_state
 * Entry: 00424090
 * Signature: undefined __stdcall update_mci_cd_audio_status_state(void)
 */


/* cgpt whole-binary semantic rename v1: maps MCI mode/status to internal state */

void update_mci_cd_audio_status_state(void)

{
  MCIERROR MVar1;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_00524674 != 0) {
    local_8 = 4;
    MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
    if (MVar1 == 0) {
      switch(local_c) {
      case 0x20d:
        DAT_00524670 = 2;
        return;
      case 0x20e:
        DAT_00524670 = 3;
        return;
      case 0x211:
        DAT_00524670 = 4;
        return;
      case 0x212:
        DAT_00524670 = 1;
        return;
      }
    }
    else if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
      DAT_00524670 = 5;
      return;
    }
  }
  DAT_00524670 = 5;
  return;
}


