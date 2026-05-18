/*
 * Program: i76.exe
 * Function: evaluate_vehicle_weapon_fire_requests
 * Entry: 00414ef0
 * Signature: undefined __cdecl evaluate_vehicle_weapon_fire_requests(uint param_1, int param_2, uint param_3)
 */


/* cgpt whole-binary semantic rename v1: iterates vehicle weapon slots and calls fire-solution test
    */

void __cdecl evaluate_vehicle_weapon_fire_requests(uint param_1,int param_2,uint param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined4 local_58 [22];
  
  iVar5 = 0;
  if (0 < *(int *)(param_2 + 0xa718)) {
    piVar4 = (int *)(param_2 + 0xa71c);
    piVar3 = (int *)(param_2 + 0xa738);
    do {
      bVar1 = weapon_runtime_slot_belongs_to_world_object(*piVar4,param_1);
      if (CONCAT31(extraout_var,bVar1) == 0) {
        report_chunk_parse_error();
      }
      extract_weapon_runtime_state_to_vsf_record(*piVar4,local_58);
      iVar2 = test_weapon_fire_solution_against_target
                        (param_1,param_3,*(float *)(param_2 + 0xa828),*(float *)(param_2 + 0xa824),
                         iVar5,(int *)(param_2 + 0xa718),piVar3,(int)local_58);
      if (iVar2 != 0) {
        set_weapon_runtime_fire_request_flag(*piVar4,1);
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
      piVar3 = piVar3 + 8;
    } while (iVar5 < *(int *)(param_2 + 0xa718));
  }
  return;
}


