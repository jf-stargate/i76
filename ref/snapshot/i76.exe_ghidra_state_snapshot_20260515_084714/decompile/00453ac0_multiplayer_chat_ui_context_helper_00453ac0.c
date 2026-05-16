/*
 * Program: i76.exe
 * Function: multiplayer_chat_ui_context_helper_00453ac0
 * Entry: 00453ac0
 * Signature: undefined __cdecl multiplayer_chat_ui_context_helper_00453ac0(int param_1, int param_2)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_chat_ui_helper_00453ac0. Remove
   duplicated multiplayer wording from readability label. */

void __cdecl multiplayer_chat_ui_context_helper_00453ac0(int param_1,int param_2)

{
  int iVar1;
  
  if ((-1 < param_2) && (-1 < param_1)) {
    if (DAT_00541040 < param_1) {
      DAT_00541040 = param_1;
    }
    DAT_00541048 = param_2;
    iVar1 = multiplayer_chat_ui_context_helper_00452df0();
    if (iVar1 != 0) {
      DAT_00541054 = 1;
    }
  }
  return;
}


