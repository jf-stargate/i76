/*
 * Program: i76shell.dll
 * Function: measure_and_draw_string_from_glyph_sheet
 * Entry: 100395b0
 * Signature: int __thiscall measure_and_draw_string_from_glyph_sheet(void * this, int param_1, int param_2, int param_3, byte * param_4, undefined * param_5)
 */


/* i76shell text/glyph render rename
   old_name: FUN_100395b0
   suggested_name: draw_or_create_text_label_from_glyph_sheet
   basis: Called with glyph sheet record buffer and string; likely creates/draws text label.
   
   i76shell text/glyph rename
   old_name: draw_or_create_text_label_from_glyph_sheet
   suggested_name: measure_and_draw_string_from_glyph_sheet
   basis: Measures string width by summing glyph widths, then draws text to destination
   surfaces/regions.
   
   i76shell forced text/glyph rename
   old_name: draw_or_create_text_label_from_glyph_sheet
   forced_name: measure_and_draw_string_from_glyph_sheet
   basis: Measures string width and draws text using glyph-sheet renderer.
   
   i76shell locale/rich-text rename
   old_name: measure_and_draw_string_from_glyph_sheet
   forced_name: measure_and_draw_string_from_glyph_sheet
   basis: Uses DAT_1004efa0 stride, measures width, and draws string. */

int __thiscall
measure_and_draw_string_from_glyph_sheet
          (void *this,int param_1,int param_2,int param_3,byte *param_4,undefined *param_5)

{
  int iVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  
  if (param_4 == (byte *)0x0) {
    return 0;
  }
  iVar5 = 0;
  bVar2 = *param_4;
  pbVar6 = param_4;
  while (bVar2 != 0) {
    iVar4 = get_glyph_width(param_3,(uint)bVar2);
    iVar5 = iVar5 + iVar4;
    pbVar6 = pbVar6 + DAT_1004efa0;
    bVar2 = *pbVar6;
  }
  if (iVar5 == 0) {
    return 0;
  }
  if (DAT_100f576c != 0) {
    if (*(int *)((int)this + 0xa0) < param_1) {
      return iVar5;
    }
    if (iVar5 + -1 + param_1 < *(int *)((int)this + 0x98)) {
      return iVar5;
    }
    if (*(int *)((int)this + 0xa4) < param_2) {
      return iVar5;
    }
    if (*(int *)(param_3 + 8) + -1 + param_2 < *(int *)((int)this + 0x9c)) {
      return iVar5;
    }
  }
  if (param_5 == (undefined *)0x0) {
    param_5 = &DAT_100f5668;
  }
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar4 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar4 != 0) goto LAB_100396fa;
    uVar3 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar3;
    **(undefined4 **)((int)this + 0x6c) = uVar3;
  }
  draw_ascii_string_from_glyph_sheet
            ((int *)((int)this + 0x6c),param_1,param_2,param_3,param_4,(int)param_5);
  draw_ascii_string_from_glyph_sheet
            ((int *)((int)this + 0xa8),param_1,param_2,param_3,param_4,(int)param_5);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_100396fa:
  iVar4 = iVar5 + -1 + param_1;
  iVar1 = *(int *)(param_3 + 8) + -1 + param_2;
  if (param_1 < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = param_1;
  }
  if (param_2 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = param_2;
  }
  if (*(int *)((int)this + 0xa0) < iVar4) {
    *(int *)((int)this + 0xa0) = iVar4;
  }
  if (*(int *)((int)this + 0xa4) < iVar1) {
    *(int *)((int)this + 0xa4) = iVar1;
  }
  return iVar5;
}


