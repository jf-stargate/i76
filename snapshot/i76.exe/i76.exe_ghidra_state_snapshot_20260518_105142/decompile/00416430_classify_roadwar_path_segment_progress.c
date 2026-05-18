/*
 * Program: i76.exe
 * Function: classify_roadwar_path_segment_progress
 * Entry: 00416430
 * Signature: undefined __cdecl classify_roadwar_path_segment_progress(float param_1, float param_2, float param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Classifies the vehicle position relative to the current
   Roadwar path segment and sets progress/direction state. */

void __cdecl
classify_roadwar_path_segment_progress(float param_1,float param_2,float param_3,int *param_4)

{
  int *piVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  int *piVar7;
  int iVar8;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar7 = param_4;
  local_28 = param_4[7];
  piVar1 = param_4 + 1;
  pfVar2 = (float *)(*(int *)(local_28 + 0x28) + 0xc + *param_4 * 0x18);
  fVar4 = *pfVar2;
  fVar5 = pfVar2[1];
  local_1c = pfVar2[2];
  param_4 = (int *)*param_4;
  local_24 = fVar4;
  local_20 = fVar5;
  iVar8 = roadwar_get_next_road_index(&local_28,*piVar1,(int *)&param_4);
  if (iVar8 == 0) {
    piVar7[2] = 2;
    piVar7[5] = 0x405ccccd;
    return;
  }
  pfVar2 = (float *)(piVar7 + 5);
  pfVar3 = (float *)(*(int *)(local_28 + 0x28) + 0xc + (int)param_4 * 0x18);
  local_18 = *pfVar3;
  local_14 = pfVar3[1];
  local_10 = pfVar3[2];
  compute_point_to_segment_unit_offset_and_distance
            (param_1,param_2,param_3,fVar4,fVar5,local_1c,*pfVar3,pfVar3[1],pfVar3[2],&local_c,
             pfVar2);
  fVar4 = -(local_10 - local_1c) * local_c +
          (local_18 - local_24) * local_4 + (local_14 - local_20) * local_8;
  if (piVar7[1] == 1) {
    bVar6 = _DAT_004bc830 < fVar4;
  }
  else {
    bVar6 = fVar4 < _DAT_004bc830;
  }
  if (!bVar6) {
    fVar4 = *pfVar2 * _DAT_004bc890;
    if (*pfVar2 < _DAT_004bc884) {
      piVar7[2] = 1;
      *pfVar2 = fVar4;
      return;
    }
    piVar7[2] = 0;
    *pfVar2 = fVar4;
    return;
  }
  if (*pfVar2 < _DAT_004bc884) {
    piVar7[2] = 2;
    return;
  }
  if (*pfVar2 < _DAT_004bc888) {
    piVar7[2] = 3;
    return;
  }
  if (*pfVar2 < _DAT_004bc88c) {
    piVar7[2] = 4;
    return;
  }
  piVar7[2] = 5;
  return;
}


