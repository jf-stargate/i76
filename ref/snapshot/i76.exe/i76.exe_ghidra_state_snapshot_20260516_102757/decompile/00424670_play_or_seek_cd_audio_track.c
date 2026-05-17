/*
 * Program: i76.exe
 * Function: play_or_seek_cd_audio_track
 * Entry: 00424670
 * Signature: MCIERROR __cdecl play_or_seek_cd_audio_track(int param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00424670
   suggested_name: play_or_seek_cd_audio_track
   basis: MCI CD-audio play/seek-style command path; uses track/index globals. */

MCIERROR __cdecl play_or_seek_cd_audio_track(int param_1)

{
  int iVar1;
  MCIERROR MVar2;
  DWORD_PTR DVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_20 [4];
  undefined4 local_1c;
  int local_18;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = param_1;
  MVar2 = 0;
  if (DAT_00524674 != 0) {
    iVar5 = param_1 + 1;
    if (param_1 < 1) {
      iVar5 = 1;
    }
    local_18 = 4;
    MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_20);
    if (MVar2 == 0) {
      MVar2 = 0;
      uVar4 = 2;
    }
    else {
      MVar2 = 0;
      if (DAT_00524674 != 0) {
        MVar2 = mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)&param_1);
        DAT_004ed890 = 0xffffffff;
        DAT_00524674 = 0;
      }
      uVar4 = 5;
    }
    if ((1 < uVar4) && (uVar4 < 5)) {
      if (DAT_00524674 != 0) {
        local_18 = 4;
        MVar2 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_20);
        if ((MVar2 != 0) && (DAT_00524674 != 0)) {
          mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)&param_1);
          DAT_004ed890 = 0xffffffff;
          DAT_00524674 = 0;
        }
        local_10 = 0;
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
      }
      MVar2 = DAT_00524588;
      if (((int)DAT_00524588 <= iVar1) && (iVar1 <= DAT_0052458c)) {
        if (uVar4 != 3) {
          if (uVar4 == 4) {
            DVar3 = 4;
            local_1c = *(undefined4 *)(&DAT_00524590 + (iVar1 - DAT_00524588) * 4);
            if (*(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4) != 0) {
              DVar3 = 0xc;
              local_18 = *(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4);
            }
            mciSendCommandA(DAT_004ed890,0x806,DVar3,(DWORD_PTR)local_20);
            DAT_00524660 = iVar1;
            DAT_00524664 = 0;
            DAT_00524668 = 0;
            return 0;
          }
          DVar3 = 4;
          local_1c = *(undefined4 *)(&DAT_00524590 + (iVar1 - DAT_00524588) * 4);
          if (*(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4) != 0) {
            DVar3 = 0xc;
            local_18 = *(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4);
          }
          MVar2 = mciSendCommandA(DAT_004ed890,0x806,DVar3,(DWORD_PTR)local_20);
          return MVar2;
        }
        mciSendCommandA(DAT_004ed890,0x808,0,(DWORD_PTR)&param_1);
        DVar3 = 4;
        local_1c = *(undefined4 *)(&DAT_00524590 + (iVar1 - DAT_00524588) * 4);
        if (*(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4) != 0) {
          DVar3 = 0xc;
          local_18 = *(int *)(&DAT_00524590 + (iVar5 - DAT_00524588) * 4);
        }
        MVar2 = mciSendCommandA(DAT_004ed890,0x806,DVar3,(DWORD_PTR)local_20);
      }
    }
  }
  return MVar2;
}


