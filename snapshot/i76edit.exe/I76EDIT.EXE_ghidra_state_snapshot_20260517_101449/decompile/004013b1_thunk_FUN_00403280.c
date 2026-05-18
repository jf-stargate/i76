/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00403280
 * Entry: 004013b1
 * Signature: undefined __cdecl thunk_FUN_00403280(int param_1, HDC param_2)
 */


void __cdecl thunk_FUN_00403280(int param_1,HDC param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  HPEN h;
  HGDIOBJ pvVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  undefined *color;
  tagSIZE tStack_100;
  tagPOINT tStack_f8;
  int aiStack_f0 [6];
  int iStack_d8;
  int iStack_d4;
  char acStack_d0 [64];
  uint uStack_90;
  undefined4 auStack_78 [30];
  
  SaveDC(param_2);
  GetWindowExtEx(param_2,&tStack_100);
  SetWindowExtEx(param_2,tStack_100.cx * 0x32,tStack_100.cy * 0x32,(LPSIZE)0x0);
  GetWindowOrgEx(param_2,&tStack_f8);
  SetWindowOrgEx(param_2,tStack_f8.x * 0x32,tStack_f8.y * 0x32,(LPPOINT)0x0);
  thunk_FUN_00409d70(param_1);
  do {
    do {
      puVar2 = thunk_FUN_00409d90();
      if (puVar2 == (undefined4 *)0x0) {
        if (DAT_004340a4 != (undefined4 *)0x0) {
          piVar3 = (int *)thunk_FUN_00409d20(auStack_78,(int)DAT_004340a4);
          piVar7 = aiStack_f0;
          for (iVar5 = 0x1e; iVar5 != 0; iVar5 = iVar5 + -1) {
            *piVar7 = *piVar3;
            piVar3 = piVar3 + 1;
            piVar7 = piVar7 + 1;
          }
          if (aiStack_f0[0] == param_1) {
            iVar5 = GetROP2(param_2);
            SetROP2(param_2,6);
            thunk_FUN_00412750(param_2,aiStack_f0[1] * 0x32,(0x7f - aiStack_f0[2]) * 0x32,100,0x96,
                               iStack_d8);
            SetROP2(param_2,iVar5);
          }
        }
        RestoreDC(param_2,-1);
        return;
      }
    } while (DAT_004340a4 == puVar2);
    piVar3 = (int *)thunk_FUN_00409d20(auStack_78,(int)puVar2);
    piVar7 = aiStack_f0;
    for (iVar5 = 0x1e; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar7 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar7 = piVar7 + 1;
    }
    iVar5 = -1;
    pcVar6 = acStack_d0;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    if (iVar5 == -2) {
LAB_00403371:
      color = &DAT_00ff00ff;
    }
    else {
      iVar5 = thunk_FUN_0041f5d0(acStack_d0);
      if (iVar5 == 0) goto LAB_00403371;
      color = (undefined *)0xff;
    }
    h = CreatePen(0,0,(COLORREF)color);
    pvVar4 = SelectObject(param_2,h);
    if ((uStack_90 & 1) == 0) {
      iVar5 = i76edit_object_type_has_runtime_position_override(iStack_d4);
      if (iVar5 != 0) {
        thunk_FUN_00412750(param_2,aiStack_f0[1] * 0x32,(0x7f - aiStack_f0[2]) * 0x32,100,0x96,
                           iStack_d8);
      }
    }
    pvVar4 = SelectObject(param_2,pvVar4);
    DeleteObject(pvVar4);
  } while( true );
}


