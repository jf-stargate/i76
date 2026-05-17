/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00490a00
 * Entry: 00490a00
 * Signature: undefined __cdecl terrain_map_context_helper_00490a00(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490a00. Remove
   duplicated terrain wording. */

void __cdecl terrain_map_context_helper_00490a00(int param_1)

{
  float fVar1;
  float fVar2;
  short *psVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  bool bVar9;
  ushort uVar10;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar11;
  int iVar12;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  int iVar13;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  float10 fVar18;
  int local_2c;
  int local_24;
  undefined4 local_1c;
  short local_10;
  short local_c;
  
  _DAT_0059c578 = DAT_006435f0;
  _DAT_0059c564 = 0;
  _DAT_0059c57c = DAT_006435f4;
  _DAT_0059c580 = DAT_006435f8;
  fVar18 = palette_dib_surface_setter_helper_00477ae0();
  DAT_0059c54c = (float)fVar18;
  bVar9 = get_global_heap_handle();
  DAT_005a4618 = CONCAT31(extraout_var,bVar9);
  bVar9 = get_global_heap_handle();
  if (CONCAT31(extraout_var_00,bVar9) == 0) {
    uVar11 = 0xf4;
    DAT_0059c584 = 0xe8;
    DAT_0059c554 = 0xf4;
  }
  else {
    uVar11 = 0x15;
    DAT_0059c584 = 9;
    DAT_0059c554 = 0x15;
  }
  DAT_0059c570 = uVar11 | 2;
  DAT_006442d4 = param_1;
  _DAT_006442cc =
       ABS(*(float *)(param_1 + 0x2c) * *(float *)(param_1 + 0x2c) * _DAT_004be7f8) * _DAT_004fad24
       * DAT_006442c0 * _DAT_004be7fc;
  DAT_0059c560 = 0;
  DAT_0059c574 = 0;
  _DAT_006442c8 =
       (ABS(*(float *)(param_1 + 8)) * _DAT_004fad20) / (float)(**(int **)(param_1 + 0x3c) >> 1);
  DAT_006442ec = 0;
  DAT_00654380 = DAT_005dd324;
  _DAT_006442d0 = 1;
  _DAT_006442f8 = (float)*(double *)(param_1 + 0x160) * _DAT_006442c4;
  _DAT_00644300 = (float)*(double *)(param_1 + 0x170) * _DAT_006442c4;
  iVar12 = terrain_map_context_helper_004929b0(param_1);
  iVar4 = DAT_006442ec;
  iVar16 = DAT_006442e4;
  iVar13 = DAT_006442e0;
  if (iVar12 == 0) {
    DAT_006543ac = 0xc3960000;
    _DAT_006543a4 = 0x44610000;
    _DAT_006442f4 = iVar12;
    fill_bitmap_surface_context(*(int **)(param_1 + 0x3c),0xb4);
    return;
  }
  DAT_0059c56c = 0;
  DAT_0059c568 = 0;
  DAT_005a45c0 = 0;
  local_24 = SUB84((double)(_DAT_006442f8 + (float)_DAT_004faf18),0);
  _DAT_006442d8 = local_24;
  iVar17 = 1 << ((byte)DAT_006442e8 & 0x1f);
  local_1c = SUB84((double)(_DAT_00644300 + (float)_DAT_004faf18),0);
  _DAT_006442dc = local_1c;
  fVar1 = (float)DAT_006442e0;
  iVar12 = DAT_006442ec * 0xc;
  DAT_006442ec = DAT_006442ec + 1;
  *(float *)(DAT_005dd320 + iVar12) = fVar1;
  fVar2 = (float)iVar16;
  *(float *)(DAT_005dd320 + 8 + iVar12) = fVar2;
  uVar10 = terrain_map_context_helper_00493160(iVar13,iVar16);
  *(float *)(DAT_005dd320 + 4 + iVar12) = (float)CONCAT22(extraout_var_01,uVar10);
  *(float *)(DAT_005dd2ec + iVar12) = fVar1 * _DAT_004be80c;
  *(float *)(DAT_005dd2ec + 4 + iVar12) = fVar2 * _DAT_004be80c;
  iVar16 = DAT_006442ec;
  iVar13 = DAT_006442e4;
  iVar12 = DAT_006442e0 + iVar17;
  fVar1 = (float)iVar12;
  iVar14 = DAT_006442ec * 0xc;
  DAT_006442ec = DAT_006442ec + 1;
  *(float *)(DAT_005dd320 + iVar14) = fVar1;
  fVar2 = (float)iVar13;
  *(float *)(DAT_005dd320 + 8 + iVar14) = fVar2;
  uVar10 = terrain_map_context_helper_00493160(iVar12,iVar13);
  *(float *)(DAT_005dd320 + 4 + iVar14) = (float)CONCAT22(extraout_var_02,uVar10);
  *(float *)(DAT_005dd2ec + iVar14) = fVar1 * _DAT_004be80c;
  *(float *)(DAT_005dd2ec + 4 + iVar14) = fVar2 * _DAT_004be80c;
  iVar12 = DAT_006442ec;
  iVar14 = DAT_006442e0 + iVar17;
  fVar1 = (float)iVar14;
  iVar13 = DAT_006442e4 + iVar17;
  iVar15 = DAT_006442ec * 0xc;
  DAT_006442ec = DAT_006442ec + 1;
  *(float *)(DAT_005dd320 + iVar15) = fVar1;
  fVar2 = (float)iVar13;
  *(float *)(DAT_005dd320 + 8 + iVar15) = fVar2;
  uVar10 = terrain_map_context_helper_00493160(iVar14,iVar13);
  *(float *)(DAT_005dd320 + 4 + iVar15) = (float)CONCAT22(extraout_var_03,uVar10);
  *(float *)(DAT_005dd2ec + iVar15) = fVar1 * _DAT_004be80c;
  *(float *)(DAT_005dd2ec + 4 + iVar15) = fVar2 * _DAT_004be80c;
  iVar14 = DAT_006442ec;
  iVar13 = DAT_006442e0;
  fVar1 = (float)DAT_006442e0;
  iVar17 = DAT_006442e4 + iVar17;
  iVar15 = DAT_006442ec * 0xc;
  DAT_006442ec = DAT_006442ec + 1;
  *(float *)(DAT_005dd320 + iVar15) = fVar1;
  fVar2 = (float)iVar17;
  *(float *)(DAT_005dd320 + 8 + iVar15) = fVar2;
  uVar10 = terrain_map_context_helper_00493160(iVar13,iVar17);
  *(float *)(DAT_005dd320 + 4 + iVar15) = (float)CONCAT22(extraout_var_04,uVar10);
  *(float *)(DAT_005dd2ec + iVar15) = fVar1 * _DAT_004be80c;
  *(float *)(DAT_005dd2ec + 4 + iVar15) = fVar2 * _DAT_004be80c;
  psVar3 = DAT_00654380;
  local_c = (short)iVar12;
  psVar5 = DAT_00654380 + 6;
  *DAT_00654380 = (short)iVar14;
  DAT_00654380 = psVar5;
  psVar3[1] = local_c;
  psVar3[2] = 0;
  psVar3[3] = 0;
  psVar3[4] = 0;
  psVar5 = DAT_00654380;
  psVar3[5] = 0;
  DAT_0059c568 = DAT_0059c568 + 1;
  local_10 = (short)iVar4;
  psVar6 = DAT_00654380 + 6;
  *DAT_00654380 = local_10;
  DAT_00654380 = psVar6;
  psVar5[1] = (short)iVar16;
  psVar5[2] = 0;
  psVar5[3] = 0;
  psVar5[4] = 0;
  psVar6 = DAT_00654380;
  psVar5[5] = 0;
  DAT_0059c568 = DAT_0059c568 + 1;
  psVar7 = DAT_00654380 + 6;
  *DAT_00654380 = (short)iVar16;
  DAT_00654380 = psVar7;
  psVar6[2] = 0;
  psVar6[3] = 0;
  psVar6[1] = local_c;
  psVar6[4] = 0;
  psVar7 = DAT_00654380;
  psVar6[5] = 0;
  DAT_0059c568 = DAT_0059c568 + 1;
  psVar8 = DAT_00654380 + 6;
  *DAT_00654380 = local_10;
  DAT_00654380 = psVar8;
  psVar7[1] = (short)iVar14;
  psVar7[2] = 0;
  psVar7[3] = 0;
  psVar7[4] = 0;
  psVar7[5] = 0;
  DAT_0059c568 = DAT_0059c568 + 1;
  terrain_map_context_helper_004911e0(psVar7,psVar6,psVar5,psVar3);
  if (DAT_0059c560 != 0) {
    zone_satellite_map_context_helper_004937c0();
    if ((DAT_005a4618 != 0) && (iVar13 = 0, 0 < DAT_006442ec)) {
      iVar16 = 0;
      do {
        local_24 = SUB84((double)(((float)_DAT_004faf18 -
                                  *(float *)(DAT_005dd2ec + iVar16) * _DAT_004be810) -
                                 (float)_DAT_004be818),0);
        local_2c = SUB84((double)(((float)_DAT_004faf18 -
                                  *(float *)(DAT_005dd2ec + 4 + iVar16) * _DAT_004be810) -
                                 (float)_DAT_004be818),0);
        fVar18 = terrain_map_context_helper_00490fb0
                           (local_24,local_2c,*(float *)(DAT_005dd320 + 8 + iVar16));
        iVar13 = iVar13 + 1;
        *(float *)(DAT_005dd2ec + 8 + iVar16) = (float)fVar18;
        iVar16 = iVar16 + 0xc;
      } while (iVar13 < DAT_006442ec);
    }
    if (DAT_00654b8b == '\0') {
      terrain_map_context_helper_00491a30(&LAB_0048e190,terrain_map_context_helper_004922f0);
      return;
    }
    terrain_map_context_helper_00491a30(&LAB_004923f0,terrain_map_context_helper_004924b0);
  }
  return;
}


