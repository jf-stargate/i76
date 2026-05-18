/*
 * Program: i76.exe
 * Function: update_audio_object_buffer_volume_pan_and_release_target
 * Entry: 004217e0
 * Signature: undefined __cdecl update_audio_object_buffer_volume_pan_and_release_target(int param_1, int param_2)
 */


/* cgpt rename v3: Updates DirectSound buffer volume/pan state for an audio object and releases its
   associated world-object reference when needed. */

void __cdecl update_audio_object_buffer_volume_pan_and_release_target(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 != 0) {
    if ((*(byte *)(param_1 + 0x14) & 0x20) != 0) {
      piVar1 = *(int **)(param_1 + 0x54);
      iVar2 = *piVar1;
      uVar3 = ftol();
      (**(code **)(iVar2 + 0x44))(piVar1,uVar3);
    }
    if ((DAT_0052467c == 0) && ((*(uint *)(param_1 + 0x14) & 0x40) != 0)) {
      piVar1 = *(int **)(param_1 + 0x54);
      iVar2 = *piVar1;
      ftol();
      uVar3 = ftol();
      (**(code **)(iVar2 + 0x3c))(piVar1,uVar3);
    }
    if (*(int *)(param_1 + 0x5c) == 0) {
      if ((*(int *)(param_1 + 0x14) != 0) && ((*(byte *)(param_1 + 0x78) & 0x10) == 0)) {
        piVar1 = *(int **)(param_1 + 0x54);
        iVar2 = *piVar1;
        uVar3 = ftol();
        (**(code **)(iVar2 + 0x40))(piVar1,uVar3);
        *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfffffe1f;
        return;
      }
    }
    else if (*(int *)(DAT_00524564 + 8) != 0) {
      update_audio_listener_transform_from_camera_object(param_1);
      if ((*(uint *)(param_1 + 0x14) & 0x200) != 0) {
        if (*(int *)(param_1 + 0x3c) == 1) {
          finalize_released_world_object_after_damage(*(LPVOID *)(param_1 + 0x5c),&PTR_DAT_004ed7ec)
          ;
        }
        *(undefined4 *)(param_1 + 0x5c) = 0;
        *(uint *)(param_1 + 0x78) = *(uint *)(param_1 + 0x78) | 0x10;
      }
      if (param_2 != 0) {
        (**(code **)(**(int **)(DAT_00524564 + 8) + 0x44))(*(int **)(DAT_00524564 + 8));
      }
    }
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfffffe1f;
  }
  return;
}


