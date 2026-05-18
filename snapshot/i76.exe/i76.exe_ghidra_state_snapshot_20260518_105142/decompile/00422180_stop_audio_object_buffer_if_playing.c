/*
 * Program: i76.exe
 * Function: stop_audio_object_buffer_if_playing
 * Entry: 00422180
 * Signature: undefined4 __cdecl stop_audio_object_buffer_if_playing(uint param_1)
 */


/* cgpt rename v3: Checks a DirectSound buffer status and stops it if currently playing, updating
   playback flags/counters. */

undefined4 __cdecl stop_audio_object_buffer_if_playing(uint param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_1;
  if (param_1 != 0) {
    piVar1 = *(int **)(param_1 + 0x54);
    uVar3 = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x24))(piVar1,&param_1);
      uVar3 = param_1 & 1;
    }
    if (uVar3 != 0) {
      (**(code **)(**(int **)(uVar2 + 0x54) + 0x48))(*(int **)(uVar2 + 0x54));
      *(int *)(uVar2 + 0x60) = *(int *)(uVar2 + 0x60) + -1;
      *(uint *)(uVar2 + 0x78) = *(uint *)(uVar2 + 0x78) & 0xfffffffb;
      return 1;
    }
  }
  return 0;
}


