/*
 * Program: i76.exe
 * Function: initialize_video_memory_texture_cache_record
 * Entry: 0042f5f0
 * Signature: undefined __cdecl initialize_video_memory_texture_cache_record(undefined4 * param_1, uint * param_2, uint param_3)
 */


/* cgpt rename v4: Initializes a packed video-memory texture cache record from texture dimensions,
   mode flags, and current cache generation. */

void __cdecl
initialize_video_memory_texture_cache_record(undefined4 *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = *param_2;
  uVar1 = (int)(param_2[1] * 8) >> 3;
  if (DAT_005280d4 != 0) {
    if ((int)uVar3 < (int)uVar1) {
      uVar3 = uVar1;
    }
    uVar1 = uVar3;
    uVar3 = uVar1;
    if (0x80 < (int)uVar1) {
      uVar3 = 0x80;
      uVar1 = 0x80;
    }
  }
  if ((uVar1 | uVar3) == 1) {
    uVar1 = 2;
    uVar3 = 2;
  }
  if (((DAT_005280e0 != 0) && ((param_2[1] & 0x20000000) == 0)) && (param_3 != 2)) {
    if (0x20 < (int)uVar3) {
      uVar3 = (int)uVar3 >> 1;
    }
    if (0x20 < (int)uVar1) {
      uVar1 = (int)uVar1 >> 1;
    }
  }
  *param_1 = param_2;
  param_1[2] = 0;
  param_1[1] = (param_3 & 3) << 0x12 ^ uVar3 & 0x1ff | (uVar1 & 0x1ff) << 9;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  uVar2 = get_current_texture_cache_generation();
  param_1[3] = uVar2;
  return;
}


