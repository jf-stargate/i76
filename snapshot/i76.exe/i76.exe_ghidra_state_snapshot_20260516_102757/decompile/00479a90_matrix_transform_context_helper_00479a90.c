/*
 * Program: i76.exe
 * Function: matrix_transform_context_helper_00479a90
 * Entry: 00479a90
 * Signature: undefined __cdecl matrix_transform_context_helper_00479a90(int param_1, undefined4 param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: matrix transform context helper based
   on adjacent named subsystem context. */

void __cdecl matrix_transform_context_helper_00479a90(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  DWORD DVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  int local_310;
  char local_300 [768];
  
  if (0 < param_3) {
    iVar4 = ftol();
    local_310 = param_3;
    do {
      DVar5 = GetTickCount();
      iVar7 = 0;
      do {
        cVar1 = *(char *)((int)&DAT_005dcfa8 + iVar7);
        cVar2 = ftol();
        cVar3 = *(char *)((int)&DAT_005dcfa8 + iVar7 + 1);
        local_300[iVar7] = cVar2 + cVar1;
        cVar2 = ftol();
        cVar1 = (&DAT_005dcfaa)[iVar7];
        local_300[iVar7 + 1] = cVar2 + cVar3;
        cVar3 = ftol();
        local_300[iVar7 + 2] = cVar3 + cVar1;
        iVar7 = iVar7 + 3;
      } while (iVar7 < 0x300);
      matrix_rotation_context_helper_004797f0((int)local_300,0,0x100,0);
      (*DAT_005dd2c8)(&DAT_005dcec0,local_300);
      (*DAT_005dd2e0)(&DAT_005dcec0);
      uVar6 = GetTickCount();
      while (uVar6 < DVar5 - iVar4) {
        uVar6 = GetTickCount();
      }
      local_310 = local_310 + -1;
    } while (local_310 != 0);
  }
  iVar4 = 0xc0;
  if (param_1 == 0) {
    puVar8 = (undefined4 *)&DAT_005dcfa8;
    pcVar9 = local_300;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      pcVar9 = pcVar9 + 4;
    }
    matrix_rotation_context_helper_004797f0((int)local_300,0,0x100,0);
  }
  else {
    pcVar9 = local_300;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      pcVar9[0] = '\0';
      pcVar9[1] = '\0';
      pcVar9[2] = '\0';
      pcVar9[3] = '\0';
      pcVar9 = pcVar9 + 4;
    }
  }
  _DAT_0059bb8c = 0;
  return;
}


