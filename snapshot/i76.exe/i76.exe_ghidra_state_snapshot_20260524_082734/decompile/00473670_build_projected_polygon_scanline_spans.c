/*
 * Program: i76.exe
 * Function: build_projected_polygon_scanline_spans
 * Entry: 00473670
 * Signature: undefined __cdecl build_projected_polygon_scanline_spans(int param_1, uint param_2, float * param_3, int param_4, undefined4 * param_5)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Wrapper for projected polygon
   scanline span construction. */

void __cdecl
build_projected_polygon_scanline_spans
          (int param_1,uint param_2,float *param_3,int param_4,undefined4 *param_5)

{
  if (param_1 != DAT_0058da68) {
    DAT_0058da68 = param_1;
  }
  build_projected_polygon_scanline_spans_impl(&DAT_0058da68,param_2,param_3,param_4,param_5);
  return;
}


