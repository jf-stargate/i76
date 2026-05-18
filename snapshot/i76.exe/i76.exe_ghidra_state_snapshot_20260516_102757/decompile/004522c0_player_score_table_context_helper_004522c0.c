/*
 * Program: i76.exe
 * Function: player_score_table_context_helper_004522c0
 * Entry: 004522c0
 * Signature: undefined __cdecl player_score_table_context_helper_004522c0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: player score table context helper
   based on prior focused closure context. */

void __cdecl player_score_table_context_helper_004522c0(int param_1)

{
  int iVar1;
  
  iVar1 = is_damage_side_effects_suppressed();
  if ((iVar1 != 0) && (DAT_00540fec != param_1)) {
    if (param_1 != 0) {
      _DAT_00540fe8 = 1;
      DAT_00540da0 = 0;
      multiplayer_chat_ui_context_helper_00453ef0(0);
      set_text_widget_visible_flag(DAT_00609324,1);
      _DAT_00540fe8 = 1;
      DAT_00540fec = param_1;
      return;
    }
    _DAT_00540fe8 = 0;
    DAT_00540da0 = 0;
    multiplayer_chat_ui_context_helper_00453ef0(1);
    set_text_widget_visible_flag(DAT_00609324,0);
    _DAT_00540fe8 = 0;
    DAT_00540fec = param_1;
  }
  return;
}


