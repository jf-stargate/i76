/*
 * Program: I76EDIT.EXE
 * Function: __cftoe_g
 * Entry: 00426730
 * Signature: undefined __cdecl __cftoe_g(double * param_1, char * param_2, size_t param_3, int param_4)
 */


/* Library Function - Single Match
    __cftoe_g
   
   Library: Visual Studio 1998 Release */

void __cdecl __cftoe_g(double *param_1,char *param_2,size_t param_3,int param_4)

{
  int unaff_retaddr;
  
  DAT_00438698 = 1;
  __cftoe(param_1,param_2,param_3,param_4,unaff_retaddr);
  DAT_00438698 = 0;
  return;
}


