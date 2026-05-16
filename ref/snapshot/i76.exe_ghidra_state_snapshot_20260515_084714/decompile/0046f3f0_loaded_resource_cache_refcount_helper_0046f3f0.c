/*
 * Program: i76.exe
 * Function: loaded_resource_cache_refcount_helper_0046f3f0
 * Entry: 0046f3f0
 * Signature: undefined __cdecl loaded_resource_cache_refcount_helper_0046f3f0(undefined4 * param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache refcount helper
   based on adjacent named subsystem context. */

void __cdecl loaded_resource_cache_refcount_helper_0046f3f0(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((LPVOID)*param_1 != (LPVOID)0x0) {
      release_vehicle_runtime_context((LPVOID)*param_1);
    }
    release_vehicle_runtime_context(param_1);
  }
  return;
}


