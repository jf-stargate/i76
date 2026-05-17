/*
 * Program: i76.exe
 * Function: load_or_create_player_vehicle_entity
 * Entry: 00451180
 * Signature: char * __cdecl load_or_create_player_vehicle_entity(uint param_1, int param_2, int param_3, void * param_4, size_t param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00451180
   suggested_name: load_or_create_player_vehicle_entity
   basis: Reports missing network vehicle and world-full entity creation. */

char * __cdecl
load_or_create_player_vehicle_entity
          (uint param_1,int param_2,int param_3,void *param_4,size_t param_5)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  char *_Dest;
  char *pcVar4;
  undefined4 *puVar5;
  char **ppcVar6;
  float10 fVar7;
  short sVar8;
  undefined8 local_5c;
  char *local_54 [2];
  int local_4c;
  undefined4 local_48 [12];
  undefined1 local_18 [20];
  int local_4;
  
  sVar8 = (short)param_1;
  local_5c = multiplayer_player_table_context_helper_00454800(sVar8);
  if (local_5c == 0) {
    if (param_5 == 0) {
      report_chunk_parse_error();
    }
    else {
      local_5c = write_network_vehicle_file(param_4,param_5);
    }
  }
  iVar2 = multiplayer_player_table_context_helper_004547c0(sVar8);
  if (iVar2 != 0) {
    multiplayer_player_vehicle_lookup_helper_00454750(sVar8,(undefined4)local_5c,local_5c._4_4_,0);
    piVar3 = get_active_world_object_entry_object(iVar2);
    vehicle_system_log_tag(piVar3);
  }
  _Dest = allocate_world_object_node(0);
  if (_Dest == (char *)0x0) {
    return (char *)0x0;
  }
  ppcVar6 = local_54;
  for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
    *ppcVar6 = (char *)0x0;
    ppcVar6 = ppcVar6 + 1;
  }
  local_54[0] = _Dest;
  strncpy(_Dest,(char *)&local_5c,8);
  if (param_3 == 0) {
    puVar5 = (undefined4 *)(&DAT_0053fd88 + param_2 * 0x40);
  }
  else {
    if (param_3 != 1) goto LAB_00451286;
    puVar5 = (undefined4 *)(&DAT_0053ecb0 + param_2 * 0x40);
  }
  pcVar4 = _Dest + 0x18;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pcVar4 = *puVar5;
    puVar5 = puVar5 + 1;
    pcVar4 = pcVar4 + 4;
  }
LAB_00451286:
  *(uint *)(_Dest + 0x10) = (-(uint)(sVar8 != DAT_00541028) & 0x10) + 0x10;
  lookup_multiplayer_player_vehicle_config_id(sVar8,&param_1);
  param_1 = param_1 >> 0x10 & 7;
  *(uint *)(_Dest + 0x10) = *(uint *)(_Dest + 0x10) | param_1 << 0x10;
  pcVar4 = format_8char_resource_basename_with_suffix
                     ((undefined4)local_5c,local_5c._4_4_,&s_dot_vcf);
  iVar2 = load_vehicle_config_for_world_object(0,(byte *)local_54,pcVar4);
  if (iVar2 == 0) {
    report_chunk_parse_error();
    return (char *)0x0;
  }
  if (local_4c == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = vehicle_geometry_part_binding_context_helper_004b81c0(local_48);
  }
  piVar3 = register_active_world_object_entry
                     ((int)_Dest,iVar2,(int *)(-(uint)(local_4 != 0) & (uint)local_18));
  if (piVar3 == (int *)0x0) {
    report_chunk_parse_error();
    return (char *)0x0;
  }
  multiplayer_player_vehicle_lookup_helper_00454750
            (sVar8,(undefined4)local_5c,local_5c._4_4_,(int)_Dest);
  dispatch_queued_world_object_class_callbacks();
  sVar1 = get_local_multiplayer_player_id();
  if (sVar8 == sVar1) {
    input_action_state_getter_helper_0044de20();
    fVar7 = get_network_or_session_runtime_seconds();
    _DAT_0053fd84 = (float)fVar7;
    DAT_00540d94 = 0;
    if (*(int *)(_Dest + 0x6c) == 1) {
      update_inactive_vehicle_ground_recovery_and_suspension_visuals((float)_Dest);
    }
  }
  DAT_00540d8c = 0;
  return _Dest;
}


