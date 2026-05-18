/*
 * Program: i76.exe
 * Function: stop_vehicle_engine_loop_sound
 * Entry: 00424df0
 * Signature: undefined __cdecl stop_vehicle_engine_loop_sound(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Stops the active looping
   engine runtime sound associated with a vehicle. */

void __cdecl stop_vehicle_engine_loop_sound(int param_1)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((iVar1 != 0) && (iVar1 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar1 != 0)) {
    pcVar2 = get_engine_loop_sound_name(iVar1);
    piVar3 = find_audio_object_by_name_and_world_object(pcVar2,param_1);
    release_audio_object_if_present(piVar3);
  }
  return;
}


