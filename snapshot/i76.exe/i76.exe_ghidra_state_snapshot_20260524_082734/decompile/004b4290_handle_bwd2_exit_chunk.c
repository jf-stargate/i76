/*
 * Program: i76.exe
 * Function: handle_bwd2_exit_chunk
 * Entry: 004b4290
 * Signature: bool __cdecl handle_bwd2_exit_chunk(int * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=high] Generic EXIT chunk
   callback used across vehicle/object descriptor tables.
   
   I76 rename v43: handle_bwd2_exit_chunk
   Shared EXIT chunk handler used by descriptor tables. */

bool __cdecl handle_bwd2_exit_chunk(int *param_1,int param_2)

{
  return *param_1 == param_2;
}


