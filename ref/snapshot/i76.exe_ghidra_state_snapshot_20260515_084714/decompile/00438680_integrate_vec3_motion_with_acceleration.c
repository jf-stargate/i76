/*
 * Program: i76.exe
 * Function: integrate_vec3_motion_with_acceleration
 * Entry: 00438680
 * Signature: undefined __cdecl integrate_vec3_motion_with_acceleration(float * param_1, float * param_2, float param_3, float param_4, float param_5, float param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium] Integrates 3D velocity
   and displacement using acceleration vector and timestep. */

void __cdecl
integrate_vec3_motion_with_acceleration
          (float *param_1,float *param_2,float param_3,float param_4,float param_5,float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_4 * param_6 * _DAT_004bd098;
  fVar4 = param_5 * param_6 * _DAT_004bd098;
  *param_1 = (*param_2 - param_6 * param_3 * _DAT_004bd098) * param_6;
  param_1[1] = (fVar1 - fVar3) * param_6;
  param_1[2] = (fVar2 - fVar4) * param_6;
  *param_2 = *param_2 + param_6 * param_3;
  param_2[1] = param_2[1] + param_4 * param_6;
  param_2[2] = param_2[2] + param_5 * param_6;
  return;
}


