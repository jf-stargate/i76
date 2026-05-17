/*
 * Program: i76.exe
 * Function: update_world_object_smoke_emitters_and_spawn_particles
 * Entry: 004414a0
 * Signature: undefined __cdecl update_world_object_smoke_emitters_and_spawn_particles(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Updates active world-object-attached
   smoke/effect emitters, releases stale object refs, and spawns particle records. */

void __cdecl update_world_object_smoke_emitters_and_spawn_particles(float *param_1)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  int *piVar9;
  LPVOID pvVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  double *pdVar14;
  int *piVar15;
  float10 fVar16;
  int local_30;
  double local_20;
  double local_18;
  double local_10;
  
  if (DAT_0052ba34 != 0) {
    fVar16 = get_runtime_frame_delta_seconds();
    fVar1 = (float)fVar16;
    piVar3 = DAT_0052ba24;
    while (piVar5 = piVar3, piVar3 = DAT_0052ba30, piVar5 != (int *)0x0) {
      piVar3 = (int *)piVar5[7];
      pvVar10 = release_world_object_tree_reference((LPVOID)piVar5[2],&DAT_004f1b84);
      piVar5[2] = (int)pvVar10;
      if (pvVar10 == (LPVOID)0x0) {
        if (piVar5[8] != 0) {
          *(int *)(piVar5[8] + 0x1c) = piVar5[7];
        }
        if (piVar5[7] != 0) {
          *(int *)(piVar5[7] + 0x20) = piVar5[8];
        }
        if (DAT_0052b950 == piVar5) {
          DAT_0052b950 = (int *)piVar5[8];
        }
        if (DAT_0052ba24 == piVar5) {
          DAT_0052ba24 = (int *)piVar5[7];
        }
        piVar5[8] = 0;
        piVar5[7] = (int)DAT_0052b958;
        DAT_0052b958 = piVar5;
      }
      else {
        iVar4 = piVar5[2];
        local_30 = 0;
        if (0 < piVar5[1]) {
          do {
            fVar8 = (float)piVar5[5] - _DAT_004bd268;
            fVar7 = (float)piVar5[6] - _DAT_004bd26c;
            fVar2 = (float)piVar5[4];
            iVar11 = rand();
            fVar2 = ((float)iVar11 * _DAT_004bd270 - _DAT_004bd274) + fVar2;
            iVar11 = rand();
            fVar7 = ((float)iVar11 * _DAT_004bd270 - _DAT_004bd274) + fVar7;
            iVar12 = rand();
            piVar13 = DAT_0052ba20;
            iVar11 = *piVar5;
            fVar8 = fVar8 - (float)iVar12 * _DAT_004bd270 * _DAT_004bd278;
            iVar12 = piVar5[3];
            local_20 = (double)(fVar2 * *(float *)(iVar4 + 0x18) +
                                fVar7 * *(float *)(iVar4 + 0x30) + fVar8 * *(float *)(iVar4 + 0x24)
                               + (float)*(double *)(iVar4 + 0x40));
            local_18 = (double)(fVar8 * *(float *)(iVar4 + 0x28) +
                                fVar2 * *(float *)(iVar4 + 0x1c) + fVar7 * *(float *)(iVar4 + 0x34)
                               + (float)*(double *)(iVar4 + 0x48));
            local_10 = (double)(fVar7 * *(float *)(iVar4 + 0x38) +
                                fVar8 * *(float *)(iVar4 + 0x2c) + fVar2 * *(float *)(iVar4 + 0x20)
                               + (float)*(double *)(iVar4 + 0x50));
            piVar15 = DAT_0052ba20;
            piVar9 = DAT_0052ba30;
            if (DAT_0052ba34 != 0) {
              if (DAT_0052ba28 == (int *)0x0) {
                if (DAT_0052ba20 == (int *)0x0) {
                  piVar13 = (int *)0x0;
                }
                else {
                  DAT_0052ba20 = (int *)DAT_0052ba20[0x11];
                  if (DAT_0052ba20 != (int *)0x0) {
                    DAT_0052ba20[0x10] = 0;
                  }
                }
              }
              else {
                piVar13 = DAT_0052ba28;
                DAT_0052ba28 = (int *)DAT_0052ba28[0x10];
              }
              piVar15 = DAT_0052ba20;
              piVar9 = DAT_0052ba30;
              if (piVar13 != (int *)0x0) {
                piVar13[1] = 0;
                *piVar13 = iVar11;
                if (*(float *)(iVar12 + 8) <= _DAT_004bd27c) {
                  piVar13[2] = 0;
                  piVar13[3] = 0;
                  piVar13[7] = 0;
                  piVar13[8] = 0;
                  piVar13[9] = 0;
                }
                else {
                  piVar13[7] = (int)(*(float *)(iVar12 + 0x18) * *(float *)(iVar12 + 0xc));
                  piVar13[8] = (int)(*(float *)(iVar12 + 0x1c) * *(float *)(iVar12 + 0xc));
                  piVar13[9] = (int)(*(float *)(iVar12 + 0x20) * *(float *)(iVar12 + 0xc));
                  piVar13[2] = *(int *)(iVar12 + 8);
                  piVar13[3] = (int)(*(float *)(iVar12 + 8) * _DAT_004bd280);
                }
                piVar13[4] = *(int *)(iVar12 + 0x18);
                piVar13[5] = (int)(*(float *)(iVar12 + 0x1c) - _DAT_004bd284);
                iVar11 = *(int *)(iVar12 + 0x20);
                piVar13[0x11] = 0;
                piVar13[6] = iVar11;
                pdVar14 = &local_20;
                piVar15 = piVar13 + 10;
                for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
                  *piVar15 = *(int *)pdVar14;
                  pdVar14 = (double *)((int)pdVar14 + 4);
                  piVar15 = piVar15 + 1;
                }
                piVar13[0x10] = (int)DAT_0052ba30;
                piVar15 = piVar13;
                piVar9 = piVar13;
                if (DAT_0052ba30 != (int *)0x0) {
                  DAT_0052ba30[0x11] = (int)piVar13;
                  piVar15 = DAT_0052ba20;
                }
              }
            }
            DAT_0052ba30 = piVar9;
            DAT_0052ba20 = piVar15;
            local_30 = local_30 + 1;
          } while (local_30 < piVar5[1]);
        }
      }
    }
    while (piVar3 != (int *)0x0) {
      piVar5 = (int *)piVar3[0x10];
      if (piVar3[1] < 0x14) {
        build_smoke_particle_billboard_geometry(param_1,piVar3);
        fVar7 = fVar1 + fVar1;
        bVar6 = _DAT_004bd28c <= fVar7;
        fVar2 = (float)piVar3[3];
        *(double *)(piVar3 + 10) =
             (double)(fVar1 * (float)piVar3[4] + (float)*(double *)(piVar3 + 10));
        *(double *)(piVar3 + 0xc) =
             (double)(fVar1 * (float)piVar3[5] + (float)*(double *)(piVar3 + 0xc));
        *(double *)(piVar3 + 0xe) =
             (double)(fVar1 * (float)piVar3[6] + (float)*(double *)(piVar3 + 0xe));
        if (((bVar6) && (fVar7 <= _DAT_004bd290)) &&
           (fVar8 = fVar2 - (float)piVar3[2], (float)_DAT_004bd298 <= ABS(fVar8))) {
          fVar2 = fVar7 * fVar8 + (float)piVar3[2];
        }
        fVar7 = fVar2 - (float)piVar3[2];
        piVar3[2] = (int)fVar2;
        DAT_005a7e0c = DAT_005a7e0c + 1 & 0xff;
        fVar2 = (float)(&DAT_006543e0)[DAT_005a7e0c];
        piVar3[4] = (int)((float)piVar3[7] * fVar7 + fVar2 + (float)piVar3[4]);
        piVar3[5] = (int)((float)piVar3[8] * fVar7 + fVar2 + (float)piVar3[5]);
        piVar3[6] = (int)((float)piVar3[9] * fVar7 + fVar2 + (float)piVar3[6]);
        piVar3[1] = piVar3[1] + 1;
        piVar3 = piVar5;
      }
      else {
        if (piVar3[0x11] != 0) {
          *(int **)(piVar3[0x11] + 0x40) = piVar5;
        }
        if (piVar3[0x10] != 0) {
          *(int *)(piVar3[0x10] + 0x44) = piVar3[0x11];
        }
        if (DAT_0052ba20 == piVar3) {
          DAT_0052ba20 = (int *)piVar3[0x11];
        }
        if (DAT_0052ba30 == piVar3) {
          DAT_0052ba30 = (int *)piVar3[0x10];
        }
        piVar3[0x11] = 0;
        piVar3[0x10] = (int)DAT_0052ba28;
        DAT_0052ba28 = piVar3;
        piVar3 = piVar5;
      }
    }
  }
  return;
}


