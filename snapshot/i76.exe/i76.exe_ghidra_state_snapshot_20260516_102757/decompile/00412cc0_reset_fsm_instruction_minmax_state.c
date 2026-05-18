/*
 * Program: i76.exe
 * Function: reset_fsm_instruction_minmax_state
 * Entry: 00412cc0
 * Signature: undefined __stdcall reset_fsm_instruction_minmax_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Resets FSM instruction tracking globals to default min/max
   sentinel values. */

void reset_fsm_instruction_minmax_state(void)

{
  DAT_005244dc = 0;
  _DAT_005244e0 = 0x7f7fffff;
  return;
}


