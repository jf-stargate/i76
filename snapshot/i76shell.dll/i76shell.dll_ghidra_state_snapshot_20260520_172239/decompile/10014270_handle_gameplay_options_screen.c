/*
 * Program: i76shell.dll
 * Function: handle_gameplay_options_screen
 * Entry: 10014270
 * Signature: undefined __stdcall handle_gameplay_options_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_gameplay_options_screen(void)

{
  int iVar1;
  
  DAT_10057ddc = 0;
  DAT_10057dd8 = _DAT_100cc858;
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_10057ad8);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  clear_text_rect(DAT_100cc518,0x177,0x7c,0x102,0x160);
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0xa);
  iVar1 = 1;
  do {
    *(char *)(iVar1 + 0x10057de0) = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  DAT_10057de1 = 200;
  FUN_1001c0a0(DAT_100cc50c);
  if (DAT_10047130 != 0) {
    DAT_10047130 = 0;
    PTR_s_Arcade_Phys__10047224 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Arcade_Phys__10047570);
    PTR_s_No_Salv__Manag__1004727c =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_No_Salv__Manag__10047580)
    ;
    PTR_s_Unlim__Ammo_100472d4 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Unlim__Ammo_10047590);
    PTR_s_Unlim__Armor_1004732c =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Unlim__Armor_1004759c);
    PTR_s_Unlim__Chas__Rein__10047384 =
         (undefined *)
         resolve_localized_shell_string_cached(DAT_100f5360,s_Unlim__Chas__Rein__100475ac);
    PTR_s_Unlim__Wiper_Fluid_100473dc =
         (undefined *)
         resolve_localized_shell_string_cached(DAT_100f5360,s_Unlim__Wiper_Fluid_100475c0);
    PTR_s_Difficulty_Level_10047434 =
         (undefined *)
         resolve_localized_shell_string_cached(DAT_100f5360,s_Difficulty_Level_100475d4);
    PTR_s_Done_1004748c =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Done_100475e8);
    PTR_s_Cancel_100474b8 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_100475f0);
  }
  FUN_10016600((int *)&DAT_10047200);
  FUN_1001ed30(FUN_10014410);
  return;
}


