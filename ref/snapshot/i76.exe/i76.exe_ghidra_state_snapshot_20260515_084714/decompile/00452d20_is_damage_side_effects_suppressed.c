/*
 * Program: i76.exe
 * Function: is_damage_side_effects_suppressed
 * Entry: 00452d20
 * Signature: undefined4 __stdcall is_damage_side_effects_suppressed(void)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Tiny predicate returning global
   damage/effect side-effect suppression state. */

undefined4 is_damage_side_effects_suppressed(void)

{
  return g_damage_side_effects_suppressed;
}


