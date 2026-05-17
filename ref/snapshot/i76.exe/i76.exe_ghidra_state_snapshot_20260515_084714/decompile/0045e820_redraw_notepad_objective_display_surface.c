/*
 * Program: i76.exe
 * Function: redraw_notepad_objective_display_surface
 * Entry: 0045e820
 * Signature: undefined __stdcall redraw_notepad_objective_display_surface(void)
 */


/* cgpt rename v2: Redraws notepad/objective text into its bitmap surface using GDI text rendering.
    */

void redraw_notepad_objective_display_surface(void)

{
  HGDIOBJ pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fill_bitmap_surface_context(&DAT_00609478,0xff);
  pvVar1 = GetStockObject(2);
  SelectObject(DAT_006094dc,pvVar1);
  pvVar1 = SelectObject(DAT_006094dc,DAT_006094c0);
  RealizePalette(DAT_006094dc);
  SetTextColor(DAT_006094dc,0x2101010);
  SetBkColor(DAT_006094dc,0x2f0f0f0);
  SetBkMode(DAT_006094dc,1);
  SelectObject(DAT_006094dc,DAT_006094e0);
  local_c = DAT_006094c8;
  local_10 = DAT_006094c4;
  local_8 = DAT_006094cc;
  local_4 = DAT_006094d0;
  iVar4 = (-(uint)(g_display_mode_variant_index < 6) & 2) + 0xe;
  if ((0 < DAT_006093c0) && (iVar3 = 0, 0 < DAT_006093c0)) {
    puVar5 = &DAT_00609420;
    iVar2 = DAT_006093c0;
    do {
      if ((*puVar5 & 1) == 0) {
        iVar2 = draw_wrapped_text_to_hdc_with_optional_underline
                          (DAT_006094dc,&local_10,(byte *)puVar5[-0x16],iVar4,10,
                           (int *)(-(uint)((*puVar5 & 2) != 0) & 0x609478));
        local_c = local_c + iVar2 + iVar4;
        iVar2 = DAT_006093c0;
      }
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar3 < iVar2);
  }
  GdiFlush();
  SelectObject(DAT_006094dc,pvVar1);
  return;
}


