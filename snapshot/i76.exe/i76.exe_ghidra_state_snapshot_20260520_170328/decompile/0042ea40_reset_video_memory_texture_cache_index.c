/*
 * Program: i76.exe
 * Function: reset_video_memory_texture_cache_index
 * Entry: 0042ea40
 * Signature: undefined __stdcall reset_video_memory_texture_cache_index(void)
 */


/* cgpt rename v8 display/d3d cluster: Clears the video-memory texture cache index/counters and
   resets min/max cache id bounds. */

void reset_video_memory_texture_cache_index(void)

{
  DAT_0052b910 = 0;
  DAT_005280f0 = 0;
  DAT_0052b90c = 0xfffffc18;
  DAT_005280e4 = 0xfffffc18;
  DAT_005280ec = 0;
  return;
}


