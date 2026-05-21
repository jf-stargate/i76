/*
 * Program: i76.exe
 * Function: play_flat_tire_blowout_sound
 * Entry: 0046ddd0
 * Signature: undefined __cdecl play_flat_tire_blowout_sound(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Small helper
   referenced by vehicle damage texture state update; anchored by tblow.wav. */

void __cdecl play_flat_tire_blowout_sound(int param_1)

{
  int iVar1;
  float fVar2;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if (*(int *)(iVar1 + 0x44) == 0) {
    fVar2 = *(float *)(iVar1 + 0x1c) * _DAT_004be4c8;
    *(undefined4 *)(iVar1 + 0x44) = 1;
    *(float *)(iVar1 + 0x1c) = fVar2;
    play_positional_audio_for_object_or_active_player
              (s_tblow_wav_004f89c4,param_1,(undefined4 *)0x0);
  }
  return;
}


