/*
 * Program: i76.exe
 * Function: start_ai_path_following_forward_state_with_threat_scan
 * Entry: 00420aa0
 * Signature: undefined __cdecl start_ai_path_following_forward_state_with_threat_scan(int param_1)
 */


/* cgpt readability rename v13 set A: Initializes AI path-following state and invokes nearby
   target/threat scan when transitioning from inactive progress state. */

void __cdecl start_ai_path_following_forward_state_with_threat_scan(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  iVar1 = *(int *)(iVar2 + 0x9c);
  bind_ai_path_state_to_path_record(iVar2,*(int *)(iVar2 + 0x8c));
  *(undefined4 *)(iVar2 + 0x84) = 2;
  *(undefined4 *)(iVar2 + 0x9c) = 0;
  iVar2 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  iVar2 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar2 + 0xf0) = 0;
  *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  if (iVar1 == 0) {
    update_ai_vehicle_nearest_target_threat_state(param_1);
  }
  return;
}


