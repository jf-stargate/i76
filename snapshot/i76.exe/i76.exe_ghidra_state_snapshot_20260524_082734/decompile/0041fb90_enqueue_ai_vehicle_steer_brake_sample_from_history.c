/*
 * Program: i76.exe
 * Function: enqueue_ai_vehicle_steer_brake_sample_from_history
 * Entry: 0041fb90
 * Signature: undefined __cdecl enqueue_ai_vehicle_steer_brake_sample_from_history(int param_1, int * param_2, int * param_3)
 */


/* cgpt readability rename v13 set A: Builds steering/brake sample values from vehicle runtime
   history and enqueues them as player-control style input. */

void __cdecl
enqueue_ai_vehicle_steer_brake_sample_from_history(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_c [3];
  
  iVar1 = param_1;
  local_c[2] = 0;
  local_c[1] = 0;
  iVar2 = get_vehicle_runtime_context(param_1);
  iVar3 = get_vehicle_damage_event_state_block(iVar2);
  if (*(int *)(iVar3 + 0xa6cc) == *(int *)(iVar3 + 0xa6c8)) {
    param_1 = ftol();
    local_c[0] = *(int *)(iVar2 + 0xf0);
  }
  else {
    iVar2 = *(int *)(iVar3 + 0xa6cc) + -1;
    if (iVar2 < 0) {
      iVar2 = 99;
    }
    param_1 = ftol();
    local_c[0] = *(int *)(iVar3 + iVar2 * 0x18 + 0x9d74);
  }
  enqueue_vehicle_steer_brake_input_sample
            (iVar1,param_2,param_3,local_c,&param_1,local_c + 2,local_c + 1);
  return;
}


