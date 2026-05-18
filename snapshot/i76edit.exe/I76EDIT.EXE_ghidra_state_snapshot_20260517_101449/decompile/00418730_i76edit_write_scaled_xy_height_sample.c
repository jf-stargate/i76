/*
 * Program: I76EDIT.EXE
 * Function: i76edit_write_scaled_xy_height_sample
 * Entry: 00418730
 * Signature: undefined4 __cdecl i76edit_write_scaled_xy_height_sample(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v3] Writes one 12-byte scaled coordinate/height sample; used by
   terrain/path export helpers.
   
   [cgpt_i76edit_level_renames_v6:high] Writes a scaled XY/height sample record used by road and
   linked-object export helpers. */

undefined4 __cdecl i76edit_write_scaled_xy_height_sample(int param_1,float *param_2)

{
  uint uVar1;
  longlong lVar2;
  int iVar3;
  float local_c;
  float local_8;
  float local_4;
  
  iVar3 = 0;
  local_c = *param_2 * _DAT_004321b0;
  local_4 = param_2[1] * _DAT_004321b0;
  lVar2 = __ftol();
  uVar1 = (uint)lVar2;
  lVar2 = __ftol();
  uVar1 = i76edit_get_or_create_zone_surface_sample((uint)lVar2,uVar1,iVar3);
  local_8 = (float)(int)uVar1 * _DAT_004321a4;
  if (DAT_00436494 == 0) {
    DAT_00436494 = 1;
  }
  __write(param_1,&local_c,0xc);
  return 1;
}


