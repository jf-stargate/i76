/*
 * Program: i76.exe
 * Function: dispatch_vehicle_runtime_sound_event
 * Entry: 00422f20
 * Signature: int * __cdecl dispatch_vehicle_runtime_sound_event(undefined4 param_1, int param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Dispatches vehicle sound
   events: engine loop start/stop, landing, vehicle/body collision, explosion, gun/missile fire,
   skid start/stop, and collision signs. */

int * __cdecl
dispatch_vehicle_runtime_sound_event(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  char *local_54;
  int *local_50;
  int *local_4c;
  int local_48 [3];
  undefined4 local_3c;
  undefined4 local_2c [11];
  
  local_50 = (int *)0x0;
  local_4c = (int *)0x0;
  local_54 = (char *)0x0;
  if (param_2 == 0) {
    piVar1 = (int *)get_active_player_or_camera_world_object_entry();
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    param_2 = *piVar1;
    if (param_2 == 0) {
      return (int *)0x0;
    }
  }
  switch(param_1) {
  case 1:
    local_50 = restart_vehicle_engine_loop_sound(param_2);
    break;
  case 2:
    stop_vehicle_engine_loop_sound(param_2);
    break;
  case 3:
    play_vehicle_engine_event_sound(param_2,0);
    break;
  case 4:
    iVar2 = world_object_has_optional_runtime_flag(param_2);
    if (iVar2 != 0) {
      local_54 = s_vland_wav_004ed860;
    }
    break;
  case 5:
    iVar2 = param_2;
    if ((param_2 != 0) ||
       ((piVar1 = (int *)get_active_player_or_camera_world_object_entry(), piVar1 != (int *)0x0 &&
        (iVar2 = *piVar1, iVar2 != 0)))) {
      puVar3 = param_3;
      if (param_3 == (undefined4 *)0x0) {
        puVar3 = local_2c;
        initialize_audio_distance_params_defaults(local_2c);
      }
      puVar3[4] = puVar3[4] | 0x200;
      create_or_queue_positional_audio_object(s_vvcoll_wav_004ed854,iVar2,puVar3,(int *)0x0);
    }
    break;
  case 6:
    iVar2 = param_2;
    if ((param_2 != 0) ||
       ((piVar1 = (int *)get_active_player_or_camera_world_object_entry(), piVar1 != (int *)0x0 &&
        (iVar2 = *piVar1, iVar2 != 0)))) {
      puVar3 = param_3;
      if (param_3 == (undefined4 *)0x0) {
        puVar3 = local_2c;
        initialize_audio_distance_params_defaults(local_2c);
      }
      puVar3[4] = puVar3[4] | 0x200;
      create_or_queue_positional_audio_object(s_vbcoll_wav_004ed848,iVar2,puVar3,(int *)0x0);
    }
    break;
  case 7:
    iVar2 = param_2;
    if ((param_2 != 0) ||
       ((piVar1 = (int *)get_active_player_or_camera_world_object_entry(), piVar1 != (int *)0x0 &&
        (iVar2 = *piVar1, iVar2 != 0)))) {
      puVar3 = param_3;
      if (param_3 == (undefined4 *)0x0) {
        puVar3 = local_2c;
        initialize_audio_distance_params_defaults(local_2c);
      }
      puVar3[4] = puVar3[4] | 0x200;
      create_or_queue_positional_audio_object(s_vexplode_wav_004ed838,iVar2,puVar3,(int *)0x0);
    }
    break;
  case 8:
    local_54 = s_vmgun_wav_004ed82c;
    break;
  case 9:
    local_54 = s_vmissile_wav_004ed81c;
    break;
  case 10:
    iVar2 = world_object_has_optional_runtime_flag(param_2);
    if ((iVar2 != 0) &&
       (piVar1 = find_audio_object_by_name_and_attached_world_object(s_vskid_wav_004ed810,param_2),
       piVar1 == (int *)0x0)) {
      local_4c = local_48;
      initialize_audio_gate_params_defaults(local_48);
      local_3c = 1;
      local_54 = s_vskid_wav_004ed810;
    }
    break;
  case 0xb:
    iVar2 = world_object_has_optional_runtime_flag(param_2);
    if ((iVar2 != 0) &&
       (local_50 = find_audio_object_by_name_and_attached_world_object(s_vskid_wav_004ed810,param_2)
       , local_50 != (int *)0x0)) {
      release_audio_object_if_present(local_50);
    }
    break;
  case 0x10:
    local_54 = s_vcsign_wav_004ed804;
  }
  if (local_54 != (char *)0x0) {
    local_50 = create_or_queue_positional_audio_object(local_54,param_2,param_3,local_4c);
  }
  return local_50;
}


