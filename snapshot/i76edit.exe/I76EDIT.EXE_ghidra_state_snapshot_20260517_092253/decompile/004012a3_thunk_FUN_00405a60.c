/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00405a60
 * Entry: 004012a3
 * Signature: undefined __cdecl thunk_FUN_00405a60(int param_1, uint param_2, uint param_3)
 */


void __cdecl thunk_FUN_00405a60(int param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  int x;
  int iVar2;
  LRESULT LVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  tagRECT tStack_10;
  
  SetRect(&tStack_10,0,0,1,1);
  puVar1 = thunk_FUN_00412120(param_1,2);
  hdc = GetDC(DAT_01641fb4);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,(HGDIOBJ)(&DAT_01642100)[param_1]);
  uVar5 = (int)param_2 >> 0x1f;
  x = ((param_2 ^ uVar5) - uVar5 & 0x7f ^ uVar5) - uVar5;
  uVar5 = (int)param_3 >> 0x1f;
  iVar2 = ((param_3 ^ uVar5) - uVar5 & 0x7f ^ uVar5) - uVar5;
  uVar5 = (uint)*(ushort *)((int)puVar1 + (iVar2 * 0x80 + x) * 2);
  LVar3 = SendDlgItemMessageA(DAT_01642388,0x40d,0xf2,0,0);
  if ((LVar3 == 1) || (LVar3 = SendDlgItemMessageA(DAT_01642388,0x424,0xf2,0,0), LVar3 == 1)) {
    if (uVar5 < 100) {
      tStack_10.left = 0xff;
      uVar4 = 0xff;
      uVar6 = 0xff;
    }
    else {
      tStack_10.left = 0;
      uVar4 = 0;
      uVar6 = 0;
    }
  }
  else {
    if (99 < uVar5) {
      uVar5 = uVar5 - 100;
    }
    uVar4 = tStack_10.left;
    uVar6 = tStack_10.left;
    switch(uVar5) {
    case 0:
      tStack_10.left = 0;
      uVar4 = 0;
      uVar6 = 0;
      break;
    case 1:
      tStack_10.left = 0xff;
      uVar4 = 0xff;
      uVar6 = 0xff;
      break;
    case 2:
      tStack_10.left = 0xff;
      uVar4 = 0;
      uVar6 = 0;
      break;
    case 3:
      tStack_10.left = 0;
      uVar4 = 0xff;
      uVar6 = 0;
      break;
    case 4:
      tStack_10.left = 0xff;
      uVar4 = 0xff;
      uVar6 = 0;
      break;
    case 5:
      tStack_10.left = 0;
      uVar4 = 0;
      uVar6 = 0xff;
      break;
    case 6:
      tStack_10.left = 0xff;
      uVar4 = 0;
      uVar6 = 0xff;
      break;
    case 7:
      tStack_10.left = 0xff;
      uVar4 = 0;
      uVar6 = 0xff;
    }
  }
  SetPixel(hdc_00,x,0x80 - iVar2,
           (uVar4 & 0xff) << 8 | (uVar6 & 0xff) << 0x10 | tStack_10.left & 0xffU);
  SelectObject(hdc_00,h);
  DeleteDC(hdc_00);
  ReleaseDC(DAT_01641fb4,hdc);
  return;
}


