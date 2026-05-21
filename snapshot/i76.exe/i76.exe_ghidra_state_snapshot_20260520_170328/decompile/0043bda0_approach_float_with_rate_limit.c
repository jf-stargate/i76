/*
 * Program: i76.exe
 * Function: approach_float_with_rate_limit
 * Entry: 0043bda0
 * Signature: float10 __cdecl approach_float_with_rate_limit(float param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=high] Moves one scalar toward a
   target by a rate if the delta exceeds a small threshold. */

float10 __cdecl approach_float_with_rate_limit(float param_1,float param_2,float param_3)

{
  if ((_DAT_004bd148 <= param_3) && (param_3 <= _DAT_004bd1c0)) {
    if (ABS((float10)param_2 - (float10)param_1) < (float10)_DAT_004bd1c8) {
      return (float10)param_2;
    }
    return ((float10)param_2 - (float10)param_1) * (float10)param_3 + (float10)param_1;
  }
  return (float10)param_2;
}


