/*
 * Program: i76.exe
 * Function: poll_mci_cd_audio_state_change
 * Entry: 00424550
 * Signature: undefined4 __stdcall poll_mci_cd_audio_state_change(void)
 */


/* cgpt whole-binary semantic rename v1: detects MCI state change and retries start */

undefined4 poll_mci_cd_audio_state_change(void)

{
  MCIERROR MVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_00524674 == 0) {
    return 0;
  }
  iVar3 = 4;
  local_8 = 4;
  MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
  if (MVar1 == 0) {
    switch(local_c) {
    case 0x20d:
      iVar3 = 2;
      break;
    case 0x20e:
      iVar3 = 3;
      break;
    default:
      goto switchD_00424634_caseD_20f;
    case 0x211:
      break;
    case 0x212:
      iVar3 = 1;
    }
  }
  else {
    if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
    }
switchD_00424634_caseD_20f:
    iVar3 = 5;
  }
  if (iVar3 == DAT_00524670) {
    return 0;
  }
  if (((iVar3 != 1) && (iVar3 == 2)) && (DAT_00524670 == 1)) {
    iVar4 = 0;
    do {
      iVar2 = set_mci_cd_audio_time_format(&DAT_00524588);
      if (iVar2 == 0) break;
      _putch(7);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 3);
    if (iVar4 == 3) {
      return 0;
    }
  }
  DAT_00524670 = iVar3;
  return 1;
}


