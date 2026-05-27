/*
 * Program: i76.exe
 * Function: start_ai_path_following_forward_state
 * Entry: 00420a20
 * Signature: undefined __cdecl start_ai_path_following_forward_state(int param_1)
 */


/* cgpt readability rename v13 set A: Initializes AI path-following state and resets vehicle
   drive/throttle fields for forward mode. */

void __cdecl start_ai_path_following_forward_state(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  bind_ai_path_state_to_path_record(iVar1,*(int *)(iVar1 + 0x8c));
  *(undefined4 *)(iVar1 + 0x84) = 2;
  *(undefined4 *)(iVar1 + 0x9c) = 0;
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


