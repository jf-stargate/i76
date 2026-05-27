/*
 * Program: i76.exe
 * Function: compute_projected_triangle_barycentric_matrix
 * Entry: 0048d140
 * Signature: undefined __cdecl compute_projected_triangle_barycentric_matrix(int * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Computes a projected triangle
   inverse/barycentric coefficient matrix used for raster attribute gradients. */

void __cdecl compute_projected_triangle_barycentric_matrix(int *param_1,float *param_2)

{
  _DAT_0059bcd4 = *(float *)*param_1;
  _DAT_0059bcd8 = *(float *)param_1[1];
  _DAT_0059bcd0 = *(float *)param_1[2];
  _DAT_0059bce0 = *(float *)(*param_1 + 4);
  _DAT_0059bbe8 = _DAT_0059bcd0 * _DAT_0059bce0;
  _DAT_0059bbd8 = _DAT_0059bcd8 * _DAT_0059bce0;
  _DAT_0059bce4 = *(float *)(param_1[1] + 4);
  _DAT_0059bbec = _DAT_0059bcd0 * _DAT_0059bce4;
  _DAT_0059bcdc = *(float *)(param_1[2] + 4);
  _DAT_0059bbdc = _DAT_0059bcdc * _DAT_0059bcd8;
  _DAT_0059bbc4 = _DAT_0059bcdc * _DAT_0059bcd4;
  _DAT_0059bbc0 = _DAT_0059bce4 * _DAT_0059bcd4;
  _DAT_0059bc98 =
       _DAT_004be778 /
       ((((_DAT_0059bbe8 + (_DAT_0059bbdc - _DAT_0059bbec)) - _DAT_0059bbc4) + _DAT_0059bbc0) -
       _DAT_0059bbd8);
  *param_2 = _DAT_0059bc98 * (_DAT_0059bbdc - _DAT_0059bbec);
  param_2[3] = (_DAT_0059bbe8 - _DAT_0059bbc4) * _DAT_0059bc98;
  param_2[6] = (_DAT_0059bbc0 - _DAT_0059bbd8) * _DAT_0059bc98;
  param_2[1] = (_DAT_0059bce4 - _DAT_0059bcdc) * _DAT_0059bc98;
  param_2[4] = (_DAT_0059bcdc - _DAT_0059bce0) * _DAT_0059bc98;
  param_2[7] = (_DAT_0059bce0 - _DAT_0059bce4) * _DAT_0059bc98;
  param_2[2] = (_DAT_0059bcd0 - _DAT_0059bcd8) * _DAT_0059bc98;
  param_2[5] = (_DAT_0059bcd4 - _DAT_0059bcd0) * _DAT_0059bc98;
  param_2[8] = (_DAT_0059bcd8 - _DAT_0059bcd4) * _DAT_0059bc98;
  return;
}


