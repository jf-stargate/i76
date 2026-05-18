/*
 * Program: i76.exe
 * Function: weapon_state_validation_context_helper_004a4a00
 * Entry: 004a4a00
 * Signature: undefined4 * __stdcall weapon_state_validation_context_helper_004a4a00(void)
 */


/* cgpt label refinement v20: was weapon_state_checked_context_helper_004a4a00. Clarify
   checked/validated weapon state context. */

undefined4 * weapon_state_validation_context_helper_004a4a00(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_005da76c != 0) {
    if (DAT_004fed64 == 0) {
      iVar2 = 0x3b;
      iVar1 = 0x6a;
    }
    else {
      iVar2 = 0x7e;
      iVar1 = 0xb6;
    }
    set_bitmap_surface_clip_rect(&g_player_weapon_hud_bitmap_surface,0,0,iVar1,iVar2);
    return &g_player_weapon_hud_bitmap_surface;
  }
  return (undefined4 *)0x0;
}


