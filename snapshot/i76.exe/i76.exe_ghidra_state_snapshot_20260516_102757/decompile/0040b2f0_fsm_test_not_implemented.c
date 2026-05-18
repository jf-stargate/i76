/*
 * Program: i76.exe
 * Function: fsm_test_not_implemented
 * Entry: 0040b2f0
 * Signature: undefined4 __stdcall fsm_test_not_implemented(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: FSM:test is not implimented */

undefined4 fsm_test_not_implemented(void)

{
  if (DAT_004c2aa8 != 0) {
    report_chunk_parse_error();
    DAT_004c2aa8 = 0;
  }
  return 0;
}


