/*
 * Program: i76shell.dll
 * Function: draw_save_game_scene_list
 * Entry: 100150a0
 * Signature: undefined __stdcall draw_save_game_scene_list(void)
 */


void draw_save_game_scene_list(void)

{
  int *piVar1;
  LPCSTR pCVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte local_10 [16];
  
  iVar4 = 0xb8;
  iVar5 = 10;
  do {
    clear_text_rect(DAT_100cc518,0xb8,iVar4,0x10c,DAT_10057ee8 + -8);
    iVar4 = iVar4 + DAT_10057ee8;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = 0xb8;
  iVar4 = DAT_10057f7c;
  if (DAT_10057f7c < *(int *)(DAT_10057f8c + 4)) {
    do {
      if (DAT_10057f30 + DAT_10057f7c <= iVar4) {
        return;
      }
      piVar1 = *(int **)(*(int *)(DAT_10057f8c + 8) + iVar4 * 4);
      iVar3 = *piVar1;
      if (piVar1[0xd] == 1) {
        iVar3 = iVar3 + 1;
        pcVar6 = s_Scene__d__100476d8;
      }
      else {
        pcVar6 = s_Scene__d__100476e4;
      }
      pCVar2 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar6);
      wsprintfA((LPSTR)local_10,pCVar2,iVar3);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0xba,iVar5,*(int *)(DAT_100cc530 + 0x408),local_10,(undefined *)0x0);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0x113,iVar5,*(int *)(DAT_100cc530 + 0x408),(byte *)(piVar1 + 1),
                 (undefined *)0x0);
      iVar5 = iVar5 + DAT_10057ee8;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(DAT_10057f8c + 4));
  }
  return;
}


