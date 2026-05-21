/*
 * Program: i76.exe
 * Function: fsm_or_mission_logic_helper_a
 * Entry: 00456100
 * Signature: undefined __cdecl fsm_or_mission_logic_helper_a(int param_1, int param_2, undefined4 param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_00456100
   suggested_name: fsm_or_mission_logic_helper_a
   basis: Gameplay/FSM cluster candidate from diagnostics; name intentionally cautious. */

void __cdecl fsm_or_mission_logic_helper_a(int param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  undefined2 uVar2;
  undefined3 extraout_var;
  uint uVar3;
  undefined2 extraout_var_00;
  char *pcVar4;
  undefined2 extraout_var_01;
  float10 fVar5;
  int iVar6;
  void *pvVar7;
  size_t sVar8;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  undefined2 local_19c;
  undefined1 local_19a;
  float local_198;
  undefined4 local_194;
  undefined4 local_190;
  
  fVar5 = get_gameplay_runtime_seconds();
  if (param_1 != 0 || param_2 != 0) {
    _DAT_005419c0 = param_1;
    _DAT_005419c4 = param_2;
    multiplayer_player_vehicle_lookup_helper_00454750(DAT_00541028,param_1,param_2,0);
  }
  bVar1 = is_local_multiplayer_sync_player_current();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    uVar3 = get_spawn_location_or_report_missing();
    if (uVar3 != 0xffffffff) {
      sVar8 = 0;
      pvVar7 = (void *)0x0;
      iVar6 = 0;
      uVar2 = get_local_multiplayer_player_id();
      pcVar4 = load_or_create_player_vehicle_entity
                         (CONCAT22(extraout_var_00,uVar2),uVar3,iVar6,pvVar7,sVar8);
      local_1a8 = (float)*(double *)(pcVar4 + 0x40);
      local_1a4 = (float)*(double *)(pcVar4 + 0x48);
      local_1a0 = (float)*(double *)(pcVar4 + 0x50);
      chunk_manager_lookup_or_remove_entry(&local_1a8,20.0);
      return;
    }
    report_error();
    return;
  }
  local_19c = 0x5253;
  local_19a = 0;
  local_190 = 0;
  local_194 = param_3;
  local_198 = (float)fVar5;
  uVar2 = get_multiplayer_message_source_player_id();
  dpSend(DAT_00541024,CONCAT22(extraout_var_01,DAT_00541028),uVar2,1,&local_19c,0x10);
  return;
}


