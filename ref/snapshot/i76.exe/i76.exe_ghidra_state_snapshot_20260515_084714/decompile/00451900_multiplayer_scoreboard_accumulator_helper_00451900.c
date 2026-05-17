/*
 * Program: i76.exe
 * Function: multiplayer_scoreboard_accumulator_helper_00451900
 * Entry: 00451900
 * Signature: undefined __stdcall multiplayer_scoreboard_accumulator_helper_00451900(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer scoreboard accumulator
   helper based on prior focused closure context. */

void multiplayer_scoreboard_accumulator_helper_00451900(void)

{
  short sVar1;
  
  if (DAT_00540d8c != 0) {
    sVar1 = get_multiplayer_message_source_player_id();
    if (DAT_00540d88 != sVar1) {
      if (DAT_00540d90 == 0) {
        fsm_or_mission_logic_helper_a(0,0,0);
        return;
      }
      fsm_or_mission_logic_helper_a(0,0,0x80000000);
    }
  }
  return;
}


