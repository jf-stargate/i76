/*
 * Program: i76.exe
 * Function: world_object_has_optional_runtime_flag
 * Entry: 00458bf0
 * Signature: undefined4 __cdecl world_object_has_optional_runtime_flag(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Predicate for optional runtime
   flag used by radial-damage filtering. */

undefined4 __cdecl world_object_has_optional_runtime_flag(int param_1)

{
  if ((param_1 != 0) && ((*(byte *)(param_1 + 0x10) & 0x10) != 0)) {
    return 1;
  }
  return 0;
}


