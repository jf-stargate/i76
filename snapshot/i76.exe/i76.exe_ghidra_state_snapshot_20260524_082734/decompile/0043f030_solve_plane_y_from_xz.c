/*
 * Program: i76.exe
 * Function: solve_plane_y_from_xz
 * Entry: 0043f030
 * Signature: float10 __cdecl solve_plane_y_from_xz(int param_1, float param_2, float param_3)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Solves the Y coordinate on a plane from
   X/Z coordinates using stored plane coefficients. */

float10 __cdecl solve_plane_y_from_xz(int param_1,float param_2,float param_3)

{
  return -(((float10)*(float *)(param_1 + 0xc) * (float10)param_3 +
            (float10)*(float *)(param_1 + 4) * (float10)param_2 +
           (float10)*(float *)(param_1 + 0x10)) / (float10)*(float *)(param_1 + 8));
}


