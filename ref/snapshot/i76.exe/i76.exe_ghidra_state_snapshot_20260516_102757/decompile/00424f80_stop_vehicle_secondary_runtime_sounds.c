/*
 * Program: i76.exe
 * Function: stop_vehicle_secondary_runtime_sounds
 * Entry: 00424f80
 * Signature: undefined __cdecl stop_vehicle_secondary_runtime_sounds(int param_1)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Second vehicle audio
   cleanup helper used during vehicle destruction/removal. */

void __cdecl stop_vehicle_secondary_runtime_sounds(int param_1)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((iVar1 != 0) && (iVar1 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar1 != 0)) {
    pcVar2 = get_engine_event_sound_name(iVar1);
    if (pcVar2 != (char *)0x0) {
      piVar3 = find_audio_object_by_name_and_world_object(pcVar2,param_1);
      release_audio_object_if_present(piVar3);
    }
  }
  return;
}


