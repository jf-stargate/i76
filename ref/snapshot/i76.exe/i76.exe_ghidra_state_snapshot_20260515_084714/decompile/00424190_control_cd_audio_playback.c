/*
 * Program: i76.exe
 * Function: control_cd_audio_playback
 * Entry: 00424190
 * Signature: undefined __cdecl control_cd_audio_playback(int param_1)
 */


/* WARNING (jumptable): Removing unreachable block (ram,0x00424303) */
/* i76 first-pass rename
   old_name: FUN_00424190
   suggested_name: control_cd_audio_playback
   basis: MCI CD-audio command path using mciSendCommandA; manages playback state. */

void __cdecl control_cd_audio_playback(int param_1)

{
  MCIERROR MVar1;
  undefined4 uVar2;
  DWORD_PTR dwParam1;
  int iVar3;
  int iVar4;
  undefined1 local_10 [4];
  uint local_c;
  int local_8;
  
  iVar3 = param_1;
  if (DAT_00524674 == 0) {
    return;
  }
  iVar4 = param_1 + 1;
  if (param_1 < 1) {
    iVar4 = 1;
  }
  local_8 = 4;
  MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
  if (MVar1 == 0) {
    switch(local_c) {
    case 0x20d:
      uVar2 = 2;
      break;
    case 0x20e:
      uVar2 = 3;
      break;
    default:
      goto switchD_004243ec_caseD_20f;
    case 0x211:
      uVar2 = 4;
      break;
    case 0x212:
      uVar2 = 1;
    }
  }
  else {
    if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)&param_1);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
    }
switchD_004243ec_caseD_20f:
    uVar2 = 5;
  }
  switch(uVar2) {
  default:
    return;
  case 2:
    if (0x32 < iVar3) {
      iVar3 = 0x32;
    }
    dwParam1 = 4;
    local_c = *(uint *)(&DAT_00524590 + (iVar3 - DAT_00524588) * 4);
    if (*(int *)(&DAT_00524590 + (iVar4 - DAT_00524588) * 4) != 0) {
      dwParam1 = 0xc;
      local_8 = *(int *)(&DAT_00524590 + (iVar4 - DAT_00524588) * 4);
    }
    mciSendCommandA(DAT_004ed890,0x806,dwParam1,(DWORD_PTR)local_10);
    return;
  case 3:
    break;
  case 4:
    mciSendCommandA(DAT_004ed890,0x855,0,(DWORD_PTR)&param_1);
    return;
  }
  if (DAT_00524674 == 0) goto switchD_00424320_caseD_4;
  local_8 = 4;
  MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
  if (MVar1 == 0) {
    switch(local_c) {
    case 0x20d:
      uVar2 = 2;
      break;
    case 0x20e:
      uVar2 = 3;
      break;
    default:
      goto switchD_004242ee_caseD_20f;
    case 0x211:
      uVar2 = 4;
      break;
    case 0x212:
      uVar2 = 1;
    }
  }
  else {
    if (DAT_00524674 != 0) {
      mciSendCommandA(DAT_004ed890,0x804,0,(DWORD_PTR)&param_1);
      DAT_004ed890 = 0xffffffff;
      DAT_00524674 = 0;
    }
switchD_004242ee_caseD_20f:
    uVar2 = 5;
  }
  switch(uVar2) {
  case 1:
  case 2:
    DAT_0052466c = 0;
    DAT_00524660 = 0;
    DAT_00524664 = 0;
    DAT_00524668 = 0;
    break;
  case 3:
    if (DAT_00524674 != 0) {
      local_8 = 2;
      MVar1 = mciSendCommandA(DAT_004ed890,0x814,0x100,(DWORD_PTR)local_10);
      if (MVar1 == 0) {
        DAT_00524664 = local_c >> 8 & 0xff;
        DAT_00524660 = local_c & 0xff;
        DAT_00524668 = local_c >> 0x10 & 0xff;
        DAT_0052466c = local_c >> 0x18;
      }
    }
  }
switchD_00424320_caseD_4:
  mciSendCommandA(DAT_004ed890,0x809,0,(DWORD_PTR)&param_1);
  return;
}


