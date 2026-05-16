/*
 * Program: i76.exe
 * Function: runtime_library_memory_fill_helper_004bb080
 * Entry: 004bb080
 * Signature: undefined4 __cdecl runtime_library_memory_fill_helper_004bb080(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: runtime library memory fill helper
   based on adjacent named subsystem context. */

undefined4 __cdecl
runtime_library_memory_fill_helper_004bb080
          (float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  
  apply_world_object_transform_to_bounds_or_geometry((double)param_2,(double)param_4);
  apply_world_object_transform_to_bounds_or_geometry((double)param_5,(double)param_7);
  if (((float)extraout_ST0 < param_3) && ((float10)param_6 < extraout_ST0_00)) {
    iVar4 = 0;
    do {
      fVar1 = (param_7 + param_4) * _DAT_004bff88;
      fVar2 = (param_5 + param_2) * _DAT_004bff88;
      fVar3 = (param_6 + param_3) * _DAT_004bff88;
      *param_1 = fVar2;
      param_1[1] = fVar3;
      param_1[2] = fVar1;
      apply_world_object_transform_to_bounds_or_geometry((double)fVar2,(double)fVar1);
      if (ABS(extraout_ST0_01 - (float10)param_1[1]) < (float10)_DAT_004bff90) {
        return 1;
      }
      if ((float10)_DAT_004bff98 <= extraout_ST0_01 - (float10)param_1[1]) {
        param_5 = *param_1;
        param_6 = param_1[1];
        param_7 = param_1[2];
      }
      else {
        param_2 = *param_1;
        param_3 = param_1[1];
        param_4 = param_1[2];
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 10);
    return 0;
  }
  return 0;
}


