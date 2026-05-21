/*
 * Program: i76.exe
 * Function: get_spawn_location_or_report_missing
 * Entry: 00451030
 * Signature: uint __stdcall get_spawn_location_or_report_missing(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: SpawnLoc_GetLocation - no spawn points */

uint get_spawn_location_or_report_missing(void)

{
  int *piVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  uint local_3c;
  int iStack_24;
  
  if (g_odef_spawn_transform_count == 0) {
    report_error();
  }
  uVar6 = rand();
  uVar6 = uVar6 % g_odef_spawn_transform_count;
  local_3c = 0;
  if (g_odef_spawn_transform_count == 0) {
    return uVar6;
  }
LAB_0045107b:
  iVar9 = 0;
  iVar7 = uVar6 * 0x40;
  if (DAT_0053fd78 < 1) {
    return uVar6;
  }
  piVar8 = &DAT_0053fcb0;
  do {
    piVar1 = (int *)*piVar8;
    if (piVar1 != (int *)0x0) {
      iVar2 = *piVar1;
      dVar3 = *(double *)(&DAT_0053fdb0 + iVar7) - *(double *)(iVar2 + 0x40);
      dVar5 = (double)(float)*(double *)(&DAT_0053fdb8 + iVar7) - *(double *)(iVar2 + 0x48);
      dVar4 = (double)(float)*(double *)(&DAT_0053fdc0 + iVar7) - *(double *)(iVar2 + 0x50);
      if (((uint)((longlong)
                  ((dVar4 * dVar4 + dVar5 * dVar5 + dVar3 * dVar3) -
                  ((double)(float)piVar1[4] - _DAT_004bdf28) *
                  ((double)(float)piVar1[4] - _DAT_004bdf28)) >> 0x3f) & 1) != 0) break;
    }
    iVar9 = iVar9 + 1;
    piVar8 = piVar8 + 1;
    if (DAT_0053fd78 <= iVar9) {
      return uVar6;
    }
  } while( true );
  uVar6 = -(uint)(uVar6 + 1 != g_odef_spawn_transform_count) & uVar6 + 1;
  local_3c = local_3c + 1;
  if (g_odef_spawn_transform_count <= local_3c) {
    return uVar6;
  }
  goto LAB_0045107b;
}


