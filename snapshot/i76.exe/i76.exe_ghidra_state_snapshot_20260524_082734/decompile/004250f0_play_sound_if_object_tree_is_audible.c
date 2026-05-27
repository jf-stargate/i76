/*
 * Program: i76.exe
 * Function: play_sound_if_object_tree_is_audible
 * Entry: 004250f0
 * Signature: int * __cdecl play_sound_if_object_tree_is_audible(char * param_1, int param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium_high] Plays a named sound only when
   the root ancestor object has the audible/runtime flag set. */

int * __cdecl play_sound_if_object_tree_is_audible(char *param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 != 0) {
    iVar1 = get_root_ancestor_world_object(param_2);
    if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0x10) & 0x10) != 0)) {
      piVar2 = create_or_queue_positional_audio_object(param_1,0,param_3,(int *)0x0);
      return piVar2;
    }
  }
  return (int *)0x0;
}


