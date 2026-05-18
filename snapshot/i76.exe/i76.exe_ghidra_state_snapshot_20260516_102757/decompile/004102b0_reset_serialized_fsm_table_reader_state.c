/*
 * Program: i76.exe
 * Function: reset_serialized_fsm_table_reader_state
 * Entry: 004102b0
 * Signature: undefined __stdcall reset_serialized_fsm_table_reader_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Resets the serialized FSM/AI table reader cursor and
   backing pointer globals. */

void reset_serialized_fsm_table_reader_state(void)

{
  DAT_005244d4 = 0;
  DAT_005244d0 = 0;
  _DAT_005244cc = 0;
  return;
}


