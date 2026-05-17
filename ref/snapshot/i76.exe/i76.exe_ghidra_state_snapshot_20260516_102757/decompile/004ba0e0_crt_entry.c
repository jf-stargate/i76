/*
 * Program: i76.exe
 * Function: crt_entry
 * Entry: 004ba0e0
 * Signature: undefined __stdcall crt_entry(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe ZFSF rename corrections v14] Restore entrypoint name. v13 accidentally renamed the
   containing function while trying to name an interior LZO helper at 004ba220. */

void crt_entry(void)

{
  undefined4 *puVar1;
  HMODULE pHVar2;
  byte *pbVar3;
  int iVar5;
  char **local_74;
  _startupinfo local_70;
  WPARAM local_6c;
  char **local_68;
  int local_64;
  _STARTUPINFOA local_60;
  undefined1 *local_1c;
  void *pvStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  byte *pbVar4;
  
  puStack_c = &DAT_004beca8;
  puStack_10 = &DAT_004ba0d0;
  pvStack_14 = ExceptionList;
  local_1c = &stack0xffffff78;
  local_8 = 0;
  ExceptionList = &pvStack_14;
  __set_app_type(2);
  _DAT_00669eec = 0xffffffff;
  _DAT_00669ef0 = 0xffffffff;
  puVar1 = (undefined4 *)__p__fmode();
  *puVar1 = DAT_005dbaa8;
  puVar1 = (undefined4 *)__p__commode();
  *puVar1 = DAT_005dbaa4;
  _DAT_00669ef4 = *(undefined4 *)_adjust_fdiv_exref;
  noop_world_object_callback_stub();
  if (DAT_00500f90 == 0) {
    __setusermatherr(shell_cb_4c_display_or_directdraw_helper);
  }
  zfsf_lzo_context_helper_004ba320();
  initterm(&DAT_004c2014,&DAT_004c2018);
  local_70.newmode = DAT_005dbaa0;
  __getmainargs(&local_64,&local_74,&local_68,DAT_005dba9c,&local_70);
  initterm(&DAT_004c2000,&DAT_004c2010);
  pbVar3 = *(byte **)_acmdln_exref;
  if (*pbVar3 == 0x22) {
    do {
      pbVar4 = pbVar3;
      pbVar3 = pbVar4 + 1;
      if (*pbVar3 == 0) break;
    } while (*pbVar3 != 0x22);
    if (*pbVar3 == 0x22) {
      pbVar3 = pbVar4 + 2;
    }
  }
  else {
    for (; 0x20 < *pbVar3; pbVar3 = pbVar3 + 1) {
    }
  }
  for (; (*pbVar3 != 0 && (*pbVar3 < 0x21)); pbVar3 = pbVar3 + 1) {
  }
  local_60.dwFlags = 0;
  GetStartupInfoA(&local_60);
  iVar5 = 0;
  pHVar2 = GetModuleHandleA((LPCSTR)0x0);
  local_6c = winmain_top_level_game_fsm(pHVar2,iVar5,(char *)pbVar3);
                    /* WARNING: Subroutine does not return */
  exit(local_6c);
}


