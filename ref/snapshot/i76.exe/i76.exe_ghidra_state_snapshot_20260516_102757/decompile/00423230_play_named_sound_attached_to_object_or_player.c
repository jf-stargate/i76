/*
 * Program: i76.exe
 * Function: play_named_sound_attached_to_object_or_player
 * Entry: 00423230
 * Signature: int * __cdecl play_named_sound_attached_to_object_or_player(char * param_1, int param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium_high] Builds default 3D sound
   parameters and plays a named sound attached to a supplied object, falling back to active player
   object. */

int * __cdecl
play_named_sound_attached_to_object_or_player(char *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  int *piVar2;
  int local_1c [3];
  undefined4 local_10;
  
  piVar2 = (int *)0x0;
  initialize_audio_gate_params_defaults(local_1c);
  local_10 = 2;
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
    piVar2 = create_or_queue_positional_audio_object(param_1,param_2,param_3,local_1c);
  }
  return piVar2;
}


