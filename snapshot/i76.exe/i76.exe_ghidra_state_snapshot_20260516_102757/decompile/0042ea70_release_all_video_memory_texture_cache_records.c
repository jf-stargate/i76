/*
 * Program: i76.exe
 * Function: release_all_video_memory_texture_cache_records
 * Entry: 0042ea70
 * Signature: undefined __stdcall release_all_video_memory_texture_cache_records(void)
 */


/* cgpt rename v8 display/d3d cluster: Releases all video-memory texture cache records, associated
   DirectDraw surfaces, backing bitmap contexts, and resets the cache index. */

void release_all_video_memory_texture_cache_records(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (DAT_0052b910 != 0) {
    iVar2 = 0;
    if (0 < DAT_0052b910) {
      puVar3 = &DAT_00528108;
      iVar1 = DAT_0052b910;
      do {
        if (puVar3[-2] != 0) {
          DAT_0052b914 = DAT_0052b914 + (puVar3[-5] & 0x1ff) * ((uint)puVar3[-5] >> 9 & 0x1ff) * 2;
          (**(code **)(*(int *)*puVar3 + 0x1c))((int *)*puVar3);
          (**(code **)(*(int *)*puVar3 + 8))((int *)*puVar3);
          (**(code **)(*(int *)puVar3[-1] + 8))((int *)puVar3[-1]);
          iVar1 = DAT_0052b910;
          puVar3[-2] = 0;
          *puVar3 = 0;
          puVar3[-1] = 0;
        }
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 7;
      } while (iVar2 < iVar1);
    }
    vqm_texture_cache_context_helper_00447f70();
    DAT_0052b910 = 0;
    DAT_005280f0 = 0;
    DAT_0052b90c = 0xfffffc18;
    DAT_005280e4 = 0xfffffc18;
    DAT_005280ec = 0;
  }
  return;
}


