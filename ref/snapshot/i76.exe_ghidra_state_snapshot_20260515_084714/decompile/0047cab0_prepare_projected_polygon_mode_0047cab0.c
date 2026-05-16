/*
 * Program: i76.exe
 * Function: prepare_projected_polygon_mode_0047cab0
 * Entry: 0047cab0
 * Signature: int __cdecl prepare_projected_polygon_mode_0047cab0(undefined4 param_1, void * param_2, void * param_3, int param_4)
 */


/* [cgpt i76.exe GEO raster table renames v35; confidence=medium] Rare clip/prepare table target in
   g_geo_raster_clip_prepare_table and also appears in draw/mode table. */

int __cdecl
prepare_projected_polygon_mode_0047cab0(undefined4 param_1,void *param_2,void *param_3,int param_4)

{
  memmove(param_2,param_3,param_4 * 0x18);
  return param_4;
}


