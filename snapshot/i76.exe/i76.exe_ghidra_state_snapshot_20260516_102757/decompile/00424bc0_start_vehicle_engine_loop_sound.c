/*
 * Program: i76.exe
 * Function: start_vehicle_engine_loop_sound
 * Entry: 00424bc0
 * Signature: bool __cdecl start_vehicle_engine_loop_sound(int param_1)
 */


/* cgpt rename v3: Creates and attaches the engine loop sound object for a vehicle using engine
   sound metadata and optional runtime flags. */

bool __cdecl start_vehicle_engine_loop_sound(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  undefined4 *puVar6;
  int local_48 [3];
  undefined4 local_3c;
  undefined4 local_2c [4];
  undefined4 local_1c;
  undefined1 *local_c;
  undefined1 *local_8;
  
  initialize_audio_distance_params_defaults(local_2c);
  initialize_audio_gate_params_defaults(local_48);
  iVar2 = get_vehicle_runtime_context(param_1);
  if (iVar2 == 0) {
    return false;
  }
  iVar1 = *(int *)(*(int *)(iVar2 + 0x3c4) + 0x70);
  if (iVar1 == 0) {
    return false;
  }
  iVar3 = get_engine_loop_sound_flags(iVar1);
  if (iVar3 != 0) {
    local_8 = &LAB_00424ca0;
    local_c = &LAB_00424ca0;
  }
  local_1c = 1;
  iVar3 = world_object_has_optional_runtime_flag(param_1);
  if (iVar3 != 0) {
    local_48[1] = 0x4f;
  }
  piVar5 = local_48;
  puVar6 = local_2c;
  local_3c = 1;
  pcVar4 = get_engine_loop_sound_name(iVar1);
  piVar5 = create_or_queue_positional_audio_object(pcVar4,param_1,puVar6,piVar5);
  if (piVar5 != (int *)0x0) {
    *(undefined1 *)((int)piVar5 + 0x76) = *(undefined1 *)(iVar1 + 8);
  }
  *(int **)(iVar2 + 0x10c) = piVar5;
  return piVar5 != (int *)0x0;
}


