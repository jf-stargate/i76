/*
 * Program: i76.exe
 * Function: test_swept_point_against_effect_target_collision_payload
 * Entry: 0043ebc0
 * Signature: undefined4 __cdecl test_swept_point_against_effect_target_collision_payload(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, int param_7, float * param_8, int * param_9)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Tests a moving point/segment against an
   effect-target collision payload using runtime delta and per-axis polygon tests. */

undefined4 __cdecl
test_swept_point_against_effect_target_collision_payload
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          int param_7,float *param_8,int *param_9)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  bool bVar14;
  float10 fVar15;
  float local_20;
  int local_c;
  int local_8;
  int local_4;
  
  piVar1 = *(int **)(param_7 + 8);
  local_20 = 1e+30;
  do {
    if (piVar1 == (int *)0x0) {
      if (local_20 < _DAT_004bd22c) {
        *param_8 = local_20;
        *param_9 = local_c;
        param_9[1] = local_8;
        param_9[2] = local_4;
        return 1;
      }
      return 0;
    }
    fVar5 = (float)piVar1[1] * param_4 + param_6 * (float)piVar1[3] + param_5 * (float)piVar1[2];
    iVar8 = *(int *)(param_7 + 4);
    if ((fVar5 <= _DAT_004bd230) &&
       (fVar2 = (float)piVar1[1] * param_1 + param_3 * (float)piVar1[3] + param_2 * (float)piVar1[2]
                + (float)piVar1[4], _DAT_004bd234 < fVar2)) {
      fVar5 = -(fVar2 / fVar5);
      fVar15 = get_runtime_update_delta_seconds();
      if ((float10)fVar5 <= fVar15) {
        fVar2 = fVar5 * param_4 + param_1;
        fVar3 = fVar5 * param_5 + param_2;
        fVar4 = fVar5 * param_6 + param_3;
        if (ABS((float)piVar1[2]) <= ABS((float)piVar1[1])) {
          if (ABS((float)piVar1[1]) <= ABS((float)piVar1[3])) goto LAB_0043ef7d;
          iVar10 = *piVar1;
          uVar9 = 0;
          bVar7 = false;
          bVar6 = false;
          iVar12 = iVar10 + -1;
          if (iVar10 != 0) {
            piVar11 = (int *)(piVar1[5] + iVar12 * 4);
            iVar13 = iVar12;
            do {
              if (fVar3 < *(float *)(iVar8 + 4 + *piVar11 * 0xc)) {
                uVar9 = uVar9 | 2;
              }
              else {
                uVar9 = uVar9 | 1;
              }
              if (fVar4 < *(float *)(iVar8 + *piVar11 * 0xc + 8)) {
                uVar9 = uVar9 | 8;
              }
              else {
                uVar9 = uVar9 | 4;
              }
              if (uVar9 == 0xf) break;
              piVar11 = piVar11 + -1;
              bVar14 = iVar13 != 0;
              iVar13 = iVar13 + -1;
            } while (bVar14);
          }
          if (uVar9 == 0xf) {
            if (iVar10 != 0) {
              piVar11 = (int *)piVar1[5] + iVar12;
              iVar10 = iVar8 + *(int *)piVar1[5] * 0xc;
              do {
                iVar13 = iVar8 + *piVar11 * 0xc;
                if (((fVar4 <= *(float *)(iVar8 + 8 + *piVar11 * 0xc)) ||
                    (fVar4 <= *(float *)(iVar10 + 8))) &&
                   ((*(float *)(iVar13 + 8) <= fVar4 || (*(float *)(iVar10 + 8) <= fVar4)))) {
                  if ((*(float *)(iVar13 + 8) == fVar4) && (*(float *)(iVar10 + 8) == fVar4)) {
                    if (((fVar3 <= *(float *)(iVar13 + 4)) || (fVar3 <= *(float *)(iVar10 + 4))) &&
                       ((*(float *)(iVar13 + 4) <= fVar3 || (*(float *)(iVar10 + 4) <= fVar3))))
                    goto LAB_0043ef6e;
                    goto LAB_0043ef77;
                  }
                  if (*(float *)(iVar13 + 8) != fVar4) {
                    if ((fVar3 <= *(float *)(iVar13 + 4)) || (fVar3 <= *(float *)(iVar10 + 4))) {
                      if ((*(float *)(iVar13 + 4) <= fVar3) || (*(float *)(iVar10 + 4) <= fVar3)) {
                        fVar2 = (((fVar4 - *(float *)(iVar13 + 8)) *
                                 (*(float *)(iVar10 + 4) - *(float *)(iVar13 + 4))) /
                                 (*(float *)(iVar10 + 8) - *(float *)(iVar13 + 8)) +
                                *(float *)(iVar13 + 4)) - fVar3;
                        if (_DAT_004bd234 <= fVar2) {
                          if (_DAT_004bd234 < fVar2) {
                            if (!bVar6) goto joined_r0x0043ef18;
                            goto LAB_0043ef77;
                          }
                        }
                        else {
                          if (bVar7) goto LAB_0043ef77;
                          if (!bVar6) {
                            bVar7 = true;
                            goto LAB_0043ef22;
                          }
                        }
                      }
                      else {
                        if (bVar6) goto LAB_0043ef77;
joined_r0x0043ef18:
                        if (!bVar7) {
                          bVar6 = true;
                          goto LAB_0043ef22;
                        }
                      }
LAB_0043ef6e:
                      iVar8 = 1;
                      goto LAB_0043ef91;
                    }
                    if (bVar7) goto LAB_0043ef77;
                    if (bVar6) goto LAB_0043ef6e;
                    bVar7 = true;
                  }
                }
LAB_0043ef22:
                piVar11 = piVar11 + -1;
                bVar14 = iVar12 != 0;
                iVar10 = iVar13;
                iVar12 = iVar12 + -1;
              } while (bVar14);
              iVar8 = 0;
              goto LAB_0043ef91;
            }
          }
LAB_0043ef77:
          iVar8 = 0;
        }
        else if (ABS((float)piVar1[2]) <= ABS((float)piVar1[3])) {
LAB_0043ef7d:
          iVar8 = point_in_polygon_xy(piVar1,iVar8,fVar2,fVar3);
        }
        else {
          iVar8 = point_in_polygon_xz(piVar1,iVar8,fVar2,fVar4);
        }
LAB_0043ef91:
        if (((iVar8 != 0) && (_DAT_004bd234 <= fVar5)) && (fVar5 < local_20)) {
          local_c = piVar1[1];
          local_8 = piVar1[2];
          local_4 = piVar1[3];
          local_20 = fVar5;
        }
      }
    }
    piVar1 = (int *)piVar1[6];
  } while( true );
}


