/*
 * Program: i76.exe
 * Function: play_vehicle_engine_event_sound
 * Entry: 00424f10
 * Signature: int * __cdecl play_vehicle_engine_event_sound(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Plays a one-shot
   engine-related vehicle sound selected from the engine component sound table. */

int * __cdecl play_vehicle_engine_event_sound(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  int local_1c [3];
  undefined4 local_10;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((iVar1 != 0) && (iVar1 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar1 != 0)) {
    pcVar2 = get_engine_event_sound_name(iVar1);
    initialize_audio_gate_params_defaults(local_1c);
    if (param_2 != 0) {
      local_10 = 1;
    }
    if (pcVar2 != (char *)0x0) {
      piVar3 = create_or_queue_positional_audio_object(pcVar2,param_1,(undefined4 *)0x0,local_1c);
      return piVar3;
    }
  }
  return (int *)0x0;
}


