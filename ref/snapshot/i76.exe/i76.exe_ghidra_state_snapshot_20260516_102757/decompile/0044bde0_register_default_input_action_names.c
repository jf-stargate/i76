/*
 * Program: i76.exe
 * Function: register_default_input_action_names
 * Entry: 0044bde0
 * Signature: undefined __cdecl register_default_input_action_names(uint param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: wiggleburger/freelance/getdown/etc */

void __cdecl register_default_input_action_names(uint param_1)

{
  char cVar1;
  char *pcVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  
  iVar5 = 0;
  if ((param_1 & 0xff00) != 0x300) {
    return;
  }
  memmove(&DAT_006092f0,&DAT_006092f1,0xe);
  uVar4 = 0xffffffff;
  pcVar2 = s_wiggleburger_004f2834;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  DAT_006092fe = (undefined1)param_1;
  pcVar6 = &DAT_006092fe;
  pcVar2 = s_freelance_004f2828 + uVar4 + 10;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar6 != *pcVar2) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_freelance_004f2828;
      goto code_r0x0044be5b;
    }
    pcVar2 = pcVar2 + -1;
    pcVar6 = pcVar6 + -1;
  }
  system_cutscene_memory_context_helper_00498700();
  goto LAB_0044c028;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044be5b:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_getdown_004f2820 + uVar4 + 6;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_getdown_004f2820;
      goto code_r0x0044be90;
    }
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  toggle_runtime_camera_debug_or_reverse_flag();
  goto LAB_0044c028;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044be90:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_flflat_004f2818 + uVar4 + 6;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_flflat_004f2818;
      goto code_r0x0044bec5;
    }
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  play_gang_speech_clip_69();
  goto LAB_0044c028;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044bec5:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_frflat_004f2810 + uVar4 + 6;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_frflat_004f2810;
      goto code_r0x0044bf23;
    }
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar3 != (int *)0x0) && (*piVar3 != 0)) {
    param_1 = *(uint *)(*piVar3 + 0x70);
  }
  if (param_1 != 0) {
    iVar5 = *(int *)(param_1 + 0x3ac);
  }
  goto joined_r0x0044bfbd;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044bf23:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_blflat_004f2808 + uVar4 + 6;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_blflat_004f2808;
      goto code_r0x0044bf7d;
    }
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar3 != (int *)0x0) && (*piVar3 != 0)) {
    param_1 = *(uint *)(*piVar3 + 0x70);
  }
  if (param_1 != 0) {
    iVar5 = *(int *)(param_1 + 0x3a8);
    goto joined_r0x0044c010;
  }
  goto joined_r0x0044bfbd;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044bfd0:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_thirdnostril_004f27f0 + uVar4 + 0xe;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) goto LAB_0044c028;
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar3 != (int *)0x0) && (*piVar3 != 0)) {
    param_1 = *(uint *)(*piVar3 + 0x70);
  }
  if (param_1 != 0) {
    iVar5 = *(int *)(param_1 + 0x3b8);
  }
joined_r0x0044c010:
  if (iVar5 == 0) goto LAB_0044c028;
  goto LAB_0044c012;
  while( true ) {
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    if (cVar1 == '\0') break;
code_r0x0044bf7d:
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = s_brflat_004f2800 + uVar4 + 6;
  while (uVar4 = uVar4 - 1, uVar4 != 0) {
    if (*pcVar2 != *pcVar6) {
      uVar4 = 0xffffffff;
      pcVar2 = &DAT_006092fe;
      pcVar6 = s_brflat_004f2800;
      goto code_r0x0044bfd0;
    }
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar3 != (int *)0x0) && (*piVar3 != 0)) {
    param_1 = *(uint *)(*piVar3 + 0x70);
  }
  if (param_1 != 0) {
    iVar5 = *(int *)(param_1 + 0x3bc);
  }
joined_r0x0044bfbd:
  if (iVar5 != 0) {
LAB_0044c012:
    set_damageable_part_state_pair(iVar5,0,0x50);
    play_flat_tire_blowout_sound(iVar5);
  }
LAB_0044c028:
  uVar4 = 0xffffffff;
  pcVar2 = &DAT_006092fe;
  pcVar6 = s_thirdnostril_004f27f0;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = s_Mouse_Down_Up_Movement_004f27d8 + uVar4 + 0x16;
  while( true ) {
    uVar4 = uVar4 - 1;
    if (uVar4 == 0) {
      noop_world_object_callback_stub();
      return;
    }
    if (*pcVar2 != *pcVar6) break;
    pcVar6 = pcVar6 + -1;
    pcVar2 = pcVar2 + -1;
  }
  return;
}


