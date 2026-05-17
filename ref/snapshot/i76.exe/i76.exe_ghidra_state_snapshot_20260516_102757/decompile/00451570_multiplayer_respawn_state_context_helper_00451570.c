/*
 * Program: i76.exe
 * Function: multiplayer_respawn_state_context_helper_00451570
 * Entry: 00451570
 * Signature: undefined4 __cdecl multiplayer_respawn_state_context_helper_00451570(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: multiplayer respawn state context
   helper based on prior focused closure context. */

undefined4 __cdecl multiplayer_respawn_state_context_helper_00451570(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  iVar2 = is_damage_side_effects_suppressed();
  if ((iVar2 != 0) && (DAT_00540d8c == 0)) {
    if ((param_1 != 0) &&
       (fVar4 = get_network_or_session_runtime_seconds(),
       fVar4 - (float10)_DAT_0053fd7c < (float10)_DAT_004bdf30)) {
      return 0;
    }
    sVar1 = multiplayer_chat_ui_context_helper_00453ab0();
    if (sVar1 == 0) {
      DAT_00540d8c = 1;
      DAT_00540d90 = 0;
      DAT_00540d88 = get_multiplayer_message_source_player_id();
      uVar3 = fsm_or_mission_logic_helper_a(0,0,0);
      return uVar3;
    }
  }
  return 0;
}


