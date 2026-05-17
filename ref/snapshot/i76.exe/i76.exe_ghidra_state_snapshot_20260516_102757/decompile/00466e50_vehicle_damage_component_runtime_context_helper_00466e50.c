/*
 * Program: i76.exe
 * Function: vehicle_damage_component_runtime_context_helper_00466e50
 * Entry: 00466e50
 * Signature: undefined __cdecl vehicle_damage_component_runtime_context_helper_00466e50(int param_1, uint param_2, undefined4 param_3)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle damage component runtime
   context helper based on adjacent named subsystem context. */

void __cdecl
vehicle_damage_component_runtime_context_helper_00466e50
          (int param_1,uint param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x450) = param_3;
  *(uint *)(param_1 + 0x454) = *(uint *)(param_1 + 0x454) | param_2 | 0x80000000;
  return;
}


