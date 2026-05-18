/*
 * Program: i76.exe
 * Function: set_mci_cd_audio_time_format
 * Entry: 004249a0
 * Signature: undefined4 __cdecl set_mci_cd_audio_time_format(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: MCI helper called during CD audio init/playback */

undefined4 __cdecl set_mci_cd_audio_time_format(int *param_1)

{
  int *piVar1;
  MCIERROR MVar2;
  int iVar3;
  int iVar4;
  undefined1 local_10 [4];
  int local_c;
  undefined4 local_8;
  int local_4;
  
  if (DAT_00524674 == 0) {
    return 1;
  }
  local_8 = 3;
  MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
  piVar1 = param_1;
  if (MVar2 == 0) {
    if (0x32 < local_c) {
      local_c = 0x11;
    }
    iVar4 = 1;
    *param_1 = 1;
    param_1[1] = local_c;
    if (0 < local_c) {
      do {
        local_8 = 2;
        local_4 = iVar4;
        MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x110,(DWORD_PTR)local_10);
        if (MVar2 != 0) goto joined_r0x00424a80;
        iVar3 = iVar4 - *piVar1;
        iVar4 = iVar4 + 1;
        piVar1[iVar3 + 2] = local_4;
      } while (iVar4 <= piVar1[1]);
    }
    piVar1[(iVar4 - *piVar1) + 2] = (uint)(byte)((char)piVar1[1] + 1);
  }
  else {
joined_r0x00424a80:
    if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)&param_1);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
      return 0;
    }
  }
  return 0;
}


