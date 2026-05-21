/*
 * Program: i76shell.dll
 * Function: draw_available_multiplayer_games_list
 * Entry: 1002b450
 * Signature: undefined __cdecl draw_available_multiplayer_games_list(int param_1)
 */


void __cdecl draw_available_multiplayer_games_list(int param_1)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte local_14 [20];
  
  iVar4 = 0x95;
  clear_text_rect(DAT_100cc518,0xb,0x60,0xce,0xb4);
  if (*(int *)(DAT_100f21a0 + 4) <= DAT_100d4474) {
    DAT_100d4474 = 0;
  }
  if (*(int *)(DAT_100f21a0 + 4) != 0) {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x22,0x6d,*(int *)(DAT_100cc52c + 0x408),
               *(byte **)(*(int *)(DAT_100f21a0 + 8) + DAT_100d4474 * 4),(undefined *)0x0);
    if (param_1 < *(int *)(DAT_100f21a0 + 4)) {
      iVar1 = param_1 + 6;
      do {
        if (iVar1 <= param_1) {
          return;
        }
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0xe,iVar4,*(int *)(DAT_100cc52c + 0x408),
                   *(byte **)(*(int *)(DAT_100f21a0 + 8) + param_1 * 4),(undefined *)0x0);
        iVar2 = *(int *)(*(int *)(DAT_100f21a0 + 8) + param_1 * 4);
        sprintf((char *)local_14,s___d__d__1004c1c8,*(undefined4 *)(iVar2 + 0x78),
                *(undefined4 *)(iVar2 + 0x7c));
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0xa0,iVar4,*(int *)(DAT_100cc52c + 0x408),local_14,(undefined *)0x0)
        ;
        FUN_100315d0(0xcc,iVar4);
        iVar4 = iVar4 + DAT_10051e60;
        param_1 = param_1 + 1;
      } while (param_1 < *(int *)(DAT_100f21a0 + 4));
    }
    return;
  }
  pbVar3 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_No_games_found_1004c1b8);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x22,0x6d,*(int *)(DAT_100cc52c + 0x408),pbVar3,(undefined *)0x0);
  return;
}


