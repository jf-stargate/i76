/*
 * Program: i76.exe
 * Function: format_kill_message
 * Entry: 0046ce30
 * Signature: undefined __cdecl format_kill_message(uint param_1, undefined4 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings killed by / has been killed */

void __cdecl format_kill_message(uint param_1,undefined4 *param_2)

{
  ushort uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  short sVar6;
  undefined4 *puVar7;
  char *_Format;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  undefined8 in_stack_fffffef8;
  float in_stack_ffffff00;
  float in_stack_ffffff04;
  float in_stack_ffffff08;
  float in_stack_ffffff0c;
  float in_stack_ffffff10;
  float in_stack_ffffff14;
  float in_stack_ffffff18;
  uint *puVar12;
  uint local_c8;
  uint local_c4;
  uchar local_c0 [24];
  uchar local_a8 [24];
  uchar local_90 [80];
  float local_40 [16];
  
  iVar2 = *(int *)(param_1 + 0x70);
  if ((*(byte *)(param_2 + 0x12) & 8) != 0) {
    uVar8 = *(uint *)(iVar2 + 0x454);
    if (((uVar8 & 0x20) == 0) && ((uVar8 & 0x100000) != 0)) {
      return;
    }
    *(uint *)(iVar2 + 0x454) = uVar8 & 0xffefffff;
  }
  puVar10 = (undefined4 *)&stack0xfffffef8;
  puVar7 = param_2;
  for (iVar9 = 9; puVar7 = puVar7 + 1, iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar10 = *puVar7;
    puVar10 = puVar10 + 1;
  }
  puVar7 = (undefined4 *)
           runtime_library_string_or_memory_helper_004baee0
                     (local_40,in_stack_fffffef8,in_stack_ffffff00,in_stack_ffffff04,
                      in_stack_ffffff08,in_stack_ffffff0c,in_stack_ffffff10,in_stack_ffffff14,
                      in_stack_ffffff18);
  puVar10 = (undefined4 *)(param_1 + 0x18);
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar10 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar10 = puVar10 + 1;
  }
  *(undefined4 *)(iVar2 + 0xbc) = param_2[10];
  *(undefined4 *)(iVar2 + 0xc0) = param_2[0xb];
  *(undefined4 *)(iVar2 + 0xc4) = param_2[0xc];
  *(undefined4 *)(iVar2 + 200) = param_2[0xd];
  *(undefined4 *)(iVar2 + 0xcc) = param_2[0xe];
  *(undefined4 *)(iVar2 + 0xd0) = param_2[0xf];
  fVar5 = _DAT_004be338;
  fVar3 = (float)param_2[10];
  fVar3 = SQRT((float)param_2[0xc] * (float)param_2[0xc] +
               (float)param_2[0xb] * (float)param_2[0xb] + fVar3 * fVar3);
  *(float *)(iVar2 + 0xac) = fVar3;
  fVar4 = _DAT_004be374;
  if (fVar5 < fVar3) {
    fVar4 = _DAT_004be328 / fVar3;
  }
  uVar8 = *(uint *)(iVar2 + 0x454);
  *(float *)(iVar2 + 0xb0) = fVar4;
  *(undefined4 *)(iVar2 + 0x454) = 0;
  *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0xf0) = 0;
  if ((*(byte *)(param_2 + 0x12) & 0x20) != 0) {
    *(undefined4 *)(iVar2 + 0x454) = 1;
  }
  if ((param_2[0x12] & 0x400) != 0) {
    *(uint *)(iVar2 + 0x454) = *(uint *)(iVar2 + 0x454) | 0x40000;
  }
  if ((param_2[0x12] & 0xc0000000) == 0xc0000000) {
    *(undefined4 *)(iVar2 + 0x484) = 0x42c80000;
  }
  else if ((param_2[0x12] & 0xc0000000) == 0x80000000) {
    *(undefined4 *)(iVar2 + 0x484) = 0x42855555;
  }
  else {
    *(undefined4 *)(iVar2 + 0x484) = 0x42055555;
  }
  uVar11 = *(uint *)(iVar2 + 0x454) | uVar8 & 0x8020;
  *(uint *)(iVar2 + 0x454) = uVar11;
  if (((*(byte *)(param_2 + 0x12) & 8) != 0) && ((uVar8 & 0x20) == 0)) {
    *(uint *)(iVar2 + 0x454) = uVar11 | 0x20;
    create_textured_building_piece(param_1);
    sVar6 = get_local_multiplayer_player_id();
    if (*(short *)(param_2 + 0x16) == sVar6) {
      puVar12 = &local_c8;
      sVar6 = get_local_multiplayer_player_id();
      lookup_multiplayer_player_vehicle_config_id(sVar6,puVar12);
      lookup_multiplayer_player_vehicle_config_id(*(short *)(iVar2 + 0x480),&local_c4);
      if (((local_c4 ^ local_c8) & 0x70000) != 0) {
        multiplayer_score_spawn_context_helper_00454ff0(*(short *)(iVar2 + 0x480));
      }
    }
    if ((param_2[0x12] & 0x200) == 0) {
      multiplayer_player_count_context_helper_00454620(*(short *)(iVar2 + 0x480),local_c0);
      if (*(short *)(param_2 + 0x16) == 0) {
        _Format = (char *)StrLookupFind();
        sprintf((char *)local_90,_Format);
      }
      else {
        multiplayer_player_count_context_helper_00454620(*(short *)(param_2 + 0x16),local_a8);
        StrLookupFormat();
      }
      draw_multiplayer_chat_message(0,local_90);
    }
  }
  *(undefined4 *)(iVar2 + 0xe4) = param_2[0x10];
  *(undefined4 *)(iVar2 + 0xe0) = param_2[0x11];
  uVar1 = *(ushort *)(param_2 + 0x15);
  if (uVar1 == 0) {
    radar_render_context_helper_00461270(param_1,0);
    iVar9 = 0;
  }
  else {
    if ((*(byte *)(param_2 + 0x12) & 0x40) == 0) {
      uVar8 = multiplayer_player_table_context_helper_004547c0(uVar1);
    }
    else {
      uVar8 = network_vehicle_message_context_helper_00456700(uVar1 - 1);
    }
    radar_render_context_helper_00461270(param_1,uVar8);
    iVar9 = 1;
  }
  set_default_selected_weapon_slot_for_vehicle(param_1,iVar9);
  multiplayer_player_state_lookup_helper_00454ea0
            (*(short *)(iVar2 + 0x480),param_2[0x13],*(undefined2 *)(param_2 + 0x14),
             *(undefined2 *)((int)param_2 + 0x52));
  return;
}


