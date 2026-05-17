/*
 * Program: I76EDIT.EXE
 * Function: x64toa
 * Entry: 0042d680
 * Signature: undefined __stdcall x64toa(undefined8 param_1, char * param_2, uint param_3, int param_4)
 */


/* Library Function - Single Match
    _x64toa@20
   
   Library: Visual Studio 1998 Release
   __stdcall x64toa,20 */

void x64toa(undefined8 param_1,char *param_2,uint param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  pcVar2 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    param_2 = param_2 + 1;
    pcVar2 = param_2;
  }
  do {
    pcVar3 = pcVar2;
    uVar5 = __aullrem((uint)param_1,param_1._4_4_,param_3,0);
    uVar6 = __aulldiv((uint)param_1,param_1._4_4_,param_3,0);
    if ((uint)uVar5 < 10) {
      cVar1 = (char)uVar5 + '0';
    }
    else {
      cVar1 = (char)uVar5 + 'W';
    }
    *pcVar3 = cVar1;
    pcVar2 = pcVar3 + 1;
    param_1._4_4_ = (uint)((ulonglong)uVar6 >> 0x20);
    bVar4 = param_1._4_4_ != 0;
    param_1 = uVar6;
  } while ((bVar4) || (param_1._0_4_ = (uint)uVar6, bVar4 = (uint)param_1 != 0, bVar4));
  *pcVar2 = '\0';
  do {
    cVar1 = *pcVar3;
    *pcVar3 = *param_2;
    pcVar3 = pcVar3 + -1;
    *param_2 = cVar1;
    param_2 = param_2 + 1;
  } while (param_2 < pcVar3);
  return;
}


