/*
 * Program: i76.exe
 * Function: load_vehicle_entity
 * Entry: 004513c0
 * Signature: char * __cdecl load_vehicle_entity(int param_1, int param_2, undefined4 param_3, undefined4 param_4, int param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_004513c0
   suggested_name: load_vehicle_entity
   basis: Reports cannot load vehicle and cannot create entity; called by startup and player vehicle
   paths. */

char * __cdecl
load_vehicle_entity(int param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  char *_Dest;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  char **ppcVar6;
  float10 fVar7;
  char *local_54 [2];
  int local_4c;
  undefined4 local_48 [12];
  undefined1 local_18 [20];
  int local_4;
  
  iVar1 = param_5;
  if (param_5 != 0) {
    piVar2 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar2 != (int *)0x0) {
      vehicle_system_log_tag(piVar2);
    }
  }
  _Dest = allocate_world_object_node(0);
  if (_Dest == (char *)0x0) {
    return (char *)0x0;
  }
  ppcVar6 = local_54;
  for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
    *ppcVar6 = (char *)0x0;
    ppcVar6 = ppcVar6 + 1;
  }
  local_54[0] = _Dest;
  strncpy(_Dest,(char *)&param_3,8);
  if (param_2 == 0) {
    puVar5 = (undefined4 *)(&DAT_0053fd88 + param_1 * 0x40);
  }
  else {
    if (param_2 != 1) goto LAB_00451452;
    puVar5 = (undefined4 *)(&DAT_0053ecb0 + param_1 * 0x40);
  }
  pcVar3 = _Dest + 0x18;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar3 = *puVar5;
    puVar5 = puVar5 + 1;
    pcVar3 = pcVar3 + 4;
  }
LAB_00451452:
  *(uint *)(_Dest + 0x10) = (2 - (uint)(iVar1 != 0)) * 0x10000 | -(uint)(iVar1 != 0) & 0x10;
  pcVar3 = format_8char_resource_basename_with_suffix(param_3,param_4,&s_dot_vcf);
  iVar4 = load_vehicle_config_for_world_object(0,(byte *)local_54,pcVar3);
  if (iVar4 == 0) {
    report_chunk_parse_error();
    return (char *)0x0;
  }
  if (local_4c == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = vehicle_geometry_part_binding_context_helper_004b81c0(local_48);
  }
  piVar2 = register_active_world_object_entry
                     ((int)_Dest,iVar4,(int *)(-(uint)(local_4 != 0) & (uint)local_18));
  if (piVar2 == (int *)0x0) {
    report_chunk_parse_error();
    return (char *)0x0;
  }
  dispatch_queued_world_object_class_callbacks();
  if (iVar1 != 0) {
    input_action_state_getter_helper_0044de20();
    fVar7 = get_multiplayer_or_runtime_seconds();
    _DAT_0053fd84 = (float)fVar7;
    DAT_00540d94 = 0;
    if (*(int *)(_Dest + 0x6c) == 1) {
      update_vehicle_recovery_or_autopilot_state((float)_Dest);
    }
  }
  return _Dest;
}


