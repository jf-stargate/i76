/*
 * Program: i76shell.dll
 * Function: handle_input_binding_selection_screen
 * Entry: 10010790
 * Signature: undefined __stdcall handle_input_binding_selection_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_input_binding_selection_screen(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  char *pcVar8;
  char local_40 [64];
  
  iVar2 = format_input_binding_display_name(local_40);
  if ((iVar2 != 0) && (local_40[0] != '*')) {
    iVar2 = 0;
    pcVar7 = (char *)&DAT_100450d0;
    do {
      iVar3 = _stricmp(pcVar7,local_40);
      if (iVar3 == 0) {
        puVar6 = &DAT_100450a8 + iVar2 * 0x16;
        goto LAB_100107e7;
      }
      pcVar7 = pcVar7 + 0x58;
      iVar2 = iVar2 + 1;
    } while ((int)pcVar7 < 0x10045e90);
    puVar6 = (undefined4 *)0x0;
LAB_100107e7:
    if (puVar6 != (undefined4 *)0x0) {
      uVar4 = 0xffffffff;
      pcVar7 = &DAT_10046268;
      do {
        pcVar8 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar7 = pcVar8 + -uVar4;
      pcVar8 = (char *)(puVar6 + 10);
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      *puVar6 = 0;
    }
    iVar2 = _strnicmp((char *)(DAT_10056c2c + 2),s_throttle_100468cc,8);
    puVar6 = DAT_10056c2c;
    if (iVar2 == 0) {
      DAT_100450a8 = 0;
      if (DAT_10056c2c == &DAT_10045100) {
        if (DAT_10045158 != 1) {
          uVar4 = 0xffffffff;
          pcVar7 = &DAT_10046268;
          do {
            pcVar8 = pcVar7;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar8 = pcVar7 + 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar8;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          pcVar7 = pcVar8 + -uVar4;
          pcVar8 = (char *)&DAT_10045180;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar8 = pcVar8 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar8 = *pcVar7;
            pcVar7 = pcVar7 + 1;
            pcVar8 = pcVar8 + 1;
          }
          DAT_10045158 = 0;
        }
      }
      else if ((DAT_10056c2c == &DAT_10045158) && (DAT_10045100 != 1)) {
        uVar4 = 0xffffffff;
        pcVar7 = &DAT_10046268;
        do {
          pcVar8 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar7 = pcVar8 + -uVar4;
        pcVar8 = (char *)&DAT_10045128;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
        DAT_10045100 = 0;
      }
    }
    else {
      iVar2 = _strnicmp((char *)(DAT_10056c2c + 2),s_steer_100468d8,5);
      puVar6 = DAT_10056c2c;
      if (iVar2 == 0) {
        _DAT_100451b0 = 0;
        if (DAT_10056c2c == &DAT_10045208) {
          if (DAT_10045260 != 1) {
            uVar4 = 0xffffffff;
            pcVar7 = &DAT_10046268;
            do {
              pcVar8 = pcVar7;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar8 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar8;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            pcVar7 = pcVar8 + -uVar4;
            pcVar8 = (char *)&DAT_10045288;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar8 = pcVar8 + 4;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar8 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              pcVar8 = pcVar8 + 1;
            }
            DAT_10045260 = 0;
          }
        }
        else if ((DAT_10056c2c == &DAT_10045260) && (DAT_10045208 != 1)) {
          uVar4 = 0xffffffff;
          pcVar7 = &DAT_10046268;
          do {
            pcVar8 = pcVar7;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar8 = pcVar7 + 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar8;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          pcVar7 = pcVar8 + -uVar4;
          pcVar8 = (char *)&DAT_10045230;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar8 = pcVar8 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar8 = *pcVar7;
            pcVar7 = pcVar7 + 1;
            pcVar8 = pcVar8 + 1;
          }
          DAT_10045208 = 0;
        }
      }
    }
    uVar4 = 0xffffffff;
    pcVar7 = local_40;
    do {
      pcVar8 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar8 + -uVar4;
    pcVar8 = (char *)(puVar6 + 10);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x10);
  iVar2 = 0x2f;
  puVar6 = &DAT_10045148;
  do {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xbe,iVar2,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar6 + -8),
               (undefined *)0x0);
    iVar3 = DAT_10056c00;
    *puVar6 = 0xb1;
    puVar6[1] = 0x138;
    puVar6[2] = iVar2;
    puVar6[3] = iVar2 + 0x10;
    puVar6 = puVar6 + 0x16;
    iVar2 = iVar2 + iVar3;
  } while ((int)puVar6 < 0x100451a1);
  puVar6 = &DAT_10045250;
  do {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xbe,iVar2,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar6 + -8),
               (undefined *)0x0);
    *puVar6 = 0xb1;
    puVar6[1] = 0x138;
    puVar6[2] = iVar2;
    puVar6[3] = iVar2 + 0x10;
    puVar6 = puVar6 + 0x16;
    iVar2 = iVar2 + DAT_10056c00;
  } while ((int)puVar6 < 0x100457d1);
  iVar2 = 0x2f;
  puVar6 = &DAT_10045828;
  do {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x1e6,iVar2,*(int *)(DAT_100cc524 + 0x408),(byte *)(puVar6 + -8),
               (undefined *)0x0);
    iVar3 = DAT_10056c00;
    *puVar6 = 0x1db;
    puVar6[1] = 0x264;
    puVar6[2] = iVar2;
    puVar6[3] = iVar2 + 0x10;
    puVar6 = puVar6 + 0x16;
    iVar2 = iVar2 + iVar3;
  } while ((int)puVar6 < 0x10045e59);
  return;
}


