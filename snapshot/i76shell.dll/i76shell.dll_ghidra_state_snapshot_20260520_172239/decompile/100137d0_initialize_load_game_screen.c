/*
 * Program: i76shell.dll
 * Function: initialize_load_game_screen
 * Entry: 100137d0
 * Signature: undefined __stdcall initialize_load_game_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void initialize_load_game_screen(void)

{
  byte *pbVar1;
  int iVar2;
  undefined *puVar3;
  
  DAT_10057a2c = create_pointer_list_default_16();
  DAT_10057a30 = create_pointer_list_with_capacity(0x200);
  puVar3 = &DAT_10046e80;
  do {
    insert_pointer_list_item_sorted_or_append((int)DAT_10057a2c,(int)puVar3,(undefined *)0x0);
    puVar3 = puVar3 + 0x14;
  } while ((int)puVar3 < 0x10046ed1);
  pbVar1 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Load_10046f78);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x148,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),pbVar1,(undefined *)0x0);
  _DAT_10046ec0 = 0x148;
  pbVar1 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Load_10046f80);
  iVar2 = measure_string_width_from_glyph_sheet(DAT_100cc530,pbVar1);
  _DAT_10046ec4 = iVar2 + 0x148;
  iVar2 = iVar2 + 0x161;
  pbVar1 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_10046f88);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),pbVar1,(undefined *)0x0);
  _DAT_10046ed4 = iVar2;
  pbVar1 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_10046f90);
  _DAT_10046ed8 = measure_string_width_from_glyph_sheet(DAT_100cc530,pbVar1);
  _DAT_10046ed8 = iVar2 + _DAT_10046ed8;
  read_savegame_directory_index((int)DAT_10057a30);
  draw_load_game_scene_list();
  return;
}


