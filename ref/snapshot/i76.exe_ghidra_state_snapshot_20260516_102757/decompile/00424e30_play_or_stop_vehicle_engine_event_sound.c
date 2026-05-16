/*
 * Program: i76.exe
 * Function: play_or_stop_vehicle_engine_event_sound
 * Entry: 00424e30
 * Signature: int * __cdecl play_or_stop_vehicle_engine_event_sound(int param_1, int param_2)
 */


/* cgpt rename v3: Plays a vehicle engine event sound when requested or finds and releases an
   existing event sound when not requested. */

int * __cdecl play_or_stop_vehicle_engine_event_sound(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((iVar1 != 0) && (iVar1 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar1 != 0)) {
    pcVar2 = get_engine_event_sound_name(iVar1);
    if (pcVar2 != (char *)0x0) {
      if (param_2 != 0) {
        piVar3 = create_or_queue_positional_audio_object
                           (pcVar2,param_1,(undefined4 *)0x0,(int *)0x0);
        return piVar3;
      }
      piVar3 = find_audio_object_by_name_and_world_object(pcVar2,param_1);
      release_audio_object_if_present(piVar3);
    }
  }
  return (int *)0x0;
}


