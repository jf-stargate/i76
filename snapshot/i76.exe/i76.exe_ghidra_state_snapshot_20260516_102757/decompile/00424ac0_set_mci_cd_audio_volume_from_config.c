/*
 * Program: i76.exe
 * Function: set_mci_cd_audio_volume_from_config
 * Entry: 00424ac0
 * Signature: undefined __cdecl set_mci_cd_audio_volume_from_config(uint * param_1)
 */


/* cgpt whole-binary semantic rename v1: MCI/aux volume helper */

void __cdecl set_mci_cd_audio_volume_from_config(uint *param_1)

{
  MCIERROR MVar1;
  undefined1 local_10 [4];
  uint local_c;
  undefined4 local_8;
  
  if (DAT_00524674 != 0) {
    local_8 = 2;
    MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
    if (MVar1 == 0) {
      *param_1 = local_c & 0xff;
      param_1[1] = local_c >> 8 & 0xff;
      param_1[2] = local_c >> 0x10 & 0xff;
      param_1[3] = local_c >> 0x18;
    }
  }
  return;
}


