/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004922f0
 * Entry: 004922f0
 * Signature: undefined4 __cdecl terrain_map_context_helper_004922f0(int param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004922f0. Remove
   duplicated terrain wording. */

undefined4 __cdecl terrain_map_context_helper_004922f0(int param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  int *piVar7;
  int iVar8;
  
  iVar4 = param_2;
  piVar3 = terrain_map_context_helper_00490590();
  piVar3[3] = 0;
  piVar3[1] = 0xb4;
  piVar5 = (int *)(param_1 + param_2 * 4);
  if (0 < param_2) {
    piVar7 = piVar3 + 0xc;
    do {
      piVar1 = piVar5 + -1;
      piVar5 = piVar5 + -1;
      piVar1 = (int *)(DAT_005dd320 + *piVar1 * 0xc);
      piVar7[-5] = *piVar1;
      piVar7[-4] = piVar1[1];
      piVar7[-3] = piVar1[2];
      if (DAT_005a4618 != 0) {
        param_3 = *(int *)(DAT_005dd2ec + 8 + *piVar5 * 0xc);
      }
      *piVar7 = param_3;
      piVar7 = piVar7 + 6;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  *piVar3 = iVar4;
  fVar2 = (float)piVar3[9];
  if (1 < iVar4) {
    pfVar6 = (float *)(piVar3 + 0xf);
    iVar8 = iVar4 + -1;
    do {
      if (_DAT_004be800 < *pfVar6 - fVar2) {
        fVar2 = *pfVar6;
      }
      pfVar6 = pfVar6 + 6;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  piVar3[4] = (int)fVar2;
  iVar4 = (*(code *)g_geo_raster_clip_prepare_table)(DAT_006442d4,piVar3 + 7,piVar3 + 7,iVar4,0);
  *piVar3 = iVar4;
  if (iVar4 == 0) {
    return 0;
  }
  terrain_map_context_helper_0048fe10((float)piVar3[4]);
  piVar3[2] = DAT_0059c584;
  return 1;
}


