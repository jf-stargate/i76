/*
 * Program: i76.exe
 * Function: close_mci_cd_audio_device
 * Entry: 00423f70
 * Signature: undefined __stdcall close_mci_cd_audio_device(void)
 */


/* cgpt whole-binary semantic rename v1: sends MCI close and clears device id */

void close_mci_cd_audio_device(void)

{
  undefined1 local_4 [4];
  
  if (DAT_00524674 != 0) {
    mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_4);
    DAT_004ed890 = 0xffffffff;
    DAT_00524674 = 0;
  }
  return;
}


