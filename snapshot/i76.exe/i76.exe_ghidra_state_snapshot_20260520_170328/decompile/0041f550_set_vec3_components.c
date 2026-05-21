/*
 * Program: i76.exe
 * Function: set_vec3_components
 * Entry: 0041f550
 * Signature: undefined __cdecl set_vec3_components(undefined4 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Stores three scalar values into a 3-component vector.
    */

void __cdecl
set_vec3_components(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  return;
}


