/*
 * Program: i76.exe
 * Function: start_ai_behavior_random_offset_position_state
 * Entry: 00416f20
 * Signature: undefined __cdecl start_ai_behavior_random_offset_position_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Initializes AI behavior state with randomized target
   gating, timer, and projected offset/position fields. */

void __cdecl start_ai_behavior_random_offset_position_state(int param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  
  piVar1 = *(int **)(*(int *)(param_1 + 0x70) + 0x108);
  piVar1[0x20] = 0x420c0000;
  uVar3 = rand();
  uVar5 = (int)uVar3 >> 0x1f;
  if ((int)(((uVar3 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5) < piVar1[0x2a06]) {
    piVar1[0x2a66] = param_2;
  }
  else {
    piVar1[0x2a66] = 0;
  }
  iVar4 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar4 == 0) {
    fVar6 = get_runtime_time_seconds();
    uVar3 = rand();
    uVar5 = (int)uVar3 >> 0x1f;
    fVar2 = ((float)(int)(((uVar3 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5) + (float)fVar6) -
            _DAT_004bc890;
  }
  else {
    fVar6 = get_runtime_time_seconds();
    iVar4 = rand();
    fVar2 = ((float)piVar1[0x2a06] + (float)(iVar4 % 5) + (float)fVar6) - _DAT_004bc8b4;
  }
  piVar1[0x2a0b] = (int)fVar2;
  piVar1[0x2a58] = 0;
  iVar4 = *piVar1;
  project_point_to_path_segment_context_helper_0048e700
            ((float)*(double *)(iVar4 + 0x28),(float)*(double *)(iVar4 + 0x30),
             (float)*(double *)(iVar4 + 0x38),piVar1 + 0x2a5b,piVar1 + 0x2a54);
  if ((float)*(int *)(piVar1[0x2a5b] + 0x14) * _DAT_004bc8b8 < (float)piVar1[0x2a54]) {
    piVar1[0x2a55] = -1;
    return;
  }
  piVar1[0x2a55] = 1;
  return;
}


