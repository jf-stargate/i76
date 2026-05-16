/*
 * Program: i76.exe
 * Function: point_in_polygon_xz
 * Entry: 0043f050
 * Signature: undefined4 __cdecl point_in_polygon_xz(int * param_1, int param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Point-in-polygon test over X/Z
   coordinates for indexed polygon vertex data. */

undefined4 __cdecl point_in_polygon_xz(int *param_1,int param_2,float param_3,float param_4)

{
  float *pfVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  float fVar5;
  uint uVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  bool bVar11;
  
  uVar6 = 0;
  iVar2 = *param_1;
  iVar8 = iVar2 + -1;
  bVar3 = false;
  bVar4 = false;
  if (iVar2 != 0) {
    piVar10 = (int *)(param_1[5] + iVar8 * 4);
    iVar9 = iVar8;
    do {
      if (param_3 < *(float *)(param_2 + *piVar10 * 0xc)) {
        uVar6 = uVar6 | 2;
      }
      else {
        uVar6 = uVar6 | 1;
      }
      if (param_4 < *(float *)(param_2 + *piVar10 * 0xc + 8)) {
        uVar6 = uVar6 | 8;
      }
      else {
        uVar6 = uVar6 | 4;
      }
      if (uVar6 == 0xf) goto LAB_0043f0c6;
      piVar10 = piVar10 + -1;
      bVar11 = iVar9 != 0;
      iVar9 = iVar9 + -1;
    } while (bVar11);
  }
  if (uVar6 == 0xf) {
LAB_0043f0c6:
    if (iVar2 != 0) {
      piVar10 = (int *)param_1[5] + iVar8;
      pfVar7 = (float *)(param_2 + *(int *)param_1[5] * 0xc);
      do {
        pfVar1 = (float *)(param_2 + *piVar10 * 0xc);
        if (((param_4 <= *(float *)(param_2 + 8 + *piVar10 * 0xc)) || (param_4 <= pfVar7[2])) &&
           ((pfVar1[2] <= param_4 || (pfVar7[2] <= param_4)))) {
          if ((pfVar1[2] == param_4) && (pfVar7[2] == param_4)) {
            if ((*pfVar1 < param_3) && (*pfVar7 < param_3)) {
              return 0;
            }
            if (*pfVar1 <= param_3) {
              return 1;
            }
            if (param_3 < *pfVar7) {
              return 0;
            }
            return 1;
          }
          if (pfVar1[2] != param_4) {
            if ((param_3 <= *pfVar1) || (param_3 <= *pfVar7)) {
              if ((*pfVar1 <= param_3) || (*pfVar7 <= param_3)) {
                fVar5 = (((*pfVar7 - *pfVar1) * (param_4 - pfVar1[2])) / (pfVar7[2] - pfVar1[2]) +
                        *pfVar1) - param_3;
                if (fVar5 < _DAT_004bd234) {
                  if (bVar3) {
                    return 0;
                  }
                  if (bVar4) {
                    return 1;
                  }
                  bVar3 = true;
                  goto LAB_0043f243;
                }
                if (fVar5 <= _DAT_004bd234) {
                  return 1;
                }
              }
              if (bVar4) {
                return 0;
              }
              if (bVar3) {
                return 1;
              }
              bVar4 = true;
            }
            else {
              if (bVar3) {
                return 0;
              }
              if (bVar4) {
                return 1;
              }
              bVar3 = true;
            }
          }
        }
LAB_0043f243:
        piVar10 = piVar10 + -1;
        bVar11 = iVar8 == 0;
        pfVar7 = pfVar1;
        iVar8 = iVar8 + -1;
        if (bVar11) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}


