/*
 * Program: i76.exe
 * Function: update_cockpit_status_warning_indicators
 * Entry: 0045a450
 * Signature: undefined __cdecl update_cockpit_status_warning_indicators(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references zsy_.map and CWSTAT.WAV */

void __cdecl update_cockpit_status_warning_indicators(int param_1)

{
  byte *pbVar1;
  uint uVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar6 = *(int *)(param_1 + 0x70);
  uVar2 = *(uint *)(iVar6 + 0x420);
  pbVar1 = (byte *)(s_zsy_320_map_004f64da + DAT_004f67ec * 0xd);
  if (uVar2 != 0) {
    local_20 = iVar6;
    extract_engine_or_suspension_state_pair(*(int *)(iVar6 + 0x3c4),&local_58,&local_1c);
    local_58 = ftol();
    extract_engine_or_suspension_state_pair(*(int *)(iVar6 + 0x3c8),&local_54,&local_18);
    local_54 = ftol();
    extract_part_damage_state_pair(*(int *)(iVar6 + 0x3cc),&local_50,&local_14);
    local_50 = ftol();
    extract_part_damage_state_pair(*(int *)(iVar6 + 0x3b8),&local_4c,&local_10);
    local_4c = ftol();
    extract_part_damage_state_pair(*(int *)(iVar6 + 0x3bc),&local_48,&local_c);
    local_48 = ftol();
    extract_part_damage_state_pair(*(int *)(iVar6 + 0x3a8),&local_44,&local_8);
    local_44 = ftol();
    extract_part_damage_state_pair(*(int *)(iVar6 + 0x3ac),&local_40,&local_4);
    local_40 = ftol();
    bVar3 = false;
    iVar6 = 0;
    do {
      iVar5 = iVar6 * 0x18;
      if ((((int)(&DAT_004f62f0)[iVar6 * 6] <= local_58) &&
          (local_58 <= (int)(&DAT_004f62f4)[iVar6 * 6])) && (iVar6 != DAT_0054a418)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3engine_004f5e20 + DAT_004f67ec,
                   s_3engine_off_004f62e0 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a418 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6368)[iVar6 * 6] <= local_54) &&
          (local_54 <= (int)(&DAT_004f636c)[iVar6 * 6])) && (iVar6 != DAT_0054a41c)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3suspen_004f5e30 + DAT_004f67ec,
                   s_3suspen_off_004f6358 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a41c = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f63e0)[iVar6 * 6] <= local_50) &&
          (local_50 <= (int)(&DAT_004f63e4)[iVar6 * 6])) && (iVar6 != DAT_0054a420)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3brakes_004f5e40 + DAT_004f67ec,
                   s_3brakes_off_004f63d0 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a420 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6458)[iVar6 * 6] <= local_4c) &&
          (local_4c <= (int)(&DAT_004f645c)[iVar6 * 6])) && (iVar6 != DAT_0054a424)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3rrtire_004f5e50 + DAT_004f67ec,
                   s_3tire_off_004f6448 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a424 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6458)[iVar6 * 6] <= local_48) &&
          (local_48 <= (int)(&DAT_004f645c)[iVar6 * 6])) && (iVar6 != DAT_0054a428)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3rltire_004f5e60 + DAT_004f67ec,
                   s_3tire_off_004f6448 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a428 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6458)[iVar6 * 6] <= local_44) &&
          (local_44 <= (int)(&DAT_004f645c)[iVar6 * 6])) && (iVar6 != DAT_0054a42c)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3frtire_004f5e70 + DAT_004f67ec,
                   s_3tire_off_004f6448 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a42c = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6458)[iVar6 * 6] <= local_40) &&
          (local_40 <= (int)(&DAT_004f645c)[iVar6 * 6])) && (iVar6 != DAT_0054a430)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3fltire_004f5e80 + DAT_004f67ec,
                   s_3tire_off_004f6448 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054a430 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 5);
    local_3c = ftol();
    local_30 = ftol();
    local_38 = ftol();
    local_34 = ftol();
    local_2c = ftol();
    local_20 = ftol();
    local_28 = ftol();
    local_24 = ftol();
    iVar6 = 0;
    do {
      iVar5 = iVar6 * 0x18;
      if ((((int)(&DAT_004f5f30)[iVar6 * 6] <= local_3c) &&
          (local_3c <= (int)(&DAT_004f5f34)[iVar6 * 6])) && (iVar6 != DAT_0054abd0)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3farm_004f5da0 + DAT_004f67ec,
                   s_3farm_off_004f5f20 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abd0 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f5fa8)[iVar6 * 6] <= local_38) &&
          (local_38 <= (int)(&DAT_004f5fac)[iVar6 * 6])) && (iVar6 != DAT_0054abd8)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3rarm_004f5dc0 + DAT_004f67ec,
                   s_3rarm_off_004f5f98 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abd8 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6020)[iVar6 * 6] <= local_34) &&
          (local_34 <= (int)(&DAT_004f6024)[iVar6 * 6])) && (iVar6 != DAT_0054abdc)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3barm_004f5dd0 + DAT_004f67ec,
                   s_3barm_off_004f6010 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abdc = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6098)[iVar6 * 6] <= local_30) &&
          (local_30 <= (int)(&DAT_004f609c)[iVar6 * 6])) && (iVar6 != DAT_0054abd4)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3larm_004f5db0 + DAT_004f67ec,
                   s_3larm_off_004f6088 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abd4 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6110)[iVar6 * 6] <= local_2c) &&
          (local_2c <= (int)(&DAT_004f6114)[iVar6 * 6])) && (iVar6 != DAT_0054abe0)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3fchas_004f5de0 + DAT_004f67ec,
                   s_3fchas_off_004f6100 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abe0 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6188)[iVar6 * 6] <= local_28) &&
          (local_28 <= (int)(&DAT_004f618c)[iVar6 * 6])) && (iVar6 != DAT_0054abe8)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3rchas_004f5e00 + DAT_004f67ec,
                   s_3rchas_off_004f6178 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abe8 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6200)[iVar6 * 6] <= local_24) &&
          (local_24 <= (int)(&DAT_004f6204)[iVar6 * 6])) && (iVar6 != DAT_0054abec)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3bchas_004f5e10 + DAT_004f67ec,
                   s_3bchas_off_004f61f0 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abec = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      if ((((int)(&DAT_004f6278)[iVar6 * 6] <= local_20) &&
          (local_20 <= (int)(&DAT_004f627c)[iVar6 * 6])) && (iVar6 != DAT_0054abe4)) {
        draw_texture_widget_to_hud_surface_and_bind_object
                  (uVar2,pbVar1,s_3lchas_004f5df0 + DAT_004f67ec,
                   s_3lchas_off_004f6268 + iVar5 + DAT_004f67ec,&DAT_0054ab98,0);
        bVar3 = true;
        DAT_0054abe4 = iVar6;
        if (iVar6 == 4) {
          play_sound_if_object_tree_is_audible(s_CWSTAT_WAV_004f7138,uVar2,(undefined4 *)0x0);
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 5);
    if (bVar3) {
      pcVar7 = s_Status_004f7130;
      piVar4 = (int *)bind_or_load_texture_set_for_object(uVar2,pbVar1,0);
      mark_texture_set_binding_dirty_or_track_special_view(piVar4,pcVar7);
    }
  }
  return;
}


