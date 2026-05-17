/*
 * Program: i76.exe
 * Function: update_weapon_hud_diode_indicator
 * Entry: 004a4d50
 * Signature: undefined __cdecl update_weapon_hud_diode_indicator(int param_1, int param_2, undefined4 param_3, int param_4)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Maps ammo fraction/range to
   weapon HUD diode/off texture names. */

void __cdecl
update_weapon_hud_diode_indicator(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = ftol();
  iVar2 = 0;
  do {
    if (((*(int *)((int)&DAT_004fe7b0 + iVar3) <= iVar1) &&
        (iVar1 <= *(int *)((int)&DAT_004fe7b4 + iVar3))) &&
       ((*(int *)(param_1 + 0x3c + param_2 * 4) != iVar2 || (param_4 != 0)))) {
      draw_texture_widget_to_hud_surface_and_bind_object
                (g_player_weapon_hud_world_object,
                 (byte *)(s_zbk_320_map_004fe748 + DAT_004fed64 * 0xd),
                 s_3diode_1_004fe9a0 + DAT_004fed64 + param_2 * 0x15,
                 s_3off_004fe798 + iVar3 + DAT_004fed64,&g_player_weapon_hud_bitmap_surface,param_4)
      ;
      *(int *)(param_1 + 0x3c + param_2 * 4) = iVar2;
      g_player_weapon_hud_dirty = 1;
    }
    iVar3 = iVar3 + 0x20;
    iVar2 = iVar2 + 1;
  } while (iVar3 < 0x81);
  return;
}


