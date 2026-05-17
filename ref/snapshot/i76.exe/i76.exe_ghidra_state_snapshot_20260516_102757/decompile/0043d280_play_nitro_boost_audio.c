/*
 * Program: i76.exe
 * Function: play_nitro_boost_audio
 * Entry: 0043d280
 * Signature: undefined __stdcall play_nitro_boost_audio(void)
 */


/* cgpt whole-binary semantic rename v1: references bnitro.wav */

void play_nitro_boost_audio(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  iVar1 = *piVar2;
  iVar3 = get_vehicle_runtime_context(iVar1);
  iVar4 = find_active_special_equipment_component_by_index(iVar3,2);
  if (iVar4 != 0) {
    vehicle_damage_component_runtime_context_helper_00466e50(iVar3,0x800,0x41700000);
    play_positional_audio_for_object_or_active_player(s_bnitro_wav_004f1644,iVar1,(undefined4 *)0x0)
    ;
    vehicle_specials_display_texture_context_helper_004677d0(iVar4);
  }
  return;
}


