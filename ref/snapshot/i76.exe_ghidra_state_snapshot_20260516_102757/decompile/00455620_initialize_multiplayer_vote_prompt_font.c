/*
 * Program: i76.exe
 * Function: initialize_multiplayer_vote_prompt_font
 * Entry: 00455620
 * Signature: undefined __stdcall initialize_multiplayer_vote_prompt_font(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: courier */

void initialize_multiplayer_vote_prompt_font(void)

{
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [4];
  char local_30 [36];
  undefined4 local_c;
  undefined4 local_4;
  
  DAT_005414f0 = 0;
  DAT_005414f8 = 0;
  DAT_005414f4 = 0;
  local_44 = 0x32;
  local_40 = 0x154;
  local_3c = 0x50;
  local_38 = 1;
  local_c = 0xff;
  local_34 = (char  [4])s_courier_004f5a94._0_4_;
  local_30._0_4_ = s_courier_004f5a94._4_4_;
  local_4 = 0x18;
  DAT_005414fc = create_scroll_region_bitmap(&local_44);
  return;
}


