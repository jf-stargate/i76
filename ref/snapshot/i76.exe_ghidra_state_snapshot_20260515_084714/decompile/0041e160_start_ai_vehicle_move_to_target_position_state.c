/*
 * Program: i76.exe
 * Function: start_ai_vehicle_move_to_target_position_state
 * Entry: 0041e160
 * Signature: undefined __cdecl start_ai_vehicle_move_to_target_position_state(int param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Copies a target position into AI behavior state,
   initializes movement fields, and enters forward drive mode. */

void __cdecl start_ai_vehicle_move_to_target_position_state(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  float local_18 [3];
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(local_c + 0xf0) = 0;
  local_8 = get_ai_vehicle_behavior_state_block(param_1);
  puVar2 = (undefined4 *)copy_transform_position_vec3(local_18,param_2 + 0x18);
  puVar1 = *(undefined4 **)(local_8 + 0x60);
  *puVar1 = *puVar2;
  puVar1[1] = puVar2[1];
  puVar1[2] = puVar2[2];
  *(int *)(local_8 + 0x8c) = local_8 + 0xc;
  *(undefined4 *)(local_8 + 0x80) = 0x420c0000;
  *(undefined4 *)(local_8 + 0x84) = 2;
  bind_ai_path_state_to_path_record(local_8,*(int *)(local_8 + 0x8c));
  iVar3 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar3 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


