/*
 * Program: i76shell.dll
 * Function: shell_screen_state_handler_b
 * Entry: 1000dae0
 * Signature: undefined __stdcall shell_screen_state_handler_b(void)
 */


/* i76shell first-pass rename
   old_name: FUN_1000dae0
   suggested_name: shell_screen_state_handler_b
   basis: Shell screen/state candidate; name intentionally cautious. */

void shell_screen_state_handler_b(void)

{
  int iVar1;
  
  DAT_10053718 = 0;
  DAT_1005371c = DAT_100477b0;
  DAT_10053720 = DAT_100477b4;
  handle_audio_options_screen();
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_10053728);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  clear_text_rect(DAT_100cc518,0x177,0x7c,0x102,0x160);
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x7);
  iVar1 = 1;
  do {
    (&DAT_10055c88)[iVar1] = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  DAT_10055c89 = 200;
  FUN_1001c0a0(DAT_100cc50c);
  FUN_10016600((int *)&DAT_10053a28);
  FUN_1001ed30(FUN_1000db90);
  return;
}


