/*
 * Program: i76.exe
 * Function: enumerate_joystick_input_devices
 * Entry: 00450de0
 * Signature: undefined __cdecl enumerate_joystick_input_devices(int param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence:
   Tracker/SideWinder/Flightstick/Thrustmaster */

void __cdecl enumerate_joystick_input_devices(int param_1,int param_2)

{
  ushort uVar1;
  char *pcVar2;
  char *pcVar3;
  
  uVar1 = *(ushort *)(param_2 + 0x60);
  pcVar3 = (char *)(param_1 + 0xc);
  pcVar2 = strstr(pcVar3,s_Tracker_004f56e4);
  if (pcVar2 != (char *)0x0) {
    *(undefined4 *)(param_1 + 0x4c) = s_tracker_004f54e8._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_tracker_004f54e8._4_4_;
    return;
  }
  pcVar2 = strstr(pcVar3,s_SideWinder_004f56d8);
  if ((pcVar2 != (char *)0x0) ||
     (((((uVar1 & 1) != 0 && ((uVar1 & 2) != 0)) && ((uVar1 & 0x10) != 0)) &&
      (((uVar1 & 0x20) != 0 && (*(int *)(param_2 + 0x3c) == 8)))))) {
    *(undefined4 *)(param_1 + 0x4c) = s_sidewind_004f568c._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_sidewind_004f568c._4_4_;
    *(char *)(param_1 + 0x54) = s_sidewind_004f568c[8];
    return;
  }
  pcVar2 = strstr(pcVar3,s_Flightstick_Pro_004f56c8);
  if ((pcVar2 != (char *)0x0) ||
     ((((uVar1 & 1) != 0 && ((uVar1 & 0x10) != 0)) &&
      (((uVar1 & 0x20) != 0 && (*(int *)(param_2 + 0x3c) == 4)))))) {
    *(undefined4 *)(param_1 + 0x4c) = s_fltstick_004f5698._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_fltstick_004f5698._4_4_;
    *(char *)(param_1 + 0x54) = s_fltstick_004f5698[8];
    return;
  }
  pcVar3 = strstr(pcVar3,s_Thrustmaster_004f56b8);
  if ((pcVar3 == (char *)0x0) &&
     (((((uVar1 & 2) == 0 || ((uVar1 & 0x10) == 0)) || ((uVar1 & 0x20) == 0)) ||
      (*(int *)(param_2 + 0x3c) != 4)))) {
    *(undefined4 *)(param_1 + 0x4c) = s_joystick_004f56ac._0_4_;
    *(undefined4 *)(param_1 + 0x50) = s_joystick_004f56ac._4_4_;
    *(char *)(param_1 + 0x54) = s_joystick_004f56ac[8];
    return;
  }
  *(undefined4 *)(param_1 + 0x4c) = s_tmaster_004f56a4._0_4_;
  *(undefined4 *)(param_1 + 0x50) = s_tmaster_004f56a4._4_4_;
  return;
}


