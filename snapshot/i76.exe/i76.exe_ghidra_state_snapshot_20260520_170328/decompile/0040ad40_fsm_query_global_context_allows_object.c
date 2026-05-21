/*
 * Program: i76.exe
 * Function: fsm_query_global_context_allows_object
 * Entry: 0040ad40
 * Signature: bool __cdecl fsm_query_global_context_allows_object(int param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Predicate over global FSM context/override state:
   allows a specific object when locked, otherwise requires no global suppression flag. */

bool __cdecl fsm_query_global_context_allows_object(int param_1)

{
  if (DAT_0051f5b0 != 0) {
    return DAT_0051f5b0 == param_1;
  }
  return DAT_0051f604 == 0;
}


