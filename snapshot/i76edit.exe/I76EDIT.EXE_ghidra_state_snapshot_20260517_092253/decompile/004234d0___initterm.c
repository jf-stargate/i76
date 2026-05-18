/*
 * Program: I76EDIT.EXE
 * Function: __initterm
 * Entry: 004234d0
 * Signature: undefined __cdecl __initterm(undefined4 * param_1, undefined4 * param_2)
 */


/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 1998 Release */

void __cdecl __initterm(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}


