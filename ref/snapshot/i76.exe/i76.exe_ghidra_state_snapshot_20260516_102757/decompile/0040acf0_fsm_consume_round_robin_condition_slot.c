/*
 * Program: i76.exe
 * Function: fsm_consume_round_robin_condition_slot
 * Entry: 0040acf0
 * Signature: undefined4 __stdcall fsm_consume_round_robin_condition_slot(void)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM predicate helper: advances round-robin condition
   counters and returns true once when the current scan slot is reached. */

undefined4 fsm_consume_round_robin_condition_slot(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((DAT_0051f5cc == 0) && (DAT_0051f5b8 == DAT_0051f5bc)) {
    DAT_0051f5bc = DAT_0051f5bc + 1;
    uVar1 = 1;
    DAT_0051f5cc = 1;
  }
  DAT_0051f5b8 = DAT_0051f5b8 + 1;
  return uVar1;
}


