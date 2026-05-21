/*
 * Program: i76shell.dll
 * Function: update_debug_mouse_coordinate_overlay
 * Entry: 1001fbf0
 * Signature: undefined __fastcall update_debug_mouse_coordinate_overlay(int param_1)
 */


/* i76shell text/glyph render rename
   old_name: FUN_1001fbf0
   suggested_name: update_debug_mouse_coordinate_overlay
   basis: Builds mouse coordinate string with sprintf and updates text overlay.
   
   i76shell text/glyph rename
   old_name: update_debug_mouse_coordinate_overlay
   suggested_name: update_debug_mouse_coordinate_overlay
   basis: Builds mouse coordinate string with sprintf and updates a glyph-rendered text overlay.
   
   i76shell forced text/glyph rename
   old_name: update_debug_mouse_coordinate_overlay
   forced_name: update_debug_mouse_coordinate_overlay
   basis: Builds mouse coordinate text and updates a glyph-rendered overlay. */

void __fastcall update_debug_mouse_coordinate_overlay(int param_1)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  BOOL BVar5;
  DWORD DVar6;
  tagPOINT local_8;
  
  if (DAT_10043224 == 0) {
    return;
  }
  if ((DAT_10047720 == 0) && (*(int *)(param_1 + 0x38) == 1)) {
    sprintf(&DAT_100d3058,s___d__d__1004a2a8,*(undefined4 *)(param_1 + 0x2c),
            *(undefined4 *)(param_1 + 0x30));
    if (*(int *)(param_1 + 0xc) != 0) {
      clear_text_rect(*(void **)(param_1 + 4),0x230,0x14,*(int *)(param_1 + 0xc),
                      *(int *)(*(int *)(param_1 + 8) + 0x40c));
    }
    iVar4 = measure_and_draw_string_from_glyph_sheet
                      (*(void **)(param_1 + 4),0x230,0x14,*(int *)(*(int *)(param_1 + 8) + 0x408),
                       &DAT_100d3058,(undefined *)0x0);
    *(int *)(param_1 + 0xc) = iVar4;
  }
  iVar4 = *(int *)(param_1 + 0x3c);
  iVar1 = *(int *)(param_1 + 0x34);
  iVar2 = *(int *)(param_1 + 0x38);
  if (((((*(int *)(param_1 + 0x40) != 0) && (BVar5 = GetCursorPos(&local_8), BVar5 != 0)) &&
       (ScreenToClient(DAT_100f702c,&local_8), -1 < local_8.x)) &&
      ((local_8.x < DAT_100f701c && (-1 < local_8.y)))) && (local_8.y < DAT_100f7018)) {
    *(LONG *)(param_1 + 0x2c) = local_8.x;
    *(LONG *)(param_1 + 0x30) = local_8.y;
    uVar3 = GetAsyncKeyState(1);
    *(uint *)(param_1 + 0x34) = (uint)(uVar3 >> 0xf);
    uVar3 = GetAsyncKeyState(2);
    *(uint *)(param_1 + 0x38) = (uint)(uVar3 >> 0xf);
    uVar3 = GetAsyncKeyState(4);
    *(uint *)(param_1 + 0x3c) = (uint)(uVar3 >> 0xf);
  }
  if (*(int *)(param_1 + 0x34) == 1) {
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x10) = 1;
      goto LAB_1001fd27;
    }
    if (iVar1 == 1) {
      *(undefined4 *)(param_1 + 0x10) = 2;
      goto LAB_1001fd27;
    }
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
LAB_1001fd27:
  if ((*(int *)(param_1 + 0x38) == 1) && (iVar2 == 0)) {
    *(undefined4 *)(param_1 + 0x14) = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  if ((*(int *)(param_1 + 0x3c) == 1) && (iVar4 == 0)) {
    *(undefined4 *)(param_1 + 0x18) = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  *(undefined1 *)(param_1 + 0x1c) = 0;
  if ((*(int *)(param_1 + 0x34) == 1) && (iVar1 == 0)) {
    DVar6 = timeGetTime();
    if (DVar6 - *(int *)(param_1 + 0x20) < 0xc9) {
      *(undefined1 *)(param_1 + 0x1c) = 1;
      return;
    }
    DVar6 = timeGetTime();
    *(DWORD *)(param_1 + 0x20) = DVar6;
  }
  return;
}


