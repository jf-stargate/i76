/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00490470
 * Entry: 00490470
 * Signature: undefined __cdecl terrain_map_context_helper_00490470(undefined4 param_1, float param_2, float param_3, undefined4 param_4, undefined4 param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490470. Remove
   duplicated terrain wording. */

void __cdecl
terrain_map_context_helper_00490470
          (undefined4 param_1,float param_2,float param_3,undefined4 param_4,undefined4 param_5)

{
  float fVar1;
  int local_10;
  int local_8;
  
  fVar1 = param_2 - DAT_006543ac;
  if (param_3 < fVar1) {
    return;
  }
  local_10 = SUB84((double)((param_3 - fVar1) + (float)_DAT_004faf18),0);
  if (0 < local_10) {
    local_8 = SUB84((double)(fVar1 + (float)_DAT_004faf18),0);
    local_8 = local_8 * 0xc;
    do {
      DAT_006543a8 = (int *)(DAT_00654388 + local_8);
      if (*DAT_006543a8 == 0) {
        *DAT_006543a8 = (int)DAT_006543b8;
        DAT_006543b8[1] = param_5;
        *DAT_006543b8 = param_4;
        DAT_006543b8[3] = 0;
      }
      else {
        *(undefined4 **)(DAT_006543a8[1] + 0xc) = DAT_006543b8;
        DAT_006543b8[1] = param_5;
        *DAT_006543b8 = param_4;
        DAT_006543b8[3] = 0;
        DAT_006543a8[1] = (int)DAT_006543b8;
      }
      local_8 = local_8 + 0xc;
      DAT_006543b8[2] = param_1;
      DAT_006543a8[1] = (int)DAT_006543b8;
      DAT_006543b8 = DAT_006543b8 + 4;
      local_10 = local_10 + -1;
      DAT_006543a8[2] = DAT_006543a8[2] + 1;
    } while (local_10 != 0);
  }
  DAT_0059c498 = 1;
  return;
}


