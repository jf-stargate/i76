/*
 * Program: i76.exe
 * Function: initialize_fixedstep_accumulator_interval
 * Entry: 0049cbe0
 * Signature: undefined __cdecl initialize_fixedstep_accumulator_interval(float * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Initializes the
   accumulator interval for vehicle runtime +0x444 with constant 0.05 in the class frame callback.
    */

void __cdecl initialize_fixedstep_accumulator_interval(float *param_1,float param_2)

{
  float fVar1;
  
  if (_DAT_004be9b8 < param_2) {
    fVar1 = _DAT_004be9a4 / param_2;
    param_1[2] = 0.0;
    param_1[1] = 0.0;
    *param_1 = fVar1;
    return;
  }
  *param_1 = _DAT_004be9a8;
  param_1[2] = 0.0;
  param_1[1] = 0.0;
  return;
}


