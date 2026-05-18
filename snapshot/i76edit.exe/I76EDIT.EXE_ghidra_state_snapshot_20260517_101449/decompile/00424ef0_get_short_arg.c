/*
 * Program: I76EDIT.EXE
 * Function: get_short_arg
 * Entry: 00424ef0
 * Signature: undefined2 __cdecl get_short_arg(undefined4 * param_1)
 */


/* Library Function - Single Match
    _get_short_arg
   
   Library: Visual Studio 1998 Release */

undefined2 __cdecl get_short_arg(undefined4 *param_1)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)*param_1;
  *param_1 = puVar1 + 2;
  return *puVar1;
}


