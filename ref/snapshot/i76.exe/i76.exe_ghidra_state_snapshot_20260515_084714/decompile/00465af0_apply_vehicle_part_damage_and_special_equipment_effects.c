/*
 * Program: i76.exe
 * Function: apply_vehicle_part_damage_and_special_equipment_effects
 * Entry: 00465af0
 * Signature: int __cdecl apply_vehicle_part_damage_and_special_equipment_effects(int * param_1, float param_2, int param_3, int param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Damage path below
   player vehicle damage callback. Checks special equipment, randomizes damage outcomes, dispatches
   class damage, updates part damage states and texture frames. */

int __cdecl
apply_vehicle_part_damage_and_special_equipment_effects
          (int *param_1,float param_2,int param_3,int param_4,float param_5)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int *piVar7;
  uint *puVar8;
  
  piVar7 = param_1;
  iVar3 = param_1[0xfb];
  iVar2 = get_special_equipment_runtime_index(iVar3);
  if ((iVar2 != 9) || (iVar2 = is_special_equipment_component_active(iVar3), iVar2 == 0)) {
    iVar3 = piVar7[0xfc];
    iVar2 = get_special_equipment_runtime_index(iVar3);
    if ((iVar2 != 9) || (iVar2 = is_special_equipment_component_active(iVar3), iVar2 == 0)) {
      iVar3 = piVar7[0xfd];
      iVar2 = get_special_equipment_runtime_index(iVar3);
      if ((iVar2 != 9) || (iVar2 = is_special_equipment_component_active(iVar3), iVar2 == 0)) {
        iVar3 = 0;
      }
    }
  }
  if ((iVar3 != 0) && (iVar3 = rand(), iVar3 % 100 < 10)) {
    *(undefined2 *)(param_3 + 4) = 0;
    return 0;
  }
  iVar3 = param_3;
  fVar1 = param_2;
  if (((*(byte *)(param_3 + 6) & 1) == 0) || (_DAT_004be1d8 <= param_5)) {
    iVar5 = (int)param_2 * 0x11;
    iVar3 = rand();
    iVar2 = piVar7[iVar3 % piVar7[(int)fVar1 + 0x68] + iVar5 + 0x6f];
    iVar3 = param_3;
    while( true ) {
      if (iVar2 == -1) {
        *(undefined2 *)(iVar3 + 4) = 0;
        return 0;
      }
      param_3 = iVar3;
      if ((piVar7[iVar2 + 0xea] != 0) && (iVar2 != 6)) break;
      iVar3 = rand();
      iVar2 = piVar7[iVar3 % piVar7[(int)fVar1 + 0x68] + iVar5 + 0x6f];
      iVar3 = param_3;
    }
  }
  else {
    iVar2 = 6;
    uVar4 = rand();
    *(uint *)(iVar3 + 0x10) = (uVar4 & 0x32) + 0x4b;
  }
  iVar5 = piVar7[iVar2 + 0xea];
  if (iVar5 == 0) {
switchD_00465c51_caseD_19:
    iVar5 = 0;
  }
  else {
    switch(*(undefined4 *)(iVar5 + 0x6c)) {
    case 0x14:
      iVar5 = **(int **)(iVar5 + 0x70);
      break;
    case 0x15:
    case 0x17:
      iVar5 = **(int **)(iVar5 + 0x70);
      break;
    case 0x16:
      iVar5 = *(int *)(*(int *)(iVar5 + 0x70) + 4);
      break;
    case 0x18:
      iVar5 = *(int *)(*(int *)(iVar5 + 0x70) + 8);
      break;
    default:
      goto switchD_00465c51_caseD_19;
    case 0x1e:
      iVar5 = *(int *)(*(int *)(iVar5 + 0x70) + 4);
      break;
    case 0x32:
      iVar5 = weapon_fire_request_context_helper_004a4c50(iVar5);
    }
  }
  if (iVar5 != 0) {
    iVar5 = dispatch_damage_context_to_world_object_class_handler(piVar7[iVar2 + 0xea],iVar3,0);
    iVar3 = piVar7[iVar2 + 0xea];
    if ((*(int *)(iVar3 + 0x6c) == 0x1e) && (iVar3 != 0)) {
      extract_part_damage_state_pair(iVar3,&param_5,&param_1);
      fVar1 = _g_float_zero;
      if (param_1 != (int *)0x0) {
        fVar1 = (float)(int)param_5 / (float)(int)param_1;
      }
      if (fVar1 <= _DAT_004be1e8) {
        if (fVar1 <= _DAT_004be1dc) {
          uVar4 = 2;
          if (fVar1 <= _DAT_004be1ec) {
            uVar4 = 3;
          }
        }
        else {
          uVar4 = 1;
        }
      }
      else {
        uVar4 = 0;
      }
      update_vehicle_damage_texture_state(piVar7,iVar2 + 5U,uVar4);
      set_vehicle_damage_texture_frame_group((int)piVar7,iVar2 + 5U,uVar4);
    }
    if (iVar5 == 0) {
      return 0;
    }
    iVar3 = 0;
    iVar2 = 0;
    piVar7 = (int *)(param_3 + 8);
    do {
      if (((uint)*(ushort *)(param_3 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
        iVar3 = iVar3 + *piVar7;
      }
      iVar2 = iVar2 + 1;
      piVar7 = piVar7 + 1;
    } while (iVar2 < 4);
    return iVar3;
  }
  if (param_4 != 0) {
    iVar5 = is_damage_side_effects_suppressed();
    if (iVar5 == 0) {
      iVar5 = get_active_player_or_camera_world_object_entry();
      param_5 = 0.1;
      if (iVar5 != *piVar7) goto LAB_00465cbb;
    }
    else {
LAB_00465cbb:
      param_5 = 2.5;
    }
    if ((*(byte *)(iVar3 + 4) & 8) == 0) {
      uVar4 = 0;
      param_1 = (int *)0x0;
      iVar3 = 0;
      do {
        iVar5 = vehicle_damage_part_state_context_helper_00466ac0((int)piVar7,iVar3);
        uVar4 = uVar4 + iVar5;
        iVar5 = vehicle_damage_part_state_context_helper_00466b70((int)piVar7,iVar3);
        param_1 = (int *)((int)param_1 + iVar5);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x14);
      iVar3 = rand();
      param_2 = ((float)uVar4 / (float)(int)param_1) * (float)(iVar3 % 100);
      param_1 = (int *)vehicle_damage_texture_context_helper_00465fe0(param_3);
      iVar3 = param_3;
      if (param_2 < (float)(int)param_1 * param_5) {
        if (iVar2 != 6) {
          piVar7[0x115] = piVar7[0x115] | 0x20;
          return 0;
        }
        piVar7[0x115] = piVar7[0x115] | 0x4020;
        return 0;
      }
    }
  }
  iVar2 = piVar7[iVar2 + 0xea];
  if (iVar2 == 0) {
switchD_00465db1_caseD_19:
    iVar2 = 0;
  }
  else {
    switch(*(undefined4 *)(iVar2 + 0x6c)) {
    case 0x14:
      iVar2 = *(int *)(*(int *)(iVar2 + 0x70) + 4);
      break;
    case 0x15:
    case 0x17:
      iVar2 = *(int *)(*(int *)(iVar2 + 0x70) + 4);
      break;
    case 0x16:
      iVar2 = *(int *)(*(int *)(iVar2 + 0x70) + 8);
      break;
    case 0x18:
      iVar2 = *(int *)(*(int *)(iVar2 + 0x70) + 0xc);
      break;
    default:
      goto switchD_00465db1_caseD_19;
    case 0x1e:
      iVar2 = *(int *)(*(int *)(iVar2 + 0x70) + 8);
      break;
    case 0x32:
      iVar2 = weapon_fire_request_context_helper_004a4c90(iVar2);
    }
  }
  uVar4 = iVar2 >> 2;
  puVar8 = (uint *)(iVar3 + 8);
  iVar2 = 0;
  puVar6 = puVar8;
  do {
    if (((uint)*(ushort *)(iVar3 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
      if (uVar4 < *puVar6) {
        *(uint *)(iVar3 + 8 + iVar2 * 4) = *(int *)(iVar3 + 8 + iVar2 * 4) - uVar4;
        return 0;
      }
      uVar4 = uVar4 - *puVar6;
      *puVar6 = 0;
    }
    iVar2 = iVar2 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar2 < 4);
  iVar2 = 0;
  iVar5 = 0;
  do {
    if (((uint)*(ushort *)(iVar3 + 4) & 1 << ((byte)iVar5 & 0x1f)) != 0) {
      iVar2 = iVar2 + *puVar8;
    }
    iVar5 = iVar5 + 1;
    puVar8 = puVar8 + 1;
  } while (iVar5 < 4);
  return iVar2;
}


