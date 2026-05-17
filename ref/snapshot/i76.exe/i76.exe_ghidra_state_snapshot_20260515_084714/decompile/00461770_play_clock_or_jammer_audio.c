/*
 * Program: i76.exe
 * Function: play_clock_or_jammer_audio
 * Entry: 00461770
 * Signature: undefined __cdecl play_clock_or_jammer_audio(int param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: references clockon.wav and cjamm.wav */

void __cdecl play_clock_or_jammer_audio(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = get_vehicle_runtime_context(param_1);
  iVar1 = *(int *)(param_2 + 0x70);
  if (((iVar1 != 0) && (0 < *(int *)(iVar1 + 4))) && (0 < *(int *)(iVar1 + 8))) {
    piVar3 = find_audio_object_by_name_and_world_object(s_clockon_wav_004f1edc,0);
    release_audio_object_if_present(piVar3);
    play_sound_if_object_tree_is_audible(s_cjamm_wav_004f76d4,param_1,(undefined4 *)0x0);
    if (*(int *)(iVar1 + 0x10) == 0) {
      mark_special_equipment_runtime_activated(param_2);
    }
    vehicle_specials_display_texture_context_helper_004677d0(param_2);
    *(uint *)(iVar2 + 0x454) = *(uint *)(iVar2 + 0x454) | 0x40000;
  }
  return;
}


