/*
 * Program: i76.exe
 * Function: initialize_cd_audio_playback_state
 * Entry: 00423d50
 * Signature: undefined4 __stdcall initialize_cd_audio_playback_state(void)
 */


/* WARNING: Switch with 1 destination removed at 0x00423f12 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: calls open_mci_cd_audio_device and initializes media
   status/volume */

undefined4 initialize_cd_audio_playback_state(void)

{
  int iVar1;
  MCIERROR MVar2;
  uint uVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  uint local_c;
  undefined4 local_8;
  
  _DAT_00524658 = 0;
  _DAT_0052465c = 0;
  iVar1 = open_mci_cd_audio_device();
  if (iVar1 == 0) {
    DAT_00524674 = 1;
    local_8 = 4;
    MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
    if (MVar2 == 0) {
      DAT_00524670 = 2;
    }
    else {
      if (DAT_00524674 != 0) {
        mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
        DAT_004ed890 = 0xffffffff;
        DAT_00524674 = 0;
      }
      DAT_00524670 = 5;
    }
    switch(DAT_00524670) {
    case 1:
      if (DAT_00524674 != 0) {
        mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_14);
        DAT_004ed890 = 0xffffffff;
      }
      DAT_00524674 = 0;
      return 0;
    case 2:
    case 3:
      set_mci_cd_audio_time_format(&DAT_00524588);
      break;
    case 4:
      set_mci_cd_audio_time_format(&DAT_00524588);
      if (DAT_00524674 != 0) {
        local_8 = 2;
        MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
        if (MVar2 == 0) {
          DAT_00524664 = local_c >> 8 & 0xff;
          DAT_00524660 = local_c & 0xff;
          DAT_00524668 = local_c >> 0x10 & 0xff;
          DAT_0052466c = local_c >> 0x18;
        }
      }
    }
    uVar3 = DAT_00654b90 & 0xff;
    if (uVar3 == 1) {
      uVar3 = 0;
    }
    uVar3 = uVar3 * 0xccc;
    if (0xfffe < uVar3) {
      uVar3 = 0xffff;
    }
    if (DAT_004ed894 != 0xffffffff) {
      auxSetVolume(DAT_004ed894,uVar3 & 0xffff | (uVar3 & 0xffff) << 0x10);
    }
    return 1;
  }
  return 0;
}


