/*
 * Program: i76.exe
 * Function: update_weapon_hud_ammo_digit_wheels
 * Entry: 004a4e40
 * Signature: undefined __cdecl update_weapon_hud_ammo_digit_wheels(undefined4 param_1, int param_2, int param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Updates
   ones/tens/hundreds/thousands ammo digit texture wheels for a weapon HUD slot. */

void __cdecl
update_weapon_hud_ammo_digit_wheels(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_34 [13];
  
  iVar4 = *(int *)(&DAT_005aab28 + param_3 * 0x4c) / 10;
  iVar1 = iVar4 / 10;
  if ((*(int *)(&DAT_005aab28 + param_3 * 0x4c) % 10 != (&DAT_004fec40)[param_2]) || (param_4 != 0))
  {
    if (param_4 == 0) {
      (&DAT_004fec40)[param_2] = (&DAT_004fec40)[param_2] + -1;
    }
    if ((&DAT_004fec40)[param_2] == -1) {
      (&DAT_004fec40)[param_2] = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,g_player_weapon_hud_world_object,
                        s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd,
                        s_3num_ones_1_004fea80 + DAT_004fed64 + param_2 * 0x15,
                        s_3top_004fe768 + DAT_004fed64,s_3bottom_004fe77d + DAT_004fed64);
    puVar5 = &g_player_weapon_hud_bitmap_surface;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    g_player_weapon_hud_dirty = 1;
  }
  if ((iVar4 % 10 != (&DAT_004fec58)[param_2]) || (param_4 != 0)) {
    if (param_4 == 0) {
      (&DAT_004fec58)[param_2] = (&DAT_004fec58)[param_2] + -1;
    }
    if ((&DAT_004fec58)[param_2] == -1) {
      (&DAT_004fec58)[param_2] = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,g_player_weapon_hud_world_object,
                        s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd,
                        s_3num_tens_1_004feaf0 + DAT_004fed64 + param_2 * 0x15,
                        s_3top_004fe768 + DAT_004fed64,s_3bottom_004fe77d + DAT_004fed64);
    puVar5 = &g_player_weapon_hud_bitmap_surface;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    g_player_weapon_hud_dirty = 1;
  }
  if ((iVar1 % 10 != *(int *)(&DAT_004fec70 + param_2 * 4)) || (param_4 != 0)) {
    if (param_4 == 0) {
      *(int *)(&DAT_004fec70 + param_2 * 4) = *(int *)(&DAT_004fec70 + param_2 * 4) + -1;
    }
    if (*(int *)(&DAT_004fec70 + param_2 * 4) == -1) {
      *(undefined4 *)(&DAT_004fec70 + param_2 * 4) = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,g_player_weapon_hud_world_object,
                        s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd,
                        s_3num_hunds_1_004feb60 + DAT_004fed64 + param_2 * 0x15,
                        s_3top_004fe768 + DAT_004fed64,s_3bottom_004fe77d + DAT_004fed64);
    puVar5 = &g_player_weapon_hud_bitmap_surface;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    g_player_weapon_hud_dirty = 1;
  }
  if (((iVar1 / 10) % 10 != *(int *)(&DAT_004fec88 + param_2 * 4)) || (param_4 != 0)) {
    if (param_4 == 0) {
      *(int *)(&DAT_004fec88 + param_2 * 4) = *(int *)(&DAT_004fec88 + param_2 * 4) + -1;
    }
    if (*(int *)(&DAT_004fec88 + param_2 * 4) == -1) {
      *(undefined4 *)(&DAT_004fec88 + param_2 * 4) = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,g_player_weapon_hud_world_object,
                        s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd,
                        s_3num_thous_1_004febd0 + DAT_004fed64 + param_2 * 0x15,
                        s_3top_004fe768 + DAT_004fed64,s_3bottom_004fe77d + DAT_004fed64);
    puVar5 = &g_player_weapon_hud_bitmap_surface;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    g_player_weapon_hud_dirty = 1;
  }
  return;
}


