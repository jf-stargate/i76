/*
 * Program: i76.exe
 * Function: play_post_mission_audio_sequence_a
 * Entry: 0049c400
 * Signature: undefined __stdcall play_post_mission_audio_sequence_a(void)
 */


/* cgpt whole-binary semantic rename v1: references POSTA/GDSGC wav sequence */

void play_post_mission_audio_sequence_a(void)

{
  char *pcVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005a7dc8;
  DAT_005a7e04 = 0;
  DAT_005a7e08 = 0;
  DAT_005a7da8 = 0;
  pcVar1 = s_POSTA01_WAV_004fe2f8;
  do {
    *puVar2 = pcVar1;
    pcVar1 = pcVar1 + 0xd;
    puVar2 = puVar2 + 1;
  } while ((int)pcVar1 < 0x4fe3bb);
  qsort(&DAT_005a7dc8,0xf,4,(_PtFuncCompare *)&LAB_0049c3d0);
  DAT_005a7dc4 = 0;
  puVar2 = &DAT_005a7db0;
  pcVar1 = s_GDSGC42_WAV_004fe3d0;
  do {
    *puVar2 = pcVar1;
    pcVar1 = pcVar1 + 0xd;
    puVar2 = puVar2 + 1;
  } while ((int)pcVar1 < 0x4fe411);
  qsort(&DAT_005a7db0,5,4,(_PtFuncCompare *)&LAB_0049c3d0);
  return;
}


