/*
 * Program: I76EDIT.EXE
 * Function: get_int64_arg
 * Entry: 00424ed0
 * Signature: undefined8 __cdecl get_int64_arg(int * param_1)
 */


/* Library Function - Single Match
    _get_int64_arg
   
   Library: Visual Studio 1998 Release */

undefined8 __cdecl get_int64_arg(int *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}


