/*
 * Program: I76EDIT.EXE
 * Function: __ctrandisp2
 * Entry: 004268a4
 * Signature: undefined __cdecl __ctrandisp2(uint param_1, int param_2, uint param_3, int param_4)
 */


/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp2(uint param_1,int param_2,uint param_3,int param_4)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2(extraout_ECX,extraout_EDX);
  FUN_004268de();
  return;
}


