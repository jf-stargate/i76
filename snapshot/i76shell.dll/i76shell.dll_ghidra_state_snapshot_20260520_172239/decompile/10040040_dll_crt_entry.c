/*
 * Program: i76shell.dll
 * Function: dll_crt_entry
 * Entry: 10040040
 * Signature: int __stdcall dll_crt_entry(HMODULE param_1, int param_2, undefined4 param_3)
 */


/* i76shell first-pass rename
   old_name: entry
   suggested_name: dll_crt_entry
   basis: DLL/CRT entry point. */

int dll_crt_entry(HMODULE param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 1;
  if ((param_2 == 0) && (DAT_100f60c0 == 0)) {
    return 0;
  }
  if ((param_2 != 1) && (param_2 != 2)) {
LAB_1004009e:
    iVar1 = FUN_10040100(param_1,param_2);
    if ((param_2 == 1) && (iVar1 == 0)) {
      FUN_1003ff70(param_1,0);
    }
    if ((param_2 == 0) || (param_2 == 3)) {
      iVar2 = FUN_1003ff70(param_1,param_2);
      if (iVar2 == 0) {
        iVar1 = 0;
      }
      if ((iVar1 != 0) && (DAT_100f7040 != (code *)0x0)) {
        iVar1 = (*DAT_100f7040)(param_1,param_2,param_3);
      }
    }
    return iVar1;
  }
  if (DAT_100f7040 != (code *)0x0) {
    iVar1 = (*DAT_100f7040)(param_1,param_2,param_3);
  }
  if (iVar1 != 0) {
    iVar1 = FUN_1003ff70(param_1,param_2);
    if (iVar1 != 0) goto LAB_1004009e;
  }
  return 0;
}


