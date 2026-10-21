/*
 * Program: i76.exe
 * Function: refresh_damageable_runtime_source_when_suppressed
 * Entry: 0046aa50
 * Signature: undefined __cdecl refresh_damageable_runtime_source_when_suppressed(int param_1)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium] Damageable/traffic class
   callback that caches a source/runtime object when side effects are suppressed. */

void __cdecl refresh_damageable_runtime_source_when_suppressed(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar2 = is_damage_side_effects_suppressed();
  if (iVar2 != 0) {
    iVar2 = network_vehicle_message_context_helper_004566d0(param_1);
    *(int *)(iVar1 + 8) = iVar2;
  }
  return;
}


