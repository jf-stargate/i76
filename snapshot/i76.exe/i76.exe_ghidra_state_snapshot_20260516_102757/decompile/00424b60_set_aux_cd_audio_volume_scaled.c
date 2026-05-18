/*
 * Program: i76.exe
 * Function: set_aux_cd_audio_volume_scaled
 * Entry: 00424b60
 * Signature: undefined4 __cdecl set_aux_cd_audio_volume_scaled(int param_1)
 */


/* cgpt readability rename v13 set A: Scales a small volume argument and applies it to the
   auxiliary/CD audio device with auxSetVolume. */

undefined4 __cdecl set_aux_cd_audio_volume_scaled(int param_1)

{
  uint uVar1;
  MMRESULT MVar2;
  
  if (param_1 == 1) {
    param_1 = 0;
  }
  uVar1 = param_1 * 0xccc;
  if (0xfffe < (int)uVar1) {
    uVar1 = 0xffff;
  }
  if (DAT_004ed894 != 0xffffffff) {
    MVar2 = auxSetVolume(DAT_004ed894,uVar1 & 0xffff | (uVar1 & 0xffff) << 0x10);
    if (MVar2 == 0) {
      return 1;
    }
  }
  return 0;
}


