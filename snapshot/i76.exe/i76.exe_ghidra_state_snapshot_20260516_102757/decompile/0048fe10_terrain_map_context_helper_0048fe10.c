/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_0048fe10
 * Entry: 0048fe10
 * Signature: int * __cdecl terrain_map_context_helper_0048fe10(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_0048fe10. Remove
   duplicated terrain wording. */

int * __cdecl terrain_map_context_helper_0048fe10(float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  float *pfVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float local_10;
  float local_c;
  
  iVar3 = *DAT_006543c0;
  if (param_1 < DAT_006543ac) {
    return DAT_006543c0;
  }
  local_c = SUB84((double)((param_1 - DAT_006543ac) + (float)_DAT_004faf18),0);
  if (0x1000 < (int)local_c) {
    return DAT_006543c0;
  }
  if (0x20 < iVar3) {
    return DAT_006543c0;
  }
  iVar8 = DAT_006543c0[3];
  if (iVar8 == 0xc) {
    return DAT_006543c0;
  }
  if (iVar8 == 1) {
    local_10 = (float)DAT_006543c0[7];
    iVar8 = *DAT_006543c0;
    if (1 < iVar8) {
      pfVar5 = (float *)(DAT_006543c0 + 0xd);
      iVar7 = iVar8 + -1;
      do {
        if (_DAT_004be7d4 < *pfVar5 - local_10) {
          local_10 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    fVar9 = (float)DAT_006543c0[7];
    if (1 < iVar8) {
      pfVar5 = (float *)(DAT_006543c0 + 0xd);
      iVar7 = iVar8 + -1;
      do {
        if (*pfVar5 - fVar9 < _DAT_004be7d4) {
          fVar9 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    fVar1 = (float)DAT_006543c0[9];
    if (1 < iVar8) {
      pfVar5 = (float *)(DAT_006543c0 + 0xf);
      iVar8 = iVar8 + -1;
      do {
        if (_DAT_004be7d4 < *pfVar5 - fVar1) {
          fVar1 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    terrain_map_context_helper_00490470(local_c,param_1,fVar1 - DAT_006543ac,fVar9,local_10);
  }
  else if (iVar8 == 0xb) {
    terrain_map_context_helper_00490470
              (local_c,param_1,((float)DAT_006543c0[10] + (float)DAT_006543c0[0xb]) - DAT_006543ac,
               (float)DAT_006543c0[8] - (float)DAT_006543c0[0xb],
               (float)DAT_006543c0[0xb] + (float)DAT_006543c0[8]);
  }
  else if (1 < iVar8) {
    if (iVar3 == 0) {
      fVar9 = -0.0;
      DAT_006543a8 = (undefined4 *)(DAT_00654388 + (int)local_c * 0xc);
      pfVar5 = (float *)*DAT_006543a8;
      if (pfVar5 == (float *)0x0) {
        fVar9 = -NAN;
      }
      else {
        do {
          if (((((float)DAT_006543c0[8] - (float)DAT_006543c0[0xb] < pfVar5[1]) &&
               (*pfVar5 <= (float)DAT_006543c0[8] - (float)DAT_006543c0[0xb])) ||
              (((float)DAT_006543c0[8] + (float)DAT_006543c0[0xb] < pfVar5[1] &&
               (*pfVar5 <= (float)DAT_006543c0[8] + (float)DAT_006543c0[0xb])))) &&
             ((uint)pfVar5[2] < (uint)fVar9)) {
            fVar9 = pfVar5[2];
          }
          pfVar5 = (float *)pfVar5[3];
          _DAT_00654390 = pfVar5;
        } while (pfVar5 != (float *)0x0);
      }
    }
    else {
      fVar1 = (float)DAT_006543c0[7];
      if (1 < iVar3) {
        pfVar5 = (float *)(DAT_006543c0 + 0xd);
        iVar8 = iVar3 + -1;
        do {
          if (_DAT_004be7d4 < *pfVar5 - fVar1) {
            fVar1 = *pfVar5;
          }
          pfVar5 = pfVar5 + 6;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      fVar2 = (float)DAT_006543c0[7];
      if (1 < iVar3) {
        pfVar5 = (float *)(DAT_006543c0 + 0xd);
        iVar8 = iVar3 + -1;
        do {
          if (*pfVar5 - fVar2 < _DAT_004be7d4) {
            fVar2 = *pfVar5;
          }
          pfVar5 = pfVar5 + 6;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      fVar9 = -0.0;
      DAT_006543a8 = (undefined4 *)(DAT_00654388 + (int)local_c * 0xc);
      pfVar5 = (float *)*DAT_006543a8;
      if (pfVar5 == (float *)0x0) {
        fVar9 = -NAN;
      }
      else {
        do {
          if ((((fVar2 < pfVar5[1]) && (*pfVar5 <= fVar2)) ||
              ((fVar1 < pfVar5[1] && (*pfVar5 <= fVar1)))) && ((uint)pfVar5[2] < (uint)fVar9)) {
            fVar9 = pfVar5[2];
          }
          pfVar5 = (float *)pfVar5[3];
        } while (pfVar5 != (float *)0x0);
        _DAT_00654390 = (float *)0x0;
      }
    }
    if (0 < (int)fVar9) {
      local_c = fVar9;
    }
  }
  if ((DAT_006543c0[3] == 5) || (DAT_006543c0[3] == 6)) {
    iVar8 = 0;
    if (0 < DAT_0059c540) {
      puVar6 = &DAT_0059c4a4;
      do {
        if (*(int *)*puVar6 == DAT_006543c0[7]) {
          puVar6 = (undefined4 *)(&DAT_0059c4a0 + iVar8 * 8);
          *(float *)((&DAT_0059c4a4)[iVar8 * 2] + 0xc) = local_c;
          goto LAB_0049015c;
        }
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 2;
      } while (iVar8 < DAT_0059c540);
    }
    puVar6 = (undefined4 *)0x0;
LAB_0049015c:
    piVar4 = DAT_006543c0;
    if ((puVar6 != (undefined4 *)0x0) && (*(int *)*puVar6 != 0)) {
      *(int *)(puVar6[1] + 4) = DAT_006543c0[0xc];
      *(int *)(puVar6[1] + 8) = piVar4[0xd];
      return DAT_006543c0;
    }
  }
  DAT_00654384 = (int *)(DAT_006543b0 + (int)local_c * 0xc);
  iVar8 = *DAT_00654384;
  if (iVar8 == 0) {
    *DAT_00654384 = (int)DAT_006543c0;
    DAT_00654384[1] = (int)DAT_006543c0;
    DAT_006543c0[6] = 0;
  }
  else if (DAT_006543c0[3] == 10) {
    DAT_00654394 = *(int *)(iVar8 + 0x14);
    iVar7 = DAT_00654394;
    if (DAT_00654394 != 0) {
      do {
        DAT_00654394 = iVar7;
        if (3 < *(int *)(DAT_00654394 + 0xc)) {
          DAT_006543c0[4] = (int)param_1;
          *(int **)(iVar8 + 0x14) = DAT_006543c0;
          DAT_006543c0[6] = iVar8;
          DAT_006543c0[5] = DAT_00654394;
          *(int **)(DAT_00654394 + 0x18) = DAT_006543c0;
          DAT_00654384[2] = DAT_00654384[2] + 1;
          piVar4 = DAT_006543c0;
          DAT_006543c0 = (int *)((int)DAT_006543c0 +
                                *(int *)(&DAT_004face0 + DAT_006543c0[3] * 4) + 0x1c);
          return piVar4;
        }
        iVar7 = *(int *)(DAT_00654394 + 0x14);
        iVar8 = DAT_00654394;
      } while (*(int *)(DAT_00654394 + 0x14) != 0);
      DAT_00654394 = 0;
    }
  }
  else {
    if (((*(float *)(iVar8 + 0x10) < param_1) && (3 < *(int *)(iVar8 + 0xc))) &&
       (*(int *)(iVar8 + 0xc) < 10)) {
      DAT_00654394 = iVar8;
      DAT_006543c0[4] = (int)param_1;
      DAT_006543c0[5] = DAT_00654394;
      *(int **)(DAT_00654394 + 0x18) = DAT_006543c0;
      DAT_006543c0[6] = 0;
      *DAT_00654384 = (int)DAT_006543c0;
      if (iVar3 == 0) {
        DAT_006543c0 = (int *)((int)DAT_006543c0 +
                              *(int *)(&DAT_004face0 + DAT_006543c0[3] * 4) + 0x1c);
      }
      else {
        DAT_006543c0 = DAT_006543c0 + iVar3 * 6 + 7;
      }
      DAT_00654384[2] = DAT_00654384[2] + 1;
      return (int *)*DAT_00654384;
    }
    DAT_00654394 = *(int *)(iVar8 + 0x14);
    iVar7 = DAT_00654394;
    if (DAT_00654394 != 0) {
      do {
        DAT_00654394 = iVar7;
        if (((*(float *)(DAT_00654394 + 0x10) < param_1) && (3 < *(int *)(DAT_00654394 + 0xc))) &&
           (*(int *)(DAT_00654394 + 0xc) < 10)) {
          DAT_006543c0[4] = (int)param_1;
          *(int **)(iVar8 + 0x14) = DAT_006543c0;
          DAT_006543c0[6] = iVar8;
          DAT_006543c0[5] = DAT_00654394;
          *(int **)(DAT_00654394 + 0x18) = DAT_006543c0;
          DAT_00654384[2] = DAT_00654384[2] + 1;
          piVar4 = DAT_006543c0;
          if (iVar3 == 0) {
            DAT_006543c0 = (int *)((int)DAT_006543c0 +
                                  *(int *)(&DAT_004face0 + DAT_006543c0[3] * 4) + 0x1c);
            return piVar4;
          }
          DAT_006543c0 = DAT_006543c0 + iVar3 * 6 + 7;
          return piVar4;
        }
        iVar7 = *(int *)(DAT_00654394 + 0x14);
        iVar8 = DAT_00654394;
      } while (*(int *)(DAT_00654394 + 0x14) != 0);
      DAT_00654394 = 0;
    }
  }
  DAT_0065439c = (int *)DAT_00654384[1];
  DAT_00654384[2] = DAT_00654384[2] + 1;
  DAT_006543c0[4] = (int)param_1;
  DAT_00654384[1] = (int)DAT_006543c0;
  *(int **)((int)DAT_0065439c + 0x14) = DAT_006543c0;
  if (iVar3 == 0) {
    DAT_006543c0 = (int *)((int)DAT_006543c0 + *(int *)(&DAT_004face0 + DAT_006543c0[3] * 4) + 0x1c)
    ;
  }
  else {
    DAT_006543c0 = DAT_006543c0 + iVar3 * 6 + 7;
  }
  DAT_0065439c = *(int **)((int)DAT_0065439c + 0x14);
  DAT_0065439c[5] = 0;
  return DAT_0065439c;
}


