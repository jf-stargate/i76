/*
 * Program: I76EDIT.EXE
 * Function: i76edit_sample_weighted_height_field
 * Entry: 0040d5f0
 * Signature: float10 __cdecl i76edit_sample_weighted_height_field(int * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v5:medium] Samples a weighted float point cloud/height helper:
   accumulates inverse-distance weighted contributions, clamps to 0..4095-ish range, returns float.
    */

float10 __cdecl i76edit_sample_weighted_height_field(int *param_1,float param_2,float param_3)

{
  float *pfVar1;
  int iVar2;
  float local_4;
  
  local_4 = 0.0;
  iVar2 = *param_1;
  if (0 < iVar2) {
    local_4 = 0.0;
    pfVar1 = (float *)param_1[1];
    do {
      iVar2 = iVar2 + -1;
      local_4 = (pfVar1[2] - pfVar1[4]) /
                (((pfVar1[1] - param_3) * (pfVar1[1] - param_3) +
                 (*pfVar1 - param_2) * (*pfVar1 - param_2)) * pfVar1[3] + _DAT_004320cc) + local_4;
      pfVar1 = pfVar1 + 5;
    } while (iVar2 != 0);
  }
  if (0x457ff000 < (int)local_4) {
    local_4 = 4095.0;
  }
  if (0x80000000 < (uint)local_4) {
    local_4 = 0.0;
  }
  return (float10)local_4;
}


