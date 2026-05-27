/*
 * Program: i76.exe
 * Function: is_ai_vehicle_not_moving_backward_relative_to_forward
 * Entry: 0041ce30
 * Signature: bool __cdecl is_ai_vehicle_not_moving_backward_relative_to_forward(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Boolean negation wrapper around
   is_ai_vehicle_moving_backward_relative_to_forward. */

bool __cdecl is_ai_vehicle_not_moving_backward_relative_to_forward(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = is_ai_vehicle_moving_backward_relative_to_forward(param_1);
  return (bool)('\x01' - (CONCAT31(extraout_var,bVar1) != 0));
}


