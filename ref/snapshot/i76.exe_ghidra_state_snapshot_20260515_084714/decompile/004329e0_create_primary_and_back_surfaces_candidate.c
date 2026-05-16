/*
 * Program: i76.exe
 * Function: create_primary_and_back_surfaces_candidate
 * Entry: 004329e0
 * Signature: undefined4 __cdecl create_primary_and_back_surfaces_candidate(undefined4 param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl create_primary_and_back_surfaces_candidate(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  DAT_006080d8 = 0;
  DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x20))(DAT_006080b8,0,0,&param_1,&LAB_00432ae0);
  if ((DAT_006080d8 != 0) && (DAT_005fdc0c == 0)) {
    qsort(&DAT_006080e0,DAT_006080d8,0x10,(_PtFuncCompare *)&LAB_00432bc0);
    iVar2 = 0;
    DAT_006080dc = 0;
    if (0 < DAT_006080d8) {
      piVar1 = &DAT_006080e4;
      do {
        if (((piVar1[-1] == 0x280) && (*piVar1 == 0x1e0)) && (piVar1[1] == 0x10)) {
          iVar3 = iVar2;
          DAT_006080dc = iVar2;
        }
        iVar2 = iVar2 + 1;
        piVar1 = piVar1 + 4;
      } while (iVar2 < DAT_006080d8);
    }
    DAT_00608400 = (&DAT_006080e0)[iVar3 * 4];
    DAT_00608404 = (&DAT_006080e4)[iVar3 * 4];
    DAT_00608408 = (&DAT_006080e8)[iVar3 * 4];
    _DAT_0060840c = (&DAT_006080ec)[iVar3 * 4];
    return 1;
  }
  directdraw_error_to_string(DAT_005fdc0c);
  set_directdraw_error_message(s_EnumDisplayModes_failed___s_004f0d68);
  DAT_006080d8 = 0;
  return 0;
}


