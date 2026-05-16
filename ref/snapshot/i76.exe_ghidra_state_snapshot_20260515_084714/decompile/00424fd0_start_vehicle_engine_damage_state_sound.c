/*
 * Program: i76.exe
 * Function: start_vehicle_engine_damage_state_sound
 * Entry: 00424fd0
 * Signature: float10 __cdecl start_vehicle_engine_damage_state_sound(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Starts an engine
   damage/state sound based on engine condition fraction and returns the selected duration/timing
   scalar. */

float10 __cdecl start_vehicle_engine_damage_state_sound(int param_1)

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
        piVar2 = create_or_queue_positional_audio_object(local_14,0,(undefined4 *)0x0,(int *)0x0);
        if (piVar2 != (int *)0x0) {
          return (float10)local_4;
        }
      }
    }
  }
  return (float10)0.0;
}


