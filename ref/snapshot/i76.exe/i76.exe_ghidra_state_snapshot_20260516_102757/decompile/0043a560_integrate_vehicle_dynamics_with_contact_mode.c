/*
 * Program: i76.exe
 * Function: integrate_vehicle_dynamics_with_contact_mode
 * Entry: 0043a560
 * Signature: undefined __cdecl integrate_vehicle_dynamics_with_contact_mode(float * param_1, uint * param_2, float * param_3, float * param_4, float * param_5, float * param_6, float * param_7)
 */


/* cgpt rename v3: Chooses between free vehicle integration and wheel-contact suspension solving
   based on contact/special state. */

void __cdecl
integrate_vehicle_dynamics_with_contact_mode
          (float *param_1,uint *param_2,float *param_3,float *param_4,float *param_5,float *param_6,
          float *param_7)

{
  bool bVar1;
  undefined3 extraout_var;
  float10 fVar2;
  
  fVar2 = get_runtime_update_delta_seconds();
  bVar1 = vehicle_damage_system_context_helper_00465350((int)param_1);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    integrate_vehicle_control_vector_and_orientation
              ((float)param_1,param_2,param_3,param_4,param_6,param_7,(float)fVar2);
    return;
  }
  solve_vehicle_wheel_contact_suspension_solver
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,(float)fVar2);
  return;
}


