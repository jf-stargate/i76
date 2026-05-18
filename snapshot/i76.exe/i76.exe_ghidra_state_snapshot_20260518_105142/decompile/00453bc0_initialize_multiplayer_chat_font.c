/*
 * Program: i76.exe
 * Function: initialize_multiplayer_chat_font
 * Entry: 00453bc0
 * Signature: undefined __stdcall initialize_multiplayer_chat_font(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: courier */

void initialize_multiplayer_chat_font(void)

{
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  char local_78 [4];
  char local_74 [36];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  char local_34 [4];
  char local_30 [36];
  undefined4 local_c;
  undefined4 local_8;
  undefined1 *local_4;
  
  local_88 = 0x32;
  local_84 = 0x96;
  local_80 = 0x50;
  local_7c = 5;
  local_50 = 0xff;
  local_78 = (char  [4])s_courier_004f5a94._0_4_;
  local_74._0_4_ = s_courier_004f5a94._4_4_;
  local_48 = 3;
  local_4c = 0x41700000;
  DAT_0060931c = create_scroll_region_bitmap(&local_88);
  local_80 = 0x50;
  local_88 = 0x32;
  local_84 = 0x168;
  local_7c = 1;
  local_50 = 0xff;
  local_78[0] = s_courier_004f5a94[0];
  local_78[1] = s_courier_004f5a94[1];
  local_78[2] = s_courier_004f5a94[2];
  local_78[3] = s_courier_004f5a94[3];
  local_74[0] = s_courier_004f5a94[4];
  local_74[1] = s_courier_004f5a94[5];
  local_74[2] = s_courier_004f5a94[6];
  local_74[3] = s_courier_004f5a94[7];
  local_48 = 0x1a;
  DAT_00609314 = create_scroll_region_bitmap(&local_88);
  local_44 = 0x32;
  local_40 = 0x168;
  local_3c = 0x21c;
  local_c = 0xff;
  local_34[0] = s_courier_004f5a94[0];
  local_34[1] = s_courier_004f5a94[1];
  local_34[2] = s_courier_004f5a94[2];
  local_34[3] = s_courier_004f5a94[3];
  local_30[0] = s_courier_004f5a94[4];
  local_30[1] = s_courier_004f5a94[5];
  local_30[2] = s_courier_004f5a94[6];
  local_30[3] = s_courier_004f5a94[7];
  local_8 = 1;
  local_4 = &LAB_00453f50;
  DAT_00609318 = create_input_region_bitmap(&local_44);
  DAT_00541050 = 1;
  DAT_0054104c = 0;
  DAT_00541054 = 0;
  DAT_00541058 = 0;
  DAT_00541040 = 0;
  return;
}


