/*
 * Program: i76.exe
 * Function: update_timer_or_frame_delta
 * Entry: 00423620
 * Signature: bool __cdecl update_timer_or_frame_delta(char * param_1, int param_2, int param_3)
 */


/* i76 first-pass rename
   old_name: FUN_00423620
   suggested_name: update_timer_or_frame_delta
   basis: Timer/frame-delta candidate; calls GetTickCount in update-like path. */

bool __cdecl update_timer_or_frame_delta(char *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  DWORD DVar7;
  char *pcVar8;
  int *piVar9;
  int local_48;
  undefined4 local_44;
  undefined4 local_2c [4];
  undefined4 local_1c;
  undefined1 *local_4;
  
  if (DAT_00524580 != 0) {
    return false;
  }
  iVar5 = _stricmp(param_1,s_STOPCBXX_004c2dcc);
  if (iVar5 == 0) {
    DAT_00524580 = 1;
    return false;
  }
  if ((param_2 != 0) && ((*(uint *)(param_2 + 0x10) & 0x200) != 0)) {
    return false;
  }
  if (DAT_00654b90._3_1_ < 2) {
    return true;
  }
  if (DAT_00654b90._2_1_ < 2) {
    return true;
  }
  if (DAT_0052457c != (char *)0x0) {
    if (param_3 == 5) {
      return false;
    }
    if ((param_3 == 6) && (*(int *)(DAT_0052457c + 0x18) < 5)) {
      return false;
    }
    pcVar6 = DAT_0052457c;
    if ((param_3 == 1) || ((param_3 < 5 && (4 < *(int *)(DAT_0052457c + 0x18))))) {
      do {
        pcVar8 = *(char **)(pcVar6 + 0x20);
        iVar5 = world_object_has_optional_runtime_flag(*(int *)(pcVar6 + 0x10));
        if ((iVar5 != 0) && (iVar5 = cockpit_gauge_context_helper_00459d90(), iVar5 != 0)) {
          cockpit_hud_texture_context_helper_00459d60();
        }
        if (*(undefined4 **)(pcVar6 + 0x14) != (undefined4 *)0x0) {
          release_audio_object_if_present(*(undefined4 **)(pcVar6 + 0x14));
        }
        xfree_global_heap(pcVar6);
        pcVar6 = pcVar8;
      } while (pcVar8 != (char *)0x0);
      DAT_0052457c = (char *)0x0;
    }
  }
  pcVar6 = (char *)xalloc_global_heap(0x24);
  if (pcVar6 == (char *)0x0) {
    return false;
  }
  pcVar8 = pcVar6;
  for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar8[0] = '\0';
    pcVar8[1] = '\0';
    pcVar8[2] = '\0';
    pcVar8[3] = '\0';
    pcVar8 = pcVar8 + 4;
  }
  strncpy(pcVar6,param_1,0x10);
  *(int *)(pcVar6 + 0x18) = param_3;
  *(int *)(pcVar6 + 0x10) = param_2;
  DVar7 = GetTickCount();
  *(DWORD *)(pcVar6 + 0x1c) = DVar7;
  pcVar8 = DAT_0052457c;
  pcVar4 = (char *)0x0;
  if (DAT_0052457c != (char *)0x0) {
    if (*(int *)(pcVar6 + 0x18) == 2) {
      uVar1 = *(undefined4 *)(DAT_0052457c + 0x20);
      iVar5 = world_object_has_optional_runtime_flag(*(int *)(DAT_0052457c + 0x10));
      if ((iVar5 != 0) && (iVar5 = cockpit_gauge_context_helper_00459d90(), iVar5 != 0)) {
        cockpit_hud_texture_context_helper_00459d60();
      }
      puVar2 = *(undefined4 **)(pcVar8 + 0x14);
      if (puVar2 != (undefined4 *)0x0) {
        release_audio_object_if_present(puVar2);
      }
      xfree_global_heap(pcVar8);
      *(undefined4 *)(pcVar6 + 0x20) = uVar1;
      DAT_0052457c = (char *)0x0;
    }
    else {
      pcVar4 = *(char **)(DAT_0052457c + 0x20);
      pcVar8 = DAT_0052457c;
      while (pcVar3 = pcVar4, pcVar3 != (char *)0x0) {
        pcVar8 = pcVar3;
        pcVar4 = *(char **)(pcVar3 + 0x20);
      }
      *(char **)(pcVar8 + 0x20) = pcVar6;
      pcVar6 = (char *)0x0;
    }
    pcVar8 = DAT_0052457c;
    pcVar4 = (char *)0x0;
    if (DAT_0052457c != (char *)0x0) goto LAB_004238c9;
  }
  while (DAT_0052457c = pcVar4, pcVar6 != (char *)0x0) {
    if ((*(int *)(pcVar6 + 0x18) == 4) &&
       (DVar7 = GetTickCount(), 10000 < DVar7 - *(int *)(pcVar6 + 0x1c))) {
      piVar9 = (int *)0x0;
    }
    else {
      initialize_audio_distance_params_defaults(local_2c);
      initialize_audio_gate_params_defaults(&local_48);
      local_4 = &LAB_004238e0;
      local_1c = 5;
      local_44 = 10000;
      piVar9 = create_or_queue_positional_audio_object(pcVar6,0,local_2c,&local_48);
      if ((piVar9 != (int *)0x0) &&
         (((iVar5 = world_object_has_optional_runtime_flag(*(int *)(pcVar6 + 0x10)), iVar5 != 0 &&
           (iVar5 = weapon_hud_display_context_helper_004621a0(), iVar5 == 0)) &&
          (iVar5 = cockpit_gauge_context_helper_00459d90(), iVar5 == 0)))) {
        cockpit_hud_texture_context_helper_00459d60();
      }
    }
    *(int **)(pcVar6 + 0x14) = piVar9;
    pcVar8 = pcVar6;
    if (piVar9 != (int *)0x0) break;
    pcVar8 = *(char **)(pcVar6 + 0x20);
    iVar5 = world_object_has_optional_runtime_flag(*(int *)(pcVar6 + 0x10));
    if ((iVar5 != 0) && (iVar5 = cockpit_gauge_context_helper_00459d90(), iVar5 != 0)) {
      cockpit_hud_texture_context_helper_00459d60();
    }
    if (*(undefined4 **)(pcVar6 + 0x14) != (undefined4 *)0x0) {
      release_audio_object_if_present(*(undefined4 **)(pcVar6 + 0x14));
    }
    xfree_global_heap(pcVar6);
    pcVar6 = pcVar8;
    pcVar4 = DAT_0052457c;
  }
LAB_004238c9:
  DAT_0052457c = pcVar8;
  return pcVar6 != (char *)0x0;
}


