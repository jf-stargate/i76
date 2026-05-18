/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00491a30
 * Entry: 00491a30
 * Signature: undefined __cdecl terrain_map_context_helper_00491a30(undefined * param_1, undefined * param_2)
 */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00491a30. Remove
   duplicated terrain wording. */

void __cdecl terrain_map_context_helper_00491a30(undefined *param_1,undefined *param_2)

{
  float fVar1;
  short *psVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  float *pfVar19;
  int iVar20;
  int *piVar21;
  int iVar22;
  float local_850;
  float fStack_848;
  float fStack_83c;
  uint local_834;
  uint uStack_808;
  float afStack_800 [4];
  float afStack_7f0 [4];
  float afStack_7e0 [4];
  int aiStack_7d0 [2];
  int local_7c8 [98];
  float afStack_640 [400];
  
  _DAT_0059c578 =
       *(float *)(DAT_006442d4 + 0x40) * DAT_006435f0 +
       *(float *)(DAT_006442d4 + 0x58) * DAT_006435f8 +
       *(float *)(DAT_006442d4 + 0x4c) * DAT_006435f4;
  _DAT_0059c57c =
       *(float *)(DAT_006442d4 + 0x50) * DAT_006435f4 +
       *(float *)(DAT_006442d4 + 0x5c) * DAT_006435f8 +
       *(float *)(DAT_006442d4 + 0x44) * DAT_006435f0;
  _DAT_0059c580 =
       *(float *)(DAT_006442d4 + 0x54) * DAT_006435f4 +
       *(float *)(DAT_006442d4 + 0x48) * DAT_006435f0 +
       *(float *)(DAT_006442d4 + 0x60) * DAT_006435f8;
  iVar7 = DAT_0059c560;
  do {
    if (iVar7 == 0) {
      return;
    }
    psVar2 = *(short **)(iVar7 + 0x14);
    if (*(short **)(psVar2 + 2) == (short *)0x0) {
      piVar8 = aiStack_7d0 + 2;
      aiStack_7d0[1] = (int)*psVar2;
    }
    else {
      piVar8 = terrain_map_context_helper_00492270(aiStack_7d0 + 1,*(short **)(psVar2 + 2));
      piVar8 = terrain_map_context_helper_00492270(piVar8,*(short **)(psVar2 + 4));
    }
    psVar2 = *(short **)(iVar7 + 0x10);
    if (*(short **)(psVar2 + 2) == (short *)0x0) {
      *piVar8 = (int)*psVar2;
      piVar9 = piVar8 + 1;
    }
    else {
      piVar9 = terrain_map_context_helper_00492270(piVar8,*(short **)(psVar2 + 2));
      piVar9 = terrain_map_context_helper_00492270(piVar9,*(short **)(psVar2 + 4));
    }
    iVar20 = *(int *)(iVar7 + 0x18);
    if (*(int *)(iVar20 + 4) == 0) {
      piVar10 = piVar9 + 1;
      *piVar9 = (int)*(short *)(iVar20 + 2);
    }
    else {
      piVar10 = terrain_map_context_helper_004922b0(piVar9,*(int *)(iVar20 + 8));
      piVar10 = terrain_map_context_helper_004922b0(piVar10,*(int *)(iVar20 + 4));
    }
    iVar20 = *(int *)(iVar7 + 0xc);
    piVar21 = (int *)(iVar7 + 0xc);
    if (*(int *)(iVar20 + 4) == 0) {
      *piVar10 = (int)*(short *)(iVar20 + 2);
      piVar11 = piVar10 + 1;
    }
    else {
      piVar11 = terrain_map_context_helper_004922b0(piVar10,*(int *)(iVar20 + 8));
      piVar11 = terrain_map_context_helper_004922b0(piVar11,*(int *)(iVar20 + 4));
    }
    iVar20 = DAT_006442ec;
    for (piVar12 = piVar21; piVar12 != (int *)(iVar7 + 0x1c); piVar12 = piVar12 + 1) {
      iVar22 = *(int *)(*piVar12 + 4);
      if (((iVar22 != 0) && (*(int *)(iVar22 + 4) == 0)) &&
         (*(int *)(*(int *)(*piVar12 + 8) + 4) == 0)) {
        iVar20 = (int)*(short *)(iVar22 + 2);
        goto LAB_00491d32;
      }
    }
    if (*(int *)(*piVar21 + 4) == 0) {
      if (*(int *)(*(short **)(iVar7 + 0x14) + 2) == 0) {
        iVar20 = (int)**(short **)(iVar7 + 0x14);
      }
      else {
        if (*(int *)(*(short **)(iVar7 + 0x18) + 2) != 0) goto LAB_00491c7d;
        iVar20 = (int)**(short **)(iVar7 + 0x18);
      }
    }
    else if (*(int *)(*(int *)(iVar7 + 0x10) + 4) == 0) {
      if (*(int *)(*(int *)(iVar7 + 0x14) + 4) == 0) {
        iVar20 = (int)*(short *)(*(int *)(iVar7 + 0x14) + 2);
      }
      else {
        if (*(int *)(*(int *)(iVar7 + 0x18) + 4) != 0) goto LAB_00491c7d;
        iVar20 = (int)*(short *)(*(int *)(iVar7 + 0x18) + 2);
      }
    }
    else {
LAB_00491c7d:
      iVar17 = *(short *)*piVar21 * 0xc;
      pfVar19 = (float *)(DAT_005dd2ec + iVar17);
      iVar16 = *(short *)(*(int *)(iVar7 + 0x10) + 2) * 0xc;
      iVar22 = DAT_005dd320 + iVar17;
      iVar18 = DAT_005dd320 + iVar16;
      pfVar14 = (float *)(iVar16 + DAT_005dd2ec);
      iVar13 = DAT_006442ec * 0xc;
      DAT_006442ec = DAT_006442ec + 1;
      *(float *)(DAT_005dd320 + iVar13) =
           (*(float *)(DAT_005dd320 + iVar17) + *(float *)(DAT_005dd320 + iVar16)) *
           (float)_DAT_004be838;
      *(float *)(DAT_005dd320 + 4 + iVar13) =
           (*(float *)(iVar18 + 4) + *(float *)(iVar22 + 4)) * (float)_DAT_004be838;
      *(float *)(DAT_005dd320 + 8 + iVar13) =
           (*(float *)(iVar18 + 8) + *(float *)(iVar22 + 8)) * (float)_DAT_004be838;
      *(float *)(DAT_005dd2ec + iVar13) = (*pfVar14 + *pfVar19) * (float)_DAT_004be838;
      *(float *)(DAT_005dd2ec + 4 + iVar13) = (pfVar14[1] + pfVar19[1]) * (float)_DAT_004be838;
    }
LAB_00491d32:
    fVar1 = *(float *)(DAT_005dd320 + 8 + aiStack_7d0[1] * 0xc);
    *piVar11 = aiStack_7d0[1];
    iVar18 = 0;
    local_850 = _DAT_004be830 / *(float *)(DAT_005dd320 + 8 + piVar11[-1] * 0xc);
    piVar21 = aiStack_7d0;
    iVar22 = 0;
    fVar3 = *(float *)(DAT_005dd320 + piVar11[-1] * 0xc + 4) * local_850;
    while (piVar21 = (int *)((int)piVar21 + 4), piVar21 <= piVar11) {
      fVar5 = _DAT_004be830 / *(float *)(DAT_005dd320 + 8 + *piVar21 * 0xc);
      fVar4 = *(float *)(DAT_005dd320 + *piVar21 * 0xc + 4) * fVar5;
      if (local_850 < fVar5) {
        local_850 = fVar5;
      }
      if (fVar4 <= fVar3) {
        iVar17 = -1;
      }
      else {
        iVar22 = -iVar22;
        iVar17 = 1;
      }
      iVar18 = iVar18 + iVar22;
      iVar22 = iVar17;
      fVar3 = fVar4;
    }
    (*(code *)param_1)(iVar7,local_850);
    iVar22 = (int)piVar11 - (int)(aiStack_7d0 + 1) >> 2;
    if (iVar18 == 4 - iVar22) {
      pfVar14 = (float *)zone_satellite_map_context_helper_00494a90
                                   (afStack_800,(float *)(DAT_005dd320 + aiStack_7d0[1] * 0xc),
                                    (float *)(DAT_005dd320 + *piVar8 * 0xc),
                                    (float *)(DAT_005dd320 + *piVar9 * 0xc));
      fVar3 = *pfVar14;
      fVar4 = pfVar14[1];
      fVar5 = pfVar14[2];
      fVar6 = pfVar14[3];
      pfVar14 = (float *)zone_satellite_map_context_helper_00494a90
                                   (afStack_7e0,(float *)(DAT_005dd320 + aiStack_7d0[1] * 0xc),
                                    (float *)(DAT_005dd320 + *piVar9 * 0xc),
                                    (float *)(DAT_005dd320 + *piVar10 * 0xc));
      if ((_DAT_004be800 <= fVar6) || (_DAT_004be800 <= pfVar14[3])) goto LAB_0049209c;
      fVar3 = -(fVar5 * _DAT_0059c580 + fVar4 * _DAT_0059c57c + fVar3 * _DAT_0059c578);
      if (_DAT_004be800 <= fVar3) {
        fVar4 = fVar1 * _DAT_00643600 + _DAT_006435fc;
        if (fVar4 < _DAT_004be82c) {
          fVar4 = _DAT_004be82c;
        }
        if (_DAT_004be830 < fVar4) {
          fVar4 = _DAT_004be830;
        }
        fStack_848 = fVar3 * fVar4 + DAT_0059c54c;
        if (_DAT_004be830 < fStack_848) {
          fStack_848 = _DAT_004be830;
        }
      }
      else {
        fStack_848 = DAT_0059c54c;
      }
      fVar3 = -(pfVar14[2] * _DAT_0059c580 + pfVar14[1] * _DAT_0059c57c + *pfVar14 * _DAT_0059c578);
      fVar4 = DAT_0059c54c;
      if (_DAT_004be800 <= fVar3) {
        fVar4 = fVar1 * _DAT_00643600 + _DAT_006435fc;
        if (fVar4 < _DAT_004be82c) {
          fVar4 = _DAT_004be82c;
        }
        if (_DAT_004be830 < fVar4) {
          fVar4 = _DAT_004be830;
        }
        fVar4 = fVar3 * fVar4 + DAT_0059c54c;
        if (_DAT_004be830 < fVar4) {
          fVar4 = _DAT_004be830;
        }
      }
      uStack_808 = SUB84((double)(_DAT_004fa48c * ((float)_DAT_004be860 - fVar4) +
                                 (float)_DAT_004faf18),0);
      local_834 = SUB84((double)(((float)_DAT_004be860 - fStack_848) * _DAT_004fa48c +
                                (float)_DAT_004faf18),0);
      if ((((uStack_808 ^ local_834) & 0x1f00) != 0) ||
         (iVar22 = (*(code *)param_2)(aiStack_7d0 + 1,iVar22,fStack_848), iVar22 == 0))
      goto LAB_0049209c;
    }
    else {
LAB_0049209c:
      pfVar14 = afStack_640;
      for (piVar8 = aiStack_7d0 + 2; piVar8 <= piVar11; piVar8 = piVar8 + 1) {
        pfVar19 = pfVar14;
        if ((piVar8[-1] != iVar20) && (*piVar8 != iVar20)) {
          pfVar15 = (float *)zone_satellite_map_context_helper_00494a90
                                       (afStack_7f0,(float *)(DAT_005dd320 + iVar20 * 0xc),
                                        (float *)(DAT_005dd320 + piVar8[-1] * 0xc),
                                        (float *)(DAT_005dd320 + *piVar8 * 0xc));
          pfVar19 = pfVar14 + 4;
          *pfVar14 = *pfVar15;
          pfVar14[1] = pfVar15[1];
          fVar3 = pfVar15[3];
          pfVar14[2] = pfVar15[2];
          pfVar14[3] = fVar3;
        }
        pfVar14 = pfVar19;
      }
      piVar8 = aiStack_7d0 + 2;
      if (aiStack_7d0 + 2 <= piVar11) {
        pfVar14 = afStack_640 + 2;
        do {
          if ((piVar8[-1] != iVar20) && (*piVar8 != iVar20)) {
            if (pfVar14[1] < _DAT_004be800) {
              fStack_83c = 0.0;
              if (DAT_005a4618 == 0) {
                fVar3 = -(pfVar14[-2] * _DAT_0059c578 +
                         pfVar14[-1] * _DAT_0059c57c + _DAT_0059c580 * *pfVar14);
                if (_DAT_004be800 <= fVar3) {
                  fVar4 = fVar1 * _DAT_00643600 + _DAT_006435fc;
                  if (fVar4 < _DAT_004be82c) {
                    fVar4 = _DAT_004be82c;
                  }
                  if (_DAT_004be830 < fVar4) {
                    fVar4 = _DAT_004be830;
                  }
                  fStack_83c = fVar3 * fVar4 + DAT_0059c54c;
                  if (_DAT_004be830 < fStack_83c) {
                    fStack_83c = _DAT_004be830;
                  }
                }
                else {
                  fStack_83c = DAT_0059c54c;
                }
              }
              piVar8[-2] = iVar20;
              (*(code *)param_2)(piVar8 + -2,3,fStack_83c);
            }
            pfVar14 = pfVar14 + 4;
          }
          piVar8 = piVar8 + 1;
        } while (piVar8 <= piVar11);
      }
    }
    iVar7 = *(int *)(iVar7 + 8);
  } while( true );
}


