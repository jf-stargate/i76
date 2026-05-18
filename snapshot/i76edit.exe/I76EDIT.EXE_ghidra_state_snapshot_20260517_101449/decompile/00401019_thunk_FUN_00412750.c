/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00412750
 * Entry: 00401019
 * Signature: undefined __cdecl thunk_FUN_00412750(HDC param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


void __cdecl
thunk_FUN_00412750(HDC param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  POINT *pPVar1;
  POINT *pPVar2;
  POINT PVar3;
  POINT PStack_38;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  int iStack_14;
  POINT PStack_10;
  int iStack_8;
  int iStack_4;
  
  PStack_38.x = 0;
  iStack_30 = param_4;
  iStack_28 = param_4;
  uStack_24 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  PStack_38.y = -param_5;
  iStack_2c = PStack_38.y;
  iStack_14 = PStack_38.y;
  PStack_10.y = PStack_38.y;
  PStack_10.x = param_4 / 2;
  iStack_8 = param_4 / 2;
  iStack_4 = -((int)(param_5 * 3 + (param_5 * 3 >> 0x1f & 3U)) >> 2);
  pPVar1 = &PStack_38;
  do {
    pPVar2 = pPVar1 + 1;
    PVar3 = (POINT)thunk_FUN_00412cf0(pPVar1->x,pPVar1->y,param_6);
    *pPVar1 = PVar3;
    pPVar1->x = pPVar1->x + param_2;
    pPVar1->y = pPVar1->y + param_3;
    pPVar1 = pPVar2;
  } while (pPVar2 < (POINT *)&stack0x00000000);
  Polyline(param_1,&PStack_38,5);
  Polyline(param_1,&PStack_10,2);
  return;
}


