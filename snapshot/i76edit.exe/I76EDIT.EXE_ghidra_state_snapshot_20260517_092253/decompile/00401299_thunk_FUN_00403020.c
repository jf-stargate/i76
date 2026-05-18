/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00403020
 * Entry: 00401299
 * Signature: float10 __cdecl thunk_FUN_00403020(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl thunk_FUN_00403020(float param_1)

{
  return (float10)_DAT_01641ec8 * (float10)param_1 +
         (float10)param_1 * (float10)param_1 * (float10)param_1 * (float10)_DAT_01641ec0 +
         (float10)_DAT_01641ec4 * (float10)param_1 * (float10)param_1 + (float10)_DAT_01641ecc;
}


