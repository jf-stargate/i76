/*
 * Program: i76.exe
 * Function: ordnance_projectile_update_context_helper_004a0800
 * Entry: 004a0800
 * Signature: uint __cdecl ordnance_projectile_update_context_helper_004a0800(int * param_1, float param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: ordnance projectile update context
   helper based on adjacent named subsystem context. */

uint __cdecl ordnance_projectile_update_context_helper_004a0800(int *param_1,float param_2)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  int iVar3;
  undefined3 extraout_var_07;
  uint uVar4;
  
  uVar4 = 1;
  puVar1 = (undefined4 *)param_1[0x1c];
  switch(*puVar1) {
  case 1:
  case 6:
  case 0x12:
    bVar2 = ordnance_damage_log_tag((int)param_1,param_2);
    return CONCAT31(extraout_var,bVar2);
  case 2:
    bVar2 = ordnance_projectile_log_tag((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_03,bVar2);
    break;
  case 3:
    bVar2 = update_ordnance_damage_effects((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_04,bVar2);
    goto LAB_004a0882;
  case 4:
  case 7:
    bVar2 = ordnance_effect_log_tag((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_01,bVar2);
    break;
  case 5:
    bVar2 = release_ordnance_system((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_02,bVar2);
    goto LAB_004a08a0;
  case 8:
    bVar2 = update_ordnance_collision_state((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_05,bVar2);
    goto LAB_004a08a0;
  default:
    goto switchD_004a081b_caseD_9;
  case 0xc:
    uVar4 = update_ordnance_projectile_state_a((int)param_1);
    return uVar4;
  case 0xe:
    uVar4 = update_ordnance_projectile_state_b(param_1);
    return uVar4;
  case 0xf:
  case 0x10:
  case 0x13:
    bVar2 = ordnance_runtime_log_tag((int)param_1,param_2);
    return CONCAT31(extraout_var_07,bVar2);
  case 0x11:
    uVar4 = update_ordnance_projectile_state_c((int)param_1);
    return uVar4;
  case 0x14:
    bVar2 = ordnance_collision_log_tag((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_06,bVar2);
    break;
  case 0x15:
    bVar2 = ordnance_damage_log_tag((int)param_1,param_2);
    uVar4 = CONCAT31(extraout_var_00,bVar2);
LAB_004a08a0:
    if (uVar4 != 0) {
      return uVar4;
    }
    iVar3 = puVar1[3];
    uVar4 = 0;
    goto LAB_004a08cb;
  case 0x16:
    uVar4 = ordnance_cleanup_log_tag((int)param_1,param_2);
LAB_004a0882:
    if (uVar4 != 0) {
      return uVar4;
    }
    iVar3 = puVar1[3];
    uVar4 = 0;
    goto LAB_004a08cb;
  }
  if (uVar4 == 0) {
    iVar3 = puVar1[3];
LAB_004a08cb:
    iVar3 = world_object_has_optional_runtime_flag(iVar3);
    if (iVar3 != 0) {
      ordnance_runtime_flag_get_context_helper_004a7130((int)param_1);
      return uVar4;
    }
  }
switchD_004a081b_caseD_9:
  return uVar4;
}


