/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041ea60
 * Entry: 0040124e
 * Signature: undefined __cdecl thunk_FUN_0041ea60(int param_1)
 */


void __cdecl thunk_FUN_0041ea60(int param_1)

{
  undefined4 *puVar1;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  HBRUSH hbr;
  FILE *_File;
  LRESULT LVar2;
  COLORREF CVar3;
  HGDIOBJ h_00;
  uint uVar4;
  uint uVar5;
  char cVar6;
  undefined2 uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined2 uStack_34;
  undefined2 uStack_32;
  uint uStack_2c;
  HPEN pHStack_24;
  tagRECT tStack_10;
  
  pHStack_24 = (HPEN)0x0;
  SetRect(&tStack_10,0,0,0x80,0x80);
  puVar1 = thunk_FUN_00412120(param_1,0);
  hdc = GetDC(DAT_01641fb4);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,(HGDIOBJ)(&DAT_01642100)[param_1]);
  hbr = GetStockObject(0);
  FillRect(hdc_00,&tStack_10,hbr);
  _File = (FILE *)FUN_004232c0(s_height_txt_00436a2c,&DAT_00436a3c);
  if (((DAT_016420fe & 2) == 0) && (DAT_00433a34 != '\x01')) {
    if (((DAT_016420fe & 4) != 0) || (DAT_00433a34 == '\x02')) {
      iVar12 = 0;
      puVar1 = thunk_FUN_00412120(param_1,2);
      uStack_2c = 0;
      uVar7 = (undefined2)tStack_10.left;
      do {
        iVar10 = 0;
        do {
          uVar9 = *(ushort *)((int)puVar1 + (iVar12 + iVar10) * 2) & 0xfff;
          LVar2 = SendDlgItemMessageA(DAT_01642388,0x40d,0xf2,0,0);
          if ((LVar2 == 1) || (LVar2 = SendDlgItemMessageA(DAT_01642388,0x424,0xf2,0,0), LVar2 == 1)
             ) {
            if (uVar9 < 100) goto switchD_0041ebb1_caseD_1;
            uVar7 = 0;
            uStack_34 = uVar7;
            uStack_32 = uVar7;
          }
          else {
            if (99 < uVar9) {
              uVar9 = uVar9 - 100;
            }
            switch(uVar9) {
            case 0:
              uVar7 = 0;
              uStack_34 = uVar7;
              uStack_32 = uVar7;
              break;
            case 1:
switchD_0041ebb1_caseD_1:
              uVar7 = 0xff;
              uStack_34 = uVar7;
              uStack_32 = uVar7;
              break;
            case 2:
              uVar7 = 0xff;
              uStack_34 = 0;
              uStack_32 = 0;
              break;
            case 3:
              uStack_34 = 0xff;
              uVar7 = 0;
              uStack_32 = uVar7;
              break;
            case 4:
              uStack_32 = 0;
              uVar7 = 0xff;
              uStack_34 = 0xff;
              break;
            case 5:
              uStack_32 = 0xff;
              uVar7 = 0;
              uStack_34 = 0;
              break;
            case 6:
              uStack_34 = 0;
              uVar7 = 0xff;
              uStack_32 = uVar7;
              break;
            case 7:
              uStack_34 = 0;
              uVar7 = 0xff;
              uStack_32 = uVar7;
            }
          }
          CVar3 = SetPixel(hdc_00,iVar10,0x80 - uStack_2c,
                           (uint)(byte)uStack_34 << 8 | (uint)(byte)uStack_32 << 0x10 |
                           (uint)(byte)uVar7);
          if (CVar3 == 0xffffffff) {
            GetLastError();
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < 0x80);
        iVar12 = iVar12 + 0x80;
        uStack_2c = uStack_2c + 1;
      } while (iVar12 < 0x4000);
    }
  }
  else {
    iVar12 = 0;
    LVar2 = SendDlgItemMessageA(DAT_01642384,0x40a,0xf2,0,0);
    if (LVar2 == 1) {
      uStack_2c = 0;
      do {
        uVar9 = 0;
        do {
          uVar8 = *(ushort *)((int)puVar1 + (iVar12 + uVar9) * 2) & 0xfff;
          _fprintf(_File,s_next__d_00436a20,uVar8);
          if (((int)uVar8 < DAT_004376e8) || (DAT_004376e8 + 0x4af < (int)uVar8)) {
            uVar4 = (int)uVar9 >> 0x1f;
            uVar8 = (uVar9 ^ uVar4) - uVar4 & 1 ^ uVar4;
            uVar5 = (int)uStack_2c >> 0x1f;
            if (uVar8 == uVar4) {
LAB_0041edb9:
              if (((uStack_2c ^ uVar5) - uVar5 & 1 ^ uVar5) != uVar5) {
LAB_0041edd2:
                CVar3 = 0;
                goto LAB_0041edd4;
              }
            }
            else if (((uStack_2c ^ uVar5) - uVar5 & 1 ^ uVar5) == uVar5) {
              if (uVar8 == uVar4) goto LAB_0041edb9;
              goto LAB_0041edd2;
            }
            CVar3 = 0xffffff;
          }
          else {
            iVar10 = uVar8 - DAT_004376e8;
            cVar6 = (char)iVar10;
            if (iVar10 < 200) {
              CVar3 = (COLORREF)(byte)(cVar6 + 0x32);
            }
            else if (iVar10 < 400) {
              CVar3 = (uint)(byte)(cVar6 + 0x6a) << 0x10 | (uint)(byte)(cVar6 + 0x6a);
            }
            else if (iVar10 < 600) {
              CVar3 = (uint)(byte)(cVar6 + 0xa2) << 0x10;
            }
            else if (iVar10 < 800) {
              CVar3 = (uint)(byte)(cVar6 - 0x26) << 0x10 | (uint)(byte)(cVar6 - 0x26) << 8;
            }
            else if (iVar10 < 1000) {
              CVar3 = (uint)(byte)(cVar6 + 0x12) << 8;
            }
            else {
              CVar3 = (COLORREF)CONCAT11(cVar6 + 'J',cVar6 + 'J');
            }
          }
LAB_0041edd4:
          uVar8 = uVar9 + 1;
          SetPixel(hdc_00,uVar9,0x80 - uStack_2c,CVar3);
          uVar9 = uVar8;
        } while ((int)uVar8 < 0x80);
        iVar12 = iVar12 + 0x80;
        uStack_2c = uStack_2c + 1;
      } while (iVar12 < 0x4000);
    }
    else {
      iVar12 = 0;
      uStack_2c = 0;
      do {
        iVar10 = 0;
        do {
          uVar9 = *(ushort *)((int)puVar1 + (iVar12 + iVar10) * 2) & 0xfff;
          _fprintf(_File,s_next__d_00436a20,uVar9);
          if (uVar9 < 2000) {
            uVar9 = (uint)(byte)((char)((ulonglong)uVar9 / 0x14) + 0x37);
            uVar8 = uVar9 << 8;
LAB_0041eeca:
            CVar3 = uVar8 | uVar9;
          }
          else if (uVar9 < 4000) {
            CVar3 = (uint)(byte)((char)((int)(uVar9 - 2000) / 0x14) + 0x37) << 8 | 0x100010;
          }
          else {
            if (5999 < uVar9) {
              uVar9 = (uint)(byte)((char)((int)(uVar9 - 8000) / 0x14) + 0x23);
              uVar8 = uVar9 << 0x10 | uVar9 << 8;
              goto LAB_0041eeca;
            }
            CVar3 = (byte)((char)((int)(uVar9 - 4000) / 0x14) + 0x37) | 0x101000;
          }
          iVar11 = iVar10 + 1;
          SetPixel(hdc_00,iVar10,0x80 - uStack_2c,CVar3);
          iVar10 = iVar11;
        } while (iVar11 < 0x80);
        iVar12 = iVar12 + 0x80;
        uStack_2c = uStack_2c + 1;
      } while (iVar12 < 0x4000);
    }
  }
  _fclose(_File);
  if ((DAT_016420fe & 0x80) != 0) {
    pHStack_24 = CreatePen(0,1,0xff);
    h_00 = SelectObject(hdc_00,pHStack_24);
    MoveToEx(hdc_00,0,0,(LPPOINT)0x0);
    LineTo(hdc_00,0,0x7f);
    LineTo(hdc_00,0x7f,0x7f);
    LineTo(hdc_00,0x7f,0);
    LineTo(hdc_00,0,0);
    SelectObject(hdc_00,h_00);
  }
  SelectObject(hdc_00,h);
  if (pHStack_24 != (HPEN)0x0) {
    DeleteObject(pHStack_24);
  }
  DeleteDC(hdc_00);
  ReleaseDC(DAT_01641fb4,hdc);
  return;
}


