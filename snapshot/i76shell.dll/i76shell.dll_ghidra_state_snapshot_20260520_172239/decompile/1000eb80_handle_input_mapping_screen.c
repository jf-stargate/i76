/*
 * Program: i76shell.dll
 * Function: handle_input_mapping_screen
 * Entry: 1000eb80
 * Signature: undefined __stdcall handle_input_mapping_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_input_mapping_screen(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  
  _DAT_10046150 = 0x27;
  _DAT_10046158 = 0x33;
  _DAT_10046160 = 0x34;
  _DAT_10046164 = 0x35;
  _DAT_10046168 = 0x29;
  _DAT_100461d4 = 0x1a;
  _DAT_100461d8 = 0x2b;
  _DAT_100461dc = 0x1b;
  _DAT_100461e0 = 0x28;
  DAT_10056c14 = 0;
  DAT_10056c24 = 0;
  DAT_10051cd0 = *(int *)(DAT_100cc52c + 0x40c) + 2;
  DAT_10056c00 = *(int *)(DAT_100cc524 + 0x40c) + 5;
  DAT_10056c04 = DAT_10051cd0;
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_100cc558);
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x10);
  FUN_1001c0a0(DAT_100cc50c);
  DAT_10056c34 = create_pointer_list_default_16();
  DAT_10056c38 = create_pointer_list_with_capacity(0x200);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c34,0x10046318,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c34,0x1004632c,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c34,0x10046340,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c34,0x10046354,(undefined *)0x0);
  pcVar5 = (char *)&DAT_100450d0;
  do {
    uVar3 = 0xffffffff;
    pcVar5[-0xffffffff00000028] = '\0';
    pcVar5[-0xffffffff00000027] = '\0';
    pcVar5[-0xffffffff00000026] = '\0';
    pcVar5[-0xffffffff00000025] = '\0';
    pcVar7 = &DAT_10046268;
    do {
      pcVar9 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar5 + 0x58;
    pcVar7 = pcVar9 + -uVar3;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar5 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar5 = pcVar5 + 1;
    }
    pcVar5 = pcVar6;
    if (0x10045e8f < (int)pcVar6) {
      parse_input_mapping_file(s_input_map_100468b4);
      iVar8 = 0x2f;
      puVar10 = &DAT_10045148;
      do {
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0xbe,iVar8,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar10 + -8),
                   (undefined *)0x0);
        iVar2 = DAT_10056c00;
        *puVar10 = 0xb1;
        puVar10[1] = 0x138;
        puVar10[2] = iVar8;
        puVar10[3] = iVar8 + 0x10;
        puVar10 = puVar10 + 0x16;
        iVar8 = iVar8 + iVar2;
      } while ((int)puVar10 < 0x100451a1);
      puVar10 = &DAT_10045250;
      do {
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0xbe,iVar8,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar10 + -8),
                   (undefined *)0x0);
        *puVar10 = 0xb1;
        puVar10[1] = 0x138;
        puVar10[2] = iVar8;
        puVar10[3] = iVar8 + 0x10;
        puVar10 = puVar10 + 0x16;
        iVar8 = iVar8 + DAT_10056c00;
      } while ((int)puVar10 < 0x100457d1);
      iVar8 = 0x2f;
      puVar10 = &DAT_10045828;
      do {
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0x1e6,iVar8,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar10 + -8),
                   (undefined *)0x0);
        iVar2 = DAT_10056c00;
        *puVar10 = 0x1db;
        puVar10[1] = 0x264;
        puVar10[2] = iVar8;
        puVar10[3] = iVar8 + 0x10;
        puVar10 = puVar10 + 0x16;
        iVar8 = iVar8 + iVar2;
      } while ((int)puVar10 < 0x10045e59);
      FUN_1001ed30(&LAB_1000ee00);
      return;
    }
  } while( true );
}


