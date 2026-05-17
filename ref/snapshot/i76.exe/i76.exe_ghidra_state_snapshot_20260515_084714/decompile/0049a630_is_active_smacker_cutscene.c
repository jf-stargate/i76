/*
 * Program: i76.exe
 * Function: is_active_smacker_cutscene
 * Entry: 0049a630
 * Signature: bool __stdcall is_active_smacker_cutscene(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Tiny predicate returning whether the
   active Smacker cutscene handle/global is nonzero.
   old_name: FUN_0049a630 */

bool is_active_smacker_cutscene(void)

{
  return g_active_smacker_cutscene_handle != 0;
}


