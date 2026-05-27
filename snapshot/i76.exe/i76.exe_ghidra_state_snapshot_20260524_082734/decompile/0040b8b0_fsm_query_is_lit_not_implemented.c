/*
 * Program: i76.exe
 * Function: fsm_query_is_lit_not_implemented
 * Entry: 0040b8b0
 * Signature: undefined4 __stdcall fsm_query_is_lit_not_implemented(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: isLit is not implimented */

undefined4 fsm_query_is_lit_not_implemented(void)

{
  if (DAT_004c2aac != 0) {
    report_error();
    DAT_004c2aac = 0;
  }
  return 0;
}


