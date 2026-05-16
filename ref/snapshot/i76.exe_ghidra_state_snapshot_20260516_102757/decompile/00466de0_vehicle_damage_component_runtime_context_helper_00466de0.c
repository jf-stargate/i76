/*
 * Program: i76.exe
 * Function: vehicle_damage_component_runtime_context_helper_00466de0
 * Entry: 00466de0
 * Signature: uint __cdecl vehicle_damage_component_runtime_context_helper_00466de0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle damage component runtime
   context helper based on adjacent named subsystem context. */

uint __cdecl vehicle_damage_component_runtime_context_helper_00466de0(int param_1)

{
  int iVar1;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if ((iVar1 != 0) && ((*(uint *)(param_1 + 0x10) & 0x200) == 0)) {
    if (*(int *)(param_1 + 0x6c) != 1) {
      return 1;
    }
    return *(uint *)(*(int *)(param_1 + 0x70) + 0x454) & 1;
  }
  return 0;
}


