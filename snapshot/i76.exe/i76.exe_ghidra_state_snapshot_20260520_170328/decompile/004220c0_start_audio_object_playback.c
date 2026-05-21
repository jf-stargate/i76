/*
 * Program: i76.exe
 * Function: start_audio_object_playback
 * Entry: 004220c0
 * Signature: undefined4 __cdecl start_audio_object_playback(int param_1, int param_2)
 */


/* cgpt rename v3: Initializes randomized playback parameters, invokes the audio object start
   callback, starts the DirectSound buffer, and marks the object playing. */

undefined4 __cdecl start_audio_object_playback(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (DAT_004ed7e8 == 0) {
    return 1;
  }
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x3c) == 0) {
      uVar2 = 0;
    }
    else {
      if (*(int *)(param_1 + 0x3c) == 2) {
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
      uVar2 = 1;
    }
    *(float *)(param_1 + 0x1c) = (float)*(int *)(param_1 + 0x40);
    *(float *)(param_1 + 0x18) = (float)*(int *)(param_1 + 0x48);
    if (*(int *)(param_1 + 0x44) != 0) {
      iVar1 = rand();
      *(float *)(param_1 + 0x18) =
           *(float *)(&DAT_004ed7b8 + (iVar1 % 10) * 4) * *(float *)(param_1 + 0x18);
    }
    if ((*(code **)(param_1 + 0x24) != (code *)0x0) &&
       (iVar1 = (**(code **)(param_1 + 0x24))(param_1,1), iVar1 == 0)) {
      return 0;
    }
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x1e0;
    update_audio_object_buffer_volume_pan_and_release_target(param_1,param_2);
    (**(code **)(**(int **)(param_1 + 0x54) + 0x30))(*(int **)(param_1 + 0x54),0,0,uVar2);
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
    *(uint *)(param_1 + 0x78) = *(uint *)(param_1 + 0x78) | 4;
    uVar2 = 1;
  }
  return uVar2;
}


