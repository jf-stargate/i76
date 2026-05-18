/*
 * Program: i76.exe
 * Function: attach_named_sound_to_runtime_object
 * Entry: 004232a0
 * Signature: int * __cdecl attach_named_sound_to_runtime_object(char * param_1, int param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Attaches or plays a named sound
   against a supplied runtime object, or against the current global world/entity context. */

int * __cdecl attach_named_sound_to_runtime_object(char *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 local_2c [11];
  
  piVar2 = (int *)0x0;
  if (param_2 == 0) {
    piVar1 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    param_2 = *piVar1;
    if (param_2 == 0) {
      return (int *)0x0;
    }
  }
  if (param_1 != (char *)0x0) {
    if (param_3 == (undefined4 *)0x0) {
      param_3 = local_2c;
      initialize_audio_distance_params_defaults(local_2c);
    }
    param_3[4] = param_3[4] | 0x200;
    piVar2 = create_or_queue_positional_audio_object(param_1,param_2,param_3,(int *)0x0);
  }
  return piVar2;
}


