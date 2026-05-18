/*
 * Program: i76.exe
 * Function: is_ai_behavior_line_of_sight_not_stale
 * Entry: 0041e720
 * Signature: bool __cdecl is_ai_behavior_line_of_sight_not_stale(int param_1, int param_2)
 */


/* cgpt readability rename v13 set A: Boolean negation wrapper around
   is_ai_behavior_line_of_sight_stale. */

bool __cdecl is_ai_behavior_line_of_sight_not_stale(int param_1,int param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = is_ai_behavior_line_of_sight_stale(param_1,param_2);
  return (bool)('\x01' - (CONCAT31(extraout_var,bVar1) != 0));
}


