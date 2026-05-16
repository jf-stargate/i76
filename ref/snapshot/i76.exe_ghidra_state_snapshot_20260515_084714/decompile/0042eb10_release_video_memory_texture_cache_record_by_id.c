/*
 * Program: i76.exe
 * Function: release_video_memory_texture_cache_record_by_id
 * Entry: 0042eb10
 * Signature: undefined __cdecl release_video_memory_texture_cache_record_by_id(uint param_1)
 */


/* cgpt rename v8 display/d3d cluster: Finds a video-memory texture cache record by id, releases its
   DirectDraw surfaces/backing bitmap context, compacts the cache array, or delegates to alternate
   renderer callback. */

void __cdecl release_video_memory_texture_cache_record_by_id(uint param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  
  if (DAT_00504be8 == 0) {
    iVar5 = 0;
    iVar3 = DAT_0052b910;
    if (0 < DAT_0052b910) {
      do {
        iVar1 = iVar3 + iVar5 >> 1;
        if ((uint)(&DAT_005280f0)[iVar1 * 7] < param_1) {
          iVar5 = iVar1 + 1;
          iVar1 = iVar3;
        }
        iVar3 = iVar1;
      } while (iVar5 < iVar1);
    }
    if ((&DAT_005280f0)[iVar5 * 7] == param_1) {
      if ((&DAT_00528100)[iVar5 * 7] != 0) {
        DAT_0052b914 = DAT_0052b914 +
                       ((&DAT_005280f4)[iVar5 * 7] & 0x1ff) *
                       ((uint)(&DAT_005280f4)[iVar5 * 7] >> 9 & 0x1ff) * 2;
        (**(code **)(*(int *)(&DAT_00528108)[iVar5 * 7] + 0x1c))((int *)(&DAT_00528108)[iVar5 * 7]);
        (**(code **)(*(int *)(&DAT_00528108)[iVar5 * 7] + 8))((int *)(&DAT_00528108)[iVar5 * 7]);
        (**(code **)(*(int *)(&DAT_00528104)[iVar5 * 7] + 8))((int *)(&DAT_00528104)[iVar5 * 7]);
        (&DAT_00528100)[iVar5 * 7] = 0;
        (&DAT_00528108)[iVar5 * 7] = 0;
        (&DAT_00528104)[iVar5 * 7] = 0;
      }
      iVar5 = iVar5 + 1;
      if (iVar5 < DAT_0052b910) {
        iVar3 = DAT_0052b910 - iVar5;
        puVar2 = &DAT_005280f0 + iVar5 * 7;
        do {
          iVar3 = iVar3 + -1;
          puVar4 = puVar2;
          puVar6 = puVar2 + -7;
          for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          puVar2 = puVar2 + 7;
        } while (iVar3 != 0);
      }
      DAT_0052b910 = DAT_0052b910 + -1;
      (&DAT_005280f0)[DAT_0052b910 * 7] = 0;
    }
    return;
  }
  (*DAT_00608bc0)(0xc,param_1 + 8);
  return;
}


