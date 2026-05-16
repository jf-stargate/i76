/*
 * Program: i76.exe
 * Function: prepare_projected_polygon_mode_0047c8d0
 * Entry: 0047c8d0
 * Signature: undefined __cdecl prepare_projected_polygon_mode_0047c8d0(float * param_1, int param_2, int param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO raster table renames v35; confidence=medium] Clip/prepare table target in
   g_geo_raster_clip_prepare_table; exact raster mode semantics still being traced. */

void __cdecl
prepare_projected_polygon_mode_0047c8d0(float *param_1,int param_2,int param_3,int param_4)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  
  if (0 < param_4) {
    pfVar2 = (float *)(param_3 + 4);
    pfVar3 = (float *)(param_2 + 0x14);
    do {
      fVar1 = _DAT_004be764 / pfVar2[1];
      param_4 = param_4 + -1;
      pfVar3[-5] = pfVar2[-1] * fVar1 * param_1[2] + *param_1;
      *(float *)((param_2 - param_3) + -0x18 + (int)(pfVar2 + 6)) =
           fVar1 * param_1[3] * *pfVar2 + param_1[1];
      pfVar3[-3] = fVar1;
      *pfVar3 = pfVar2[4];
      pfVar2 = pfVar2 + 6;
      pfVar3 = pfVar3 + 6;
    } while (param_4 != 0);
  }
  return;
}


