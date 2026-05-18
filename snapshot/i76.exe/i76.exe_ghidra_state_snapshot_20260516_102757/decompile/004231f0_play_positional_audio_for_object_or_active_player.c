/*
 * Program: i76.exe
 * Function: play_positional_audio_for_object_or_active_player
 * Entry: 004231f0
 * Signature: int * __cdecl play_positional_audio_for_object_or_active_player(char * param_1, int param_2, undefined4 * param_3)
 */


/* cgpt rename v3: Plays a named positional sound on a supplied world object, falling back to the
   active player/camera object when no object is supplied. */

int * __cdecl
play_positional_audio_for_object_or_active_player(char *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  int *piVar2;
  
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
    piVar2 = create_or_queue_positional_audio_object(param_1,param_2,param_3,(int *)0x0);
  }
  return piVar2;
}


