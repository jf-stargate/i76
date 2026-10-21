/*
 * Program: i76.exe
 * Function: vehicle_damage_system_context_helper_00465350
 * Entry: 00465350
 * Signature: bool __cdecl vehicle_damage_system_context_helper_00465350(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: vehicle damage system context helper
   based on prior focused closure context. */

bool __cdecl vehicle_damage_system_context_helper_00465350(int param_1)

{
  int iVar1;
  
  iVar1 = get_world_object_runtime_activity_state(param_1,25.0);
  return iVar1 == 2;
}


