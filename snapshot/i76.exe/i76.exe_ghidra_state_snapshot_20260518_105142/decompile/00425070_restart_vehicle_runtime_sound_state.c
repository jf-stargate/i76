/*
 * Program: i76.exe
 * Function: restart_vehicle_runtime_sound_state
 * Entry: 00425070
 * Signature: undefined __cdecl restart_vehicle_runtime_sound_state(int param_1)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Vehicle sound-state restart
   helper called after destruction/lifecycle flag transitions. */

void __cdecl restart_vehicle_runtime_sound_state(int param_1)

{
  int iVar1;
  char *_Source;
  int *piVar2;
  float10 fVar3;
  char local_14 [16];
  float local_4;
  
  iVar1 = world_object_has_optional_runtime_flag(param_1);
  if (iVar1 != 0) {
    iVar1 = get_vehicle_runtime_context(param_1);
    if (((iVar1 != 0) && (piVar2 = *(int **)(*(int *)(iVar1 + 0x3c4) + 0x70), piVar2 != (int *)0x0))
       && (&stack0x00000000 != (undefined1 *)0x14)) {
      _Source = get_engine_damage_state_sound_name(piVar2);
      if (_Source != (char *)0x0) {
        strncpy(local_14,_Source,0xd);
        fVar3 = get_engine_damage_state_sound_duration(piVar2);
        local_4 = (float)fVar3;
        piVar2 = find_audio_object_by_name_and_world_object(local_14,0);
        release_audio_object_if_present(piVar2);
      }
    }
  }
  return;
}


