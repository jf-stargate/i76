/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_00457ff0
 * Entry: 00457ff0
 * Signature: undefined __cdecl world_object_geometry_context_helper_00457ff0(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00457ff0.
   Remove duplicated world_object_geometry wording. */

void __cdecl world_object_geometry_context_helper_00457ff0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  undefined3 extraout_var;
  undefined4 *puVar4;
  float *pfVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  int iStack00000008;
  int iStack0000000c;
  float fStack00000010;
  float in_stack_00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float *in_stack_00000020;
  undefined4 in_stack_00000024;
  undefined4 in_stack_00000028;
  undefined4 in_stack_0000002c;
  undefined4 in_stack_00000030;
  undefined4 in_stack_00000034;
  undefined4 in_stack_00000038;
  float *local_8;
  int *piVar12;
  
  piVar12 = param_1;
  zfsf_error_context_helper_004ba0a0();
  palette_dib_surface_unlock_context_helper_00477ed0((int)param_1);
  param_1 = (int *)0x0;
  if (((DAT_004c2724 != 0) ||
      (bVar3 = is_runtime_camera_mode_11_callback_active(), CONCAT31(extraout_var,bVar3) != 0)) &&
     (param_1 = DAT_004c2908, DAT_004c2908 == (int *)0x0)) {
    DAT_004c2908 = g_active_player_or_camera_world_object_entry;
    param_1 = DAT_004c2908;
  }
  fStack00000010 = _DAT_004bdf94 / (float)piVar12[2];
  iStack00000008 = 0;
  iStack0000000c = 0;
  iVar11 = 0;
  if (0 < g_active_world_object_entry_count) {
    in_stack_00000020 = (float *)&stack0x00000e84;
    local_8 = (float *)&stack0x00000884;
    piVar12 = &g_active_world_object_entries;
    do {
      iVar8 = *piVar12;
      if (iVar8 != 0) {
        if ((*(uint *)(iVar8 + 0x10) & 0x100) == 0) {
          if (piVar12 != param_1) {
            puVar4 = (undefined4 *)
                     zone_satellite_map_context_helper_00494be0
                               ((float *)(piVar12 + 1),(float *)(iVar8 + 0x18),
                                (undefined4 *)&stack0x0000006c);
            puVar10 = &stack0x00000024;
            for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
              *puVar10 = *puVar4;
              puVar4 = puVar4 + 1;
              puVar10 = puVar10 + 1;
            }
            pfVar5 = (float *)raster_scratch_arena_context_helper_00472d30
                                        ((float *)&stack0x00000048,(int)param_1,
                                         (double)CONCAT44(in_stack_00000028,in_stack_00000024),
                                         (double)CONCAT44(in_stack_00000030,in_stack_0000002c),
                                         (double)CONCAT44(in_stack_00000038,in_stack_00000034));
            in_stack_00000014 = *pfVar5;
            in_stack_00000018 = pfVar5[1];
            in_stack_0000001c = pfVar5[2];
            uVar6 = software_raster_queue_context_helper_00472c10
                              ((int)param_1,&stack0x00000014,(float)piVar12[4] * _DAT_004bdfbc);
            if ((int)uVar6 < 1) {
              iVar8 = is_vehicle_or_weapon_source_world_object(*piVar12);
              if (iVar8 == 1) {
                *(int **)(&stack0x00000084 + iStack00000008 * 4) = piVar12;
                *local_8 = in_stack_00000014;
                *(uint *)(&stack0x00000484 + iStack00000008 * 4) = ~uVar6 & 0x100;
                local_8[1] = in_stack_00000018;
                iStack00000008 = iStack00000008 + 1;
                local_8[2] = in_stack_0000001c;
                local_8 = local_8 + 3;
              }
              else {
                *(int **)(&stack0x00000284 + iStack0000000c * 4) = piVar12;
                *in_stack_00000020 = in_stack_00000014;
                *(uint *)(&stack0x00000684 + iStack0000000c * 4) = ~uVar6 & 0x100;
                in_stack_00000020[1] = in_stack_00000018;
                iStack0000000c = iStack0000000c + 1;
                in_stack_00000020[2] = in_stack_0000001c;
                in_stack_00000020 = in_stack_00000020 + 3;
              }
            }
            else {
              for (piVar7 = DAT_006543b4; piVar7 < DAT_006543a0; piVar7 = piVar7 + 0x24) {
                if (*piVar7 == *piVar12) {
                  piVar7[2] = 0;
                  goto LAB_00458360;
                }
              }
              piVar7 = (int *)0x0;
LAB_00458360:
              if (piVar7 != (int *)0x0) {
                *piVar7 = 0;
              }
            }
          }
        }
        else {
          for (iVar8 = *(int *)(iVar8 + 100); iVar8 != 0; iVar8 = *(int *)(iVar8 + 0x60)) {
            puVar4 = (undefined4 *)
                     zone_satellite_map_context_helper_00494be0
                               ((float *)(iVar8 + 0x84),(float *)(iVar8 + 0x18),
                                (undefined4 *)&stack0x00000054);
            puVar10 = &stack0x00000024;
            for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
              *puVar10 = *puVar4;
              puVar4 = puVar4 + 1;
              puVar10 = puVar10 + 1;
            }
            pfVar5 = (float *)raster_scratch_arena_context_helper_00472d30
                                        ((float *)&stack0x0000003c,(int)param_1,
                                         (double)CONCAT44(in_stack_00000028,in_stack_00000024),
                                         (double)CONCAT44(in_stack_00000030,in_stack_0000002c),
                                         (double)CONCAT44(in_stack_00000038,in_stack_00000034));
            in_stack_00000014 = *pfVar5;
            in_stack_00000018 = pfVar5[1];
            in_stack_0000001c = pfVar5[2];
            uVar6 = software_raster_queue_context_helper_00472c10
                              ((int)param_1,&stack0x00000014,
                               *(float *)(iVar8 + 0x90) * _DAT_004bdfbc);
            if ((int)uVar6 < 1) {
              puVar4 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
              *(uint *)(iVar8 + 0x14) = *(uint *)(iVar8 + 0x14) & 0xffffffee;
              puVar4[0x10] = 0;
              puVar4[7] = iVar8;
              puVar4[0xd] = ~uVar6 & 0x100;
              puVar4[8] = in_stack_00000014;
              puVar4[9] = in_stack_00000018;
              puVar4[10] = in_stack_0000001c;
              if (*(int *)(iVar8 + 0x6c) == 0x33) {
                puVar4[0xc] = 0;
              }
              else {
                iVar9 = world_object_tree_context_helper_00457f40
                                  (piVar12,in_stack_0000001c * fStack00000010);
                puVar4[0xc] = iVar9;
              }
              if (*(int *)(iVar8 + 100) == 0) {
                puVar4[0xe] = 1;
              }
              else {
                puVar4[0xe] = 0;
              }
              uVar1 = *(undefined4 *)(iVar8 + 0x90);
              puVar4[0xf] = 0;
              puVar4[0xb] = uVar1;
              if ((*(byte *)(iVar8 + 0x10) & 0x40) == 0) {
                puVar4[3] = 5;
              }
              else {
                puVar4[3] = 7;
              }
              if (*(int *)(iVar8 + 0x6c) == 0x34) {
                iVar9 = *(int *)(iVar8 + 0x70);
                iVar2 = *(int *)(iVar9 + 0x10);
                if (iVar2 != 0) {
                  highlight_merge_context_helper_0048f750(iVar8,iVar2);
                  *(undefined4 **)(iVar9 + 0x14) = puVar4;
                  terrain_map_context_helper_004905c0();
                  goto LAB_00458202;
                }
              }
              i76_runtime_bin_terrain_polygon_work_record((float)puVar4[10] - (float)puVar4[0xb]);
            }
LAB_00458202:
          }
        }
      }
      iVar11 = iVar11 + 1;
      piVar12 = piVar12 + 0x1e;
    } while (iVar11 < g_active_world_object_entry_count);
  }
  if (0 < iStack0000000c) {
    local_8 = (float *)&stack0x00000284;
    pfVar5 = (float *)&stack0x00000e8c;
    iVar11 = iStack0000000c;
    do {
      piVar12 = (int *)*local_8;
      iVar8 = world_object_tree_context_helper_00457f40(piVar12,fStack00000010 * *pfVar5);
      if ((DAT_00654b86 != '\0') && (*pfVar5 < _DAT_004bdfa0)) {
        puVar4 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
        puVar4[3] = 0xb;
        puVar4[7] = piVar12;
        puVar4[8] = pfVar5[-2];
        puVar4[9] = pfVar5[-1];
        puVar4[10] = *pfVar5;
        puVar4[0xb] = piVar12[4];
        if (DAT_00654b86 == '\x01') {
          puVar4[0xc] = 3;
        }
        else {
          puVar4[0xc] = iVar8;
        }
        i76_runtime_bin_terrain_polygon_work_record(*pfVar5 - (float)piVar12[4]);
      }
      local_8 = local_8 + 1;
      pfVar5 = pfVar5 + 3;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  if (0 < iStack00000008) {
    local_8 = (float *)&stack0x00000084;
    pfVar5 = (float *)&stack0x0000088c;
    iVar11 = iStack00000008;
    do {
      piVar12 = (int *)*local_8;
      iVar8 = world_object_tree_context_helper_00457f40(piVar12,fStack00000010 * *pfVar5);
      if ((DAT_00654b86 != '\0') && (*pfVar5 < _DAT_004bdfa0)) {
        puVar4 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
        puVar4[3] = 3;
        puVar4[7] = piVar12;
        puVar4[8] = pfVar5[-2];
        puVar4[9] = pfVar5[-1];
        puVar4[10] = *pfVar5;
        puVar4[0xb] = piVar12[4];
        if (DAT_00654b86 == '\x01') {
          puVar4[0xc] = 3;
        }
        else {
          puVar4[0xc] = iVar8;
        }
        i76_runtime_bin_terrain_polygon_work_record(*pfVar5 - (float)piVar12[4]);
      }
      local_8 = local_8 + 1;
      pfVar5 = pfVar5 + 3;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  iVar11 = 0;
  if (0 < iStack0000000c) {
    local_8 = (float *)&stack0x00000e84;
    do {
      piVar12 = *(int **)(&stack0x00000284 + iVar11 * 4);
      iVar8 = *piVar12;
      iVar9 = world_object_tree_context_helper_00457f40(piVar12,local_8[2] * fStack00000010);
      puVar4 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
      uVar1 = *(undefined4 *)(&stack0x00000684 + iVar11 * 4);
      puVar4[3] = 6;
      puVar4[0xc] = iVar9;
      puVar4[0xd] = uVar1;
      puVar4[7] = iVar8;
      uVar1 = *local_8;
      puVar4[0x10] = piVar12;
      puVar4[8] = uVar1;
      puVar4[0xe] = 0;
      uVar1 = local_8[1];
      puVar4[0xf] = 0;
      puVar4[9] = uVar1;
      puVar4[10] = local_8[2];
      puVar4[0xb] = piVar12[4];
      i76_runtime_bin_terrain_polygon_work_record((float)puVar4[10] - (float)piVar12[4]);
      iVar11 = iVar11 + 1;
      local_8 = local_8 + 3;
    } while (iVar11 < iStack0000000c);
  }
  if (((((param_1 != (int *)0x0) && (iVar11 = get_current_headlight_runtime_state(), iVar11 == 0))
       && (*param_1 != 0)) &&
      ((iVar11 = *(int *)(*param_1 + 0x70), iVar11 != 0 &&
       (iVar8 = *(int *)(iVar11 + 0x440), iVar8 != 0)))) && ((*(byte *)(iVar8 + 0x10) & 1) == 0)) {
    ensure_world_object_geometry_variant_binding(iVar8,4);
    highlight_system_log_tag(*(int *)(iVar11 + 0x440),(int)param_1,-5.0);
  }
  iVar11 = 0;
  if (0 < iStack00000008) {
    local_8 = (float *)&stack0x00000884;
    do {
      piVar12 = *(int **)(&stack0x00000084 + iVar11 * 4);
      iVar8 = *piVar12;
      iVar9 = world_object_tree_context_helper_00457f40(piVar12,local_8[2] * fStack00000010);
      puVar4 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
      uVar1 = *(undefined4 *)(&stack0x00000484 + iVar11 * 4);
      puVar4[3] = 6;
      puVar4[0xc] = iVar9;
      puVar4[0xd] = uVar1;
      puVar4[7] = iVar8;
      uVar1 = *local_8;
      puVar4[0x10] = piVar12;
      puVar4[8] = uVar1;
      puVar4[0xe] = 0;
      uVar1 = local_8[1];
      puVar4[0xf] = 0;
      puVar4[9] = uVar1;
      puVar4[10] = local_8[2];
      puVar4[0xb] = piVar12[4];
      i76_runtime_bin_terrain_polygon_work_record((float)puVar4[10] - (float)piVar12[4]);
      iVar11 = iVar11 + 1;
      local_8 = local_8 + 3;
    } while (iVar11 < iStack00000008);
  }
  iVar11 = get_current_headlight_runtime_state();
  if ((iVar11 == 0) && (0 < iStack00000008)) {
    param_1 = (int *)&stack0x00000084;
    pfVar5 = (float *)&stack0x0000088c;
    iVar11 = iStack00000008;
    do {
      piVar12 = (int *)*param_1;
      iVar8 = *piVar12;
      iVar9 = is_vehicle_or_actor_runtime_world_object(iVar8);
      if (iVar9 != 0) {
        iVar8 = *(int *)(iVar8 + 0x70);
        iVar9 = *(int *)(iVar8 + 0x440);
        if ((iVar9 != 0) && ((*(byte *)(iVar9 + 0x10) & 1) == 0)) {
          ensure_world_object_geometry_variant_binding(iVar9,0);
          highlight_system_log_tag(*(int *)(iVar8 + 0x440),(int)param_1,*pfVar5 - (float)piVar12[4])
          ;
        }
      }
      param_1 = param_1 + 1;
      pfVar5 = pfVar5 + 3;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  return;
}


