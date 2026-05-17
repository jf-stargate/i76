/*
 * Program: I76EDIT.EXE
 * Function: __cftog
 * Entry: 00426680
 * Signature: undefined __cdecl __cftog(double * param_1, char * param_2, size_t param_3, int param_4)
 */


/* Library Function - Single Match
    __cftog
   
   Library: Visual Studio 1998 Release */

void __cdecl __cftog(double *param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  STRFLT unaff_EBP;
  bool bVar5;
  
  DAT_0043c15c = (int *)__fltout();
  DAT_0043869c = DAT_0043c15c[1] + -1;
  iVar1 = *DAT_0043c15c;
  __fptostr(param_2 + (iVar1 == 0x2d),param_3,(int)DAT_0043c15c,unaff_EBP);
  DAT_004386a0 = DAT_0043869c < DAT_0043c15c[1] + -1;
  iVar3 = DAT_0043c15c[1] + -1;
  if ((-5 < iVar3) && (iVar3 < (int)param_3)) {
    bVar5 = DAT_0043869c < DAT_0043c15c[1] + -1;
    pcVar2 = param_2 + (iVar1 == 0x2d);
    DAT_0043869c = iVar3;
    if (bVar5) {
      do {
        pcVar4 = pcVar2;
        pcVar2 = pcVar4 + 1;
      } while (*pcVar4 != '\0');
      pcVar4[-1] = '\0';
    }
    __cftof_g(param_1,param_2,param_3);
    return;
  }
  DAT_0043869c = iVar3;
  __cftoe_g(param_1,param_2,param_3,param_4);
  return;
}


