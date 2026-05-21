/*
 * Program: i76shell.dll
 * Function: handle_modem_setup_screen
 * Entry: 10013950
 * Signature: undefined __stdcall handle_modem_setup_screen(void)
 */


void handle_modem_setup_screen(void)

{
  char cVar1;
  FILE *_File;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  undefined *puVar5;
  char *pcVar6;
  char *pcVar7;
  
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_100cc558);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x20);
  DAT_10057a38 = create_pointer_list_default_16();
  puVar5 = &DAT_10046fd0;
  do {
    insert_pointer_list_item_sorted_or_append((int)DAT_10057a38,(int)puVar5,(undefined *)0x0);
    puVar5 = puVar5 + 0x14;
  } while ((int)puVar5 < 0x10047035);
  _File = fopen(s_modem_ini_10047108,s_rb_10047104);
  if (_File == (FILE *)0x0) {
    DAT_10057a88 = DAT_10046fc0;
    DAT_10057a3c = 2;
    DAT_10057a8c = 2;
    DAT_10057a80 = 2;
    uVar3 = 0xffffffff;
    DAT_10057ad4 = 1;
    pcVar6 = &DAT_10047114;
    do {
      pcVar7 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar7 + -uVar3;
    pcVar7 = &DAT_10057a40;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar6 = &DAT_10047118;
    do {
      pcVar7 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar7 + -uVar3;
    pcVar7 = (char *)&DAT_10057a94;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    goto LAB_10013b02;
  }
  fread(&DAT_10057a88,0x4c,1,_File);
  if (DAT_10057a88 < 0x4b01) {
    if (DAT_10057a88 == 0x4b00) {
      DAT_10057a3c = 1;
    }
    else if (DAT_10057a88 == 0x3840) {
      DAT_10057a3c = 0;
    }
    else {
LAB_10013a1d:
      DAT_10057a3c = 5;
    }
  }
  else if (DAT_10057a88 == 0x7080) {
    DAT_10057a3c = 2;
  }
  else if (DAT_10057a88 == 0x8278) {
    DAT_10057a3c = 3;
  }
  else {
    if (DAT_10057a88 != 0x9790) goto LAB_10013a1d;
    DAT_10057a3c = 4;
  }
  DAT_10057ad4 = DAT_10057a90;
  uVar3 = 0xffffffff;
  pcVar6 = (char *)&DAT_10057a94;
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  DAT_10057a80 = DAT_10057a8c;
  pcVar6 = pcVar7 + -uVar3;
  pcVar7 = &DAT_10057a40;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  fclose(_File);
LAB_10013b02:
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Baud_Rate_100470bc);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xcc,0xa5,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_COM_Port_100470c8);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xcc,0xb9,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Dialing_Method_100470d4);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xcc,0xd2,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Init_String__100470e4);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xcc,0xff,*(int *)(DAT_100cc530 + 0x408),pbVar2,(undefined *)0x0);
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_100470f4);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,399,0x1b5,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0);
  pbVar2 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_Done_100470fc);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x156,0x1b5,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0);
  draw_modem_setup_current_values();
  FUN_1001ed30(&LAB_10013c70);
  return;
}


