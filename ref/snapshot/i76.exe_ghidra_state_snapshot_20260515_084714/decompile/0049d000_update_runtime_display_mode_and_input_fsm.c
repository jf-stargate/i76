/*
 * Program: i76.exe
 * Function: update_runtime_display_mode_and_input_fsm
 * Entry: 0049d000
 * Signature: undefined __stdcall update_runtime_display_mode_and_input_fsm(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Per-frame display/input mode FSM.
   Consumes pending action codes, handles loading/FMV/menu/gameplay input modes, and dispatches
   mode-specific action handlers. */

void update_runtime_display_mode_and_input_fsm(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  code *pcVar11;
  
  iVar6 = g_current_loading_screen_record;
  switch(g_runtime_display_input_mode) {
  case 2:
    if ((g_pending_input_action_code != 0) &&
       (uVar10 = input_action_state_setter_helper_0044de30(g_pending_input_action_code),
       (short)uVar10 == 0x33)) {
      iVar6 = is_damage_side_effects_suppressed();
      if (iVar6 == 0) {
        if (g_runtime_display_input_mode == 2) {
          iVar6 = ui_bitmap_region_context_helper_0049ae50();
          if ((iVar6 == 0) && (g_requested_runtime_display_input_mode == 1)) {
            resume_cd_audio_after_cutscene_or_mode_change();
            force_feedback_runtime_helper_00445b40();
          }
          if (g_runtime_display_input_mode == g_requested_runtime_display_input_mode) {
            g_runtime_display_input_mode = 1;
            g_pending_input_action_code = 0;
            return;
          }
          g_runtime_display_input_mode = g_requested_runtime_display_input_mode;
          g_pending_input_action_code = 0;
          return;
        }
        iVar6 = ui_bitmap_region_context_helper_0049ae20();
        if ((iVar6 == 0) && (g_requested_runtime_display_input_mode == 1)) {
          pause_cd_audio_for_cutscene_or_mode_change();
          force_feedback_runtime_helper_00445b60();
        }
        g_requested_runtime_display_input_mode = g_runtime_display_input_mode;
        g_runtime_display_input_mode = (g_runtime_display_input_mode != 2) + 1;
      }
      g_pending_input_action_code = 0;
      return;
    }
    break;
  case 4:
    if (g_pending_input_action_code != 0) {
      if (DAT_005367ec == '\0') {
        initialize_mission_map_display();
      }
      dispatch_pending_input_action_bindings();
      return;
    }
    break;
  case 8:
    if (g_pending_input_action_code != 0) {
      if (DAT_005367ed == '\0') {
        initialize_notepad_objective_display();
      }
      dispatch_pending_input_action_bindings();
      return;
    }
    break;
  case 0x10:
    iVar5 = 0;
    iVar9 = 0;
    pcVar11 = (code *)0x0;
    if (DAT_00654b1c != 0) {
      return;
    }
    if (g_pending_input_action_code != 0) {
      iVar7 = (int)g_pending_input_action_code;
      if (iVar7 < 0xe) {
        if ((iVar7 == 0xd) || (iVar7 == 9)) goto LAB_00496e6d;
      }
      else if (iVar7 < 0x21) {
        if ((iVar7 == 0x20) || (iVar7 == 0x1b)) {
LAB_00496e6d:
          iVar9 = iVar7;
        }
      }
      else if ((0xc5 < iVar7) && ((iVar7 < 0xca || (iVar7 == 0x209)))) goto LAB_00496e6d;
      if (iVar9 == 0) {
        return;
      }
      g_pending_input_action_code = 0;
    }
    if (iVar9 == 0) {
      return;
    }
    DAT_00536812 = 1;
    DAT_00536815 = 1;
    if (iVar9 < 0xe) {
      if (iVar9 == 0xd) {
        uVar10 = 4;
      }
      else {
        if (iVar9 != 9) goto switchD_00497072_default;
switchD_00497072_caseD_c7:
        uVar10 = 0;
      }
    }
    else if (iVar9 < 0x21) {
      if (iVar9 == 0x20) {
switchD_00497072_caseD_c8:
        uVar10 = 2;
      }
      else {
        if (iVar9 != 0x1b) goto switchD_00497072_default;
        uVar10 = 9;
      }
    }
    else if (iVar9 < 0x20a) {
      if (iVar9 != 0x209) {
        switch(iVar9) {
        case 0xc6:
          break;
        case 199:
          goto switchD_00497072_caseD_c7;
        case 200:
          goto switchD_00497072_caseD_c8;
        case 0xc9:
          uVar10 = 3;
          goto LAB_00496eae;
        default:
          goto switchD_00497072_default;
        }
      }
      uVar10 = 1;
    }
    else {
switchD_00497072_default:
      uVar10 = 0xffffffff;
    }
LAB_00496eae:
    iVar9 = *(int *)(g_current_loading_screen_record + 0x18);
    puVar1 = (uint *)(iVar9 + *(int *)(g_current_loading_screen_record + 0x20) * 0x3c);
    switch(uVar10) {
    case 0:
    case 1:
      iVar5 = *(int *)(g_current_loading_screen_record + 0x1c);
      do {
        iVar7 = *(int *)(iVar6 + 0x20);
        if (iVar5 == 1) {
          iVar7 = 0;
        }
        else {
          switch(uVar10) {
          case 0:
          case 2:
            iVar7 = iVar7 + 1;
            if (iVar5 <= iVar7) {
              iVar7 = 0;
            }
            break;
          case 1:
          case 3:
            iVar7 = iVar7 + -1;
            if (iVar7 < 0) {
              iVar7 = iVar5 + -1;
            }
          }
        }
        *(int *)(iVar6 + 0x20) = iVar7;
      } while (*(int *)(iVar9 + 8 + iVar7 * 0x3c) == 0);
      iVar5 = 1;
      break;
    case 2:
    case 3:
      uVar2 = *puVar1;
      pcVar11 = (code *)puVar1[2];
      if ((uVar2 & 0x800) == 0) {
        uVar3 = puVar1[4];
        uVar4 = puVar1[6];
        if (uVar3 == 1) {
          uVar10 = 7;
          puVar1[6] = 0;
          iVar5 = 1;
        }
        else {
          uVar8 = uVar4;
          switch(uVar10) {
          case 0:
          case 2:
            uVar8 = uVar4 + 1;
            if ((int)uVar3 <= (int)uVar8) {
              if (((uVar2 & 0x180) == 0) || ((uVar2 & 0x2000) != 0)) {
                uVar10 = 7;
                iVar5 = 1;
                puVar1[6] = uVar2 >> 0xc & 1;
              }
              else {
                uVar10 = 7;
                puVar1[6] = uVar4;
                iVar5 = 1;
              }
              goto switchD_00496ed4_caseD_5;
            }
            break;
          case 1:
          case 3:
            uVar8 = uVar4 - 1;
            if ((int)uVar8 < (int)(uVar2 >> 0xc & 1)) {
              if (((uVar2 & 0x180) != 0) && ((uVar2 & 0x2000) == 0)) {
                uVar10 = 7;
                puVar1[6] = uVar4;
                iVar5 = 1;
                goto switchD_00496ed4_caseD_5;
              }
              uVar8 = uVar3 - 1;
            }
          }
          puVar1[6] = uVar8;
          uVar10 = 7;
          iVar5 = 1;
        }
      }
      else {
        (*pcVar11)(puVar1,uVar10);
        uVar10 = 7;
        iVar5 = 1;
      }
      break;
    case 4:
      if (((*puVar1 & 0x200) == 0) && ((*puVar1 & 6) == 0)) {
        pcVar11 = player_definition_flow_context_helper_004979a0;
      }
      else {
        pcVar11 = (code *)puVar1[2];
      }
      break;
    case 9:
      if ((*(byte *)(g_current_loading_screen_record + 4) & 1) == 0) {
        pcVar11 = player_definition_flow_context_helper_00497a30;
      }
    }
switchD_00496ed4_caseD_5:
    if (pcVar11 != (code *)0x0) {
      iVar5 = (*pcVar11)(puVar1,uVar10);
    }
    if (iVar5 != 0) {
      redraw_mission_loading_screen();
    }
    return;
  }
  return;
}


