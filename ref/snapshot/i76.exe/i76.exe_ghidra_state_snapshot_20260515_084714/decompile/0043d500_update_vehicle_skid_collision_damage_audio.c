/*
 * Program: i76.exe
 * Function: update_vehicle_skid_collision_damage_audio
 * Entry: 0043d500
 * Signature: undefined __cdecl update_vehicle_skid_collision_damage_audio(int param_1, uint param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Per-frame vehicle audio
   feedback path for tire flat, body damage, tire skid/contact, and brake/damage related WAV
   triggers. */

void __cdecl update_vehicle_skid_collision_damage_audio(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  char *pcVar4;
  
  iVar2 = *(int *)(param_1 + 0x70);
  iVar1 = world_object_has_optional_runtime_flag(param_1);
  bVar3 = false;
  if ((iVar1 != 0) && ((param_2 & 4) == 0)) {
    if (((param_2 & 2) != 0) && ((&PTR_s_tskid2_wav_004bd0d0)[param_3 * 3] != (char *)0x0)) {
      bVar3 = true;
      play_named_sound_attached_to_object_or_player
                ((&PTR_s_tskid2_wav_004bd0d0)[param_3 * 3],param_1,(undefined4 *)0x0);
    }
    if (_DAT_004bd1f4 < *(float *)(iVar2 + 0xac)) {
      if ((!bVar3) &&
         ((((param_2 & 0x2000) != 0 &&
           (pcVar4 = (&PTR_s_tturn2_wav_004bd0d4)[param_3 * 3], pcVar4 != (char *)0x0)) ||
          (pcVar4 = (&PTR_s_vcddirt_wav_004bd0d8)[param_3 * 3], pcVar4 != (char *)0x0)))) {
        play_named_sound_attached_to_object_or_player(pcVar4,param_1,(undefined4 *)0x0);
      }
      iVar1 = is_tire_contact_active(*(int *)(iVar2 + 0x3ac));
      if (((iVar1 != 0) || (iVar1 = is_tire_contact_active(*(int *)(iVar2 + 0x3a8)), iVar1 != 0)) ||
         ((iVar1 = is_tire_contact_active(*(int *)(iVar2 + 0x3bc)), iVar1 != 0 ||
          (iVar1 = is_tire_contact_active(*(int *)(iVar2 + 0x3b8)), iVar1 != 0)))) {
        play_named_sound_attached_to_object_or_player
                  (s_tflat_wav_004f165c,param_1,(undefined4 *)0x0);
      }
      if ((*(float *)(iVar2 + 0xe4) < _DAT_004bd13c) &&
         (iVar2 = get_vehicle_brake_runtime_component(iVar2),
         *(float *)(iVar2 + 0x10) < *(float *)(iVar2 + 0xc) * _DAT_004bd138)) {
        play_named_sound_attached_to_object_or_player
                  (s_fdmg1_wav_004f1650,param_1,(undefined4 *)0x0);
      }
    }
  }
  return;
}


