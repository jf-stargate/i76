/*
 * Program: i76.exe
 * Function: load_road_textures
 * Entry: 0048e1a0
 * Signature: undefined __cdecl load_road_textures(char * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_0048e1a0
   suggested_name: load_road_textures
   basis: References road textures and abort diagnostic. */

void __cdecl load_road_textures(char *param_1)

{
  char cVar1;
  byte bVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  code *pcVar9;
  bool bVar10;
  undefined3 extraout_var;
  uint *puVar11;
  float *pfVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  undefined **ppuVar16;
  char *pcVar17;
  int iVar18;
  char *pcVar19;
  byte *pbVar20;
  char *pcVar21;
  double *pdVar22;
  double *pdVar23;
  undefined4 *puVar24;
  int iVar25;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  undefined8 local_360;
  undefined8 local_358;
  int local_350;
  undefined4 uStack_34c;
  int local_348;
  undefined4 uStack_344;
  int local_340;
  undefined4 uStack_33c;
  int local_338;
  undefined4 uStack_334;
  double local_330 [2];
  double local_320 [2];
  char local_30c [4];
  byte local_308 [256];
  char local_208 [256];
  char local_108 [260];
  
  DAT_0059c490 = 0;
  ppuVar16 = &PTR_DAT_004fa928;
  pcVar17 = &DAT_0059c1c0;
  do {
    pcVar19 = *ppuVar16;
    uVar13 = 0xffffffff;
    ppuVar16 = ppuVar16 + 1;
    do {
      pcVar21 = pcVar19;
      if (uVar13 == 0) break;
      uVar13 = uVar13 - 1;
      pcVar21 = pcVar19 + 1;
      cVar1 = *pcVar19;
      pcVar19 = pcVar21;
    } while (cVar1 != '\0');
    uVar13 = ~uVar13;
    pcVar19 = pcVar21 + -uVar13;
    pcVar21 = pcVar17;
    for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *(undefined4 *)pcVar21 = *(undefined4 *)pcVar19;
      pcVar19 = pcVar19 + 4;
      pcVar21 = pcVar21 + 4;
    }
    for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
      *pcVar21 = *pcVar19;
      pcVar19 = pcVar19 + 1;
      pcVar21 = pcVar21 + 1;
    }
    pcVar17 = pcVar17 + 0x10;
  } while (ppuVar16 < &DAT_004fa9a0);
  _splitpath(param_1,local_30c,local_108,(char *)local_320,local_208);
  uVar13 = 0xffffffff;
  pdVar22 = local_320;
  do {
    pdVar23 = pdVar22;
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    pdVar23 = (double *)((int)pdVar22 + 1);
    cVar1 = *(char *)pdVar22;
    pdVar22 = pdVar23;
  } while (cVar1 != '\0');
  uVar13 = ~uVar13;
  puVar24 = (undefined4 *)((int)pdVar23 - uVar13);
  pdVar22 = local_330;
  for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
    *(undefined4 *)pdVar22 = *puVar24;
    puVar24 = puVar24 + 1;
    pdVar22 = (double *)((int)pdVar22 + 4);
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *(undefined1 *)pdVar22 = *(undefined1 *)puVar24;
    puVar24 = (undefined4 *)((int)puVar24 + 1);
    pdVar22 = (double *)((int)pdVar22 + 1);
  }
  uVar13 = 0xffffffff;
  pcVar17 = &DAT_004fac94;
  do {
    pcVar19 = pcVar17;
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    pcVar19 = pcVar17 + 1;
    cVar1 = *pcVar17;
    pcVar17 = pcVar19;
  } while (cVar1 != '\0');
  uVar13 = ~uVar13;
  iVar15 = -1;
  pdVar22 = local_330;
  do {
    pdVar23 = pdVar22;
    if (iVar15 == 0) break;
    iVar15 = iVar15 + -1;
    pdVar23 = (double *)((int)pdVar22 + 1);
    cVar1 = *(char *)pdVar22;
    pdVar22 = pdVar23;
  } while (cVar1 != '\0');
  pcVar17 = pcVar19 + -uVar13;
  pcVar19 = (char *)((int)pdVar23 + -1);
  for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
    *(undefined4 *)pcVar19 = *(undefined4 *)pcVar17;
    pcVar17 = pcVar17 + 4;
    pcVar19 = pcVar19 + 4;
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *pcVar19 = *pcVar17;
    pcVar17 = pcVar17 + 1;
    pcVar19 = pcVar19 + 1;
  }
  bVar10 = resource_exists_in_cache_or_search_paths((char *)local_330);
  if (CONCAT31(extraout_var,bVar10) != 0) {
    puVar11 = open_resource_file_into_memory((char *)local_330);
    local_360 = (double)CONCAT44(local_360._4_4_,puVar11);
    if (puVar11 != (uint *)0x0) {
      iVar15 = get_loaded_resource_file_size((char *)local_330);
      local_358 = (double)CONCAT44(local_358._4_4_,iVar15);
      uVar13 = 0;
      do {
        iVar15 = system_cutscene_memory_context_helper_00499110
                           ((int *)&local_360,local_308,(int *)&local_358,0xff);
        if (iVar15 == 0) break;
        iVar15 = 0;
        do {
          pcVar9 = __mb_cur_max_exref;
          bVar2 = local_308[iVar15];
          (&DAT_0059c1c0)[uVar13 + iVar15] = bVar2;
          if (*(int *)pcVar9 < 2) {
            uVar14 = *(byte *)(*(int *)_pctype_exref + (char)bVar2 * 2) & 8;
          }
          else {
            uVar14 = _isctype((int)(char)bVar2,8);
          }
        } while ((uVar14 == 0) && (iVar15 = iVar15 + 1, iVar15 < 0xf));
        (&DAT_0059c1c0)[uVar13 + iVar15] = 0;
        uVar13 = uVar13 + 0x10;
      } while (uVar13 < 0x1e0);
      release_resource_file_reference((char *)local_330);
    }
  }
  puVar24 = (undefined4 *)&DAT_0059c3a0;
  pbVar20 = &DAT_0059c1c0;
  do {
    iVar15 = load_fullres_texture_list(puVar24,pbVar20);
    if (iVar15 == 0) {
      report_error();
    }
    pbVar20 = pbVar20 + 0x10;
    puVar24 = puVar24 + 2;
  } while (pbVar20 < &DAT_0059c3a0);
  for (iVar15 = world_reader_record_table_context_helper_004b8970(); iVar15 != 0;
      iVar15 = *(int *)(iVar15 + 4)) {
    iVar18 = 0;
    local_350 = 0x20000000;
    uStack_34c = 0x4202a05f;
    local_338 = 0x20000000;
    uStack_334 = 0xc202a05f;
    local_330[0] = 10000000000.0;
    local_320[0] = -10000000000.0;
    local_340 = 0x20000000;
    uStack_33c = 0x4202a05f;
    local_348 = 0x20000000;
    uStack_344 = 0xc202a05f;
    if (0 < *(int *)(iVar15 + 0x14)) {
      iVar25 = 0;
      do {
        local_360 = (double)*(float *)(iVar25 + 0xc + *(int *)(iVar15 + 0x28));
        local_358 = (double)*(float *)(iVar25 + *(int *)(iVar15 + 0x28) + 0x14);
        apply_world_object_transform_to_bounds_or_geometry(local_360,local_358);
        *(float *)(iVar25 + 0x10 + *(int *)(iVar15 + 0x28)) = (float)extraout_ST0;
        if (local_360 < (double)CONCAT44(uStack_34c,local_350)) {
          local_350 = (int)local_360;
          uStack_34c = local_360._4_4_;
        }
        if (extraout_ST0 < (float10)local_330[0]) {
          local_330[0] = (double)extraout_ST0;
        }
        if (local_358 < (double)CONCAT44(uStack_33c,local_340)) {
          local_340 = (int)local_358;
          uStack_33c = local_358._4_4_;
        }
        if ((double)CONCAT44(uStack_334,local_338) < local_360) {
          local_338 = (int)local_360;
          uStack_334 = local_360._4_4_;
        }
        if ((float10)local_320[0] < extraout_ST0) {
          local_320[0] = (double)extraout_ST0;
        }
        if ((double)CONCAT44(uStack_344,local_348) < local_358) {
          local_348 = (int)local_358;
          uStack_344 = local_358._4_4_;
        }
        pfVar12 = (float *)(*(int *)(iVar15 + 0x28) + iVar25);
        local_360 = (double)*pfVar12;
        local_358 = (double)pfVar12[2];
        apply_world_object_transform_to_bounds_or_geometry(local_360,local_358);
        *(float *)(iVar25 + 4 + *(int *)(iVar15 + 0x28)) = (float)extraout_ST0_00;
        if (local_360 < (double)CONCAT44(uStack_34c,local_350)) {
          local_350 = (int)local_360;
          uStack_34c = local_360._4_4_;
        }
        if (extraout_ST0_00 < (float10)local_330[0]) {
          local_330[0] = (double)extraout_ST0_00;
        }
        if (local_358 < (double)CONCAT44(uStack_33c,local_340)) {
          local_340 = (int)local_358;
          uStack_33c = local_358._4_4_;
        }
        if ((double)CONCAT44(uStack_334,local_338) < local_360) {
          local_338 = (int)local_360;
          uStack_334 = local_360._4_4_;
        }
        if ((float10)local_320[0] < extraout_ST0_00) {
          local_320[0] = (double)extraout_ST0_00;
        }
        if ((double)CONCAT44(uStack_344,local_348) < local_358) {
          local_348 = (int)local_358;
          uStack_344 = local_358._4_4_;
        }
        iVar18 = iVar18 + 1;
        iVar25 = iVar25 + 0x18;
      } while (iVar18 < *(int *)(iVar15 + 0x14));
    }
    fVar3 = (float10)_DAT_004be798;
    fVar4 = (float10)_DAT_004be798;
    fVar6 = (float)_DAT_004be7a0;
    *(float *)(iVar15 + 0x18) =
         (float)(((float10)(double)CONCAT44(uStack_334,local_338) +
                 (float10)(double)CONCAT44(uStack_34c,local_350)) * (float10)_DAT_004be798);
    *(float *)(iVar15 + 0x1c) = (float)(((float10)local_320[0] + (float10)local_330[0]) * fVar3);
    *(float *)(iVar15 + 0x20) =
         (float)(((float10)(double)CONCAT44(uStack_344,local_348) +
                 (float10)(double)CONCAT44(uStack_33c,local_340)) * fVar4);
    iVar18 = *(int *)(iVar15 + 0x14);
    if (0 < iVar18) {
      pfVar12 = *(float **)(iVar15 + 0x28);
      do {
        fVar8 = pfVar12[3] - *(float *)(iVar15 + 0x18);
        fVar5 = pfVar12[4] - *(float *)(iVar15 + 0x1c);
        fVar7 = pfVar12[5] - *(float *)(iVar15 + 0x20);
        fVar5 = fVar7 * fVar7 + fVar5 * fVar5 + fVar8 * fVar8;
        if (fVar6 < fVar5) {
          fVar6 = fVar5;
        }
        fVar5 = *pfVar12 - *(float *)(iVar15 + 0x18);
        fVar7 = pfVar12[1] - *(float *)(iVar15 + 0x1c);
        fVar8 = pfVar12[2] - *(float *)(iVar15 + 0x20);
        fVar5 = fVar8 * fVar8 + fVar7 * fVar7 + fVar5 * fVar5;
        if (fVar6 < fVar5) {
          fVar6 = fVar5;
        }
        pfVar12 = pfVar12 + 6;
        iVar18 = iVar18 + -1;
      } while (iVar18 != 0);
    }
    *(float *)(iVar15 + 0x24) = SQRT(fVar6);
  }
  DAT_0059c490 = 1;
  return;
}


