/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00404570
 * Entry: 0040149c
 * Signature: undefined __cdecl thunk_FUN_00404570(HDC param_1)
 */


void __cdecl thunk_FUN_00404570(HDC param_1)

{
  HPEN h;
  HPEN ho;
  HPEN ho_00;
  HGDIOBJ h_00;
  undefined4 *puVar1;
  int *piVar2;
  uint uVar3;
  HPEN h_01;
  int iVar4;
  int iVar5;
  int *piVar6;
  int aiStack_a8 [21];
  undefined4 auStack_54 [21];
  
  thunk_FUN_00415a50();
  h = CreatePen(0,0,0xff);
  ho = CreatePen(0,0,0xff00);
  ho_00 = CreatePen(0,0,0xffff);
  h_00 = SelectObject(param_1,h);
  while (puVar1 = thunk_FUN_00415a70(), puVar1 != (undefined4 *)0x0) {
    if (puVar1 != DAT_0043433c) {
      piVar2 = (int *)thunk_FUN_00415a00(auStack_54,(int)puVar1);
      piVar6 = aiStack_a8;
      for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar6 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar6 = piVar6 + 1;
      }
      uVar3 = aiStack_a8[1] & 0xffff;
      h_01 = h;
      if (((uVar3 == 0) || (h_01 = ho, uVar3 == 1)) || (h_01 = ho_00, uVar3 == 2)) {
        SelectObject(param_1,h_01);
      }
      thunk_FUN_00405670(param_1,aiStack_a8);
    }
  }
  if (DAT_0043433c != (undefined4 *)0x0) {
    iVar4 = GetROP2(param_1);
    SetROP2(param_1,6);
    piVar2 = (int *)thunk_FUN_00415a00(auStack_54,(int)DAT_0043433c);
    piVar6 = aiStack_a8;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar6 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar6 = piVar6 + 1;
    }
    thunk_FUN_00405670(param_1,aiStack_a8);
    SetROP2(param_1,iVar4);
  }
  SelectObject(param_1,h_00);
  DeleteObject(h);
  DeleteObject(ho);
  DeleteObject(ho_00);
  return;
}


