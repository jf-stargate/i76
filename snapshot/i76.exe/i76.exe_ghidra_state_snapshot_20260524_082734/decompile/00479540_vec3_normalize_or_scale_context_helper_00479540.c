/*
 * Program: i76.exe
 * Function: vec3_normalize_or_scale_context_helper_00479540
 * Entry: 00479540
 * Signature: undefined __cdecl vec3_normalize_or_scale_context_helper_00479540(int param_1, float * param_2, float * param_3, float * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: vec3 normalize or scale context helper
   based on adjacent named subsystem context. */

void __cdecl
vec3_normalize_or_scale_context_helper_00479540
          (int param_1,float *param_2,float *param_3,float *param_4)

{
  int iVar1;
  
  iVar1 = param_1 * 3;
  *param_2 = (float)*(byte *)((int)&g_palette_cube_sample_points + iVar1) * _DAT_004be698;
  *param_3 = (float)*(byte *)((int)&g_palette_cube_sample_points + iVar1 + 1) * _DAT_004be698;
  *param_4 = (float)*(byte *)((int)&g_palette_cube_sample_points + iVar1 + 2) * _DAT_004be698;
  return;
}


