/*
 * Program: i76.exe
 * Function: multiplayer_chat_message_queue_helper_00454090
 * Entry: 00454090
 * Signature: undefined __stdcall multiplayer_chat_message_queue_helper_00454090(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: multiplayer chat message queue helper
   based on prior focused closure context. */

void multiplayer_chat_message_queue_helper_00454090(void)

{
  undefined2 *puVar1;
  undefined2 extraout_var;
  int iVar2;
  undefined4 local_208;
  undefined1 local_204 [2];
  undefined1 local_202 [2];
  undefined1 local_200 [512];
  
  puVar1 = &DAT_00541070;
  DAT_00541068 = 0;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 0x24;
  } while ((int)puVar1 < 0x5414f0);
  DAT_00541064 = 0;
  _DAT_0054106c = 0;
  DAT_00541060 = 0;
  dpEnumGroups(DAT_00541024,0,&LAB_004554e0,0,0);
  local_208 = 0x200;
  time((time_t *)0x0);
  while (DAT_00541060 == 0) {
    iVar2 = 3;
    do {
      local_208 = 0x200;
      dpReceive(DAT_00541024,local_204,local_202,0,local_200,&local_208);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    time((time_t *)0x0);
    dpEnumGroups(DAT_00541024,0,&LAB_004554e0,0,0);
  }
  dpEnumPlayers(DAT_00541024,0,multiplayer_prompt_context_helper_00455500,0,0);
  dpEnumGroupPlayers(DAT_00541024,CONCAT22(extraout_var,DAT_00541060),0,
                     multiplayer_prompt_context_helper_00455590,0,1000);
  return;
}


