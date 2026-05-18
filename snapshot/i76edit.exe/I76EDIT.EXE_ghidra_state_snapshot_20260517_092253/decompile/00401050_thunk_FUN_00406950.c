/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00406950
 * Entry: 00401050
 * Signature: undefined __cdecl thunk_FUN_00406950(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00406950(int param_1,int param_2)

{
  uint uVar1;
  LRESULT LVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  uVar6 = param_2 - 4;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  if (DAT_00434434 < 5) {
    iVar7 = 0;
    iVar3 = DAT_00434434;
    do {
      iVar5 = 0;
      uVar4 = param_1 - 4;
      do {
        if (*(int *)(&DAT_00436a40 + ((iVar3 * 9 + iVar7) * 9 + iVar5) * 4) != 0) {
          if ((DAT_0043442c == 0) || (DAT_00434430 == 0)) {
            LVar2 = SendDlgItemMessageA(DAT_01642388,0x424,0xf2,0,0);
            if (LVar2 == 1) {
              _DAT_00434428 = thunk_FUN_0041f200(uVar4,uVar6);
              if (99 < (int)_DAT_00434428) {
                _DAT_00434428 = _DAT_00434428 - 100;
                thunk_FUN_0041f4a0(uVar4,uVar6,(short)_DAT_00434428,1);
              }
              _DAT_00434428 = thunk_FUN_0041f150(uVar4,uVar6);
              if (99 < (int)_DAT_00434428) {
                uVar1 = _DAT_00434428 - 100;
                _DAT_00434428 = uVar1;
                goto LAB_00406aab;
              }
            }
            else {
              _DAT_00434428 = thunk_FUN_0041f200(uVar4,uVar6);
              if ((int)_DAT_00434428 < 100) {
                _DAT_00434428 = _DAT_00434428 + 100;
                thunk_FUN_0041f4a0(uVar4,uVar6,(short)_DAT_00434428,1);
              }
              _DAT_00434428 = thunk_FUN_0041f150(uVar4,uVar6);
              if ((int)_DAT_00434428 < 100) {
                uVar1 = _DAT_00434428 + 100;
                _DAT_00434428 = uVar1;
                goto LAB_00406aab;
              }
            }
          }
          else {
            uVar1 = thunk_FUN_0041f200(uVar4,uVar6);
            if (((int)uVar1 < 100) && (uVar1 = thunk_FUN_0041f150(uVar4,uVar6), (int)uVar1 < 100)) {
              thunk_FUN_0041f4a0(uVar4,uVar6,(short)DAT_00433a6c,1);
              uVar1 = DAT_00433a6c;
            }
            else {
              thunk_FUN_0041f4a0(uVar4,uVar6,(short)DAT_00433a6c + 100,1);
              uVar1 = DAT_00433a6c + 100;
            }
LAB_00406aab:
            thunk_FUN_0041f4a0(uVar4,uVar6,(short)uVar1,0);
          }
          iVar3 = thunk_FUN_00411ba0(uVar4,uVar6,0);
          thunk_FUN_00405a60(iVar3,uVar4,uVar6);
          iVar3 = DAT_00434434;
        }
        uVar4 = uVar4 + 1;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 9);
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 1;
    } while (iVar7 < 9);
    InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
  }
  return;
}


