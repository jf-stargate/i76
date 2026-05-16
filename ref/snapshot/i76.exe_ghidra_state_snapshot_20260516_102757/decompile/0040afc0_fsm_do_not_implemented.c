/*
 * Program: i76.exe
 * Function: fsm_do_not_implemented
 * Entry: 0040afc0
 * Signature: undefined __stdcall fsm_do_not_implemented(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: FSM: do is not implimented */

void fsm_do_not_implemented(void)

{
  if (DAT_004c2aa4 != 0) {
    report_chunk_parse_error();
    DAT_004c2aa4 = 0;
  }
  return;
}


