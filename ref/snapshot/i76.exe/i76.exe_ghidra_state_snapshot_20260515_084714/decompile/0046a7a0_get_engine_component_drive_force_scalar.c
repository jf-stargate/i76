/*
 * Program: i76.exe
 * Function: get_engine_component_drive_force_scalar
 * Entry: 0046a7a0
 * Signature: float10 __cdecl get_engine_component_drive_force_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Accessor returning
   engine component scalar at runtime/definition offset +0x10, used in drive force calculation. */

float10 __cdecl get_engine_component_drive_force_scalar(int param_1)

{
  return (float10)*(float *)(param_1 + 0x10);
}


