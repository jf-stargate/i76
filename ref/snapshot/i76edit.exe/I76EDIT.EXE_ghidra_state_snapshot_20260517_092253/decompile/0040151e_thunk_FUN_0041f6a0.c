/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f6a0
 * Entry: 0040151e
 * Signature: undefined __cdecl thunk_FUN_0041f6a0(HDC param_1)
 */


void __cdecl thunk_FUN_0041f6a0(HDC param_1)

{
  HPEN h;
  HGDIOBJ pvVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int aiStack_a8 [21];
  undefined4 auStack_54 [21];
  
  thunk_FUN_0040c9c0();
  h = CreatePen(0,0,0xff00);
  pvVar1 = SelectObject(param_1,h);
  while( true ) {
    puVar2 = thunk_FUN_0040c9e0();
    if (puVar2 == (undefined4 *)0x0) break;
    if (DAT_00437700 != puVar2) {
      piVar3 = (int *)thunk_FUN_00415a00(auStack_54,(int)puVar2);
      piVar6 = aiStack_a8;
      for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar6 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar6 = piVar6 + 1;
      }
      thunk_FUN_00405670(param_1,aiStack_a8);
    }
  }
  if (DAT_00437700 != (undefined4 *)0x0) {
    iVar4 = GetROP2(param_1);
    SetROP2(param_1,6);
    piVar3 = (int *)thunk_FUN_00415a00(auStack_54,(int)DAT_00437700);
    piVar6 = aiStack_a8;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar6 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar6 = piVar6 + 1;
    }
    thunk_FUN_00405670(param_1,aiStack_a8);
    SetROP2(param_1,iVar4);
  }
  pvVar1 = SelectObject(param_1,pvVar1);
  DeleteObject(pvVar1);
  return;
}


