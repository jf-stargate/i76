/*
 * Program: i76.exe
 * Function: video_memory_texture_cache_record_exists
 * Entry: 0042e9c0
 * Signature: uint __cdecl video_memory_texture_cache_record_exists(uint param_1)
 */


/* cgpt rename v8 display/d3d cluster: Checks whether a video-memory texture cache record exists by
   resource/bitmap id, or delegates to the alternate renderer callback. */

uint __cdecl video_memory_texture_cache_record_exists(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (g_cmdline_hardware_raster_requested == 0) {
    if (param_1 != 0) {
      iVar3 = 0;
      iVar4 = DAT_0052b910;
      if (0 < DAT_0052b910) {
        do {
          iVar2 = iVar4 + iVar3 >> 1;
          if ((uint)(&DAT_005280f0)[iVar2 * 7] < param_1) {
            iVar3 = iVar2 + 1;
            iVar2 = iVar4;
          }
          iVar4 = iVar2;
        } while (iVar3 < iVar2);
      }
      return (uint)(param_1 == (&DAT_005280f0)[iVar3 * 7]);
    }
    return 0;
  }
  if (param_1 != 0) {
    uVar1 = (*DAT_00608bc0)(0xb,param_1 + 8);
    return uVar1;
  }
  return 0;
}


