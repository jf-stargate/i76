/*
 * Program: i76.exe
 * Function: set_tire_child_speed_scalar
 * Entry: 0046daf0
 * Signature: undefined __cdecl set_tire_child_speed_scalar(int param_1, undefined4 param_2)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Tiny setter storing
   vehicle speed/contact scalar into tire child runtime state. */

void __cdecl set_tire_child_speed_scalar(int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x20) = param_2;
  return;
}


