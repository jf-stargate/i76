/*
 * Program: i76shell.dll
 * Function: select_shell_display_mode_and_backend
 * Entry: 1000cb40
 * Signature: undefined4 __cdecl select_shell_display_mode_and_backend(int * param_1, int param_2, undefined4 param_3, int param_4, int param_5, BOOL param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
select_shell_display_mode_and_backend
          (int *param_1,int param_2,undefined4 param_3,int param_4,int param_5,BOOL param_6)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == (int *)0xffffffff) {
    param_1 = (int *)PTR_DAT_100442d8;
  }
  else {
    if ((int)param_1 < 0) {
      return 0;
    }
    if (5 < (int)param_1) {
      return 0;
    }
    param_1 = (int *)(&PTR_DAT_100442d8)[(int)param_1];
  }
  DAT_100533e4 = param_2;
  puVar1 = (&PTR_DAT_100442c8)[param_1[1]];
  iVar2 = GetSystemMetrics(0);
  iVar3 = GetSystemMetrics(1);
  DAT_100f6bc0 = 0;
  DAT_100f6bc4 = 0;
  DAT_100f6bc8 = param_4;
  DAT_100f6bcc = param_5;
  if ((param_4 < iVar2) || (param_5 < iVar3)) {
    _DAT_1004ae98 = 0xca0000;
    AdjustWindowRect((LPRECT)&DAT_100f6bc0,0xca0000,param_6);
    DAT_100f6bc8 = DAT_100f6bc8 - DAT_100f6bc0;
    DAT_100f6bcc = DAT_100f6bcc - DAT_100f6bc4;
    DAT_100f6bc4 = (iVar3 - DAT_100f6bcc) / 2;
    DAT_100f6bc0 = (iVar2 - DAT_100f6bc8) / 2;
    DAT_1005370c = *(undefined4 *)(puVar1 + 4);
  }
  else {
    _DAT_1004ae98 = 0x80000000;
    DAT_1005370c = 1;
  }
  if (*(int *)(puVar1 + 4) == 1) {
    GetSystemMetrics(0);
    GetSystemMetrics(1);
  }
  if (DAT_100442f4 == 0) {
    if (((DAT_100533dc != param_1) || (param_4 != DAT_100f700c)) || (param_5 != DAT_100f7010)) {
      FUN_1000d0a0((int)puVar1);
      (*(code *)DAT_100533dc[5])();
    }
  }
  else {
    DAT_100f700c = param_4;
    DAT_100f7010 = param_5;
    FUN_1000d0a0((int)puVar1);
    DAT_100533d8 = puVar1;
  }
  DAT_100f7008 = param_5 * param_4;
  iVar2 = param_1[2];
  DAT_100f700c = param_4;
  DAT_100533dc = param_1;
  DAT_100f7010 = param_5;
  DAT_100533e8 = param_3;
  while( true ) {
    if ((iVar2 == 0) || (iVar2 = (*(code *)DAT_100533dc[4])(param_3,param_4,param_5), iVar2 == 0)) {
      DAT_100442f4 = 0;
      return 1;
    }
    log_or_report_shell_ddraw_error_candidate(s_RefreshMode__d_not_available_100442f8);
    DAT_100533dc[2] = 0;
    if ((DAT_100533e4 == 0) || (*DAT_100533dc == 5)) break;
    DAT_100533dc = (int *)(&PTR_DAT_100442dc)[*DAT_100533dc];
    iVar2 = DAT_100533dc[2];
  }
  return 0;
}


