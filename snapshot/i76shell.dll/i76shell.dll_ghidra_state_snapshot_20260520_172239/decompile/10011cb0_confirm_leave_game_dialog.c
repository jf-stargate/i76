/*
 * Program: i76shell.dll
 * Function: confirm_leave_game_dialog
 * Entry: 10011cb0
 * Signature: undefined __stdcall confirm_leave_game_dialog(void)
 */


void confirm_leave_game_dialog(void)

{
  int iVar1;
  
  if (DAT_10046c1c != 0) {
    DAT_10046c1c = 0;
    PTR_s_Are_you_gonna_10046b64 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Are_you_gonna_10046c20);
    PTR_s_leave_me__Sweetheart___10046b90 =
         (undefined *)
         resolve_localized_shell_string_cached(DAT_100f5360,s_leave_me__Sweetheart___10046c30);
    PTR_s_Yes_10046bbc =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Yes_10046c48);
    PTR_s_No_10046be8 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_No_10046c4c);
  }
  DAT_10056c40 = 0;
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_10056c48);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  clear_text_rect(DAT_100cc518,0x177,0x7c,0x102,0x160);
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x8);
  iVar1 = 1;
  do {
    *(char *)(iVar1 + 0x10056f48) = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  DAT_10056f49 = 200;
  FUN_1001c0a0(DAT_100cc50c);
  FUN_10016600((int *)&DAT_10046b40);
  FUN_1001ed30(FUN_10011dc0);
  return;
}


