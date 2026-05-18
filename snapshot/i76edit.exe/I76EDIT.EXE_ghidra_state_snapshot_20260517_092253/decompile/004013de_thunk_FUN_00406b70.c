/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00406b70
 * Entry: 004013de
 * Signature: undefined __stdcall thunk_FUN_00406b70(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_00406b70(void)

{
  uint uVar1;
  LRESULT LVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uStack_118;
  uint uStack_114;
  uint uStack_110;
  char acStack_100 [256];
  
  if ((int)DAT_00439b90 < (int)DAT_00439b98) {
    uStack_110 = DAT_00439b90;
    uVar1 = DAT_00439b98;
  }
  else {
    uStack_110 = DAT_00439b98;
    uVar1 = DAT_00439b90;
  }
  uStack_114 = DAT_00439b94;
  uVar5 = DAT_00439b9c;
  if ((int)DAT_00439b9c <= (int)DAT_00439b94) {
    uStack_114 = DAT_00439b9c;
    uVar5 = DAT_00439b94;
  }
  iVar4 = uVar1 - uStack_110;
  if (-1 < (int)(uVar5 - uStack_114)) {
    iVar6 = (uVar5 - uStack_114) + 1;
    do {
      uStack_118 = uStack_110;
      iVar3 = iVar4;
      if (0 < iVar4) {
        do {
          if ((DAT_0043442c == 0) || (DAT_00434430 == 0)) {
            LVar2 = SendDlgItemMessageA(DAT_01642388,0x424,0xf2,0,0);
            if (LVar2 == 1) {
              _DAT_00434428 = thunk_FUN_0041f200(uStack_118,uStack_114);
              if (99 < (int)_DAT_00434428) {
                _DAT_00434428 = _DAT_00434428 - 100;
                thunk_FUN_0041f4a0(uStack_118,uStack_114,(short)_DAT_00434428,1);
              }
              _DAT_00434428 = thunk_FUN_0041f150(uStack_118,uStack_114);
              if (99 < (int)_DAT_00434428) {
                _DAT_00434428 = _DAT_00434428 - 100;
                uVar1 = _DAT_00434428;
                goto LAB_00406d63;
              }
            }
            else {
              _DAT_00434428 = thunk_FUN_0041f200(uStack_118,uStack_114);
              if ((int)_DAT_00434428 < 100) {
                _DAT_00434428 = _DAT_00434428 + 100;
                thunk_FUN_0041f4a0(uStack_118,uStack_114,(short)_DAT_00434428,1);
              }
              _DAT_00434428 = thunk_FUN_0041f150(uStack_118,uStack_114);
              if ((int)_DAT_00434428 < 100) {
                _DAT_00434428 = _DAT_00434428 + 100;
                uVar1 = _DAT_00434428;
                goto LAB_00406d63;
              }
            }
          }
          else {
            uVar1 = thunk_FUN_0041f200(uStack_118,uStack_114);
            if (((int)uVar1 < 100) &&
               (uVar1 = thunk_FUN_0041f150(uStack_118,uStack_114), (int)uVar1 < 100)) {
              thunk_FUN_0041f4a0(uStack_118,uStack_114,(short)DAT_00433a6c,1);
              uVar1 = DAT_00433a6c;
            }
            else {
              thunk_FUN_0041f4a0(uStack_118,uStack_114,(short)DAT_00433a6c + 100,1);
              uVar1 = DAT_00433a6c + 100;
            }
LAB_00406d63:
            thunk_FUN_0041f4a0(uStack_118,uStack_114,(short)uVar1,0);
          }
          uStack_118 = uStack_118 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      uStack_114 = uStack_114 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  iVar4 = 0;
  do {
    thunk_FUN_0040d940(iVar4,(int *)&uStack_118,(int *)&uStack_114);
    if (uStack_118 != 0xffffffff) {
      _sprintf(acStack_100,s_Painting_Zone__d_00434598,iVar4 + 1);
      thunk_FUN_0041e120(acStack_100);
      thunk_FUN_0041ea60(iVar4);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x50);
  thunk_FUN_0041e120(s_Ready__00434590);
  InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
  return;
}


