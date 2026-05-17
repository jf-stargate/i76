/*
 * Program: i76.exe
 * Function: path_records_share_same_route_object
 * Entry: 00415b00
 * Signature: undefined4 __cdecl path_records_share_same_route_object(int * param_1, int * param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Returns true when two path records are non-null and
   refer to the same route/path object. */

undefined4 __cdecl path_records_share_same_route_object(int *param_1,int *param_2)

{
  if (((param_1 != (int *)0x0) && (param_2 != (int *)0x0)) && (*param_1 == *param_2)) {
    return 1;
  }
  return 0;
}


