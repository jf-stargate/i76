/*
 * Program: i76.exe
 * Function: broadcast_host_migration_notice
 * Entry: 00454c10
 * Signature: undefined __cdecl broadcast_host_migration_notice(short param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: host migration notices */

void __cdecl broadcast_host_migration_notice(short param_1)

{
  char *pcVar1;
  short *psVar2;
  int iVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  uchar local_250 [24];
  char local_238 [80];
  uchar local_1e8 [80];
  undefined4 local_198 [102];
  
  if (DAT_00541064 == DAT_00541028) {
    pcVar1 = local_238;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      pcVar1 = pcVar1 + 4;
    }
    dpGetPlayerName(DAT_00541024,DAT_00541028,local_238,0x50);
    dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_01,DAT_00541028),2,0,0,0);
    dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),3,0,0,0);
  }
  DAT_00541064 = param_1;
  if (param_1 == DAT_00541028) {
    pcVar1 = local_238;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      pcVar1 = pcVar1 + 4;
    }
    dpGetPlayerName(DAT_00541024,DAT_00541028,local_238,0x50);
    copy_shell_session_text_block(local_238);
    dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_00,DAT_00541028),2,local_238,0x1e,0);
    copy_shell_session_descriptor_block(local_198);
    dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_02,DAT_00541028),3,local_198,0x198,0);
  }
  multiplayer_scoreboard_accumulator_helper_00451900();
  if (param_1 == DAT_00541028) {
    pcVar1 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                   s_____You_are_now_the_host__004f5b38);
    sprintf((char *)local_1e8,pcVar1);
  }
  else {
    iVar3 = 0;
    psVar2 = &DAT_00541070;
    do {
      if (*psVar2 == param_1) break;
      psVar2 = psVar2 + 0x24;
      iVar3 = iVar3 + 1;
    } while ((int)psVar2 < 0x5414f0);
    if (iVar3 == 0x10) {
      iVar3 = -1;
    }
    if ((iVar3 != -1) && (&stack0x00000000 != (undefined1 *)0x250)) {
      _mbsnbcpy(local_250,&DAT_00541072 + iVar3 * 0x48,0x18);
    }
    pcVar1 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                   s______s_is_now_the_host__004f5b20,local_250);
    sprintf((char *)local_1e8,pcVar1);
  }
  draw_multiplayer_chat_message(0,local_1e8);
  return;
}


