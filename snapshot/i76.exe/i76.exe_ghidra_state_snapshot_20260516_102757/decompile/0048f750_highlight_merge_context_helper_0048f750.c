/*
 * Program: i76.exe
 * Function: highlight_merge_context_helper_0048f750
 * Entry: 0048f750
 * Signature: undefined __cdecl highlight_merge_context_helper_0048f750(int param_1, int param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: highlight merge context helper based
   on adjacent named subsystem context. */

void __cdecl highlight_merge_context_helper_0048f750(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  if (DAT_006543a0 < DAT_0065438c) {
    iVar3 = *(int *)(param_2 + 0x68);
    while (iVar1 = iVar3, piVar2 = DAT_006543b4, iVar1 != 0) {
      param_2 = iVar1;
      iVar3 = *(int *)(iVar1 + 0x68);
    }
    for (; (piVar4 = (int *)0x0, piVar2 < DAT_006543a0 && (piVar4 = piVar2, *piVar2 != param_2));
        piVar2 = piVar2 + 0x24) {
    }
    if (piVar4 == (int *)0x0) {
      *DAT_006543a0 = param_2;
      DAT_006543a0[1] = 0;
      DAT_006543a0[3] = 1;
      DAT_006543a0[2] = 1000000;
      DAT_006543a0[4] = param_1;
      DAT_006543a0[6] = 0;
      DAT_006543a0[7] = 1000000;
      DAT_006543a0 = DAT_006543a0 + 0x24;
    }
    else if (piVar4[3] != 8) {
      piVar4[(piVar4[3] + 1) * 4] = param_1;
      piVar4[piVar4[3] * 4 + 6] = 0;
      piVar4[piVar4[3] * 4 + 7] = 1000000;
      piVar4[3] = piVar4[3] + 1;
      return;
    }
  }
  return;
}


