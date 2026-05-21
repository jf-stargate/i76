/*
 * Program: i76.exe
 * Function: update_audio_listener_cached_vectors_from_active_object
 * Entry: 00422440
 * Signature: undefined __stdcall update_audio_listener_cached_vectors_from_active_object(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Copies active-object listener vectors and camera basis globals
   into the audio listener parameter block. */

void update_audio_listener_cached_vectors_from_active_object(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if ((((DAT_00524564 != 0) && (*(int *)(DAT_00524564 + 8) != 0)) &&
      ((DAT_004c2908 != (int *)0x0 ||
       (DAT_004c2908 = (int *)get_active_player_or_camera_world_object_entry(),
       DAT_004c2908 != (int *)0x0)))) && (*DAT_004c2908 != 0)) {
    get_world_object_damage_or_target_vectors(*DAT_004c2908,&local_c,&local_10);
    DAT_005fcdc4 = (float)_DAT_004c2890;
    DAT_005fcdc8 = (float)_DAT_004c2898;
    DAT_005fcdd0 = local_c;
    DAT_005fcdd4 = local_8;
    DAT_005fcdd8 = local_4;
    _DAT_005fcddc = DAT_004c2778;
    _DAT_005fcde0 = DAT_004c2784;
    DAT_005fcdcc = (float)_DAT_004c28a0;
    _DAT_005fcde4 = DAT_004c2790;
    _DAT_005fcde8 = DAT_004c2774;
    _DAT_005fcdec = DAT_004c2780;
    _DAT_005fcdf0 = DAT_004c278c;
    (**(code **)(**(int **)(DAT_00524564 + 8) + 0x28))(*(int **)(DAT_00524564 + 8),&DAT_005fcdc0,1);
  }
  return;
}


