/*
 * Program: i76.exe
 * Function: normalize_angle_delta_signed_pi
 * Entry: 00417e50
 * Signature: float10 __cdecl normalize_angle_delta_signed_pi(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Normalizes signed angle delta into the [-pi, pi] range.
    */

float10 __cdecl normalize_angle_delta_signed_pi(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)param_2 - (float10)param_1;
  if ((float10)_DAT_004bc8f4 < fVar1) {
    return fVar1 - (float10)_DAT_004bc8f8;
  }
  if (fVar1 < (float10)_DAT_004bc8fc) {
    fVar1 = fVar1 - (float10)_DAT_004bc900;
  }
  return fVar1;
}


