/*
 * Program: i76.exe
 * Function: play_gang_speech_clip_69
 * Entry: 0040a050
 * Signature: undefined __stdcall play_gang_speech_clip_69(void)
 */


/* cgpt whole-binary semantic rename v1: references gdsgc69.wav */

void play_gang_speech_clip_69(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int local_8;
  int *local_4;
  
  local_8 = 0x19;
  iVar2 = is_damage_side_effects_suppressed();
  if ((iVar2 == 0) && (DAT_0051f5c0 == (int *)0x0)) {
    piVar3 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar3 == (int *)0x0) {
      DAT_0051f5c0 = piVar3;
      return;
    }
    piVar5 = &DAT_00507da0;
    piVar4 = &DAT_0051f5d0;
    local_4 = piVar3;
    do {
      iVar2 = *piVar4;
      piVar6 = piVar5;
      if (0 < iVar2) {
        do {
          piVar1 = (int *)*piVar6;
          if (((piVar1 != (int *)0x0) && (piVar3 != piVar1)) && (*(int *)(*piVar1 + 0x6c) == 9)) {
            fsm_set_helicopter_height(*piVar1,&local_8);
            local_8 = local_8 + 10;
            piVar3 = local_4;
          }
          iVar2 = iVar2 + -1;
          piVar6 = piVar6 + 1;
        } while (iVar2 != 0);
      }
      piVar4 = piVar4 + 1;
      piVar5 = piVar5 + 0x40;
    } while ((int)piVar4 < 0x51f5f0);
    update_timer_or_frame_delta(s_gdsgc69_wav_004c2a60,0,0);
    DAT_0051f5c0 = (int *)0x1;
    iVar2 = *(int *)(*(int *)(*local_4 + 0x70) + 0x108);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0xa948) = 1000;
    }
  }
  return;
}


