/*
 * Program: i76.exe
 * Function: initialize_palette_shading_tables
 * Entry: 0045f520
 * Signature: undefined __stdcall initialize_palette_shading_tables(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Builds palette shading and
   lookup tables used by display/surface color effects. */

void initialize_palette_shading_tables(void)

{
  float fVar1;
  undefined1 uVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  float fVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float local_414;
  float local_410;
  float local_40c;
  float local_408;
  float local_404;
  float local_400;
  float local_3fc [255];
  
  local_404 = 0.7764706;
  local_408 = 0.3882353;
  iVar5 = 0;
  pfVar4 = local_3fc;
  do {
    uVar2 = convert_rgb_floats_to_nearest_palette_index();
    (&DAT_0054b068)[iVar5] = uVar2;
    local_404 = local_404 - _DAT_004be114;
    local_408 = local_408 - _DAT_004be110;
    vec3_normalize_or_scale_context_helper_00479540
              (CONCAT31(extraout_var,uVar2),&local_410,&local_40c,&local_400);
    iVar5 = iVar5 + 1;
    *pfVar4 = (local_410 * _DAT_004be118 - local_400 * _DAT_004be11c) - local_40c * _DAT_004be120;
    pfVar4 = pfVar4 + 1;
  } while (iVar5 < 0xff);
  uVar2 = convert_rgb_floats_to_nearest_palette_index();
  DAT_0054b1e8 = CONCAT31(extraout_var_00,uVar2);
  uVar2 = convert_rgb_floats_to_nearest_palette_index();
  DAT_0054b168 = CONCAT31(extraout_var_01,uVar2);
  iVar5 = 0;
  fVar6 = local_40c;
  do {
    vec3_normalize_or_scale_context_helper_00479540(iVar5,&local_410,&local_40c,&local_400);
    local_414 = 1e+06;
    fVar3 = 0.0;
    pfVar4 = local_3fc;
    local_410 = (local_410 * _DAT_004be118 - local_400 * _DAT_004be11c) - local_40c * _DAT_004be120;
    do {
      fVar1 = (local_410 - *pfVar4) * (local_410 - *pfVar4);
      if (fVar1 < local_414) {
        fVar6 = fVar3;
        local_414 = fVar1;
      }
      fVar3 = (float)((int)fVar3 + 1);
      pfVar4 = pfVar4 + 1;
    } while ((int)fVar3 < 0xff);
    (&DAT_0054ad48)[iVar5] = (&DAT_0054b068)[(int)fVar6];
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x100);
  DAT_0054b167 = convert_rgb_floats_to_nearest_palette_index();
  return;
}


