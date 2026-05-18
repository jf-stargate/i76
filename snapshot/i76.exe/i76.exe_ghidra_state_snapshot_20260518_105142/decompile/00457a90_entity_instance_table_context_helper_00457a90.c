/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_00457a90
 * Entry: 00457a90
 * Signature: undefined __cdecl entity_instance_table_context_helper_00457a90(float param_1, float param_2, float param_3, int param_4, int param_5, float param_6, float * param_7, float * param_8, undefined4 param_9, undefined4 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457a90. Remove
   duplicated network/entity wording. */

void __cdecl
entity_instance_table_context_helper_00457a90
          (float param_1,float param_2,float param_3,int param_4,int param_5,float param_6,
          float *param_7,float *param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,
          undefined4 param_12,undefined4 param_13,undefined4 param_14)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  float *local_8;
  int iVar13;
  
  zfsf_error_context_helper_004ba0a0();
  fVar2 = param_1;
  palette_dib_surface_unlock_context_helper_00477ed0((int)param_1);
  if (((DAT_004c2724 != 0) ||
      (bVar5 = is_runtime_camera_mode_11_callback_active(), piVar12 = (int *)0x0,
      CONCAT31(extraout_var,bVar5) != 0)) && (piVar12 = DAT_004c2908, DAT_004c2908 == (int *)0x0)) {
    DAT_004c2908 = g_active_player_or_camera_world_object_entry;
    piVar12 = g_active_player_or_camera_world_object_entry;
  }
  param_6 = _DAT_004bdf94 / *(float *)((int)fVar2 + 8);
  param_5 = 0;
  param_4 = 0;
  iVar13 = 0;
  if (0 < g_active_world_object_entry_count) {
    param_8 = (float *)&stack0x00000884;
    param_7 = (float *)&stack0x00000e84;
    local_8 = (float *)&g_active_world_object_entries;
    do {
      iVar9 = (int)*local_8;
      if (iVar9 != 0) {
        if ((*(uint *)(iVar9 + 0x10) & 0x100) == 0) {
          if (local_8 != (float *)piVar12) {
            puVar6 = (undefined4 *)
                     zone_satellite_map_context_helper_00494be0
                               (local_8 + 1,(float *)(iVar9 + 0x18),(undefined4 *)&stack0x0000006c);
            fVar2 = param_1;
            puVar11 = &param_9;
            for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
              *puVar11 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar11 = puVar11 + 1;
            }
            pfVar7 = (float *)raster_scratch_arena_context_helper_00472d30
                                        ((float *)&stack0x00000048,(int)param_1,
                                         (double)CONCAT44(param_10,param_9),
                                         (double)CONCAT44(param_12,param_11),
                                         (double)CONCAT44(param_14,param_13));
            param_1 = *pfVar7;
            param_2 = pfVar7[1];
            param_3 = pfVar7[2];
            uVar8 = software_raster_queue_context_helper_00472c10
                              ((int)fVar2,&param_1,local_8[4] * _DAT_004bdfbc);
            if ((int)uVar8 < 1) {
              iVar9 = is_vehicle_or_weapon_source_world_object((int)*local_8);
              if (iVar9 == 1) {
                *(float **)(&stack0x00000684 + param_5 * 4) = local_8;
                *param_7 = param_1;
                *(uint *)(&stack0x00000284 + param_5 * 4) = ~uVar8 & 0x100;
                param_7[1] = param_2;
                param_5 = param_5 + 1;
                param_7[2] = param_3;
                param_7 = param_7 + 3;
              }
              else {
                *(float **)(&stack0x00000484 + param_4 * 4) = local_8;
                *param_8 = param_1;
                *(uint *)(&stack0x00000084 + param_4 * 4) = ~uVar8 & 0x100;
                param_8[1] = param_2;
                param_4 = param_4 + 1;
                param_8[2] = param_3;
                param_8 = param_8 + 3;
              }
            }
          }
        }
        else {
          for (iVar9 = *(int *)(iVar9 + 100); iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x60)) {
            puVar6 = (undefined4 *)
                     zone_satellite_map_context_helper_00494be0
                               ((float *)(iVar9 + 0x84),(float *)(iVar9 + 0x18),
                                (undefined4 *)&stack0x00000054);
            fVar2 = param_1;
            puVar11 = &param_9;
            for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
              *puVar11 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar11 = puVar11 + 1;
            }
            pfVar7 = (float *)raster_scratch_arena_context_helper_00472d30
                                        ((float *)&stack0x0000003c,(int)param_1,
                                         (double)CONCAT44(param_10,param_9),
                                         (double)CONCAT44(param_12,param_11),
                                         (double)CONCAT44(param_14,param_13));
            param_1 = *pfVar7;
            param_2 = pfVar7[1];
            param_3 = pfVar7[2];
            uVar8 = software_raster_queue_context_helper_00472c10
                              ((int)fVar2,&param_1,*(float *)(iVar9 + 0x90) * _DAT_004bdfbc);
            if ((int)uVar8 < 1) {
              puVar6 = i76_runtime_prepare_terrain_polygon_material_or_light();
              *(uint *)(iVar9 + 0x14) = *(uint *)(iVar9 + 0x14) & 0xffffffee;
              puVar6[7] = iVar9;
              puVar6[0xd] = ~uVar8 & 0x100;
              puVar6[8] = param_1;
              puVar6[9] = param_2;
              puVar6[10] = param_3;
              if (*(int *)(iVar9 + 0x6c) == 0x33) {
                puVar6[0xc] = 0;
              }
              else {
                iVar10 = world_object_tree_context_helper_00457f40((int *)local_8,param_3 * param_6)
                ;
                puVar6[0xc] = iVar10;
              }
              puVar6[0xe] = 1;
              if ((*(byte *)(iVar9 + 0x10) & 0x40) == 0) {
                puVar6[3] = 5;
                puVar6[0xb] = local_8[4];
              }
              else {
                puVar6[3] = 7;
                puVar6[0xb] = 0x3f800000;
              }
              i76_runtime_bin_terrain_primitive_for_scan_or_span_render
                        ((float)puVar6[10] - (float)puVar6[0xb]);
            }
          }
        }
      }
      iVar13 = iVar13 + 1;
      local_8 = local_8 + 0x1e;
    } while (iVar13 < g_active_world_object_entry_count);
  }
  iVar13 = 0;
  if (0 < param_4) {
    local_8 = (float *)&stack0x0000088c;
    do {
      piVar12 = *(int **)(&stack0x00000484 + iVar13 * 4);
      iVar9 = *piVar12;
      puVar6 = i76_runtime_prepare_terrain_polygon_material_or_light();
      uVar1 = *(undefined4 *)(&stack0x00000084 + iVar13 * 4);
      puVar6[3] = 5;
      puVar6[7] = iVar9;
      puVar6[0xd] = uVar1;
      fVar2 = local_8[-2];
      puVar6[0x10] = piVar12;
      puVar6[8] = fVar2;
      fVar2 = local_8[-1];
      puVar6[0xe] = 0;
      fVar3 = *local_8;
      puVar6[9] = fVar2;
      puVar6[10] = fVar3;
      fVar2 = *local_8;
      puVar6[0xb] = piVar12[4];
      iVar9 = world_object_tree_context_helper_00457f40(piVar12,param_6 * fVar2);
      puVar6[0xc] = iVar9;
      local_8 = local_8 + 3;
      iVar13 = iVar13 + 1;
      i76_runtime_bin_terrain_primitive_for_scan_or_span_render
                ((float)puVar6[10] - (float)piVar12[4]);
    } while (iVar13 < param_4);
  }
  iVar13 = 0;
  if (0 < param_5) {
    pfVar7 = (float *)&stack0x00000e8c;
    do {
      piVar12 = *(int **)(&stack0x00000684 + iVar13 * 4);
      iVar9 = *piVar12;
      puVar6 = i76_runtime_prepare_terrain_polygon_material_or_light();
      uVar1 = *(undefined4 *)(&stack0x00000284 + iVar13 * 4);
      puVar6[3] = 5;
      puVar6[7] = iVar9;
      puVar6[0xd] = uVar1;
      fVar3 = pfVar7[-2];
      puVar6[0x10] = piVar12;
      fVar2 = *pfVar7;
      puVar6[8] = fVar3;
      fVar3 = pfVar7[-1];
      puVar6[0xe] = 0;
      fVar4 = *pfVar7;
      puVar6[9] = fVar3;
      puVar6[10] = fVar4;
      puVar6[0xb] = piVar12[4];
      iVar9 = world_object_tree_context_helper_00457f40(piVar12,param_6 * fVar2);
      fVar2 = *pfVar7;
      puVar6[0xc] = iVar9;
      i76_runtime_bin_terrain_primitive_for_scan_or_span_render(fVar2 - (float)piVar12[4]);
      iVar13 = iVar13 + 1;
      pfVar7 = pfVar7 + 3;
    } while (iVar13 < param_5);
  }
  return;
}


