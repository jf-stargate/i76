/*
 * Program: i76.exe
 * Function: loaded_resource_cache_hash_context_helper_0046f980
 * Entry: 0046f980
 * Signature: undefined __cdecl loaded_resource_cache_hash_context_helper_0046f980(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache hash context
   helper based on adjacent named subsystem context. */

void __cdecl loaded_resource_cache_hash_context_helper_0046f980(int param_1)

{
  int iVar1;
  
  iVar1 = get_root_ancestor_world_object(param_1);
  if (iVar1 == param_1) {
    refresh_damageable_runtime_source_when_suppressed(param_1);
  }
  return;
}


