/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_00455490
 * Entry: 00455490
 * Signature: undefined __stdcall multiplayer_player_table_context_helper_00455490(void)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_00455490.
   Remove duplicated multiplayer wording from readability label. */

void multiplayer_player_table_context_helper_00455490(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  
  iVar1 = multiplayer_chat_ui_context_helper_00452df0();
  puVar4 = &DAT_0054108c;
  do {
    if ((short)puVar4[-7] != 0) {
      iVar2 = multiplayer_chat_ui_context_helper_00452e10();
      if (iVar2 == 0) {
        uVar3 = puVar4[9];
      }
      else {
        uVar3 = multiplayer_network_scoreboard_table_helper_00452930
                          (*puVar4 >> 0x10 & 7,(short *)0x0,(short *)0x0);
      }
      multiplayer_chat_ui_context_helper_00453ac0(uVar3,iVar1);
    }
    puVar4 = puVar4 + 0x12;
  } while ((int)puVar4 < 0x54150c);
  return;
}


