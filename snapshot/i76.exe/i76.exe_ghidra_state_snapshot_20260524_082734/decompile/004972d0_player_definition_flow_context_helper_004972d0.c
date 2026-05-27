/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_004972d0
 * Entry: 004972d0
 * Signature: undefined __cdecl player_definition_flow_context_helper_004972d0(int param_1, undefined4 param_2, uint * param_3)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_004972d0. Shorten readability label
   for player-definition / mission-flow loading screen context. */

void __cdecl
player_definition_flow_context_helper_004972d0(int param_1,undefined4 param_2,uint *param_3)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int local_28;
  int local_18;
  int local_8;
  
  iVar5 = g_current_loading_screen_record;
  uVar2 = (uint)param_3 >> 0x10;
  uVar11 = (uint)param_3 & 0xffff;
  bVar1 = false;
  if ((DAT_004f9f20 != 0) || (g_cmdline_hardware_window_or_hal_requested != 0)) {
    uVar11 = ftol();
    uVar2 = ftol();
  }
  if (((((int)uVar11 < DAT_00654a3c) || (DAT_00654a44 < (int)uVar11)) || ((int)uVar2 < DAT_00654a40)
      ) || (DAT_00654a48 < (int)uVar2)) {
    return;
  }
  param_3 = *(uint **)(iVar5 + 0x18);
  iVar9 = uVar2 - DAT_00654a40;
  iVar5 = *(int *)(iVar5 + 0x1c);
  iVar12 = uVar11 - DAT_00654a3c;
  local_18 = 0;
  iVar7 = 0;
  if (0 < iVar5) {
    puVar8 = param_3 + 8;
    do {
      local_28 = -1;
      if (puVar8[-6] != 0) {
        uVar2 = puVar8[-1];
        iVar7 = local_18;
        if (((((int)uVar2 <= iVar12) && (iVar12 <= (int)puVar8[1])) &&
            (((int)*puVar8 <= iVar9 && (iVar9 <= (int)puVar8[2])))) ||
           ((((int)puVar8[3] <= iVar12 && (iVar12 <= (int)puVar8[5])) &&
            (((int)puVar8[4] <= iVar9 && (iVar9 <= (int)puVar8[6])))))) {
          bVar1 = true;
          break;
        }
        if ((*param_3 & 0x80) != 0) {
          if (g_display_mode_variant_index < 6) {
            iVar3 = 0x11;
            iVar13 = uVar2 + 5;
            iVar6 = *puVar8 + 0x1c;
            local_8 = 0x11;
            iVar10 = 0x11;
          }
          else {
            iVar3 = 7;
            iVar13 = uVar2 + 1;
            iVar6 = *puVar8 + 0xd;
            local_8 = 7;
            iVar10 = 7;
          }
          local_8 = local_8 + iVar13;
          local_28 = 0;
          if (0 < (int)(puVar8[-4] - 1)) {
            do {
              if ((((iVar13 <= iVar12) && (iVar12 <= local_8)) && (iVar6 <= iVar9)) &&
                 (iVar9 <= iVar10 + iVar6)) {
                bVar1 = true;
                break;
              }
              iVar13 = iVar13 + iVar3;
              local_28 = local_28 + 1;
              local_8 = local_8 + iVar3;
            } while (local_28 < (int)(puVar8[-4] - 1));
          }
          if (bVar1) break;
        }
      }
      local_18 = local_18 + 1;
      param_3 = param_3 + 0xf;
      puVar8 = puVar8 + 0xf;
      iVar7 = local_18;
    } while (local_18 < iVar5);
  }
  if (!bVar1) {
    DAT_00654b1c = 0;
    return;
  }
  if (param_1 == 0x201) {
    *(int *)(g_current_loading_screen_record + 0x20) = iVar7;
    if (((*param_3 & 0x80) != 0) && (local_28 != -1)) {
      param_3[6] = local_28 + 1;
    }
    redraw_mission_loading_screen();
    DAT_00654b1c = 1;
    return;
  }
  if (param_1 != 0x202) {
    return;
  }
  if (DAT_00654b1c == 0) {
    DAT_00654b1c = 0;
    return;
  }
  if (iVar7 != *(int *)(g_current_loading_screen_record + 0x20)) {
    DAT_00654b1c = 0;
    return;
  }
  uVar2 = *param_3;
  if ((((uVar2 & 0x80) != 0) && (local_28 != -1)) && (local_28 + 1U != param_3[6])) {
    bVar1 = false;
  }
  if (!bVar1) {
    DAT_00654b1c = 0;
    return;
  }
  if (((uVar2 & 0x200) == 0) && ((uVar2 & 6) == 0)) {
    if ((uVar2 & 0x800) == 0) {
      if (((uVar2 & 0x80) == 0) || (local_28 == -1)) {
        if (param_3[4] == 1) {
          uVar4 = 7;
          param_3[6] = 0;
          goto LAB_004975e2;
        }
        uVar11 = param_3[6] + 1;
        if ((int)param_3[4] <= (int)uVar11) {
          if (((uVar2 & 0x180) != 0) && ((uVar2 & 0x2000) == 0)) {
            uVar4 = 7;
            param_3[6] = param_3[6];
            goto LAB_004975e2;
          }
          uVar11 = uVar2 >> 0xc & 1;
        }
        param_3[6] = uVar11;
      }
      uVar4 = 7;
    }
    else {
      (*(code *)param_3[2])(param_3,2);
      uVar4 = 7;
    }
  }
  else {
    uVar4 = 4;
  }
LAB_004975e2:
  iVar5 = (*(code *)param_3[2])(param_3,uVar4);
  if (iVar5 != 0) {
    redraw_mission_loading_screen();
  }
  DAT_00654b1c = 0;
  return;
}


