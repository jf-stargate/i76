/*
 * Program: i76shell.dll
 * Function: draw_modem_setup_current_values
 * Entry: 10013ea0
 * Signature: undefined __stdcall draw_modem_setup_current_values(void)
 */


void draw_modem_setup_current_values(void)

{
  char *pcVar1;
  byte *pbVar2;
  undefined4 uVar3;
  byte local_20 [32];
  
  clear_text_rect(DAT_100cc518,0x18c,0x9f,0x46,0x14);
  sprintf((char *)local_20,s__d_100470a0,*(undefined4 *)(&DAT_10046fb8 + DAT_10057a3c * 4));
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,400,0xa5,*(int *)(DAT_100cc530 + 0x408),local_20,(undefined *)0x0);
  clear_text_rect(DAT_100cc518,0x18c,0xb7,0x46,0x14);
  uVar3 = DAT_10057a80;
  pcVar1 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_com__d_100470a4);
  sprintf((char *)local_20,pcVar1,uVar3);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,400,0xb9,*(int *)(DAT_100cc530 + 0x408),local_20,(undefined *)0x0);
  clear_text_rect(DAT_100cc518,0x18c,0xce,0x46,0x14);
  if (DAT_10057ad4 == 0) {
    pcVar1 = s_Pulse_100470ac;
  }
  else {
    if (DAT_10057ad4 != 1) goto LAB_10013fd5;
    pcVar1 = s_Tone_100470b4;
  }
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,pcVar1);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,400,0xd1,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
LAB_10013fd5:
  clear_text_rect(DAT_100cc518,0xc3,0x113,0xc4,0x14);
  FUN_1001c320(&DAT_10057a40,DAT_100cc520,0xc0,0xc4,0x119);
  return;
}


