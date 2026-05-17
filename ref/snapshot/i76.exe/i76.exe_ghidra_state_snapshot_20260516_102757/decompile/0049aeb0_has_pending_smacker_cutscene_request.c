/*
 * Program: i76.exe
 * Function: has_pending_smacker_cutscene_request
 * Entry: 0049aeb0
 * Signature: bool __stdcall has_pending_smacker_cutscene_request(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Tiny predicate returning whether the
   pending Smacker cutscene path/request global is nonzero.
   old_name: FUN_0049aeb0 */

bool has_pending_smacker_cutscene_request(void)

{
  return g_pending_smacker_cutscene_path != 0;
}


