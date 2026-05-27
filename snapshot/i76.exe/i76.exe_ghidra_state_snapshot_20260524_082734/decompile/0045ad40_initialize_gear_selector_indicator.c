/*
 * Program: i76.exe
 * Function: initialize_gear_selector_indicator
 * Entry: 0045ad40
 * Signature: undefined __cdecl initialize_gear_selector_indicator(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references prnd/park/arrow and VSHIF1A.WAV */

void __cdecl initialize_gear_selector_indicator(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_004f67ec * 0xd;
  uVar1 = *(uint *)(*(int *)(param_1 + 0x70) + 0x438);
  if (uVar1 != 0) {
    iVar3 = get_vehicle_drivetrain_mode_state(param_1);
    if (DAT_0054a338 != iVar3) {
      play_sound_if_object_tree_is_audible(s_VSHIF1A_WAV_004f7160,uVar1,(undefined4 *)0x0);
      DAT_0054a338 = iVar3;
      draw_texture_widget_to_hud_surface_and_bind_object
                (uVar1,(byte *)(s_zgear101_map_004f650e + iVar2),s_prnd_004f714c,s_prndback_004f7154
                 ,&DAT_0054ac30,0);
      draw_texture_widget_to_hud_surface_and_bind_object
                (uVar1,(byte *)(s_zgear101_map_004f650e + iVar2),s_park_004f5ea0 + iVar3 * 0x10,
                 s_arrow_004f7144,&DAT_0054ac30,1);
    }
  }
  return;
}


