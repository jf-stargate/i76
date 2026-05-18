/*
 * Program: i76.exe
 * Function: set_damage_side_effects_suppressed
 * Entry: 00452d30
 * Signature: undefined __cdecl set_damage_side_effects_suppressed(undefined4 param_1)
 */


/* cgpt rename v2: Setter for g_damage_side_effects_suppressed. */

void __cdecl set_damage_side_effects_suppressed(undefined4 param_1)

{
  g_damage_side_effects_suppressed = param_1;
  return;
}


