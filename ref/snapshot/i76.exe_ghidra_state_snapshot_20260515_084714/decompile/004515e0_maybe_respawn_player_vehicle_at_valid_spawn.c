/*
 * Program: i76.exe
 * Function: maybe_respawn_player_vehicle_at_valid_spawn
 * Entry: 004515e0
 * Signature: undefined4 __stdcall maybe_respawn_player_vehicle_at_valid_spawn(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM_HIGH] Checks active player/camera
   object, spawn locations, mission/network mode, and loads a replacement/player vehicle when
   conditions allow.
   old_name: FUN_004515e0 */

undefined4 maybe_respawn_player_vehicle_at_valid_spawn(void)

{
  int *piVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  short sVar5;
  int *piVar6;
  double *pdVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  float10 fVar12;
  undefined2 *puVar13;
  undefined2 *puVar14;
  undefined2 local_68 [2];
  int local_64;
  double local_60;
  undefined2 local_54 [2];
  undefined8 local_50;
  undefined8 local_48;
  float local_40;
  undefined8 local_38;
  undefined8 local_2c;
  float local_24;
  float local_1c;
  float local_18;
  float local_10;
  float local_c;
  
  piVar6 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar6 == (int *)0x0) {
    return 0;
  }
  iVar8 = *piVar6;
  uVar10 = 0;
  local_2c = (double)CONCAT44((float)*(double *)(iVar8 + 0x48),(float)*(double *)(iVar8 + 0x40));
  local_24 = (float)*(double *)(iVar8 + 0x50);
  if (DAT_00540d9c != 0) {
    pdVar7 = (double *)&DAT_0053ece0;
    do {
      local_48 = (double)CONCAT44((float)*pdVar7,(undefined4)local_48);
      local_40 = (float)pdVar7[1];
      dVar3 = (double)(float)*(double *)(iVar8 + 0x40) - pdVar7[-1];
      local_60 = (double)(float)*(double *)(iVar8 + 0x48) - *pdVar7;
      local_50 = (double)local_24 - pdVar7[1];
      local_38 = (local_50 * local_50 + local_60 * local_60 + dVar3 * dVar3) - _DAT_004bdf38;
      if (((uint)((longlong)local_38 >> 0x3f) & 1) != 0) break;
      uVar10 = uVar10 + 1;
      pdVar7 = pdVar7 + 8;
    } while (uVar10 < DAT_00540d9c);
  }
  if (uVar10 == DAT_00540d9c) {
    DAT_00540d94 = 1;
    return 0;
  }
  fVar12 = get_multiplayer_or_runtime_seconds();
  if (fVar12 - (float10)_DAT_0053fd84 < (float10)_DAT_004bdf40) {
    if (DAT_00540d94 == 0) {
      fVar12 = get_multiplayer_or_runtime_seconds();
      _DAT_0053fd84 = (float)fVar12;
    }
    return 0;
  }
  fVar12 = get_multiplayer_or_runtime_seconds();
  _DAT_0053fd84 = (float)fVar12;
  DAT_00540d94 = 0;
  iVar8 = is_damage_side_effects_suppressed();
  if (iVar8 == 0) {
    get_multiplayer_score_accumulators(&local_64,local_68);
    set_multiplayer_score_accumulators(local_64 + 400,local_68[0]);
  }
  else {
    puVar14 = local_54;
    puVar13 = local_68;
    piVar6 = &local_64;
    sVar5 = get_local_multiplayer_player_id();
    get_multiplayer_player_spawn_score_fields(sVar5,piVar6,puVar13,puVar14);
    iVar8 = local_64 + 400;
    sVar5 = get_local_multiplayer_player_id();
    multiplayer_player_state_lookup_helper_00454ea0(sVar5,iVar8,local_68[0],local_54[0]);
  }
  dispatch_vehicle_runtime_sound_event(3,0,(undefined4 *)0x0);
  iVar8 = is_damage_side_effects_suppressed();
  if (iVar8 != 0) {
    DAT_00540d8c = 1;
    DAT_00540d90 = 1;
    DAT_00540d88 = get_multiplayer_message_source_player_id();
    fsm_or_mission_logic_helper_a(0,0,0x80000000);
    return 1;
  }
  local_50 = (double)get_selected_mission_resource_stem8();
  if (DAT_00540d98 == 0) {
    report_chunk_parse_error();
  }
  uVar10 = rand();
  uVar10 = uVar10 % DAT_00540d98;
  local_60 = (double)((ulonglong)local_60 & 0xffffffff00000000);
  if (DAT_00540d98 == 0) {
LAB_004518d9:
    load_vehicle_entity(uVar10,0,(undefined4)local_50,local_50._4_4_,1);
    return 1;
  }
LAB_004517fd:
  iVar11 = 0;
  iVar8 = uVar10 * 0x40;
  local_1c = (float)*(double *)(&DAT_0053fdb8 + iVar8);
  local_18 = (float)*(double *)(&DAT_0053fdc0 + iVar8);
  if (0 < DAT_0053fd78) {
    piVar6 = &DAT_0053fcb0;
    do {
      piVar1 = (int *)*piVar6;
      if (piVar1 != (int *)0x0) {
        iVar2 = *piVar1;
        local_10 = (float)*(double *)(iVar2 + 0x48);
        local_c = (float)*(double *)(iVar2 + 0x50);
        local_48 = *(double *)(&DAT_0053fdb0 + iVar8) - *(double *)(iVar2 + 0x40);
        dVar4 = (double)local_1c - *(double *)(iVar2 + 0x48);
        dVar3 = (double)local_18 - *(double *)(iVar2 + 0x50);
        local_38 = (double)(float)piVar1[4] - _DAT_004bdf28;
        local_2c = (dVar3 * dVar3 + dVar4 * dVar4 + local_48 * local_48) - local_38 * local_38;
        if (((uint)((longlong)local_2c >> 0x3f) & 1) != 0) goto LAB_004518b5;
      }
      iVar11 = iVar11 + 1;
      piVar6 = piVar6 + 1;
      if (DAT_0053fd78 <= iVar11) break;
    } while( true );
  }
  goto LAB_004518d9;
LAB_004518b5:
  uVar10 = -(uint)(uVar10 + 1 != DAT_00540d98) & uVar10 + 1;
  uVar9 = local_60._0_4_ + 1;
  local_60 = (double)CONCAT44(local_60._4_4_,uVar9);
  if (DAT_00540d98 <= uVar9) goto LAB_004518d9;
  goto LAB_004517fd;
}


