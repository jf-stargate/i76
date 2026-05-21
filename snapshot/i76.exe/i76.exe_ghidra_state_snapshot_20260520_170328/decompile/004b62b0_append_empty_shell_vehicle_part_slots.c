/*
 * Program: i76.exe
 * Function: append_empty_shell_vehicle_part_slots
 * Entry: 004b62b0
 * Signature: undefined __cdecl append_empty_shell_vehicle_part_slots(int param_1)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Initializes EMPTY placeholder records
   for vehicle part categories 2,3,4,5,7,8,9,10,11,13 before real records are appended. */

void __cdecl append_empty_shell_vehicle_part_slots(int param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 2;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 3;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 4;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 5;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 7;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 8;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 9;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 10;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 0xb;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  pcVar1 = (char *)(param_1 + DAT_005db984 * 0x54);
  *(undefined4 *)pcVar1 = s_EMPTY_0050090c._0_4_;
  *(undefined2 *)(pcVar1 + 4) = s_EMPTY_0050090c._4_2_;
  *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 0xd;
  *(undefined1 *)(param_1 + 0x2e + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined1 *)(param_1 + 0x3b + DAT_005db984 * 0x54) = DAT_00504c28;
  *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = 1;
  DAT_005db984 = DAT_005db984 + 1;
  return;
}


