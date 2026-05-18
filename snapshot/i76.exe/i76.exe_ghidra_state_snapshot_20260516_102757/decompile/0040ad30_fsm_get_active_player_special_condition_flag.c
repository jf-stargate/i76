/*
 * Program: i76.exe
 * Function: fsm_get_active_player_special_condition_flag
 * Entry: 0040ad30
 * Signature: undefined4 __stdcall fsm_get_active_player_special_condition_flag(void)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Returns the global active-player special-condition
   flag maintained during the per-frame FSM/vehicle runtime update. */

undefined4 fsm_get_active_player_special_condition_flag(void)

{
  return DAT_0051f5c8;
}


