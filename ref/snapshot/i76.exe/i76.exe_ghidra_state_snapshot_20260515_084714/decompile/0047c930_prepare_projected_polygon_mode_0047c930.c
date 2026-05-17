/*
 * Program: i76.exe
 * Function: prepare_projected_polygon_mode_0047c930
 * Entry: 0047c930
 * Signature: int __cdecl prepare_projected_polygon_mode_0047c930(float * param_1, int param_2, int param_3, int param_4, byte param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO raster table renames v35; confidence=medium] Clip/prepare table target in
   g_geo_raster_clip_prepare_table; exact raster mode semantics still being traced. */

int __cdecl
prepare_projected_polygon_mode_0047c930
          (float *param_1,int param_2,int param_3,int param_4,byte param_5)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  
  if ((param_5 & 2) == 0) {
    if (0 < param_4) {
      pfVar2 = (float *)(param_3 + 4);
      pfVar3 = (float *)(param_2 + 0xc);
      iVar4 = param_4;
      do {
        fVar1 = _DAT_004be764 / pfVar2[1];
        iVar4 = iVar4 + -1;
        pfVar3[-3] = pfVar2[-1] * fVar1 * param_1[2] + *param_1;
        *(float *)((int)pfVar2 + (param_2 - param_3)) = fVar1 * *pfVar2 * param_1[3] + param_1[1];
        pfVar3[-1] = fVar1;
        *pfVar3 = pfVar2[2] * fVar1;
        pfVar3[1] = pfVar2[3] * fVar1;
        pfVar3[2] = pfVar2[4];
        pfVar2 = pfVar2 + 6;
        pfVar3 = pfVar3 + 6;
      } while (iVar4 != 0);
    }
  }
  else if (0 < param_4) {
    iVar5 = param_2 - param_3;
    pfVar2 = (float *)(param_3 + 0xc);
    pfVar3 = (float *)(param_2 + 0x14);
    iVar4 = param_4;
    do {
      fVar1 = _DAT_004be764 / pfVar2[-1];
      pfVar3[-5] = pfVar2[-3] * fVar1 * param_1[2] + *param_1;
      *(float *)((int)pfVar2 + iVar5 + -8) = fVar1 * pfVar2[-2] * param_1[3] + param_1[1];
      *(float *)(iVar5 + -4 + (int)pfVar2) = fVar1;
      if (*pfVar2 < _DAT_004be768) {
        *pfVar2 = -32.0;
      }
      if (_DAT_004be76c < *pfVar2) {
        *pfVar2 = 32.0;
      }
      if (pfVar2[1] < _DAT_004be768) {
        pfVar2[1] = -32.0;
      }
      if (_DAT_004be76c < pfVar2[1]) {
        pfVar2[1] = 32.0;
      }
      iVar4 = iVar4 + -1;
      *(float *)(iVar5 + -0x18 + (int)(pfVar2 + 6)) = fVar1 * *pfVar2;
      pfVar3[-1] = fVar1 * pfVar2[1];
      *pfVar3 = pfVar2[2];
      pfVar2 = pfVar2 + 6;
      pfVar3 = pfVar3 + 6;
    } while (iVar4 != 0);
  }
  if (((param_5 & 0x10) == 0) && (0 < param_4)) {
    pfVar2 = (float *)(param_2 + 0xc);
    iVar4 = param_4;
    do {
      fVar1 = _DAT_004be764 / pfVar2[-1];
      iVar4 = iVar4 + -1;
      *pfVar2 = fVar1 * *pfVar2;
      pfVar2[1] = fVar1 * pfVar2[1];
      pfVar2 = pfVar2 + 6;
    } while (iVar4 != 0);
  }
  return param_4;
}


