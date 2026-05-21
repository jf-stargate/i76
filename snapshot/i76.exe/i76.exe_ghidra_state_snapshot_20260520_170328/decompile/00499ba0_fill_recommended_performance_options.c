/*
 * Program: i76.exe
 * Function: fill_recommended_performance_options
 * Entry: 00499ba0
 * Signature: undefined __cdecl fill_recommended_performance_options(undefined4 * param_1)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=medium-high] Fills recommended
   performance/video option profile values.
   
   [cgpt_i76exe_render_mode_v13] proposed=fill_recommended_display_performance_options :: Builds
   default display/performance option block used before I76PLYR.DEF overrides. */

void __cdecl fill_recommended_performance_options(undefined4 *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  int iVar3;
  
  if (DAT_005a7ca4 < 0xa6) {
    if (DAT_005a7ca4 < 0x85) {
      iVar3 = 0;
    }
    else {
      iVar3 = (0x1dfffff < DAT_005a7ca8) + 1;
    }
  }
  else {
    iVar3 = 3;
  }
  bVar1 = is_miss16_high_color_resource_mode();
  if ((CONCAT31(extraout_var,bVar1) != 0) || (g_cmdline_hardware_raster_requested != 0)) {
    iVar2 = iVar3 * 0x10;
    (&DAT_004fe201)[iVar2] = 1;
    (&DAT_004fe20f)[iVar2] = 1;
    (&DAT_004fe20b)[iVar2] = 1;
  }
  iVar3 = iVar3 * 0x10;
  *param_1 = *(undefined4 *)(&DAT_004fe200 + iVar3);
  param_1[1] = *(undefined4 *)(iVar3 + 0x4fe204);
  param_1[2] = *(undefined4 *)(iVar3 + 0x4fe208);
  param_1[3] = *(undefined4 *)(iVar3 + 0x4fe20c);
  return;
}


