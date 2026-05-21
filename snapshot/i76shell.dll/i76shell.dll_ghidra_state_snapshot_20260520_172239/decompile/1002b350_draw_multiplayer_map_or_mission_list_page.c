/*
 * Program: i76shell.dll
 * Function: draw_multiplayer_map_or_mission_list_page
 * Entry: 1002b350
 * Signature: undefined __cdecl draw_multiplayer_map_or_mission_list_page(int param_1)
 */


void __cdecl draw_multiplayer_map_or_mission_list_page(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  
  iVar3 = 0x95;
  clear_text_rect(DAT_100cc518,0xb,0x5c,0xce,0xb6);
  if (DAT_100d4474 < 0xf) {
    pbVar4 = (byte *)(s_The_Crater_1004b510 + DAT_100d4474 * 0x2d);
  }
  else {
    pbVar4 = *(byte **)(*(int *)(DAT_100f2194 + 8) + -0x3c + DAT_100d4474 * 4);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x22,0x6d,*(int *)(DAT_100cc52c + 0x408),pbVar4,(undefined *)0x0);
  if (param_1 < DAT_1004b2f8) {
    iVar1 = param_1 + 6;
    iVar2 = param_1 * 4;
    pbVar4 = (byte *)(s_The_Crater_1004b510 + param_1 * 0x2d);
    do {
      if (iVar1 <= param_1) {
        return;
      }
      if (((int)pbVar4 < 0x1004b787) || (DAT_100f2194 == 0)) {
        iVar5 = *(int *)(DAT_100cc52c + 0x408);
        pbVar6 = pbVar4;
      }
      else {
        iVar5 = *(int *)(DAT_100cc52c + 0x408);
        pbVar6 = *(byte **)(*(int *)(DAT_100f2194 + 8) + -0x3c + iVar2);
      }
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0x22,iVar3,iVar5,pbVar6,(undefined *)0x0);
      iVar3 = iVar3 + DAT_10051e60;
      param_1 = param_1 + 1;
      iVar2 = iVar2 + 4;
      pbVar4 = pbVar4 + 0x2d;
    } while (param_1 < DAT_1004b2f8);
  }
  return;
}


