/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040c030
 * Entry: 0040101e
 * Signature: undefined __stdcall thunk_FUN_0040c030(void)
 */


void thunk_FUN_0040c030(void)

{
  HDC hdc;
  int iVar1;
  int iVar2;
  HDC hdc_00;
  HDC hdc_01;
  HBITMAP h;
  HBRUSH hbr;
  int iVar3;
  HGDIOBJ pvVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined8 uVar9;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  uint uStack_88;
  uint uStack_84;
  int iStack_68;
  tagPOINT tStack_64;
  int iStack_5c;
  int iStack_58;
  tagRECT tStack_54;
  int iStack_44;
  tagPAINTSTRUCT tStack_40;
  
  hdc = BeginPaint(DAT_01641fb4,&tStack_40);
  SetMapMode(hdc,7);
  SetWindowExtEx(hdc,100,100,(LPSIZE)0x0);
  SetViewportExtEx(hdc,DAT_00433a44,DAT_00433a44,(LPSIZE)0x0);
  GetClientRect(DAT_01641fb4,&tStack_54);
  tStack_64.x = tStack_54.left;
  tStack_64.y = tStack_54.top;
  iStack_5c = tStack_54.right;
  iStack_58 = tStack_54.bottom;
  DPtoLP(hdc,&tStack_64,2);
  uVar9 = thunk_FUN_0040c580(0,0);
  iVar1 = ((int)(iStack_58 + 0x7f + (iStack_58 + 0x7f >> 0x1f & 0x7fU)) >> 7) + 1;
  uStack_84 = (uint)((ulonglong)uVar9 >> 0x20);
  uVar6 = (int)uStack_84 >> 0x1f;
  uStack_88 = (uint)uVar9;
  iVar2 = ((int)(iStack_5c + 0x7f + (iStack_5c + 0x7f >> 0x1f & 0x7fU)) >> 7) + 1;
  uVar7 = (int)uStack_88 >> 0x1f;
  hdc_00 = CreateCompatibleDC(hdc);
  hdc_01 = CreateCompatibleDC(hdc);
  h = CreateCompatibleBitmap(hdc,tStack_54.right,tStack_54.bottom);
  SelectObject(hdc_00,h);
  hbr = GetStockObject(0);
  FillRect(hdc_00,&tStack_54,hbr);
  SetMapMode(hdc_00,7);
  SetWindowExtEx(hdc_00,100,100,(LPSIZE)0x0);
  SetViewportExtEx(hdc_00,DAT_00433a44,DAT_00433a44,(LPSIZE)0x0);
  iStack_94 = 0;
  if (0 < iVar1) {
    iStack_8c = -(0x7f - (((uStack_84 ^ uVar6) - uVar6 & 0x7f ^ uVar6) - uVar6));
    do {
      iVar8 = 0;
      if (0 < iVar2) {
        iStack_90 = -(((uStack_88 ^ uVar7) - uVar7 & 0x7f ^ uVar7) - uVar7);
        do {
          iVar5 = ((int)(uStack_88 + (uVar7 & 0x7f)) >> 7) + iVar8;
          if ((iVar5 < 0x50) &&
             (iVar3 = ((int)(uStack_84 + (uVar6 & 0x7f)) >> 7) - iStack_94, iVar3 < 0x50)) {
            iVar5 = i76edit_get_or_assign_zone_map_cell_id(iVar5,iVar3,0);
            SetWindowOrgEx(hdc_00,-iStack_90,-iStack_8c,(LPPOINT)0x0);
            if (iVar5 == -1) {
              if ((DAT_016420fe & 0x80) != 0) {
                pvVar4 = SelectObject(hdc_01,DAT_016423a8);
                BitBlt(hdc_00,0,0,0x80,0x80,hdc_01,0,0,0xcc0020);
                SelectObject(hdc_01,pvVar4);
              }
            }
            else {
              pvVar4 = SelectObject(hdc_01,(HGDIOBJ)(&DAT_01642100)[iVar5]);
              BitBlt(hdc_00,0,0,0x80,0x80,hdc_01,0,0,0xcc0020);
              SelectObject(hdc_01,pvVar4);
              if ((DAT_016420fe & 1) != 0) {
                FUN_0040c640(iVar5,hdc_00,0,0);
              }
              if ((DAT_016420fe & 0x40) != 0) {
                thunk_FUN_00403280(iVar5,hdc_00);
              }
            }
          }
          iVar8 = iVar8 + 1;
          iStack_90 = iStack_90 + 0x80;
        } while (iVar8 < iVar2);
      }
      iStack_8c = iStack_8c + 0x80;
      iStack_94 = iStack_94 + 1;
    } while (iStack_94 < iVar1);
  }
  SetWindowOrgEx(hdc_00,0,0,(LPPOINT)0x0);
  if ((DAT_016420fe & 0x10) != 0) {
    thunk_FUN_00404570(hdc_00);
  }
  if (((DAT_016420fe & 2) != 0) || (DAT_00433a34 == '\x01')) {
    thunk_FUN_0041f6a0(hdc_00);
  }
  if ((DAT_016420fe & 8) != 0) {
    thunk_FUN_0040ac80(hdc_00);
  }
  if ((DAT_016420fe & 0x20) != 0) {
    iVar1 = 0;
    thunk_FUN_004160e0(hdc_00);
    do {
      i76edit_convert_zone_id_to_cell_xy(iVar1,&iStack_68,&iStack_44);
      if (iStack_68 != -1) {
        thunk_FUN_004162a0(iVar1,hdc_00);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x50);
  }
  BitBlt(hdc,0,0,iStack_5c,iStack_58,hdc_00,0,0,0xcc0020);
  DeleteDC(hdc_01);
  DeleteDC(hdc_00);
  DeleteObject(h);
  EndPaint(DAT_01641fb4,&tStack_40);
  return;
}


