/*
 * Program: I76EDIT.EXE
 * Function: doexit
 * Entry: 00423420
 * Signature: undefined __cdecl doexit(UINT param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _doexit
   
   Library: Visual Studio 1998 Release */

void __cdecl doexit(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  UINT uExitCode;
  
  if (DAT_00437b2c == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_00437b28 = 1;
  DAT_00437b24 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_01643868 != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(DAT_01643854 + -4), DAT_01643868 <= puVar1)) {
      do {
        if ((code *)*puVar1 != (code *)0x0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (DAT_01643868 <= puVar1);
    }
    __initterm((undefined4 *)&DAT_00433514,(undefined4 *)&DAT_0043371c);
  }
  __initterm((undefined4 *)&DAT_00433820,(undefined4 *)&DAT_00433924);
  if (param_3 == 0) {
    DAT_00437b2c = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_1);
  }
  return;
}


