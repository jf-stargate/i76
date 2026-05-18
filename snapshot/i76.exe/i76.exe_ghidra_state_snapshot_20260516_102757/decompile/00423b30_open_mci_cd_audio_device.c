/*
 * Program: i76.exe
 * Function: open_mci_cd_audio_device
 * Entry: 00423b30
 * Signature: undefined4 __stdcall open_mci_cd_audio_device(void)
 */


/* WARNING: Removing unreachable block (ram,0x00423ba0) */
/* cgpt whole-binary semantic rename v1: opens MCI CDAudio device and probes aux volume */

undefined4 open_mci_cd_audio_device(void)

{
  bool bVar1;
  MCIERROR MVar2;
  UINT UVar3;
  MMRESULT MVar4;
  UINT_PTR UVar5;
  UINT_PTR UVar6;
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  CHAR *local_84;
  undefined4 local_80;
  int local_7c;
  undefined4 local_78;
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined4 local_6c;
  undefined1 local_64 [4];
  MCIDEVICEID local_60;
  CHAR *local_5c;
  CHAR local_50 [32];
  tagAUXCAPSA local_30;
  
  local_7c = check_i76_cd2_volume_available();
  if (local_7c == 0) {
    return 1;
  }
  local_84 = local_8c;
  local_78 = 0x204;
  local_80 = 4;
  MVar2 = mciSendCommandA(0,0x810,0x100,(DWORD_PTR)local_88);
  if (MVar2 != 0) {
    return 1;
  }
  local_84 = local_50;
  local_80 = 0x20;
  MVar2 = mciSendCommandA(0,0x810,0x400,(DWORD_PTR)local_88);
  if (MVar2 != 0) {
    mciGetErrorStringA(MVar2,local_50,0x20);
    return 1;
  }
  local_5c = local_50;
  MVar2 = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)local_64);
  if (MVar2 == 0) {
    DAT_004ed890 = local_60;
    local_6c = 10;
    MVar2 = mciSendCommandA(local_60,0x80d,0x400,(DWORD_PTR)local_70);
    if (MVar2 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)local_74);
      DAT_004ed890 = 0xffffffff;
      return 1;
    }
    bVar1 = false;
    UVar5 = 0xffffffff;
    UVar3 = auxGetNumDevs();
    if (0 < (int)UVar3) {
      UVar6 = 0;
      if (0 < (int)UVar3) {
        do {
          if (bVar1) {
            DAT_004ed894 = UVar5;
            return 0;
          }
          MVar4 = auxGetDevCapsA(UVar6,&local_30,0x30);
          if (MVar4 != 0) {
            DAT_004ed894 = 0xffffffff;
            return 0;
          }
          if (local_30.wTechnology == 1) {
            bVar1 = true;
            UVar5 = UVar6;
          }
          UVar6 = UVar6 + 1;
        } while ((int)UVar6 < (int)UVar3);
      }
      if ((!bVar1) && (UVar6 = 0, 0 < (int)UVar3)) {
        while (!bVar1) {
          MVar4 = auxGetDevCapsA(UVar6,&local_30,0x30);
          if (MVar4 != 0) {
            DAT_004ed894 = 0xffffffff;
            return 0;
          }
          if (local_30.wTechnology == 2) {
            bVar1 = true;
            UVar5 = UVar6;
          }
          UVar6 = UVar6 + 1;
          if ((int)UVar3 <= (int)UVar6) {
            DAT_004ed894 = UVar5;
            return 0;
          }
        }
      }
    }
    DAT_004ed894 = UVar5;
    return 0;
  }
  DAT_00524678 = MVar2;
  return 1;
}


