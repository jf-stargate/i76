/*
 * Program: i76.exe
 * Function: integrate_vertical_motion_with_gravity
 * Entry: 00438630
 * Signature: undefined __cdecl integrate_vertical_motion_with_gravity(float * param_1, float * param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium] Integrates
   position/velocity with a gravity-like Y acceleration term. */

void __cdecl
integrate_vertical_motion_with_gravity(float *param_1,float *param_2,float param_3,float param_4)

{
  float fVar1;
  
  *param_1 = *param_2 * param_4 + *param_1;
  fVar1 = param_4 * param_3 * _DAT_004bd098;
  param_1[2] = param_2[2] * param_4 + param_1[2];
  param_1[1] = (param_2[1] - fVar1) * param_4 + param_1[1];
  param_2[1] = param_4 * param_3 + param_2[1];
  return;
}


