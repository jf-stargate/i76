/*
 * Program: i76.exe
 * Function: initialize_multiplayer_join_prompt_font
 * Entry: 00455820
 * Signature: undefined __stdcall initialize_multiplayer_join_prompt_font(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: courier */

void initialize_multiplayer_join_prompt_font(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  char local_34 [4];
  char local_30 [36];
  undefined4 local_c;
  undefined4 local_4;
  
  puVar2 = &DAT_00541528;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_005419b4 = 0;
  DAT_00541520 = 0;
  DAT_00541828 = 0;
  puVar2 = &DAT_00541830;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_005419b0 = 0;
  local_44 = 0x32;
  local_40 = 0x154;
  local_3c = 0x50;
  local_38 = 1;
  local_c = 0xff;
  local_34[0] = s_courier_004f5a94[0];
  local_34[1] = s_courier_004f5a94[1];
  local_34[2] = s_courier_004f5a94[2];
  local_34[3] = s_courier_004f5a94[3];
  local_30[0] = s_courier_004f5a94[4];
  local_30[1] = s_courier_004f5a94[5];
  local_30[2] = s_courier_004f5a94[6];
  local_30[3] = s_courier_004f5a94[7];
  local_4 = 0x18;
  DAT_00609310 = create_scroll_region_bitmap(&local_44);
  return;
}


