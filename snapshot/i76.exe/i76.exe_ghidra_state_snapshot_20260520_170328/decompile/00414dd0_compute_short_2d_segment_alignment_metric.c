/*
 * Program: i76.exe
 * Function: compute_short_2d_segment_alignment_metric
 * Entry: 00414dd0
 * Signature: float10 __cdecl compute_short_2d_segment_alignment_metric(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Computes a short-distance 2D alignment/dot metric used
   by path simplification and waypoint progress logic. */

float10 __cdecl
compute_short_2d_segment_alignment_metric
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  float10 fVar7;
  
  fVar3 = param_3 - param_1;
  fVar1 = param_4 - param_2;
  fVar2 = fVar1 * fVar1 + fVar3 * fVar3;
  if ((_DAT_004bc7ac < fVar2) && (fVar2 < _DAT_004bc7b0)) {
    return (float10)_DAT_004bc7b4;
  }
  fVar6 = zone_satellite_map_context_helper_00495000
                    (SUB84((double)fVar2,0),(uint)((ulonglong)(double)fVar2 >> 0x20));
  if ((float10)_DAT_004bc7b8 < fVar6) {
    return (float10)_DAT_004bc7b4;
  }
  fVar5 = param_5 - param_1;
  fVar2 = param_6 - param_2;
  fVar4 = fVar2 * fVar2 + fVar5 * fVar5;
  if ((_DAT_004bc7ac < fVar4) && (fVar4 < _DAT_004bc7b0)) {
    return (float10)_DAT_004bc7b4;
  }
  fVar7 = zone_satellite_map_context_helper_00495000
                    (SUB84((double)fVar4,0),(uint)((ulonglong)(double)fVar4 >> 0x20));
  if ((float10)_DAT_004bc7c0 < fVar7) {
    return (float10)_DAT_004bc7b4;
  }
  return fVar7 * (float10)fVar2 * (float10)(float)(fVar6 * (float10)fVar1) +
         fVar7 * (float10)fVar5 * (float10)(float)(fVar6 * (float10)fVar3);
}


