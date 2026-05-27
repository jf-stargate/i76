/*
 * Program: i76.exe
 * Function: update_vehicle_ai_target_and_attack_state
 * Entry: 00412830
 * Signature: undefined __cdecl update_vehicle_ai_target_and_attack_state(LPVOID param_1, LPVOID param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: sets vehicle runtime target/ref and attack/state tables */

void __cdecl update_vehicle_ai_target_and_attack_state(LPVOID param_1,LPVOID param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  LPVOID pvVar3;
  int iVar4;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int local_4;
  
                    /* I76 semantic baseline: update_vehicle_ai_target_and_attack_state
                       Updates AI vehicle target/attack state against active object. */
  if (param_1 == (LPVOID)0x0) {
    return;
  }
  iVar1 = *(int *)(*(int *)((int)param_1 + 0x70) + 0x108);
  pvVar3 = *(LPVOID *)(iVar1 + 0xa9b4);
  if (param_2 != pvVar3) {
    if (pvVar3 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(pvVar3,&DAT_004c2a10);
    }
    if (param_2 != (LPVOID)0x0) {
      increment_refcount_recursive_for_object_tree((int)param_2,&DAT_004c2a10);
    }
    *(LPVOID *)(iVar1 + 0xa9b4) = param_2;
  }
  if (param_2 != (LPVOID)0x0) {
    pvVar3 = release_world_object_tree_reference(param_2,&DAT_004c2a10);
    *(LPVOID *)(iVar1 + 0xa9b4) = pvVar3;
    if (pvVar3 == (LPVOID)0x0) {
      set_vehicle_brake_to_max_safe_value((float)param_1);
      return;
    }
  }
  iVar4 = ai_behavior_condition_always_true();
  if (iVar4 == 0) {
    set_vehicle_brake_to_max_safe_value((float)param_1);
    return;
  }
  get_vehicle_runtime_context((int)param_1);
  fsm_get_vehicle_weapon_info((int)param_1);
  if ((*(int *)(iVar1 + 0xa93c) != -1) &&
     (bVar2 = is_active_player_object_control_change_allowed((int)param_1),
     CONCAT31(extraout_var,bVar2) == 0)) {
    switch(param_3) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      switch(*(undefined4 *)(iVar1 + 0xa874)) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
switchD_00412958_caseD_0:
        if (*(LPVOID *)(iVar1 + 0xa944) == param_2) {
          iVar4 = *(int *)(iVar1 + 0xa874 + *(int *)(iVar1 + 0xa93c) * 4);
          while( true ) {
            local_4 = 0;
            iVar8 = iVar4 * 0x1354;
            iVar6 = *(int *)(&DAT_004c3edc + iVar8);
            if (iVar6 < 1) break;
            puVar7 = (undefined4 *)(&DAT_004c3ee0 + iVar8);
            while (iVar5 = (*(code *)*puVar7)(param_1,param_2), iVar5 == 0) {
              puVar7 = puVar7 + 0x76;
              local_4 = local_4 + 1;
              if (iVar6 <= local_4) goto LAB_00412a8d;
            }
            if (*(code **)(&DAT_004c5150 + iVar8) != (code *)0x0) {
              (**(code **)(&DAT_004c5150 + iVar8))(param_1,param_2);
            }
            if (*(int *)(iVar1 + 0xa93c) < 1) {
              switch(*(undefined4 *)(iVar1 + 0xa874)) {
              case 0:
              case 1:
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
              case 8:
              case 9:
              case 10:
              case 0xb:
              case 0xc:
              case 0xd:
              case 0xe:
              case 0xf:
                iVar4 = compute_fsm_aggression_sum((int)param_1,param_2,iVar4,local_4);
                break;
              default:
                iVar4 = param_3;
              }
              *(int *)(iVar1 + 0xa874 + *(int *)(iVar1 + 0xa93c) * 4) = iVar4;
              if (*(code **)(&DAT_004c3e58 + iVar4 * 0x1354) != (code *)0x0) {
                (**(code **)(&DAT_004c3e58 + iVar4 * 0x1354))(param_1,param_2);
              }
              break;
            }
            iVar4 = *(int *)(iVar1 + 0xa93c) + -1;
            *(int *)(iVar1 + 0xa93c) = iVar4;
            iVar4 = *(int *)(iVar1 + 0xa874 + iVar4 * 4);
          }
          goto LAB_00412a8d;
        }
      }
      break;
    default:
      switch(*(int *)(iVar1 + 0xa874)) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
        break;
      default:
        if (param_3 == *(int *)(iVar1 + 0xa874)) goto switchD_00412958_caseD_0;
      }
    }
  }
  *(LPVOID *)(iVar1 + 0xa944) = param_2;
  iVar4 = param_3;
  switch(param_3) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
    iVar4 = compute_fsm_aggression_sum((int)param_1,param_2,0,0);
  }
  *(undefined4 *)(iVar1 + 0xa93c) = 0;
  *(int *)(iVar1 + 0xa874) = iVar4;
  if (*(code **)(&DAT_004c3e58 + iVar4 * 0x1354) != (code *)0x0) {
    (**(code **)(&DAT_004c3e58 + iVar4 * 0x1354))(param_1,param_2);
  }
LAB_00412a8d:
  (**(code **)(&DAT_004c3e54 + iVar4 * 0x1354))(param_1,param_2);
  while( true ) {
    iVar8 = 0;
    iVar4 = iVar4 * 0x1354;
    iVar6 = *(int *)(&DAT_004c3e88 + iVar4);
    if (iVar6 < 1) break;
    puVar7 = (undefined4 *)(&DAT_004c3e8c + iVar4);
    while (iVar5 = (*(code *)*puVar7)(param_1,param_2), iVar5 == 0) {
      iVar8 = iVar8 + 1;
      puVar7 = puVar7 + 2;
      if (iVar6 <= iVar8) goto LAB_00412b79;
    }
    iVar4 = *(int *)(&DAT_004c3e90 + iVar8 * 8 + iVar4);
    if (*(int *)(iVar1 + 0xa93c) < 0x31) {
      iVar6 = *(int *)(iVar1 + 0xa93c) + 1;
      *(int *)(iVar1 + 0xa93c) = iVar6;
      *(int *)(iVar1 + 0xa874 + iVar6 * 4) = iVar4;
      if (*(code **)(&DAT_004c3e58 + iVar4 * 0x1354) != (code *)0x0) {
        (**(code **)(&DAT_004c3e58 + iVar4 * 0x1354))(param_1,param_2);
      }
      (**(code **)(&DAT_004c3e54 + iVar4 * 0x1354))(param_1,param_2);
    }
    else {
      report_error();
    }
  }
LAB_00412b79:
  if (param_1 != param_2) {
    if (param_3 == 0x1e) {
      if (*(int *)(iVar1 + 0xa98c) != 0) {
        evaluate_vehicle_weapon_fire_requests((uint)param_1,iVar1,*(uint *)(iVar1 + 0xa990));
        return;
      }
    }
    else if (param_2 != (LPVOID)0x0) {
      evaluate_vehicle_weapon_fire_requests((uint)param_1,iVar1,(uint)param_2);
    }
  }
  return;
}


