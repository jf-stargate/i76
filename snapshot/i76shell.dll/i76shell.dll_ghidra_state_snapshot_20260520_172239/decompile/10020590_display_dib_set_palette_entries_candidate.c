/*
 * Program: i76shell.dll
 * Function: display_dib_set_palette_entries_candidate
 * Entry: 10020590
 * Signature: undefined4 __cdecl display_dib_set_palette_entries_candidate(int param_1, int param_2, char * param_3)
 */


undefined4 __cdecl display_dib_set_palette_entries_candidate(int param_1,int param_2,char *param_3)

{
  char *pcVar1;
  undefined2 *puVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined *local_4;
  
  if ((((DAT_100d30f4 == 0) || (param_3 == (char *)0x0)) || (param_1 < 0)) ||
     (((0xff < param_1 || (param_2 < 1)) || (0x100 - param_1 < param_2)))) {
    return 0xffffffff;
  }
  if (0 < param_2) {
    pcVar1 = (char *)((int)&DAT_100f6c08 + param_1 * 4 + 1);
    puVar2 = (undefined2 *)((int)&DAT_100533f0 + param_1 * 3);
    do {
      *puVar2 = *(undefined2 *)param_3;
      *(char *)(puVar2 + 1) = param_3[2];
      pcVar1[1] = *param_3 << 2;
      *pcVar1 = param_3[1] << 2;
      pcVar1[-1] = param_3[2] << 2;
      param_2 = param_2 + -1;
      param_3 = param_3 + 3;
      pcVar1 = pcVar1 + 4;
      puVar2 = (undefined2 *)((int)puVar2 + 3);
    } while (param_2 != 0);
  }
  local_c = 0x400;
  local_8 = 0x428;
  local_4 = &DAT_100f6be0;
  DAT_100f63ec = SendMessageA(DAT_100d30d8,0x4a,0,(LPARAM)&local_c);
  if (DAT_100f63ec != 0) {
    log_or_report_shell_ddraw_error_candidate(s_DisplayDibWindowSetFmt_err___d_1004a494);
    return 0xffffffff;
  }
  return 0;
}


