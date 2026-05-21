/*
 * Program: i76shell.dll
 * Function: calculate_current_vehicle_config_weight
 * Entry: 10007720
 * Signature: int __stdcall calculate_current_vehicle_config_weight(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int calculate_current_vehicle_config_weight(void)

{
  int *piVar1;
  double dVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar4 = *(int *)(DAT_100d1dac + 4);
  iVar6 = 0;
  if (0 < iVar4) {
    piVar5 = *(int **)(DAT_100d1dac + 8);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1[4] == 3) {
        dVar2 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412a0;
        if (dVar2 <= (double)piVar1[3]) {
          iVar3 = 2;
          if (dVar2 + dVar2 <= (double)piVar1[3]) {
            iVar3 = 1;
          }
        }
        else {
          iVar3 = 3;
        }
        iVar6 = iVar6 + *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar3;
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  iVar4 = *(int *)(DAT_100d1db4 + 4);
  if (0 < iVar4) {
    piVar5 = *(int **)(DAT_100d1db4 + 8);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1[4] == 3) {
        dVar2 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412a0;
        if (dVar2 <= (double)piVar1[3]) {
          iVar3 = 2;
          if (dVar2 + dVar2 <= (double)piVar1[3]) {
            iVar3 = 1;
          }
        }
        else {
          iVar3 = 3;
        }
        iVar6 = iVar6 + *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar3;
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  iVar4 = *(int *)(DAT_100d1db8 + 4);
  if (0 < iVar4) {
    piVar5 = *(int **)(DAT_100d1db8 + 8);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1[4] == 3) {
        dVar2 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412a0;
        if (dVar2 <= (double)piVar1[3]) {
          iVar3 = 2;
          if (dVar2 + dVar2 <= (double)piVar1[3]) {
            iVar3 = 1;
          }
        }
        else {
          iVar3 = 3;
        }
        iVar6 = iVar6 + *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar3;
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  iVar4 = *(int *)(DAT_100d1dbc + 4);
  if (0 < iVar4) {
    piVar5 = *(int **)(DAT_100d1dbc + 8);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1[4] == 3) {
        dVar2 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412a0;
        if (dVar2 <= (double)piVar1[3]) {
          iVar3 = 2;
          if (dVar2 + dVar2 <= (double)piVar1[3]) {
            iVar3 = 1;
          }
        }
        else {
          iVar3 = 3;
        }
        iVar6 = iVar6 + *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar3;
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  iVar4 = *(int *)(DAT_100d1dc0 + 4);
  if (0 < iVar4) {
    piVar5 = *(int **)(DAT_100d1dc0 + 8);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1[4] == 3) {
        dVar2 = (double)*(int *)(*piVar1 + 0x4c) * _DAT_100412a0;
        if (dVar2 <= (double)piVar1[3]) {
          iVar3 = 2;
          if (dVar2 + dVar2 <= (double)piVar1[3]) {
            iVar3 = 1;
          }
        }
        else {
          iVar3 = 3;
        }
        iVar6 = iVar6 + *(int *)(&DAT_10043558 + *(int *)(*piVar1 + 0x1e) * 4) * iVar3;
      }
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return iVar6;
}


