/*
 * Program: i76.exe
 * Function: resolve_discrete_input_channel
 * Entry: 0044c390
 * Signature: int __cdecl resolve_discrete_input_channel(int param_1, char * param_2)
 */


/* i76 second-pass rename
   old_name: FUN_0044c390
   suggested_name: resolve_discrete_input_channel
   basis: Reports missing discrete input channel/device from input.map. */

int __cdecl resolve_discrete_input_channel(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  
  if (*(int *)__mb_cur_max_exref < 2) {
    uVar1 = *(byte *)(*(int *)_pctype_exref + *param_2 * 2) & 4;
  }
  else {
    uVar1 = _isctype((int)*param_2,4);
  }
  if (uVar1 == 0) {
    if (param_1 != -1) {
      iVar2 = param_1 * 0x74;
      if (*(int *)(&DAT_005363ec + iVar2) == 0) {
        report_error();
        return -1;
      }
      iVar5 = 0;
      if (0 < *(int *)(&DAT_005363dc + iVar2)) {
        do {
          pcVar4 = *(char **)(*(int *)(&DAT_005363ec + iVar2) + iVar5 * 4);
          if ((pcVar4 != (char *)0x0) && (iVar3 = _stricmp(pcVar4,param_2), iVar3 == 0)) {
            return iVar5;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < *(int *)(&DAT_005363dc + iVar2));
      }
      pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s_The___s__input_channel_on_the____004f48a0,param_2,
                                     &DAT_0053638c + iVar2);
      sprintf(&DAT_00535f80,pcVar4);
      release_and_show_mouse_cursor();
      report_error();
    }
    return -1;
  }
  iVar2 = atoi(param_2);
  return iVar2;
}


