/*
 * Program: i76.exe
 * Function: get_vehicle_front_right_tire_runtime_component
 * Entry: 00467460
 * Signature: undefined4 __cdecl get_vehicle_front_right_tire_runtime_component(int param_1)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=medium] Vehicle runtime
   component accessor in the tire/contact helper cluster. */

undefined4 __cdecl get_vehicle_front_right_tire_runtime_component(int param_1)

{
                    /* I76 semantic baseline: get_vehicle_front_right_tire_runtime_component
                       Returns front-right tire runtime component. */
  return *(undefined4 *)(*(int *)(param_1 + 0x3a8) + 0x70);
}


