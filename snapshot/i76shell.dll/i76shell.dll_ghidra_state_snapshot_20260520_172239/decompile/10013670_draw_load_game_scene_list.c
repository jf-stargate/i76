/*
 * Program: i76shell.dll
 * Function: draw_load_game_scene_list
 * Entry: 10013670
 * Signature: undefined __stdcall draw_load_game_scene_list(void)
 */


void draw_load_game_scene_list(void)

{
  int *piVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte local_10 [16];
  
  if (*(int *)(DAT_10057a30 + 4) == 0) {
    pbVar2 = (byte *)resolve_localized_shell_string_cached
                               (DAT_100f5360,s__No_Games_available__10046f48);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xe4,0xfc,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
    return;
  }
  iVar4 = 0xb8;
  iVar5 = 10;
  do {
    clear_text_rect(DAT_100cc518,0xb8,iVar4,0x10c,DAT_100579e0 + -8);
    iVar4 = iVar4 + DAT_100579e0;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = 0xb8;
  iVar4 = DAT_100579e4;
  if (DAT_100579e4 < *(int *)(DAT_10057a30 + 4)) {
    do {
      if (DAT_100579e4 + DAT_10057a24 <= iVar4) {
        return;
      }
      piVar1 = *(int **)(*(int *)(DAT_10057a30 + 8) + iVar4 * 4);
      if (piVar1[0xd] == 1) {
        iVar3 = *piVar1 + 1;
        pcVar6 = s_Scene__d__10046f60;
      }
      else {
        iVar3 = *piVar1;
        pcVar6 = s_Scene__d__10046f6c;
      }
      wsprintfA((LPSTR)local_10,pcVar6,iVar3);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0xba,iVar5,*(int *)(DAT_100cc530 + 0x408),local_10,(undefined *)0x0);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0x113,iVar5,*(int *)(DAT_100cc530 + 0x408),(byte *)(piVar1 + 1),
                 (undefined *)0x0);
      iVar5 = iVar5 + DAT_100579e0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(DAT_10057a30 + 4));
  }
  return;
}


