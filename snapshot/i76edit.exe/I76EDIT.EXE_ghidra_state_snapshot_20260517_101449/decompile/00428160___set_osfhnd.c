/*
 * Program: I76EDIT.EXE
 * Function: __set_osfhnd
 * Entry: 00428160
 * Signature: int __cdecl __set_osfhnd(int param_1, intptr_t param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 1998 Release */

int __cdecl __set_osfhnd(int param_1,intptr_t param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((uint)param_1 < DAT_016424ec) {
    piVar1 = (int *)((int)&DAT_016423b0 + ((int)(param_1 & 0xffffffe7U) >> 3));
    iVar2 = (param_1 & 0x1fU) * 8;
    if (*(int *)(*piVar1 + iVar2) == -1) {
      if (DAT_00437e44 == 1) {
        if (param_1 == 0) {
          SetStdHandle(0xfffffff6,(HANDLE)param_2);
        }
        else if (param_1 == 1) {
          SetStdHandle(0xfffffff5,(HANDLE)param_2);
        }
        else if (param_1 == 2) {
          SetStdHandle(0xfffffff4,(HANDLE)param_2);
        }
      }
      *(intptr_t *)(*piVar1 + iVar2) = param_2;
      return 0;
    }
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


