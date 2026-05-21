/*
 * Program: i76shell.dll
 * Function: classify_joystick_oem_name
 * Entry: 1001bee0
 * Signature: undefined __cdecl classify_joystick_oem_name(int param_1, int param_2)
 */


void __cdecl classify_joystick_oem_name(int param_1,int param_2)

{
  ushort uVar1;
  char *pcVar2;
  char *pcVar3;
  
  uVar1 = *(ushort *)(param_2 + 0x60);
  pcVar3 = (char *)(param_1 + 0xc);
  pcVar2 = strstr(pcVar3,s_Tracker_100493cc);
  if (pcVar2 != (char *)0x0) {
    *(undefined4 *)(param_1 + 0x4c) = s_tracker_100493d4._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_tracker_100493d4._4_4_;
    return;
  }
  pcVar2 = strstr(pcVar3,s_SideWinder_100493dc);
  if ((pcVar2 != (char *)0x0) ||
     (((((uVar1 & 1) != 0 && ((uVar1 & 2) != 0)) && ((uVar1 & 0x10) != 0)) &&
      (((uVar1 & 0x20) != 0 && (*(int *)(param_2 + 0x3c) == 8)))))) {
    *(undefined4 *)(param_1 + 0x4c) = s_sidewind_100493e8._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_sidewind_100493e8._4_4_;
    *(char *)(param_1 + 0x54) = s_sidewind_100493e8[8];
    return;
  }
  pcVar2 = strstr(pcVar3,s_Flightstick_Pro_100493f4);
  if ((pcVar2 != (char *)0x0) ||
     ((((uVar1 & 1) != 0 && ((uVar1 & 0x10) != 0)) &&
      (((uVar1 & 0x20) != 0 && (*(int *)(param_2 + 0x3c) == 4)))))) {
    *(undefined4 *)(param_1 + 0x4c) = s_fltstick_10049404._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_fltstick_10049404._4_4_;
    *(char *)(param_1 + 0x54) = s_fltstick_10049404[8];
    return;
  }
  pcVar3 = strstr(pcVar3,s_Thrustmaster_10049410);
  if ((pcVar3 == (char *)0x0) &&
     (((((uVar1 & 2) == 0 || ((uVar1 & 0x10) == 0)) || ((uVar1 & 0x20) == 0)) ||
      (*(int *)(param_2 + 0x3c) != 4)))) {
    *(undefined4 *)(param_1 + 0x4c) = s_joystick_10049428._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_joystick_10049428._4_4_;
    *(char *)(param_1 + 0x54) = s_joystick_10049428[8];
    return;
  }
  *(undefined4 *)(param_1 + 0x4c) = s_tmaster_10049420._0_4_;
  *(undefined4 *)(param_1 + 0x50) = s_tmaster_10049420._4_4_;
  return;
}


