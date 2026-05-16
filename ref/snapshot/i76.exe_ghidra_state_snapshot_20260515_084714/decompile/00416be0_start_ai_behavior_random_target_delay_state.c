/*
 * Program: i76.exe
 * Function: start_ai_behavior_random_target_delay_state
 * Entry: 00416be0
 * Signature: int __cdecl start_ai_behavior_random_target_delay_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Stores or clears a target object using random gating
   and starts a randomized target/behavior timer. */

int __cdecl start_ai_behavior_random_target_delay_state(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  uVar2 = rand();
  uVar4 = (int)uVar2 >> 0x1f;
  if ((int)(((uVar2 ^ uVar4) - uVar4 & 3 ^ uVar4) - uVar4) < *(int *)(iVar1 + 0xa818)) {
    *(int *)(iVar1 + 0xa998) = param_2;
  }
  else {
    *(undefined4 *)(iVar1 + 0xa998) = 0;
  }
  iVar3 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar3 == 0) {
    fVar5 = get_runtime_time_seconds();
    uVar2 = rand();
    uVar4 = (int)uVar2 >> 0x1f;
    *(undefined4 *)(iVar1 + 0x80) = 0x420c0000;
    iVar3 = ((uVar2 ^ uVar4) - uVar4 & 3 ^ uVar4) - uVar4;
    *(float *)(iVar1 + 0xa82c) = ((float)iVar3 + (float)fVar5) - _DAT_004bc890;
    return iVar3;
  }
  fVar5 = get_runtime_time_seconds();
  iVar3 = rand();
  *(undefined4 *)(iVar1 + 0x80) = 0x420c0000;
  *(float *)(iVar1 + 0xa82c) = ((float)(iVar3 % 5) + (float)fVar5) - _DAT_004bc8a8;
  return iVar3 / 5;
}


