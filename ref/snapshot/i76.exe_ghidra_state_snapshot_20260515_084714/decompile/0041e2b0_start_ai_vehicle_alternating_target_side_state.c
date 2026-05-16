/*
 * Program: i76.exe
 * Function: start_ai_vehicle_alternating_target_side_state
 * Entry: 0041e2b0
 * Signature: undefined __cdecl start_ai_vehicle_alternating_target_side_state(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Initializes alternating side/target behavior,
   randomizes side choice, and synchronizes paired AI state fields. */

void __cdecl start_ai_vehicle_alternating_target_side_state(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  *(undefined4 *)(iVar1 + 0xa998) = 0;
  fVar6 = get_runtime_time_seconds();
  fVar7 = (float10)_DAT_004bcb34;
  iVar2 = rand();
  *(float *)(iVar1 + 0xa82c) = (float)(iVar2 % 5) + (float)(fVar6 + fVar7);
  fVar7 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
  if ((float10)_DAT_004bcae0 <= fVar7) {
    uVar3 = rand();
    uVar5 = (int)uVar3 >> 0x1f;
    *(uint *)(iVar1 + 0xa9a0) = ((uVar3 ^ uVar5) - uVar5 & 1 ^ uVar5) - uVar5;
  }
  else {
    *(undefined4 *)(iVar1 + 0xa9a0) = 0;
  }
  *(undefined4 *)(iVar1 + 0xa99c) = 0;
  *(undefined4 *)(iVar1 + 0xa9a4) = 0;
  *(undefined4 *)(iVar1 + 0xa9ac) = 0;
  *(undefined4 *)(iVar1 + 0xa9b0) = 0;
  uVar4 = shell_cb_4c_display_or_directdraw_helper();
  *(undefined4 *)(iVar1 + 0xa99c) = uVar4;
  if (*(int *)(iVar1 + 0xa99c) == 0) {
    *(undefined4 *)(iVar1 + 0xa9a4) = 1;
  }
  else {
    iVar2 = get_ai_vehicle_behavior_state_block(*(int *)(iVar1 + 0xa99c));
    *(undefined4 *)(iVar2 + 0xa9ac) = 1;
    *(undefined4 *)(iVar1 + 0xa9b0) = *(undefined4 *)(iVar2 + 0xa9b0);
  }
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


