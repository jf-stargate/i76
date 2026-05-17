/*
 * Program: i76.exe
 * Function: set_audio_runtime_category_enable_mask
 * Entry: 00421ac0
 * Signature: undefined __cdecl set_audio_runtime_category_enable_mask(uint param_1, uint param_2, uint param_3)
 */


/* cgpt readability rename v13 set A: Updates audio runtime category/channel enable flags,
   substituting default category bits for sentinel arguments. */

void __cdecl set_audio_runtime_category_enable_mask(uint param_1,uint param_2,uint param_3)

{
  if (param_1 == 0xffffffff) {
    param_1 = DAT_00654b90 & 0xff;
  }
  if (param_2 == 0xffffffff) {
    param_2 = DAT_00654b90 >> 8 & 0xff;
  }
  if (param_3 == 0xffffffff) {
    param_3 = DAT_00654b90 >> 0x10 & 0xff;
  }
  if (param_1 == 1) {
    param_1 = 0;
  }
  if (param_2 == 1) {
    param_2 = 0;
  }
  if (param_3 == 1) {
    param_3 = 0;
  }
  if (param_1 != 0xfffffffe) {
    set_aux_cd_audio_volume_scaled(param_1);
  }
  if (DAT_00524564 != 0) {
    if (param_2 != 0xfffffffe) {
      *(uint *)(DAT_00524564 + 0x14) = param_2;
    }
    if (param_3 != 0xfffffffe) {
      *(uint *)(DAT_00524564 + 0x18) = param_3;
    }
  }
  return;
}


