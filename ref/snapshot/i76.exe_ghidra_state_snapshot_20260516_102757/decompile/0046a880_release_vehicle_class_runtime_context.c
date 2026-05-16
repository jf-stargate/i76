/*
 * Program: i76.exe
 * Function: release_vehicle_class_runtime_context
 * Entry: 0046a880
 * Signature: undefined __cdecl release_vehicle_class_runtime_context(LPVOID param_1)
 */


/* [cgpt i76.exe world/runtime table rename v17; confidence=HIGH] Vehicle class-specific release
   callback; delegates to the shared vehicle runtime context cleanup helper. */

void __cdecl release_vehicle_class_runtime_context(LPVOID param_1)

{
  release_vehicle_runtime_context(param_1);
  return;
}


