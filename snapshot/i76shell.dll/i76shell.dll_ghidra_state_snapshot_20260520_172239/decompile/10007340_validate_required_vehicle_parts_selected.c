/*
 * Program: i76shell.dll
 * Function: validate_required_vehicle_parts_selected
 * Entry: 10007340
 * Signature: undefined4 __stdcall validate_required_vehicle_parts_selected(void)
 */


undefined4 validate_required_vehicle_parts_selected(void)

{
  char cVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int *piVar9;
  char *pcVar10;
  char local_20 [32];
  
  if (((int *)**(int **)(DAT_1005209c + 8) == (int *)0x0) ||
     (iVar4 = _stricmp((char *)(*(int *)**(int **)(DAT_1005209c + 8) + 0x2e),s_null_10043ab0),
     iVar4 == 0)) {
    FUN_1000b800(0x15,0x77,0x3d,0x2a,0x10);
    return 0;
  }
  piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + 4);
  if ((piVar9 == (int *)0x0) ||
     (iVar4 = _stricmp((char *)(*piVar9 + 0x2e),s_null_10043ab8), iVar4 == 0)) {
    FUN_1000b800(0x16,0x77,0x3d,0x2a,0x10);
    return 0;
  }
  piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + 8);
  if ((piVar9 == (int *)0x0) ||
     (iVar4 = _stricmp((char *)(*piVar9 + 0x2e),s_null_10043ac0), iVar4 == 0)) {
    FUN_1000b800(0x17,0x77,0x3d,0x2a,0x10);
    return 0;
  }
  piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + 0xc);
  if ((piVar9 != (int *)0x0) && (iVar4 = *piVar9, iVar4 != 0)) {
    uVar6 = 0xffffffff;
    pcVar8 = (char *)(iVar4 + 0x3b);
    do {
      pcVar10 = pcVar8;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar10 + -uVar6;
    pcVar10 = local_20;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
  }
  iVar4 = 0xc;
  do {
    piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + iVar4);
    if ((piVar9 == (int *)0x0) ||
       (iVar5 = _stricmp((char *)(*piVar9 + 0x3b),s_null_10043ac8), iVar5 == 0)) goto LAB_100075ff;
    iVar5 = _stricmp((char *)(*piVar9 + 0x3b),local_20);
    if (iVar5 != 0) goto LAB_100075e3;
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0x14);
  piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + 0x14);
  if ((piVar9 != (int *)0x0) && (iVar4 = *piVar9, iVar4 != 0)) {
    uVar6 = 0xffffffff;
    pcVar8 = (char *)(iVar4 + 0x3b);
    do {
      pcVar10 = pcVar8;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar10 + -uVar6;
    pcVar10 = local_20;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
  }
  iVar4 = 0x14;
  while ((piVar9 = *(int **)(*(int *)(DAT_1005209c + 8) + iVar4), piVar9 != (int *)0x0 &&
         (iVar5 = _stricmp((char *)(*piVar9 + 0x3b),s_null_10043ad0), iVar5 != 0))) {
    iVar5 = _stricmp((char *)(*piVar9 + 0x3b),local_20);
    if (iVar5 != 0) {
LAB_100075e3:
      FUN_1000b800(0x1b,0x77,0x3d,0x2a,0x10);
      return 0;
    }
    iVar4 = iVar4 + 4;
    if (0x1b < iVar4) {
      bVar3 = false;
      iVar4 = 0;
      if (0 < *(int *)(DAT_100520a4 + 4)) {
        piVar9 = &DAT_10052018;
        do {
          piVar2 = *(int **)(*(int *)(DAT_100520a4 + 8) + -0x10052018 + (int)piVar9);
          if ((piVar2 != (int *)0x0) && (*(int *)(*piVar2 + 0x22) == 0xb)) {
            if (bVar3) {
              FUN_1000b800(0x1a,0x77,0x3d,0x2a,0x10);
              return 0;
            }
            bVar3 = true;
            if (*(int *)(&DAT_10058a10 + (*(int *)(DAT_100c5ad8 + 0x38) * 0xbb + *piVar9) * 0xc) !=
                1) {
              FUN_1000b800(0x1c,0x77,0x3d,0x2a,0x10);
              return 0;
            }
          }
          iVar4 = iVar4 + 1;
          piVar9 = piVar9 + 1;
        } while (iVar4 < *(int *)(DAT_100520a4 + 4));
      }
      return 1;
    }
  }
LAB_100075ff:
  FUN_1000b800(0x18,0x77,0x3d,0x2a,0x10);
  return 0;
}


