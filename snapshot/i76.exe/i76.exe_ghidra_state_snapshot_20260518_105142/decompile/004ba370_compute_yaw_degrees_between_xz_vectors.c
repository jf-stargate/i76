/*
 * Program: i76.exe
 * Function: compute_yaw_degrees_between_xz_vectors
 * Entry: 004ba370
 * Signature: float10 __cdecl compute_yaw_degrees_between_xz_vectors(float * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe ZFSF rename corrections v14] Restore previously established math helper name. v13
   accidentally renamed the containing function while trying to name an interior LZO helper at
   004ba4d0. */

float10 __cdecl compute_yaw_degrees_between_xz_vectors(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float10 fVar10;
  
  pfVar8 = param_1;
  fVar1 = param_1[1] * _DAT_004becb4;
  *param_1 = *param_1 * _DAT_004becb4;
  fVar2 = param_1[2] * _DAT_004becb4;
  param_1[1] = fVar1;
  param_1[2] = fVar2;
  param_1[1] = 0.0;
  dVar5 = (double)(*param_1 * *param_1 + param_1[2] * param_1[2]);
  fVar10 = zone_satellite_map_context_helper_00495000
                     (SUB84(dVar5,0),(uint)((ulonglong)dVar5 >> 0x20));
  *param_1 = (float)((float10)*param_1 * fVar10);
  param_1[1] = (float)((float10)param_1[1] * fVar10);
  param_1[2] = (float)((float10)param_1[2] * fVar10);
  fVar1 = param_2[1] * _DAT_004becb4;
  fVar2 = param_2[2] * _DAT_004becb4;
  *param_2 = *param_2 * _DAT_004becb4;
  param_2[1] = fVar1;
  param_2[2] = fVar2;
  param_2[1] = 0.0;
  dVar5 = (double)(*param_2 * *param_2 + param_2[2] * param_2[2]);
  fVar10 = zone_satellite_map_context_helper_00495000
                     (SUB84(dVar5,0),(uint)((ulonglong)dVar5 >> 0x20));
  *param_2 = (float)((float10)*param_2 * fVar10);
  param_2[1] = (float)((float10)param_2[1] * fVar10);
  param_2[2] = (float)((float10)param_2[2] * fVar10);
  param_1 = (float *)(param_2[2] * param_1[2] + param_2[1] * param_1[1] + *param_1 * *param_2);
  if (_DAT_004becb8 < (float)param_1) {
    param_1 = (float *)0x3f7ff972;
  }
  if ((float)param_1 < _DAT_004becbc) {
    param_1 = (float *)0xbf7ff972;
  }
  fVar10 = (float10)fpatan((float10)SQRT(_DAT_004becc0 - (float)param_1 * (float)param_1),
                           (float10)(float)param_1);
  fVar1 = (float)fVar10;
  if (fVar1 < _DAT_004becc4) {
    fVar1 = fVar1 - _DAT_004becc8;
  }
  fVar7 = fVar1 * _DAT_004beccc * _DAT_004becd0;
  fVar6 = *param_2 * pfVar8[2] - *pfVar8 * param_2[2];
  fVar1 = *pfVar8;
  fVar2 = param_2[1];
  fVar3 = *param_2;
  fVar4 = pfVar8[1];
  iVar9 = _isnan((double)(param_2[2] * pfVar8[1] - param_2[1] * pfVar8[2]));
  if (iVar9 == 0) {
    iVar9 = _isnan((double)fVar6);
    if (iVar9 == 0) {
      iVar9 = _isnan((double)(fVar1 * fVar2 - fVar3 * fVar4));
      if ((iVar9 == 0) && (fVar6 < _DAT_004becc4)) {
        fVar10 = (float10)_DAT_004becd4 - (float10)fVar7;
        goto LAB_004ba5c8;
      }
    }
  }
  fVar10 = (float10)fVar7;
LAB_004ba5c8:
  if (fVar10 == (float10)_DAT_004becd4) {
    fVar10 = (float10)_DAT_004becc4;
  }
  return fVar10;
}


