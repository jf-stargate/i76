/*
 * Program: i76.exe
 * Function: notify_remote_player_became_host
 * Entry: 00454960
 * Signature: undefined __cdecl notify_remote_player_became_host(ushort param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: %s is now the host */

void __cdecl notify_remote_player_became_host(ushort param_1,float param_2)

{
  ushort *puVar1;
  char *pcVar2;
  int iVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  uchar local_250 [24];
  char local_238 [80];
  uchar local_1e8 [80];
  undefined4 local_198 [102];
  
  iVar3 = 0;
  puVar1 = &DAT_00541070;
  do {
    if (*puVar1 == param_1) break;
    puVar1 = puVar1 + 0x24;
    iVar3 = iVar3 + 1;
  } while ((int)puVar1 < 0x5414f0);
  if (iVar3 == 0x10) {
    iVar3 = -1;
  }
  if (iVar3 != -1) {
    if ((&DAT_005410a0)[iVar3 * 0x12] != -0x40800000) {
      param_2 = param_2 * _DAT_004bdf70 - (float)(&DAT_005410a0)[iVar3 * 0x12] * _DAT_004bdf74;
    }
    (&DAT_005410a0)[iVar3 * 0x12] = param_2;
    if ((DAT_00541064 == 0) || (param_1 < DAT_00541064)) {
      if (DAT_00541064 == DAT_00541028) {
        pcVar2 = local_238;
        for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
          pcVar2[0] = '\0';
          pcVar2[1] = '\0';
          pcVar2[2] = '\0';
          pcVar2[3] = '\0';
          pcVar2 = pcVar2 + 4;
        }
        dpGetPlayerName(DAT_00541024,DAT_00541028,local_238,0x50);
        dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_01,DAT_00541028),2,0,0,0);
        dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),3,0,0,0);
      }
      DAT_00541064 = param_1;
      if (param_1 == DAT_00541028) {
        pcVar2 = local_238;
        for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
          pcVar2[0] = '\0';
          pcVar2[1] = '\0';
          pcVar2[2] = '\0';
          pcVar2[3] = '\0';
          pcVar2 = pcVar2 + 4;
        }
        dpGetPlayerName(DAT_00541024,DAT_00541028,local_238,0x50);
        copy_shell_session_text_block(local_238);
        dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_00,DAT_00541028),2,local_238,0x1e,0);
        copy_shell_session_descriptor_block(local_198);
        dpSetPlayerData(DAT_00541024,CONCAT22(extraout_var_02,DAT_00541028),3,local_198,0x198,0);
      }
      multiplayer_scoreboard_accumulator_helper_00451900();
      if (param_1 == DAT_00541028) {
        pcVar2 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                       s_____You_are_now_the_host__004f5b38);
        sprintf((char *)local_1e8,pcVar2);
      }
      else {
        iVar3 = 0;
        puVar1 = &DAT_00541070;
        do {
          if (*puVar1 == param_1) break;
          puVar1 = puVar1 + 0x24;
          iVar3 = iVar3 + 1;
        } while ((int)puVar1 < 0x5414f0);
        if (iVar3 == 0x10) {
          iVar3 = -1;
        }
        if ((iVar3 != -1) && (&stack0x00000000 != (undefined1 *)0x250)) {
          _mbsnbcpy(local_250,&DAT_00541072 + iVar3 * 0x48,0x18);
        }
        pcVar2 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                       s______s_is_now_the_host__004f5b20,local_250);
        sprintf((char *)local_1e8,pcVar2);
      }
      draw_multiplayer_chat_message(0,local_1e8);
    }
  }
  return;
}


