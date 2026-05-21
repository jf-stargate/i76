/*
 * Program: i76.exe
 * Function: world_object_texture_animation_stop_helper_0046da60
 * Entry: 0046da60
 * Signature: undefined __cdecl world_object_texture_animation_stop_helper_0046da60(LPVOID param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object texture animation stop
   helper based on adjacent named subsystem context. */

void __cdecl world_object_texture_animation_stop_helper_0046da60(LPVOID param_1)

{
  release_vehicle_runtime_context(*(LPVOID *)((int)param_1 + 0x84));
  if (param_1 != (LPVOID)0x0) {
    release_vehicle_runtime_context(param_1);
  }
  return;
}


