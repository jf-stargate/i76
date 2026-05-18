/*
 * Program: I76EDIT.EXE
 * Function: __ctrandisp1
 * Entry: 00426a15
 * Signature: undefined __cdecl __ctrandisp1(uint param_1, int param_2)
 */


/* Library Function - Single Match
    __ctrandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp1(uint param_1,int param_2)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __trandisp1(extraout_ECX,extraout_EDX);
  FUN_004268de();
  return;
}


