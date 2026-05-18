/*
 * Program: i76.exe
 * Function: vehicle_contact_physics_scalar_helper_0043bc90
 * Entry: 0043bc90
 * Signature: undefined __cdecl vehicle_contact_physics_scalar_helper_0043bc90(undefined4 * param_1, double param_2, double param_3, double param_4, double param_5, double param_6, double param_7, double param_8)
 */


/* cgpt readability rename set B v14: Readability pass set B: vehicle contact physics scalar helper
   based on prior focused closure context. */

void __cdecl
vehicle_contact_physics_scalar_helper_0043bc90
          (undefined4 *param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8)

{
  int iVar1;
  double *pdVar2;
  
  param_6 = param_6 * param_5 + param_2;
  param_7 = param_7 * param_5 + param_3;
  param_8 = param_8 * param_5 + param_4;
  pdVar2 = &param_6;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *(undefined4 *)pdVar2;
    pdVar2 = (double *)((int)pdVar2 + 4);
    param_1 = param_1 + 1;
  }
  return;
}


