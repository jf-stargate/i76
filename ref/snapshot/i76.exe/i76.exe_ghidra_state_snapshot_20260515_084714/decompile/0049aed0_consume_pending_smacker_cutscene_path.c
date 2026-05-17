/*
 * Program: i76.exe
 * Function: consume_pending_smacker_cutscene_path
 * Entry: 0049aed0
 * Signature: undefined4 __stdcall consume_pending_smacker_cutscene_path(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Returns pending Smacker cutscene path
   and clears the pending-request global.
   old_name: FUN_0049aed0 */

undefined4 consume_pending_smacker_cutscene_path(void)

{
  undefined4 uVar1;
  
  uVar1 = g_pending_smacker_cutscene_path;
  g_pending_smacker_cutscene_path = 0;
  return uVar1;
}


