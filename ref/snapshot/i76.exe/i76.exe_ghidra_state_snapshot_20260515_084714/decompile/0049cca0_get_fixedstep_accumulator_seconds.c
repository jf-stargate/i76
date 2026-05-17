/*
 * Program: i76.exe
 * Function: get_fixedstep_accumulator_seconds
 * Entry: 0049cca0
 * Signature: float10 __cdecl get_fixedstep_accumulator_seconds(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Returns accumulated
   seconds from the fixed-step accumulator/timer; compared against the global fixed-step interval.
    */

float10 __cdecl get_fixedstep_accumulator_seconds(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
    return (float10)*(float *)(param_1 + 4);
  }
  return (float10)_DAT_004be998;
}


