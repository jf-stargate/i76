/*
 * Program: i76.exe
 * Function: set_audio_object_playback_flags_and_queue
 * Entry: 00422d20
 * Signature: undefined4 __cdecl set_audio_object_playback_flags_and_queue(int * param_1, uint param_2)
 */


/* cgpt rename v3: Stops any currently playing buffer, moves the object to the correct audio list,
   and applies playback state flags. */

undefined4 __cdecl set_audio_object_playback_flags_and_queue(int *param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  piVar2 = param_1;
  uVar4 = param_2;
  if (param_1[0xf] == 0) {
    uVar4 = 0;
  }
  if (uVar4 == 0x40) {
    piVar1 = (int *)param_1[0x15];
    if ((piVar1 != (int *)0x0) && (param_1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 0x24))(piVar1,&param_1);
      param_1 = (int *)((uint)param_1 & 1);
      if (param_1 != (int *)0x0) {
        (**(code **)(*(int *)piVar2[0x15] + 0x48))((int *)piVar2[0x15]);
        piVar2[0x1e] = piVar2[0x1e] & 0xfffffffb;
        piVar2[0x18] = piVar2[0x18] + -1;
      }
    }
    iVar3 = move_audio_object_between_active_and_pending_lists(piVar2,(undefined4 *)0x0);
    if (iVar3 != 0) {
      piVar2[0x1e] = piVar2[0x1e] | 0x40;
      return 1;
    }
  }
  else if (param_1[0xf] == 1) {
    piVar1 = (int *)param_1[0x15];
    if ((piVar1 != (int *)0x0) && (param_1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 0x24))(piVar1,&param_1);
      param_1 = (int *)((uint)param_1 & 1);
      if (param_1 != (int *)0x0) {
        (**(code **)(*(int *)piVar2[0x15] + 0x48))((int *)piVar2[0x15]);
        piVar2[0x1e] = piVar2[0x1e] & 0xfffffffb;
        piVar2[0x18] = piVar2[0x18] + -1;
      }
    }
    iVar3 = move_audio_object_between_active_and_pending_lists(piVar2,(undefined4 *)0x0);
    if (iVar3 != 0) {
      piVar2[0x1e] = piVar2[0x1e] | uVar4;
      return 1;
    }
  }
  else {
    if (param_1[0x19] != 0) {
      release_audio_object_resource_and_buffers(param_1);
      return 0;
    }
    piVar1 = (int *)param_1[0x15];
    if ((piVar1 != (int *)0x0) && (param_1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 0x24))(piVar1,&param_1);
      param_1 = (int *)((uint)param_1 & 1);
      if (param_1 != (int *)0x0) {
        (**(code **)(*(int *)piVar2[0x15] + 0x48))((int *)piVar2[0x15]);
        piVar2[0x1e] = piVar2[0x1e] & 0xfffffffb;
        piVar2[0x18] = piVar2[0x18] + -1;
      }
    }
    iVar3 = move_audio_object_between_active_and_pending_lists(piVar2,(undefined4 *)0x0);
    if (iVar3 != 0) {
      piVar2[0x1e] = piVar2[0x1e] | uVar4;
      return 1;
    }
  }
  return 0;
}


