/*
 * Program: i76shell.dll
 * Function: render_rich_text_object
 * Entry: 100373e0
 * Signature: undefined __fastcall render_rich_text_object(undefined4 * param_1)
 */


/* i76shell localized glyph rename
   old_name: FUN_100373e0
   forced_name: render_rich_text_object
   basis: High-level rich-text object render path. */

void __fastcall render_rich_text_object(undefined4 *param_1)

{
  byte bVar1;
  byte *pbVar2;
  bool bVar3;
  int iVar4;
  
  pbVar2 = (byte *)param_1[7];
  if (pbVar2 != (byte *)0x0) {
    iVar4 = 0;
    if (pbVar2 == (byte *)0x0) {
      iVar4 = 0;
    }
    else if (*pbVar2 == 0) {
      iVar4 = 0;
    }
    else {
      bVar3 = false;
      do {
        bVar1 = pbVar2[iVar4];
        if ((((((bVar1 < 0x81) || (bVar1 == 0x85)) || (bVar1 == 0x86)) ||
             ((bVar1 == 0xeb || (bVar1 == 0xec)))) ||
            ((0x90 < (bVar1 & 0xf0) && ((bVar1 & 0xf0) < 0xe0)))) ||
           ((0xee < bVar1 && (bVar1 < 0xfa)))) {
          if (bVar1 == 0) {
            bVar3 = true;
          }
          else {
            iVar4 = iVar4 + 1;
          }
        }
        else {
          iVar4 = iVar4 + 2;
        }
      } while (!bVar3);
    }
    if (0 < iVar4) {
      if (param_1[4] == 1) {
        iVar4 = param_1[0x10];
        param_1[0x10] = 0xffffffff;
        if (-1 < iVar4) {
          do {
            process_rich_text_glyph_stream(param_1);
          } while ((int)param_1[0x10] < iVar4);
          return;
        }
      }
      else {
        draw_string_from_glyph_sheet_object
                  ((void *)*param_1,param_1[10],param_1[0xb],pbVar2,(undefined *)param_1[1]);
        *(undefined1 *)(param_1 + 0xe) = 1;
      }
    }
  }
  return;
}


