/*
 * Program: I76EDIT.EXE
 * Function: __free_osfhnd
 * Entry: 00428210
 * Signature: int __cdecl __free_osfhnd(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __free_osfhnd
   
   Library: Visual Studio 1998 Release */

int __cdecl __free_osfhnd(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  DWORD nStdHandle;
  
  if ((uint)param_1 < DAT_016424ec) {
    piVar1 = (int *)((int)&DAT_016423b0 + ((int)(param_1 & 0xffffffe7U) >> 3));
    iVar2 = (param_1 & 0x1fU) * 8;
    piVar3 = (int *)(*piVar1 + iVar2);
    if (((*(byte *)(piVar3 + 1) & 1) != 0) && (*piVar3 != -1)) {
      if (DAT_00437e44 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_00428276;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_00428276:
      *(undefined4 *)(*piVar1 + iVar2) = 0xffffffff;
      return 0;
    }
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


