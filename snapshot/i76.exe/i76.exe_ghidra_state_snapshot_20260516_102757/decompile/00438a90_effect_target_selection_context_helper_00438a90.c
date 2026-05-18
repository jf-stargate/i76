/*
 * Program: i76.exe
 * Function: effect_target_selection_context_helper_00438a90
 * Entry: 00438a90
 * Signature: undefined __cdecl effect_target_selection_context_helper_00438a90(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was effect_target_scan_target_selection_helper_00438a90. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl effect_target_selection_context_helper_00438a90(float param_1)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  ushort uVar6;
  undefined4 *puVar7;
  float *pfVar8;
  undefined4 *puVar9;
  int iVar10;
  float fVar11;
  undefined2 extraout_var;
  int *piVar12;
  int local_30;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  fVar5 = param_1;
  local_18 = (float)*(double *)((int)param_1 + 0x40);
  local_14 = (float)*(double *)((int)param_1 + 0x48);
  local_10 = (float)*(double *)((int)param_1 + 0x50);
  probe_effect_target_surface_height_at_position
            ((double)CONCAT44(local_14,local_18),local_10,&param_1,(undefined4 *)0x0);
  *(double *)((int)fVar5 + 0x48) = (double)param_1;
  puVar7 = (undefined4 *)get_vehicle_runtime_context((int)fVar5);
  iVar2 = *(int *)(puVar7[0xf1] + 0x70);
  world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xeb]);
  world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xea]);
  world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xef]);
  world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xee]);
  if ((float)puVar7[0xed] != 0.0) {
    world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xed]);
  }
  if ((float)puVar7[0xec] != 0.0) {
    world_object_texture_animation_tick_helper_0046da90((float)puVar7[0xec]);
  }
  pfVar8 = (float *)compose_world_object_runtime_transform(&local_24,puVar7[0xeb]);
  local_18 = *pfVar8;
  local_14 = pfVar8[1];
  local_10 = pfVar8[2];
  pfVar8 = (float *)compose_world_object_runtime_transform(local_c,puVar7[0xea]);
  local_24 = *pfVar8;
  local_20 = pfVar8[1];
  local_1c = pfVar8[2];
  puVar7[0x45] = SQRT((local_10 - local_1c) * (local_10 - local_1c) +
                      (local_14 - local_20) * (local_14 - local_20) +
                      (local_18 - local_24) * (local_18 - local_24));
  pfVar8 = (float *)compose_world_object_runtime_transform(local_c,puVar7[0xef]);
  local_24 = *pfVar8;
  local_20 = pfVar8[1];
  local_1c = pfVar8[2];
  fVar11 = SQRT((local_10 - local_1c) * (local_10 - local_1c) +
                (local_14 - local_20) * (local_14 - local_20) +
                (local_18 - local_24) * (local_18 - local_24));
  puVar7[0x46] = fVar11;
  puVar7[0x44] = _DAT_004bd134 / (fVar11 + fVar11);
  puVar7[0x47] = (float)*(double *)(puVar7[0xef] + 0x50);
  puVar7[0x11e] = 0x3dcccccd;
  puVar9 = get_active_world_object_entry_object((int)fVar5);
  *puVar7 = puVar9;
  iVar10 = puVar9[6];
  local_14 = (*(float *)(iVar10 + 0x24) + *(float *)(iVar10 + 0x20)) * _DAT_004bd138;
  uVar1 = *(undefined4 *)(iVar10 + 0x2c);
  puVar7[1] = *(undefined4 *)(iVar10 + 0xc);
  local_30 = 3;
  puVar7[2] = local_14;
  puVar7[3] = uVar1;
  uVar1 = *(undefined4 *)(iVar10 + 0x2c);
  puVar7[4] = *(undefined4 *)(iVar10 + 0x18);
  puVar7[5] = local_14;
  puVar7[6] = uVar1;
  uVar1 = *(undefined4 *)(iVar10 + 0x38);
  puVar7[7] = *(undefined4 *)(iVar10 + 0x18);
  puVar7[8] = local_14;
  puVar7[9] = uVar1;
  local_10 = *(float *)(iVar10 + 0x38);
  local_18 = *(float *)(iVar10 + 0xc);
  puVar7[10] = local_18;
  puVar7[0xb] = local_14;
  piVar12 = puVar7 + 0xfb;
  puVar7[0xc] = local_10;
  puVar7[0xd] = *(undefined4 *)(iVar10 + 0x28);
  puVar7[0x123] = 0;
  puVar7[0x122] = 0;
  puVar7[0x141] = 0;
  puVar7[0x140] = 0;
  puVar7[0x125] = 0;
  puVar7[0x124] = 0;
  puVar7[0x127] = 0;
  puVar7[0x126] = 0;
  puVar7[299] = 0;
  puVar7[0x12a] = 0;
  fVar11 = (float)puVar7[0x46] * _DAT_004bd13c;
  fVar3 = (float)puVar7[0x46] * _DAT_004bd138;
  fVar4 = (float)puVar7[0x45] * _DAT_004bd138;
  param_1 = (float)puVar7[0x45] * _DAT_004bd13c;
  puVar7[0x13b] = fVar11;
  puVar7[0x129] = fVar3;
  puVar7[0x130] = param_1;
  puVar7[0x131] = fVar3;
  puVar7[0x138] = fVar4;
  puVar7[0x139] = fVar3;
  puVar7[0x13c] = param_1;
  puVar7[0x133] = 0;
  puVar7[0x132] = 0;
  puVar7[0x13d] = fVar11;
  puVar7[0x13e] = fVar4;
  puVar7[0x13a] = 0;
  puVar7[0x128] = 0;
  puVar7[0x13f] = fVar11;
  puVar7[0x137] = 0;
  puVar7[0x136] = fVar4;
  puVar7[300] = param_1;
  puVar7[0x12d] = 0;
  puVar7[0x12f] = 0;
  puVar7[0x12e] = 0;
  puVar7[0x135] = 0;
  puVar7[0x134] = 0;
  do {
    iVar10 = get_special_equipment_runtime_index(*piVar12);
    if (iVar10 == 3) {
      puVar7[0x4a] = 0x3fa00000;
    }
    else if (iVar10 == 8) {
      set_weapon_state_checked((int)fVar5);
    }
    piVar12 = piVar12 + 1;
    local_30 = local_30 + -1;
  } while (local_30 != 0);
  puVar7[0x115] = puVar7[0x115] | 0x1001;
  fVar11 = (float)get_fsm_registered_instance_count();
  if (fVar5 != fVar11) {
    if (((byte)DAT_00654b98 & 1) == 0) goto LAB_00438f26;
    iVar10 = world_object_has_optional_runtime_flag((int)fVar5);
    if (iVar10 == 0) goto LAB_00438f26;
  }
  puVar7[0x115] = puVar7[0x115] | 0x10000;
LAB_00438f26:
  uVar6 = lookup_terrain_material_index_at_world_xz
                    (*(double *)((int)fVar5 + 0x40),*(double *)((int)fVar5 + 0x50));
  param_1 = (float)puVar7[0x29];
  puVar7[0x117] = CONCAT22(extraout_var,uVar6);
  effect_target_list_scan_context_helper_00438340((float *)(puVar7 + 0x29),param_1,param_1);
  puVar7[0x2d] = _DAT_004bd140 / (float)puVar7[0x46];
  building_child_piece_context_helper_0046a890(puVar7[0xf3],(float)puVar7[0x2a] * _DAT_004bd144);
  iVar10 = get_vehicle_drivetrain_mode_state((int)fVar5);
  update_engine_gear_rpm_torque_state(iVar2,0.0,(float)puVar7[0x2b],puVar7[0x115],0,iVar10);
  start_vehicle_engine_loop_sound((int)fVar5);
  return;
}


