/*
 * Program: i76shell.dll
 * Function: process_rich_text_glyph_stream
 * Entry: 100374c0
 * Signature: uint __fastcall process_rich_text_glyph_stream(undefined4 * param_1)
 */


/* i76shell locale/rich-text rename
   old_name: FUN_100374c0
   forced_name: process_rich_text_glyph_stream
   basis: Walks byte/DBCS-like text stream, handles backslash control sequences, and emits glyph
   codes. */

uint __fastcall process_rich_text_glyph_stream(undefined4 *param_1)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  uint uVar4;
  bool bVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  char local_80;
  char local_7f;
  char local_7e;
  undefined1 local_7d;
  
  if (*(char *)(param_1 + 5) == '\0') {
    prepare_or_clear_text_draw_context((void *)param_1[3],param_1,1);
    *(undefined1 *)(param_1 + 5) = 1;
  }
  if ((int)param_1[0x10] < 0) {
    param_1[2] = param_1[1];
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0xf] = param_1[10];
  }
  pcVar3 = (char *)param_1[7];
  uVar8 = 0xffffffff;
  pcVar9 = pcVar3;
  do {
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  uVar4 = param_1[0x11];
  if (uVar4 < ~uVar8 - 1) {
    iVar7 = param_1[0x10];
    bVar2 = pcVar3[iVar7];
    if ((((((0x80 < bVar2) && (bVar2 != 0x85)) && (bVar2 != 0x86)) &&
         ((bVar2 != 0xeb && (bVar2 != 0xec)))) &&
        ((((bVar2 & 0xf0) < 0x91 || (0xdf < (bVar2 & 0xf0))) && ((bVar2 < 0xef || (0xf9 < bVar2)))))
        ) || ((bVar2 != 0 || ((int)uVar4 < 2)))) {
      if (bVar2 == 0x5c) {
        uVar8 = iVar7 + 1;
        uVar10 = 0;
        param_1[2] = param_1[1];
        param_1[0x10] = uVar8;
        param_1[0x11] = uVar4 + 1;
        if (pcVar3 == (char *)0x0) {
          uVar10 = 0;
        }
        else if (*pcVar3 == '\0') {
          uVar10 = 0;
        }
        else {
          bVar5 = false;
          do {
            bVar2 = pcVar3[uVar10];
            if (((((bVar2 < 0x81) || (bVar2 == 0x85)) || (bVar2 == 0x86)) ||
                (((bVar2 == 0xeb || (bVar2 == 0xec)) ||
                 ((0x90 < (bVar2 & 0xf0) && ((bVar2 & 0xf0) < 0xe0)))))) ||
               ((0xee < bVar2 && (bVar2 < 0xfa)))) {
              if (bVar2 == 0) {
                bVar5 = true;
              }
              else {
                uVar10 = uVar10 + 1;
              }
            }
            else {
              uVar10 = uVar10 + 2;
            }
          } while (!bVar5);
        }
        if (uVar8 < uVar10) {
          switch(pcVar3[uVar8]) {
          case 'A':
          case 'a':
            param_1[0x10] = iVar7 + 2;
            param_1[0x11] = uVar4 + 2;
            param_1[2] = &DAT_1004d268;
            break;
          case 'B':
          case 'b':
            param_1[0x10] = iVar7 + 2;
            local_80 = pcVar3[iVar7 + 2];
            param_1[0x10] = iVar7 + 3;
            local_7f = pcVar3[iVar7 + 3];
            param_1[0x10] = iVar7 + 4;
            local_7e = pcVar3[iVar7 + 4];
            param_1[0x10] = iVar7 + 5;
            local_7d = 0;
            param_1[0x11] = uVar4 + 2;
            iVar7 = atoi(&local_80);
            param_1[0xf] = param_1[0xf] - iVar7;
            break;
          case 'G':
          case 'g':
            param_1[0x10] = iVar7 + 2;
            local_80 = pcVar3[iVar7 + 2];
            param_1[0x10] = iVar7 + 3;
            local_7f = pcVar3[iVar7 + 3];
            param_1[0x10] = iVar7 + 4;
            local_7e = pcVar3[iVar7 + 4];
            param_1[0x10] = iVar7 + 5;
            local_7d = 0;
            param_1[0x11] = uVar4 + 2;
            iVar7 = atoi(&local_80);
            param_1[0xf] = iVar7 + param_1[10];
            break;
          case 'T':
          case 't':
            param_1[0x10] = iVar7 + 2;
            iVar7 = 0;
            param_1[0x11] = uVar4 + 2;
            piVar6 = &DAT_10047728;
            do {
              if ((int)(param_1[0xf] - param_1[10]) < *piVar6) {
                param_1[0xf] = (&DAT_10047728)[iVar7] + param_1[10];
                break;
              }
              piVar6 = piVar6 + 1;
              iVar7 = iVar7 + 1;
            } while ((int)piVar6 < 0x10047774);
          }
        }
      }
      else {
        if (bVar2 == 0x20) {
          param_1[2] = param_1[1];
        }
        iVar7 = draw_glyph_from_glyph_sheet_object
                          ((void *)*param_1,param_1[0xf],param_1[0xb],
                           (uint)CONCAT11(pcVar3[iVar7 + 1],pcVar3[iVar7]),(undefined *)param_1[2]);
        param_1[0xf] = param_1[0xf] + iVar7;
        param_1[0x10] = param_1[0x10] + DAT_1004efa0;
        param_1[0x11] = param_1[0x11] + 1;
      }
      uVar8 = (param_1[0xf] - param_1[10]) + 1;
      if ((int)param_1[9] < (int)uVar8) {
        param_1[9] = uVar8;
      }
      return uVar8 & 0xffffff00;
    }
  }
  *(undefined1 *)(param_1 + 0xe) = 1;
  param_1[2] = param_1[1];
  return CONCAT31((int3)((uint)param_1[1] >> 8),1);
}


