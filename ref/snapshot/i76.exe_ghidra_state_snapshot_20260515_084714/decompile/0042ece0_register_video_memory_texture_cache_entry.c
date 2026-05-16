/*
 * Program: i76.exe
 * Function: register_video_memory_texture_cache_entry
 * Entry: 0042ece0
 * Signature: bool __cdecl register_video_memory_texture_cache_entry(uint * param_1, uint param_2)
 */


/* cgpt rename v4: Binary-searches/inserts a texture cache entry and creates/restores its
   video-memory surface. */

bool __cdecl register_video_memory_texture_cache_entry(uint *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_1c [7];
  
  iVar3 = 0;
  iVar2 = DAT_0052b910;
  if (0 < DAT_0052b910) {
    do {
      iVar1 = iVar2 + iVar3 >> 1;
      if ((uint *)(&DAT_005280f0)[iVar1 * 7] < param_1) {
        iVar3 = iVar1 + 1;
        iVar1 = iVar2;
      }
      iVar2 = iVar1;
    } while (iVar3 < iVar1);
  }
  if ((uint *)(&DAT_005280f0)[iVar3 * 7] != param_1) {
    if (0x1ff < DAT_0052b910) {
      return false;
    }
    initialize_video_memory_texture_cache_record(local_1c,param_1,param_2);
    local_1c[3] = 0xffffffff;
    if (iVar3 < DAT_0052b910) {
      iVar2 = DAT_0052b910 - iVar3;
      puVar5 = &DAT_005280f0 + DAT_0052b910 * 7;
      do {
        iVar2 = iVar2 + -1;
        puVar4 = puVar5 + -7;
        puVar6 = puVar5;
        for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar6 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar5 = puVar5 + -7;
      } while (iVar2 != 0);
    }
    DAT_0052b910 = DAT_0052b910 + 1;
    (&DAT_005280f0)[DAT_0052b910 * 7] = 0;
    puVar5 = local_1c;
    puVar4 = &DAT_005280f0 + iVar3 * 7;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar4 = puVar4 + 1;
    }
    create_or_restore_video_memory_texture_surface(&DAT_005280f0 + iVar3 * 7);
  }
  return (&DAT_00528100)[iVar3 * 7] != 0;
}


