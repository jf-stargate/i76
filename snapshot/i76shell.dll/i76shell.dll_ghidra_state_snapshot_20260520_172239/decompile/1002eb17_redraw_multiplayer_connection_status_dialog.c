/*
 * Program: i76shell.dll
 * Function: redraw_multiplayer_connection_status_dialog
 * Entry: 1002eb17
 * Signature: undefined __stdcall redraw_multiplayer_connection_status_dialog(void)
 */


void redraw_multiplayer_connection_status_dialog(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  char *pcVar10;
  byte *pbVar11;
  byte local_20 [32];
  
  iVar8 = DAT_100f352c;
  iVar2 = DAT_100f3528;
  iVar7 = DAT_100f352c + 0x5b;
  FUN_1000ca90(DAT_100f3528 + 0xb,DAT_100f352c + 0xe,0x256,0xd4);
  iVar8 = iVar8 + 0x21;
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2 + 0x14,iVar8,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_100f2250,
             (undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2 + 0xb5,iVar8,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_100f22c3,
             (undefined *)0x0);
  if (DAT_100f22e4 == 0) {
    pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_None_1004c3dc);
    uVar5 = 0xffffffff;
    do {
      pcVar10 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pbVar9 = (byte *)(pcVar10 + -uVar5);
    pbVar11 = local_20;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
      pbVar9 = pbVar9 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pbVar11 = *pbVar9;
      pbVar9 = pbVar9 + 1;
      pbVar11 = pbVar11 + 1;
    }
  }
  else {
    wsprintfA((LPSTR)local_20,s__d_1004c3d8,DAT_100f22e4);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2 + 0x13a,iVar8,*(int *)(DAT_100cc52c + 0x408),local_20,
             (undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2 + 0x1cb,iVar8,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_100f22e8,
             (undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar2 + 0x1e8,iVar8,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_100f22fc,
             (undefined *)0x0);
  iVar8 = 0;
  if (0 < *(int *)(DAT_100f21d4 + 4)) {
    do {
      pbVar9 = *(byte **)(*(int *)(DAT_100f21d4 + 8) + iVar8 * 4);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar2 + 0x12,iVar7,*(int *)(DAT_100cc52c + 0x408),pbVar9,
                 (undefined *)0x0);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar2 + 0xb8,iVar7,*(int *)(DAT_100cc52c + 0x408),pbVar9 + 0x22,
                 (undefined *)0x0);
      iVar4 = toupper((int)(char)DAT_100f22e8);
      if (iVar4 == 0x59) {
        pbVar9 = pbVar9 + 0x42;
        iVar4 = *(int *)(DAT_100cc52c + 0x408);
      }
      else {
        pbVar9 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_N_A_1004c3e4);
        iVar4 = *(int *)(DAT_100cc52c + 0x408);
      }
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar2 + 0x1cc,iVar7,iVar4,pbVar9,(undefined *)0x0);
      iVar7 = iVar7 + DAT_10051e60;
      iVar8 = iVar8 + 1;
    } while (iVar8 < *(int *)(DAT_100f21d4 + 4));
  }
  return;
}


