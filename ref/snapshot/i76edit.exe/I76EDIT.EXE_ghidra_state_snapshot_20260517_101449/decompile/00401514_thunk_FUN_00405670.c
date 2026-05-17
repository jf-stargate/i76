/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00405670
 * Entry: 00401514
 * Signature: undefined __cdecl thunk_FUN_00405670(HDC param_1, int * param_2)
 */


void __cdecl thunk_FUN_00405670(HDC param_1,int *param_2)

{
  int iVar1;
  HPEN h;
  HGDIOBJ pvVar2;
  int iVar3;
  POINT *pPVar4;
  POINT *pPVar5;
  undefined8 uVar6;
  longlong lVar7;
  POINT PStack_20;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  int iStack_4;
  
  uVar6 = thunk_FUN_0040c580(0,0);
  iVar3 = (int)((ulonglong)uVar6 >> 0x20);
  iVar1 = (int)uVar6;
  if (*param_2 == 0) {
    lVar7 = __ftol();
    PStack_20.x = (int)lVar7 - iVar1;
    lVar7 = __ftol();
    PStack_20.y = iVar3 - (int)lVar7;
    lVar7 = __ftol();
    iStack_18 = (int)lVar7 - iVar1;
    lVar7 = __ftol();
    iStack_14 = iVar3 - (int)lVar7;
    Polyline(param_1,&PStack_20,2);
    FUN_00405960(param_1,&PStack_20.x);
    FUN_00405960(param_1,&iStack_18);
    return;
  }
  if (*param_2 != 1) {
    return;
  }
  pPVar4 = &PStack_20;
  do {
    lVar7 = __ftol();
    pPVar4->x = (int)lVar7 - iVar1;
    pPVar5 = pPVar4 + 1;
    lVar7 = __ftol();
    pPVar4->y = iVar3 - (int)lVar7;
    pPVar4 = pPVar5;
  } while (pPVar5 < (POINT *)&stack0x00000000);
  PolyBezier(param_1,&PStack_20,4);
  FUN_00405960(param_1,&PStack_20.x);
  FUN_00405960(param_1,&iStack_8);
  if (((DAT_00434348 == 5) || (DAT_004376f4 == 5)) || (DAT_004363b4 == 5)) {
    h = CreatePen(2,0,0xff);
    pvVar2 = SelectObject(param_1,h);
    MoveToEx(param_1,PStack_20.x,PStack_20.y,(LPPOINT)0x0);
    LineTo(param_1,iStack_18,iStack_14);
    MoveToEx(param_1,iStack_8,iStack_4,(LPPOINT)0x0);
    LineTo(param_1,iStack_10,iStack_c);
    pvVar2 = SelectObject(param_1,pvVar2);
    DeleteObject(pvVar2);
    FUN_00405960(param_1,&iStack_18);
    FUN_00405960(param_1,&iStack_10);
  }
  return;
}


