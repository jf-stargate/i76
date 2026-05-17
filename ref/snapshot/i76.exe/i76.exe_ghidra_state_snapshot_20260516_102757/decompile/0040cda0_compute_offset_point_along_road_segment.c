/*
 * Program: i76.exe
 * Function: compute_offset_point_along_road_segment
 * Entry: 0040cda0
 * Signature: undefined __cdecl compute_offset_point_along_road_segment(float param_1, int param_2, int param_3, float * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Computes an X/Z point offset perpendicular to a
   road/path segment by a fixed lane-width-style offset. */

void __cdecl
compute_offset_point_along_road_segment
          (float param_1,int param_2,int param_3,float *param_4,float *param_5)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  
  fVar5 = param_1;
  if (param_3 != 1) {
    if (0 < param_2) {
      iVar8 = param_2 * 0x18;
      pfVar6 = (float *)(*(int *)((int)param_1 + 0x28) + iVar8);
      fVar2 = pfVar6[-6] - *pfVar6;
      fVar4 = pfVar6[-4] - pfVar6[2];
      fVar3 = fVar4 * fVar4 + fVar2 * fVar2;
      if ((fVar3 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar3)) {
        fVar10 = zone_satellite_map_context_helper_00495000
                           (SUB84((double)fVar3,0),(uint)((ulonglong)(double)fVar3 >> 0x20));
        fVar9 = -(fVar10 * (float10)fVar4);
        param_1 = (float)(fVar10 * (float10)fVar2);
      }
      else {
        fVar9 = (float10)_DAT_004bc6b4;
        param_1 = 1.0;
      }
      fVar2 = param_1 * _DAT_004bc6b8;
      *param_4 = (float)((float10)*(float *)(iVar8 + *(int *)((int)fVar5 + 0x28)) -
                        fVar9 * (float10)_DAT_004bc6b8);
      *param_5 = *(float *)(iVar8 + 8 + *(int *)((int)fVar5 + 0x28)) - fVar2;
      return;
    }
    iVar8 = *(int *)((int)param_1 + 0x28);
    iVar7 = param_2 * 0x18;
    fVar5 = *(float *)(iVar8 + (param_2 + 1) * 0x18) - *(float *)(iVar8 + iVar7);
    fVar3 = *(float *)(iVar8 + 0x20 + iVar7) - *(float *)(iVar8 + 8 + iVar7);
    fVar2 = fVar3 * fVar3 + fVar5 * fVar5;
    if ((fVar2 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar2)) {
      fVar10 = zone_satellite_map_context_helper_00495000
                         (SUB84((double)fVar2,0),(uint)((ulonglong)(double)fVar2 >> 0x20));
      fVar9 = fVar10 * (float10)fVar3;
      fVar10 = -(fVar10 * (float10)fVar5);
    }
    else {
      fVar10 = (float10)_DAT_004bc6ac;
      fVar9 = (float10)_DAT_004bc6b4;
    }
    fVar1 = (float10)_DAT_004bc6b8;
    *param_4 = (float)((float10)*(float *)(iVar7 + *(int *)((int)param_1 + 0x28)) -
                      fVar9 * (float10)_DAT_004bc6b8);
    *param_5 = (float)((float10)*(float *)(iVar7 + 8 + *(int *)((int)param_1 + 0x28)) -
                      fVar10 * fVar1);
    return;
  }
  if (param_2 < *(int *)((int)param_1 + 0x14) + -1) {
    iVar8 = *(int *)((int)param_1 + 0x28);
    iVar7 = param_2 * 0x18;
    fVar2 = *(float *)(iVar7 + 0x24 + iVar8) - *(float *)(iVar7 + 0xc + iVar8);
    fVar4 = *(float *)(iVar7 + 0x2c + iVar8) - *(float *)(iVar7 + iVar8 + 0x14);
    fVar3 = fVar4 * fVar4 + fVar2 * fVar2;
    if ((fVar3 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar3)) {
      fVar10 = zone_satellite_map_context_helper_00495000
                         (SUB84((double)fVar3,0),(uint)((ulonglong)(double)fVar3 >> 0x20));
      fVar9 = -(fVar10 * (float10)fVar4);
      param_1 = (float)(fVar10 * (float10)fVar2);
    }
    else {
      fVar9 = (float10)_DAT_004bc6b4;
      param_1 = 1.0;
    }
    fVar2 = param_1 * _DAT_004bc6b8;
    *param_4 = (float)((float10)*(float *)(iVar7 + 0xc + *(int *)((int)fVar5 + 0x28)) -
                      fVar9 * (float10)_DAT_004bc6b8);
    *param_5 = *(float *)(iVar7 + 0x14 + *(int *)((int)fVar5 + 0x28)) - fVar2;
    return;
  }
  iVar8 = *(int *)((int)param_1 + 0x28);
  iVar7 = param_2 * 0x18;
  fVar5 = *(float *)(iVar7 + -0xc + iVar8) - *(float *)(iVar7 + 0xc + iVar8);
  fVar3 = *(float *)(iVar7 + -4 + iVar8) - *(float *)(iVar7 + iVar8 + 0x14);
  fVar2 = fVar3 * fVar3 + fVar5 * fVar5;
  if ((fVar2 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar2)) {
    fVar10 = zone_satellite_map_context_helper_00495000
                       (SUB84((double)fVar2,0),(uint)((ulonglong)(double)fVar2 >> 0x20));
    fVar9 = fVar10 * (float10)fVar3;
    fVar10 = -(fVar10 * (float10)fVar5);
  }
  else {
    fVar10 = (float10)_DAT_004bc6ac;
    fVar9 = (float10)_DAT_004bc6b4;
  }
  fVar1 = (float10)_DAT_004bc6b8;
  *param_4 = (float)((float10)*(float *)(iVar7 + 0xc + *(int *)((int)param_1 + 0x28)) -
                    fVar9 * (float10)_DAT_004bc6b8);
  *param_5 = (float)((float10)*(float *)(iVar7 + 0x14 + *(int *)((int)param_1 + 0x28)) -
                    fVar10 * fVar1);
  return;
}


