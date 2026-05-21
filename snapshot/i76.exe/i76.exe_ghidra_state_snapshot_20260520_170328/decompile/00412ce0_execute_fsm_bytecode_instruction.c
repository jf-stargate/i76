/*
 * Program: i76.exe
 * Function: execute_fsm_bytecode_instruction
 * Entry: 00412ce0
 * Signature: undefined __cdecl execute_fsm_bytecode_instruction(int param_1, int param_2, int param_3, undefined4 param_4, int param_5, undefined4 param_6, int param_7, undefined4 param_8, int param_9, int * param_10)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: large switch over FSM instruction prototype/state; string
   evidence unknown fsm prototype */

void __cdecl
execute_fsm_bytecode_instruction
          (int param_1,int param_2,int param_3,undefined4 param_4,int param_5,undefined4 param_6,
          int param_7,undefined4 param_8,int param_9,int *param_10)

{
  int *piVar1;
  int *piVar2;
  uint *puVar3;
  undefined4 *puVar4;
  bool bVar5;
  LPVOID pvVar6;
  undefined3 extraout_var;
  int iVar7;
  undefined3 extraout_var_00;
  undefined4 uVar8;
  uint uVar9;
  LPVOID pvVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  float10 fVar14;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  
  switch(*(undefined4 *)(param_3 + param_2 * 0x54 + 0x50)) {
  case 0:
    break;
  case 1:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_behave_not_implemented();
    break;
  case 2:
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    update_vehicle_ai_target_and_attack_state(pvVar6,pvVar10,0);
    break;
  case 3:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    update_vehicle_ai_target_and_attack_state(pvVar10,(LPVOID)0x0,0x1f);
    break;
  case 4:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = *(int *)(*(int *)((int)pvVar10 + 0x70) + 0x108);
    *(int *)(iVar11 + 0x8c) = param_7 + **(int **)(param_1 + 0x1004) * 0x58;
    *(float *)(iVar11 + 0x80) = (float)**(int **)(param_1 + 0x1008);
    update_vehicle_ai_target_and_attack_state(pvVar10,(LPVOID)0x0,0x16);
    break;
  case 5:
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    update_vehicle_ai_target_and_attack_state(pvVar6,pvVar10,0x20);
    break;
  case 6:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_do_not_implemented();
    break;
  case 7:
  case 0x2f:
    **(undefined4 **)(param_1 + 0x1000) = **(undefined4 **)(param_1 + 0x1004);
    break;
  case 8:
    **(int **)(param_1 + 0x1000) = **(int **)(param_1 + 0x1000) + 1;
    break;
  case 9:
    **(int **)(param_1 + 0x1000) = **(int **)(param_1 + 0x1000) + -1;
    break;
  case 10:
    piVar17 = *(int **)(param_1 + 0x1004);
    piVar16 = *(int **)(param_1 + 0x1000);
    iVar11 = rand();
    *piVar16 = iVar11 % *piVar17;
    break;
  case 0xb:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_query_who_rammed((int)pvVar10,piVar17,param_10,param_9);
    break;
  case 0xc:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_query_recent_special_damage_source((int)pvVar10,piVar17,param_10,param_9);
    break;
  case 0xd:
    puVar4 = *(undefined4 **)(param_1 + 0x1000);
    mission_flow_map_context_helper_0049c7e0();
    uVar8 = ftol();
    *puVar4 = uVar8;
    break;
  case 0xe:
    mark_mission_objective_succeeded(**(int **)(param_1 + 0x1000));
    break;
  case 0xf:
    piVar17 = *(int **)(param_1 + 0x1000);
    fVar14 = mission_flow_map_context_helper_0049c7e0();
    DAT_005244e4 = 1;
    _DAT_005244e0 = (float)(fVar14 + (float10)*piVar17);
    mission_objective_state_context_helper_0045eb30(-1);
    break;
  case 0x10:
    mark_mission_objective_failed(**(int **)(param_1 + 0x1000));
    break;
  case 0x11:
    piVar17 = *(int **)(param_1 + 0x1000);
    fVar14 = mission_flow_map_context_helper_0049c7e0();
    DAT_005244e4 = 0;
    _DAT_005244e0 = (float)(fVar14 + (float10)*piVar17);
    mission_objective_state_context_helper_0045eb30(-1);
    break;
  case 0x12:
    piVar17 = *(int **)(param_1 + 0x1004);
    piVar16 = *(int **)(param_1 + 0x1000);
    fVar14 = mission_flow_map_context_helper_0049c7e0();
    DAT_005244e4 = 0;
    _DAT_005244e0 = (float)(fVar14 + (float10)*piVar16);
    mission_objective_state_context_helper_0045eb30(*piVar17);
    break;
  case 0x13:
    if (*(int *)(param_5 + 0x50 + **(int **)(param_1 + 0x1000) * 0x54) != 0) {
      update_timer_or_frame_delta((char *)(param_5 + **(int **)(param_1 + 0x1000) * 0x54),0,3);
    }
    break;
  case 0x14:
    fsm_update_timer_with_script_type
              ((char *)(param_5 + **(int **)(param_1 + 0x1000) * 0x54),*(int **)(param_1 + 0x1004));
    break;
  case 0x15:
    piVar17 = *(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_update_timer_with_value_and_type
              ((char *)(param_5 + **(int **)(param_1 + 0x1000) * 0x54),(int)pvVar10,piVar17);
    break;
  default:
    report_error();
                    /* WARNING: Subroutine does not return */
    abort();
  case 0x17:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_format_default_label_name((int)pvVar10,piVar17,param_9,param_10);
    break;
  case 0x18:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_find_nearest_enemy((int)pvVar10,piVar17,param_9,param_10);
    break;
  case 0x19:
    *(undefined4 *)(param_1 + 0x10a0) = 1;
    break;
  case 0x1a:
    *(undefined4 *)(param_1 + 0x10a0) = 0;
    break;
  case 0x1b:
    *(uint *)(param_1 + 0x10a0) =
         (uint)(**(int **)(param_1 + 0x1000) == **(int **)(param_1 + 0x1004));
    break;
  case 0x1c:
    *(uint *)(param_1 + 0x10a0) =
         (uint)(**(int **)(param_1 + 0x1004) < **(int **)(param_1 + 0x1000));
    break;
  case 0x1d:
    *(uint *)(param_1 + 0x10a0) =
         (uint)(**(int **)(param_1 + 0x1000) < **(int **)(param_1 + 0x1004));
    break;
  case 0x1e:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_test_not_implemented();
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x1f:
    piVar17 = *(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    uVar8 = fsm_query_objects_within_radius((int)pvVar6,(int)pvVar10,piVar17);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x20:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_current_actor_matches_state_slot_a6d4((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x21:
    piVar17 = *(int **)(param_1 + 0x1008);
    uVar8 = *(undefined4 *)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_object_integrity_less_than((int)pvVar10,uVar8,piVar17);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x22:
    puVar3 = *(uint **)(param_1 + 0x1008);
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    bVar5 = fsm_query_ammo_lesser((int)pvVar10,piVar17,puVar3);
    *(uint *)(param_1 + 0x10a0) = CONCAT31(extraout_var_00,bVar5);
    break;
  case 0x23:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_current_actor_matches_state_slot_a6d8((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x24:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_world_object_flag_0x200_set((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x25:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_is_lit_not_implemented();
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x26:
    iVar11 = **(int **)(param_1 + 0x1000);
    iVar12 = **(int **)(param_1 + 0x1004);
    mission_flow_map_context_helper_0049c7e0();
    iVar7 = ftol();
    if ((float)(iVar11 + iVar12) < (float)iVar7 - _DAT_004bc798) {
      *(undefined4 *)(param_1 + 0x10a0) = 1;
      break;
    }
    goto LAB_00413992;
  case 0x27:
    iVar11 = **(int **)(param_1 + 0x1000);
    iVar12 = **(int **)(param_1 + 0x1004);
    mission_flow_map_context_helper_0049c7e0();
    iVar7 = ftol();
    if ((float)iVar7 - _DAT_004bc798 < (float)(iVar11 + iVar12)) {
      *(undefined4 *)(param_1 + 0x10a0) = 1;
      break;
    }
LAB_00413992:
    *(undefined4 *)(param_1 + 0x10a0) = 0;
    break;
  case 0x28:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_and_clear_vehicle_damage_event_flag((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x29:
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    *(uint *)(param_1 + 0x10a0) = (uint)(pvVar6 == pvVar10);
    break;
  case 0x2a:
    piVar17 = *(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_object_near_script_xy_position
                      (param_7 + **(int **)(param_1 + 0x1000) * 0x58,(int)pvVar10,piVar17);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x2b:
    piVar17 = *(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_object_inside_script_xy_box
                      (param_7 + **(int **)(param_1 + 0x1000) * 0x58,(int)pvVar10,piVar17);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x2c:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_enemy_vehicle_within_radius((int)pvVar10,piVar17);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x2d:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_current_actor_matches_any_damage_state_slot((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x2e:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_query_who_attacked((int)pvVar10,piVar17,param_10,param_9);
    break;
  case 0x30:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = *(int *)(*(int *)((int)pvVar10 + 0x70) + 0x108);
    iVar12 = **(int **)(param_1 + 0x1008) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar12 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar12 + 0x58 + param_9) = pvVar10;
    *(LPVOID *)(iVar11 + 0xa990) = pvVar10;
    *(undefined4 *)(iVar11 + 0xa98c) = **(undefined4 **)(param_1 + 0x100c);
    *(float *)(iVar11 + 0xa980) = (float)**(int **)(param_1 + 0x1010);
    *(float *)(iVar11 + 0xa984) = (float)**(int **)(param_1 + 0x1014);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    update_vehicle_ai_target_and_attack_state(pvVar6,pvVar10,0x1e);
    break;
  case 0x31:
    piVar13 = *(int **)(param_1 + 0x1008);
    piVar16 = *(int **)(param_1 + 0x100c);
    iVar11 = **(int **)(param_1 + 0x1004);
    iVar12 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar12 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar12 + 0x58 + param_9) = pvVar10;
    piVar15 = (int *)0x0;
    piVar17 = (int *)0x0;
    goto LAB_0041389b;
  case 0x32:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_destroy_target_object((int)pvVar10);
    break;
  case 0x33:
    if (*(int *)(param_5 + 0x50 + **(int **)(param_1 + 0x1000) * 0x54) != 0) {
      ui_bitmap_region_context_helper_0049aec0(param_5 + **(int **)(param_1 + 0x1000) * 0x54);
    }
    break;
  case 0x34:
    iVar11 = weapon_hud_display_context_helper_004621a0();
    if (iVar11 != 0) {
      input_device_binding_input_action_state_helper_0044dff0(0);
      input_device_binding_input_action_state_helper_0044e000(0xd);
      iVar11 = 0xd;
      uVar8 = get_active_player_or_camera_world_object_entry();
      dispatch_runtime_camera_mode_activation_by_id(uVar8,iVar11);
    }
    fsm_camera_stack_underflow_error();
    break;
  case 0x35:
    fsm_camera_stack_overflow_error();
    break;
  case 0x36:
    iVar11 = **(int **)(param_1 + 0x1010) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    piVar17 = *(int **)(param_1 + 0x100c);
    piVar16 = *(int **)(param_1 + 0x1008);
    piVar13 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    mission_flow_map_context_helper_0049d5f0((int)pvVar6,piVar13,piVar16,piVar17,(int)pvVar10);
    break;
  case 0x37:
    piVar17 = *(int **)(param_1 + 0x1010);
    piVar16 = *(int **)(param_1 + 0x100c);
    piVar13 = *(int **)(param_1 + 0x1008);
    piVar15 = *(int **)(param_1 + 0x1004);
    piVar1 = *(int **)(param_1 + 0x1018);
    piVar2 = *(int **)(param_1 + 0x1014);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    mission_flow_map_context_helper_0049d4a0
              ((int)pvVar10,piVar15,piVar13,piVar16,piVar17,piVar2,piVar1);
    break;
  case 0x38:
    iVar11 = **(int **)(param_1 + 0x1008) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    mission_flow_map_context_helper_0049d740
              (param_7 + **(int **)(param_1 + 0x1000) * 0x58,*(int **)(param_1 + 0x1004),(int *)0x0,
               (int)pvVar10);
    break;
  case 0x39:
    piVar17 = *(int **)(param_1 + 0x1010);
    piVar16 = *(int **)(param_1 + 0x100c);
    piVar13 = *(int **)(param_1 + 0x1008);
    piVar15 = (int *)0x0;
    goto LAB_0041328f;
  case 0x3a:
    iVar11 = **(int **)(param_1 + 0x100c) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    mission_flow_map_context_helper_0049d740
              (param_7 + **(int **)(param_1 + 0x1000) * 0x58,*(int **)(param_1 + 0x1004),
               *(int **)(param_1 + 0x1008),(int)pvVar10);
    break;
  case 0x3b:
    piVar17 = *(int **)(param_1 + 0x1008);
    piVar16 = *(int **)(param_1 + 0x100c);
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    mission_flow_map_context_helper_0049dda0((int)pvVar6,(int)pvVar10,piVar17,piVar16);
    break;
  case 0x3c:
    piVar17 = *(int **)(param_1 + 0x1014);
    piVar16 = *(int **)(param_1 + 0x1010);
    piVar13 = *(int **)(param_1 + 0x100c);
    piVar15 = *(int **)(param_1 + 0x1008);
LAB_0041328f:
    mission_flow_map_context_helper_0049dac0
              ((float)(param_7 + **(int **)(param_1 + 0x1000) * 0x58),*(int **)(param_1 + 0x1004),
               piVar15,piVar13,piVar16,piVar17);
    break;
  case 0x3d:
    uVar8 = mission_flow_map_context_helper_0049d730();
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x3e:
    uVar8 = input_action_state_clearer_helper_0044de40();
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x3f:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_start_world_object_action_slot_7((int)pvVar10);
    break;
  case 0x40:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = *(int *)(*(int *)((int)pvVar10 + 0x70) + 0x108);
    *(int *)(iVar11 + 0x8c) = param_7 + **(int **)(param_1 + 0x1004) * 0x58;
    *(float *)(iVar11 + 0x80) = (float)**(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x100c) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    update_vehicle_ai_target_and_attack_state(pvVar10,pvVar6,0x18);
    break;
  case 0x41:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_toggle_ai_behavior_state_flag_9d14((int)pvVar10);
    break;
  case 0x42:
    uVar8 = fsm_query_no_visible_transform_targets_active();
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x43:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_all_other_team_vehicles_flag_0x20_set((uint)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x44:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_set_helicopter_height((int)pvVar10,piVar17);
    break;
  case 0x45:
    piVar17 = *(int **)(param_1 + 0x1008);
    piVar16 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_set_tactics_weights_from_script_indices((int)pvVar10,piVar16,piVar17);
    break;
  case 0x46:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_is_at_follow_target((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x47:
    piVar17 = *(int **)(param_1 + 0x1008);
    piVar16 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    enqueue_ai_vehicle_steer_brake_sample_from_history((int)pvVar10,piVar16,piVar17);
    break;
  case 0x48:
    piVar17 = *(int **)(param_1 + 0x100c);
    piVar16 = *(int **)(param_1 + 0x1010);
    piVar13 = *(int **)(param_1 + 0x1008);
    piVar15 = *(int **)(param_1 + 0x1004);
    piVar1 = *(int **)(param_1 + 0x1018);
    piVar2 = *(int **)(param_1 + 0x1014);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    enqueue_vehicle_steer_brake_input_sample
              ((int)pvVar10,piVar15,piVar13,piVar17,piVar16,piVar2,piVar1);
    break;
  case 0x49:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    apply_player_control_input_to_vehicle_runtime((int)pvVar10);
    break;
  case 0x4a:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = get_ai_vehicle_damage_state_field_a6d0((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x4b:
    fsm_reveal_mission_objective(*(int **)(param_1 + 0x1000));
    break;
  case 0x4c:
    bVar5 = is_voice_speech_channel_available();
    *(uint *)(param_1 + 0x10a0) = CONCAT31(extraout_var,bVar5);
    break;
  case 0x4d:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_set_tactics_tag_from_index((int)pvVar10,piVar17);
    break;
  case 0x4e:
    fsm_set_active_player_vehicle_control_context(*(int **)(param_1 + 0x1000));
    break;
  case 0x4f:
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_update_timer_default_type3
              ((char *)(param_5 + **(int **)(param_1 + 0x1000) * 0x54),(int)pvVar10);
    break;
  case 0x50:
    release_audio_world_object_attachment_records(0);
    break;
  case 0x51:
    fsm_append_salvage_resource_reference((char *)(param_5 + **(int **)(param_1 + 0x1000) * 0x54));
    break;
  case 0x52:
    piVar17 = *(int **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_play_or_stop_vehicle_engine_event_sound((int)pvVar10,piVar17);
    break;
  case 0x53:
    puVar4 = *(undefined4 **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_set_ai_behavior_state_field_9d14((int)pvVar10,puVar4);
    break;
  case 0x54:
    puVar4 = *(undefined4 **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_set_ai_behavior_state_field_a948((int)pvVar10,puVar4);
    break;
  case 0x55:
    iVar11 = **(int **)(param_1 + 0x1004) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    uVar8 = test_weapon_projectile_path_clear_to_target((int)pvVar6,(int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x56:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar9 = fsm_query_vehicle_runtime_flag_0x454_bit2((int)pvVar10);
    *(uint *)(param_1 + 0x10a0) = uVar9;
    break;
  case 0x57:
    piVar17 = *(int **)(param_1 + 0x1010);
    piVar16 = *(int **)(param_1 + 0x100c);
    piVar13 = *(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x1004);
    piVar15 = *(int **)(param_1 + 0x1014);
    iVar12 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar12 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar12 + 0x58 + param_9) = pvVar10;
LAB_0041389b:
    fsm_teleport_object((int)pvVar10,param_7 + iVar11 * 0x58,piVar13,piVar16,piVar17,piVar15);
    break;
  case 0x58:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    uVar8 = fsm_query_is_grooves_fault((int)pvVar10);
    *(undefined4 *)(param_1 + 0x10a0) = uVar8;
    break;
  case 0x59:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    update_vehicle_ai_target_and_attack_state(pvVar10,(LPVOID)0x0,0x21);
    break;
  case 0x5a:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    vehicle_specials_indicator_update_helper_00467400((int)pvVar10);
    break;
  case 0x5b:
    puVar3 = *(uint **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    fsm_mark_vehicle_effect_object_if_flag6_mismatch((int)pvVar10,puVar3);
    break;
  case 0x5c:
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    iVar11 = *(int *)(*(int *)((int)pvVar10 + 0x70) + 0x108);
    *(int *)(iVar11 + 0x8c) = param_7 + **(int **)(param_1 + 0x1004) * 0x58;
    *(float *)(iVar11 + 0x80) = (float)**(int **)(param_1 + 0x1008);
    iVar11 = **(int **)(param_1 + 0x100c) * 0x60;
    pvVar6 = release_world_object_tree_reference(*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10)
    ;
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar6;
    update_vehicle_ai_target_and_attack_state(pvVar10,pvVar6,0x1a);
    break;
  case 0x5d:
    puVar4 = *(undefined4 **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    vehicle_specials_display_context_helper_00462c80((int)pvVar10,puVar4);
    break;
  case 0x5e:
    puVar4 = *(undefined4 **)(param_1 + 0x1004);
    iVar11 = **(int **)(param_1 + 0x1000) * 0x60;
    pvVar10 = release_world_object_tree_reference
                        (*(LPVOID *)(iVar11 + 0x58 + param_9),&DAT_004c2a10);
    *(LPVOID *)(iVar11 + 0x58 + param_9) = pvVar10;
    vehicle_specials_display_context_helper_00462ca0((int)pvVar10,puVar4);
    break;
  case 0x5f:
    fsm_stop_callback_handler();
  }
  *(int *)(param_1 + 0x10b4) = param_1 + 0x1000;
  *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
  return;
}


