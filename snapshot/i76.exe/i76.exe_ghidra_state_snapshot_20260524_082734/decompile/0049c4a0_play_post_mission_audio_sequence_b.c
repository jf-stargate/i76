/*
 * Program: i76.exe
 * Function: play_post_mission_audio_sequence_b
 * Entry: 0049c4a0
 * Signature: undefined __cdecl play_post_mission_audio_sequence_b(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references GDSGC/POSTA wav sequence */

void __cdecl play_post_mission_audio_sequence_b(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  char *pcVar3;
  undefined4 *puVar4;
  
  iVar2 = get_fsm_registered_instance_count();
  bVar1 = is_voice_speech_channel_available();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    if (DAT_005a7e04 == 0) {
      bVar1 = update_timer_or_frame_delta(s_GDSGC40_WAV_004fe3c0,param_1,5);
      if (CONCAT31(extraout_var_01,bVar1) != 0) {
        puVar4 = &DAT_005a7dc8 + DAT_005a7da8;
        DAT_005a7da8 = DAT_005a7da8 + 1;
        update_timer_or_frame_delta((char *)*puVar4,iVar2,6);
        puVar4 = &DAT_005a7db0 + DAT_005a7dc4;
        DAT_005a7dc4 = DAT_005a7dc4 + 1;
        update_timer_or_frame_delta((char *)*puVar4,param_1,6);
        if (DAT_005a7da8 == 0xf) {
          DAT_005a7da8 = 0;
          puVar4 = &DAT_005a7dc8;
          pcVar3 = s_POSTA01_WAV_004fe2f8;
          do {
            *puVar4 = pcVar3;
            pcVar3 = pcVar3 + 0xd;
            puVar4 = puVar4 + 1;
          } while ((int)pcVar3 < 0x4fe3bb);
          qsort(&DAT_005a7dc8,0xf,4,(_PtFuncCompare *)&LAB_0049c3d0);
        }
        if (DAT_005a7dc4 == 5) {
          DAT_005a7dc4 = 0;
          puVar4 = &DAT_005a7db0;
          pcVar3 = s_GDSGC42_WAV_004fe3d0;
          do {
            *puVar4 = pcVar3;
            pcVar3 = pcVar3 + 0xd;
            puVar4 = puVar4 + 1;
          } while ((int)pcVar3 < 0x4fe411);
          qsort(&DAT_005a7db0,5,4,(_PtFuncCompare *)&LAB_0049c3d0);
        }
      }
    }
    else if (DAT_005a7e08 == 1) {
      bVar1 = update_timer_or_frame_delta(s_GDSGC40_WAV_004fe3c0,param_1,5);
      if (CONCAT31(extraout_var_00,bVar1) != 0) {
        update_timer_or_frame_delta(s_GDSGC41_WAV_004fe414,param_1,6);
        return;
      }
    }
  }
  return;
}


