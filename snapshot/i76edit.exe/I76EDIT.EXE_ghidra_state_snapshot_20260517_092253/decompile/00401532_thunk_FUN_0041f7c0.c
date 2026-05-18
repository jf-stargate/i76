/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f7c0
 * Entry: 00401532
 * Signature: undefined __cdecl thunk_FUN_0041f7c0(int param_1, uint param_2, uint param_3)
 */


void __cdecl thunk_FUN_0041f7c0(int param_1,uint param_2,uint param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  LRESULT LVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  COLORREF color;
  uint uVar7;
  uint uVar8;
  char cVar9;
  int iVar10;
  tagRECT tStack_10;
  
  SetRect(&tStack_10,0,0,1,1);
  puVar2 = thunk_FUN_00412120(param_1,0);
  hdc = GetDC(DAT_01641fb4);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,(HGDIOBJ)(&DAT_01642100)[param_1]);
  uVar5 = (int)param_2 >> 0x1f;
  uVar5 = ((param_2 ^ uVar5) - uVar5 & 0x7f ^ uVar5) - uVar5;
  uVar6 = (int)param_3 >> 0x1f;
  uVar6 = ((param_3 ^ uVar6) - uVar6 & 0x7f ^ uVar6) - uVar6;
  uVar1 = *(ushort *)((int)puVar2 + (uVar6 * 0x80 + uVar5) * 2);
  uVar4 = (uint)uVar1;
  LVar3 = SendDlgItemMessageA(DAT_01642384,0x40a,0xf2,0,0);
  if (LVar3 != 1) {
    if (uVar1 < 2000) {
      uVar4 = (uint)(byte)((char)((ulonglong)uVar4 / 0x14) + 0x37);
      uVar7 = uVar4 << 8;
    }
    else {
      if (uVar1 < 4000) {
        color = (uint)(byte)((char)((int)(uVar4 - 2000) / 0x14) + 0x37) << 8 | 0x100010;
        goto LAB_0041f9f4;
      }
      if (uVar1 < 6000) {
        color = (byte)((char)((int)(uVar4 - 4000) / 0x14) + 0x37) | 0x101000;
        goto LAB_0041f9f4;
      }
      uVar4 = (uint)(byte)((char)((int)(uVar4 - 8000) / 0x14) + 0x23);
      uVar7 = uVar4 << 0x10 | uVar4 << 8;
    }
    color = uVar7 | uVar4;
    goto LAB_0041f9f4;
  }
  if ((DAT_004376e8 <= (int)uVar4) && ((int)uVar4 <= DAT_004376e8 + 0x4af)) {
    iVar10 = uVar4 - DAT_004376e8;
    cVar9 = (char)iVar10;
    if (iVar10 < 200) {
      color = (COLORREF)(byte)(cVar9 + 0x32);
    }
    else if (iVar10 < 400) {
      color = (uint)(byte)(cVar9 + 0x6a) << 0x10 | (uint)(byte)(cVar9 + 0x6a);
    }
    else if (iVar10 < 600) {
      color = (uint)(byte)(cVar9 + 0xa2) << 0x10;
    }
    else if (iVar10 < 800) {
      color = (uint)(byte)(cVar9 - 0x26) << 0x10 | (uint)(byte)(cVar9 - 0x26) << 8;
    }
    else if (iVar10 < 1000) {
      color = (uint)(byte)(cVar9 + 0x12) << 8;
    }
    else {
      color = (COLORREF)CONCAT11(cVar9 + 'J',cVar9 + 'J');
    }
    goto LAB_0041f9f4;
  }
  uVar7 = (int)uVar5 >> 0x1f;
  uVar4 = (uVar5 ^ uVar7) - uVar7 & 1 ^ uVar7;
  uVar8 = (int)uVar6 >> 0x1f;
  if (uVar4 == uVar7) {
LAB_0041f949:
    if (((uVar6 ^ uVar8) - uVar8 & 1 ^ uVar8) != uVar8) {
LAB_0041f965:
      color = 0;
      goto LAB_0041f9f4;
    }
  }
  else if (((uVar6 ^ uVar8) - uVar8 & 1 ^ uVar8) == uVar8) {
    if (uVar4 == uVar7) goto LAB_0041f949;
    goto LAB_0041f965;
  }
  color = 0xffffff;
LAB_0041f9f4:
  SetPixel(hdc_00,uVar5,0x80 - uVar6,color);
  SelectObject(hdc_00,h);
  DeleteDC(hdc_00);
  ReleaseDC(DAT_01641fb4,hdc);
  return;
}


