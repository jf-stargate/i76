/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ac80
 * Entry: 004010dc
 * Signature: undefined __cdecl thunk_FUN_0040ac80(HDC param_1)
 */


void __cdecl thunk_FUN_0040ac80(HDC param_1)

{
  HPEN h;
  HGDIOBJ pvVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 auStack_a8 [21];
  undefined4 auStack_54 [21];
  
  thunk_FUN_00408c80();
  h = CreatePen(0,0,0xff0000);
  pvVar1 = SelectObject(param_1,h);
  while( true ) {
    puVar2 = thunk_FUN_00408ca0();
    if (puVar2 == (undefined4 *)0x0) break;
    if (DAT_00434780 != puVar2) {
      puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_54,(int)puVar2);
      puVar5 = auStack_a8;
      for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_0040ba10(param_1,(int)auStack_a8);
    }
  }
  if (DAT_00434780 != (undefined4 *)0x0) {
    iVar3 = GetROP2(param_1);
    SetROP2(param_1,6);
    puVar2 = (undefined4 *)thunk_FUN_00408c30(auStack_54,(int)DAT_00434780);
    puVar5 = auStack_a8;
    for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_0040ba10(param_1,(int)auStack_a8);
    SetROP2(param_1,iVar3);
  }
  pvVar1 = SelectObject(param_1,pvVar1);
  DeleteObject(pvVar1);
  return;
}


