/*
 * Program: i76.exe
 * Function: wait_for_mci_cd_audio_playing_state
 * Entry: 00424470
 * Signature: undefined __stdcall wait_for_mci_cd_audio_playing_state(void)
 */


/* cgpt whole-binary semantic rename v1: polls MCI until playing state */

void wait_for_mci_cd_audio_playing_state(void)

{
  MCIERROR MVar1;
  int iVar2;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_00524674 != 0) {
    do {
      mciSendCommandA(DAT_004ed890,0x808,0,(DWORD_PTR)local_18);
      if (DAT_00524674 == 0) {
switchD_00424516_caseD_20f:
        iVar2 = 5;
      }
      else {
        local_8 = 4;
        MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
        if (MVar1 != 0) {
          if (DAT_00524674 != 0) {
            mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
            DAT_004ed890 = 0xffffffff;
            DAT_00524674 = 0;
          }
          goto switchD_00424516_caseD_20f;
        }
        switch(local_c) {
        case 0x20d:
          iVar2 = 2;
          break;
        case 0x20e:
          iVar2 = 3;
          break;
        default:
          goto switchD_00424516_caseD_20f;
        case 0x211:
          iVar2 = 4;
          break;
        case 0x212:
          iVar2 = 1;
        }
      }
    } while (iVar2 != 2);
  }
  return;
}


