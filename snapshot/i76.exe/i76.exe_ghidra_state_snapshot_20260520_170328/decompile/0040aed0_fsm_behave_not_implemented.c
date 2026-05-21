/*
 * Program: i76.exe
 * Function: fsm_behave_not_implemented
 * Entry: 0040aed0
 * Signature: undefined __stdcall fsm_behave_not_implemented(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: FSM: behave is not implimented */

void fsm_behave_not_implemented(void)

{
  if (DAT_004c2aa0 != 0) {
    report_error();
    DAT_004c2aa0 = 0;
  }
  return;
}


