/*
 * Program: i76.exe
 * Function: runtime_library_string_or_memory_helper_004baee0
 * Entry: 004baee0
 * Signature: undefined __cdecl runtime_library_string_or_memory_helper_004baee0(float * param_1, undefined8 param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9)
 */


/* cgpt readability rename set E v17: Readability pass set E: runtime library string or memory
   helper based on adjacent named subsystem context. */

void __cdecl
runtime_library_string_or_memory_helper_004baee0
          (float *param_1,undefined8 param_2,float param_3,float param_4,float param_5,float param_6
          ,float param_7,float param_8,float param_9)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float *pfVar7;
  float10 fVar8;
  float local_40 [4];
  float local_30;
  float local_2c;
  undefined8 local_28;
  float local_20;
  double local_18;
  double local_10;
  double local_8;
  
  local_18 = (double)param_7;
  local_10 = (double)param_8;
  local_40[3] = param_4;
  local_8 = (double)param_9;
  fVar2 = param_5 * param_3 - param_6 * param_2._4_4_;
  fVar4 = param_6 * (float)param_2 - param_4 * param_3;
  fVar3 = param_4 * param_2._4_4_ - param_5 * (float)param_2;
  local_30 = param_5;
  local_2c = param_6;
  local_20 = param_3;
  dVar1 = (double)(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
  local_28 = param_2;
  fVar8 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  fVar5 = (float)fVar8;
  local_40[0] = fVar2 * fVar5;
  local_40[2] = fVar3 * fVar5;
  local_40[1] = fVar4 * fVar5;
  pfVar7 = local_40;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *param_1 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


