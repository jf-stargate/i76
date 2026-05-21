/*
 * Program: i76.exe
 * Function: init_sky_textures
 * Entry: 00404e50
 * Signature: undefined __stdcall init_sky_textures(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00404e50
   suggested_name: init_sky_textures
   basis: Diagnostics for missing sky/moon/sun textures. */

void init_sky_textures(void)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  undefined3 extraout_var;
  int iVar6;
  undefined3 extraout_var_00;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_5c;
  float local_58;
  int local_40 [16];
  
  _DAT_00507cd8 = 0;
  _DAT_00507cdc = 0;
  _DAT_00507c50 = 0;
  _DAT_00507c54 = 0;
  iVar5 = load_fullres_texture_list(&DAT_00504c38,(byte *)&DAT_005dce60);
  if (iVar5 == 0) {
    report_error();
    return;
  }
  _DAT_00507cec = 6000.0;
  _DAT_00507ce8 = 6000.0;
  _DAT_00507ce0 = 6000.0;
  _DAT_00504c30 = 0x3c000000;
  DAT_00507cd4 = 0;
  DAT_00504c48 = 0;
  DAT_00504c4c = 0x44160000;
  _DAT_00504c50 = 0;
  DAT_00504c54 = 0x40000000;
  DAT_00504c58 = 0x40000000;
  bVar4 = is_miss16_high_color_resource_mode();
  if (CONCAT31(extraout_var,bVar4) == 0) {
    (&DAT_00504c5c)[DAT_00507cd4 * 6] = 0;
  }
  else {
    (&DAT_00504c5c)[DAT_00507cd4 * 6] = 0x3f4ccccd;
  }
  fVar9 = (float10)fcos((float10)_DAT_004bc4b8);
  iVar5 = DAT_00507cd4 + 1;
  local_58 = 0.3926991;
  fVar9 = fVar9 * (float10)_DAT_004bc4a0 - (float10)_DAT_004bc4c0;
  do {
    fVar1 = (float10)_DAT_004bc4c8;
    fVar10 = (fVar9 - (float10)_DAT_00507ce8) / (float10)_DAT_00507cec;
    local_5c = 0.0;
    fVar12 = (float)SQRT((float10)_DAT_004bc4c4 - fVar10 * fVar10);
    do {
      DAT_00507cd4 = iVar5;
      iVar5 = DAT_00507cd4;
      fVar10 = (float10)fcos((float10)local_5c);
      iVar6 = DAT_00507cd4 * 0x18;
      fVar11 = (float10)fsin((float10)local_5c);
      fVar14 = fVar12 * (float)fVar11;
      fVar13 = (float)((float10)fVar12 * fVar10);
      fVar2 = _DAT_00507ce0 * fVar14;
      fVar3 = fVar13 - _DAT_004bc4cc;
      fVar14 = fVar14 - _DAT_004bc4cc;
      (&DAT_00504c48)[DAT_00507cd4 * 6] = _DAT_00507ce0 * fVar13;
      *(float *)(&DAT_00504c50 + iVar6) = fVar2;
      (&DAT_00504c4c)[iVar5 * 6] = (float)(fVar9 - fVar1);
      (&DAT_00504c54)[iVar5 * 6] = fVar3;
      (&DAT_00504c58)[iVar5 * 6] = fVar14;
      (&DAT_00504c54)[iVar5 * 6] = (float)(&DAT_00504c54)[iVar5 * 6] * _DAT_004bc4d0;
      (&DAT_00504c58)[iVar5 * 6] = (float)(&DAT_00504c58)[iVar5 * 6] * _DAT_004bc4d0;
      bVar4 = is_miss16_high_color_resource_mode();
      if (CONCAT31(extraout_var_00,bVar4) == 0) {
        (&DAT_00504c5c)[DAT_00507cd4 * 6] = 0;
      }
      else {
        (&DAT_00504c5c)[DAT_00507cd4 * 6] = 0x3f4ccccd;
      }
      local_5c = local_5c - _DAT_004bc4d4;
      iVar5 = DAT_00507cd4 + 1;
    } while (_DAT_004bc4dc < _DAT_004bc4d8 - local_5c);
    fVar9 = (float10)local_58;
    local_58 = (float)(fVar9 - (float10)_DAT_004bc4e0);
    fVar9 = (float10)fcos(fVar9 - (float10)_DAT_004bc4e0);
    fVar9 = fVar9 * (float10)_DAT_004bc4a0 - (float10)_DAT_004bc4c0;
  } while (local_58 < _DAT_004bc4e4);
  DAT_00507cd4 = DAT_00507cd4 + 2;
  puVar7 = &DAT_00504c48;
  puVar8 = &DAT_00504c48 + iVar5 * 6;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  (&DAT_00504c4c)[iVar5 * 6] = 0xc6322000;
  DAT_00504c40 = 8;
  _DAT_00507c50 = 0;
  _DAT_00507c54 = 0;
  _DAT_00507cd8 = 0;
  _DAT_00507cdc = 0;
  _DAT_00507c48 = 0;
  _DAT_00507c98 = DAT_006435e0;
  if (DAT_006435e0 == (int *)0x0) {
    report_error();
    return;
  }
  _DAT_00507c48 = 1;
  puVar7 = (undefined4 *)
           construct_bitmap_surface_context
                     (local_40,*DAT_006435e0,(DAT_006435e0[1] << 3) >> 3,(int)(DAT_006435e0 + 2),0);
  fVar13 = DAT_004fa0a4;
  fVar12 = DAT_004fa0a0;
  puVar8 = &DAT_00507ca0;
  for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  fVar14 = DAT_004fa0a8;
  fVar9 = palette_dib_surface_getter_helper_00477ad0();
  puVar7 = (undefined4 *)
           zone_satellite_map_context_helper_00494460(local_40,(float)fVar9,fVar12,fVar13,fVar14);
  puVar8 = &DAT_00507c58;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  return;
}


