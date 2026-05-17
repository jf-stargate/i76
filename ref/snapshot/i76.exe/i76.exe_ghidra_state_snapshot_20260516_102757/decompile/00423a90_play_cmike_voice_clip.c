/*
 * Program: i76.exe
 * Function: play_cmike_voice_clip
 * Entry: 00423a90
 * Signature: undefined __cdecl play_cmike_voice_clip(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references cmike.wav */

void __cdecl play_cmike_voice_clip(int param_1)

{
  undefined4 uVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  LPVOID pvVar4;
  int iVar5;
  LPVOID pvVar6;
  
  pvVar2 = DAT_0052457c;
  pvVar4 = DAT_0052457c;
  pvVar6 = DAT_0052457c;
  while (pvVar3 = pvVar4, pvVar3 != (LPVOID)0x0) {
    if (*(int *)((int)pvVar3 + 0x10) == param_1) {
      if (pvVar3 == pvVar2) {
        update_timer_or_frame_delta(s_cmike_wav_004ed884,param_1,2);
        pvVar6 = DAT_0052457c;
      }
      else {
        uVar1 = *(undefined4 *)((int)pvVar3 + 0x20);
        iVar5 = world_object_has_optional_runtime_flag(*(int *)((int)pvVar3 + 0x10));
        if ((iVar5 != 0) && (iVar5 = cockpit_gauge_context_helper_00459d90(), iVar5 != 0)) {
          cockpit_hud_texture_context_helper_00459d60();
        }
        if (*(undefined4 **)((int)pvVar3 + 0x14) != (undefined4 *)0x0) {
          release_audio_object_if_present(*(undefined4 **)((int)pvVar3 + 0x14));
        }
        xfree_global_heap(pvVar3);
        *(undefined4 *)((int)pvVar6 + 0x20) = uVar1;
      }
      pvVar2 = DAT_0052457c;
      if (pvVar6 == (LPVOID)0x0) {
        pvVar4 = (LPVOID)0x0;
      }
      else {
        pvVar4 = *(LPVOID *)((int)pvVar6 + 0x20);
      }
    }
    else {
      pvVar4 = *(LPVOID *)((int)pvVar3 + 0x20);
      pvVar6 = pvVar3;
    }
  }
  return;
}


