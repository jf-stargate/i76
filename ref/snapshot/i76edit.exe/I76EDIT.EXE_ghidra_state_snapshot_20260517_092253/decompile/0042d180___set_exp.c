/*
 * Program: I76EDIT.EXE
 * Function: __set_exp
 * Entry: 0042d180
 * Signature: float10 __cdecl __set_exp(undefined4 param_1, undefined4 param_2, short param_3)
 */


/* Library Function - Single Match
    __set_exp
   
   Library: Visual Studio 1998 Release */

float10 __cdecl __set_exp(undefined4 param_1,undefined4 param_2,short param_3)

{
  undefined2 uStack_4;
  
  uStack_4 = (undefined2)param_2;
  return (float10)(double)CONCAT26((param_3 + 0x3fe) * 0x10 | param_2._2_2_ & 0x800f,
                                   CONCAT24(uStack_4,param_1));
}


