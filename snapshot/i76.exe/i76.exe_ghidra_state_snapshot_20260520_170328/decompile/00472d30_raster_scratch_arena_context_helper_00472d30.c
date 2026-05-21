/*
 * Program: i76.exe
 * Function: raster_scratch_arena_context_helper_00472d30
 * Entry: 00472d30
 * Signature: undefined __cdecl raster_scratch_arena_context_helper_00472d30(float * param_1, int param_2, double param_3, double param_4, double param_5)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster scratch arena context helper
   based on adjacent named subsystem context. */

void __cdecl
raster_scratch_arena_context_helper_00472d30
          (float *param_1,int param_2,double param_3,double param_4,double param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  
  fVar1 = *(float *)(param_2 + 0x44);
  fVar2 = *(float *)(param_2 + 0x50);
  fVar3 = *(float *)(param_2 + 0x48);
  fVar4 = *(float *)(param_2 + 0x54);
  fVar5 = *(float *)(param_2 + 0x5c);
  dVar7 = *(double *)(param_2 + 0x70);
  fVar6 = *(float *)(param_2 + 0x60);
  dVar8 = *(double *)(param_2 + 0x78);
  *param_1 = *(float *)(param_2 + 0x58) * (float)param_5 +
             *(float *)(param_2 + 0x4c) * (float)param_4 +
             *(float *)(param_2 + 0x40) * (float)param_3 + (float)*(double *)(param_2 + 0x68);
  param_1[1] = fVar5 * (float)param_5 + fVar2 * (float)param_4 + fVar1 * (float)param_3 +
               (float)dVar7;
  param_1[2] = fVar6 * (float)param_5 + fVar4 * (float)param_4 + fVar3 * (float)param_3 +
               (float)dVar8;
  return;
}


