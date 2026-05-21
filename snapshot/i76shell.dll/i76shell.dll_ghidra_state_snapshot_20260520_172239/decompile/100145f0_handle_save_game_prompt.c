/*
 * Program: i76shell.dll
 * Function: handle_save_game_prompt
 * Entry: 100145f0
 * Signature: undefined __stdcall handle_save_game_prompt(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_save_game_prompt(void)

{
  int iVar1;
  undefined *puVar2;
  
  DAT_10057f30 = 10;
  DAT_10057f7c = 0;
  DAT_10057f78 = 0;
  DAT_10057f74 = 0;
  DAT_10057ee8 = *(int *)(DAT_100cc52c + 0x40c) + 8;
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_100cc558);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0xb);
  DAT_10057f88 = create_pointer_list_default_16();
  DAT_10057f8c = create_pointer_list_with_capacity(0x200);
  puVar2 = &DAT_10047600;
  do {
    insert_pointer_list_item_sorted_or_append((int)DAT_10057f88,(int)puVar2,(undefined *)0x0);
    puVar2 = puVar2 + 0x14;
  } while ((int)puVar2 < 0x10047665);
  read_savegame_directory_index((int)DAT_10057f8c);
  if (DAT_10047678 != 0) {
    DAT_10047678 = 0;
    PTR_s_Save_100475f8 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Save_100476f0);
    PTR_s_Cancel_100475fc =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_100476f8);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x148,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),PTR_s_Save_100475f8,
             (undefined *)0x0);
  _DAT_10047654 = 0x148;
  iVar1 = measure_string_width_from_glyph_sheet(DAT_100cc530,PTR_s_Save_100475f8);
  _DAT_10047658 = iVar1 + 0x148;
  iVar1 = iVar1 + 0x161;
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar1,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),PTR_s_Cancel_100475fc,
             (undefined *)0x0);
  _DAT_10047668 = iVar1;
  _DAT_1004766c = measure_string_width_from_glyph_sheet(DAT_100cc530,PTR_s_Cancel_100475fc);
  _DAT_1004766c = iVar1 + _DAT_1004766c;
  draw_save_game_scene_list();
  DAT_10057ef0 = 0;
  handle_save_game_scene_selection();
  FUN_1001ed30(&LAB_10014cd0);
  return;
}


