/*
 * Program: i76.exe
 * Function: append_tire_skid_mark_trail_point
 * Entry: 00444f50
 * Signature: undefined __cdecl append_tire_skid_mark_trail_point(float * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Appends another skid trail
   point/segment when the tire has moved far enough from the previous segment. */

void __cdecl append_tire_skid_mark_trail_point(float *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  
  fVar2 = _DAT_004bd34c;
  iVar6 = -1;
  if (DAT_0052bb98 != (int *)0x0) {
    piVar7 = (int *)0x0;
    piVar5 = DAT_0052bb98;
    do {
      if ((piVar5[2] == param_2) && (iVar6 < piVar5[1])) {
        iVar6 = piVar5[1];
        piVar7 = piVar5;
      }
      piVar5 = (int *)*piVar5;
    } while (piVar5 != DAT_0052bb98);
    if ((piVar7 != (int *)0x0) && (iVar6 = piVar7[4], iVar6 < 0x1f)) {
      fVar3 = *param_1 - (float)piVar7[iVar6 * 6 + -1];
      fVar1 = param_1[2] - (float)piVar7[iVar6 * 6 + 1];
      fVar4 = SQRT(fVar1 * fVar1 + fVar3 * fVar3);
      if (_DAT_004bd34c <= fVar4) {
        piVar7[iVar6 * 6 + 5] = (int)*param_1;
        fVar2 = fVar2 / fVar4;
        piVar7[iVar6 * 6 + 6] = (int)param_1[1];
        piVar7[iVar6 * 6 + 7] = (int)param_1[2];
        fVar1 = fVar1 * fVar2;
        fVar3 = fVar3 * fVar2;
        piVar7[iVar6 * 6 + 8] = (int)(*param_1 + fVar1);
        piVar7[iVar6 * 6 + 10] = (int)(param_1[2] - fVar3);
        piVar7[iVar6 * 6 + 9] = (int)param_1[1];
        if (iVar6 == 1) {
          piVar7[9] = piVar7[6];
          piVar7[8] = (int)((float)piVar7[5] + fVar1);
          piVar7[10] = (int)((float)piVar7[7] - fVar3);
        }
        piVar7[4] = piVar7[4] + 1;
        return;
      }
    }
  }
  return;
}


