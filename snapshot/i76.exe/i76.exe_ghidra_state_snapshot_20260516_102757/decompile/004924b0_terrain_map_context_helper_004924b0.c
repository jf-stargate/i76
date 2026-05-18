/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004924b0
 * Entry: 004924b0
 * Signature: undefined4 __cdecl terrain_map_context_helper_004924b0(int param_1, int param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004924b0. Remove
   duplicated terrain wording. */

undefined4 __cdecl terrain_map_context_helper_004924b0(int param_1,int param_2,float param_3)

{
  int *piVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  
  piVar3 = terrain_map_context_helper_00490590();
  piVar3[3] = 0;
  piVar3[1] = DAT_0059c558;
  piVar3[2] = DAT_0059c548;
  iVar6 = param_1 + param_2 * 4;
  if (0 < param_2) {
    pfVar5 = (float *)(piVar3 + 10);
    param_1 = param_2;
    do {
      piVar1 = (int *)(iVar6 + -4);
      iVar6 = iVar6 + -4;
      iVar4 = *piVar1 * 0xc;
      pfVar7 = (float *)(DAT_005dd320 + iVar4);
      pfVar5[-3] = *pfVar7;
      pfVar5[-2] = pfVar7[1];
      pfVar5[-1] = pfVar7[2];
      *pfVar5 = *(float *)(DAT_005dd2ec + iVar4) - _DAT_0059c55c;
      pfVar5[1] = *(float *)(DAT_005dd2ec + 4 + iVar4) - _DAT_0059c550;
      if (DAT_005a4618 != 0) {
        param_3 = *(float *)(DAT_005dd2ec + 8 + iVar4);
      }
      pfVar5[2] = param_3;
      pfVar5 = pfVar5 + 6;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  *piVar3 = param_2;
  fVar2 = (float)piVar3[9];
  if (1 < param_2) {
    pfVar5 = (float *)(piVar3 + 0xf);
    iVar6 = param_2 + -1;
    do {
      if (_DAT_004be800 < *pfVar5 - fVar2) {
        fVar2 = *pfVar5;
      }
      pfVar5 = pfVar5 + 6;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  piVar3[4] = (int)fVar2;
  iVar6 = (*(code *)(&g_geo_raster_clip_prepare_table)[piVar3[2]])
                    (DAT_006442d4,piVar3 + 7,piVar3 + 7,param_2,piVar3[2]);
  *piVar3 = iVar6;
  if (iVar6 == 0) {
    return 0;
  }
  terrain_map_context_helper_0048fe10((float)piVar3[4]);
  piVar3[2] = piVar3[2] & 0xffffffefU | 8;
  return 1;
}


