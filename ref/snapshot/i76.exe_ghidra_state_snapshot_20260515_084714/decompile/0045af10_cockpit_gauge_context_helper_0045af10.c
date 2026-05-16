/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_0045af10
 * Entry: 0045af10
 * Signature: undefined __cdecl cockpit_gauge_context_helper_0045af10(float * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_0045af10. Remove duplicated
   cockpit wording. */

void __cdecl cockpit_gauge_context_helper_0045af10(float *param_1,int param_2)

{
  float fVar1;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  uint uVar11;
  float10 fVar12;
  int local_48;
  int local_44;
  int local_40;
  int *local_3c;
  uint local_38;
  int local_34;
  uint *local_30;
  float local_2c;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  pfVar2 = param_1;
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if ((((piVar3 != (int *)0x0) &&
       (iVar4 = is_vehicle_or_actor_runtime_world_object(*piVar3), iVar4 != 0)) &&
      (iVar4 = get_pending_active_player_ai_control_change_flag(), iVar4 == 0)) &&
     (fVar5 = (float)get_primary_vehicle_weapon_target_object(*piVar3), fVar5 != 0.0)) {
    uVar11 = *(uint *)((int)fVar5 + 0x10) >> 0x10 & 7;
    local_38 = uVar11;
    local_2c = fVar5;
    pfVar6 = (float *)get_world_object_position_vector(local_c,fVar5);
    local_18 = *pfVar6;
    local_14 = pfVar6[1];
    local_10 = pfVar6[2];
    pfVar6 = (float *)raster_scratch_arena_context_helper_00472d30
                                (local_c,(int)param_1,(double)local_18,(double)local_14,
                                 (double)local_10);
    local_24 = *pfVar6;
    local_20 = pfVar6[1];
    local_1c = _DAT_004bdfd8 / pfVar6[2];
    special_equipment_state_context_helper_00468620((int)fVar5);
    ftol();
    iVar4 = cockpit_gauge_context_helper_0045baa0(&local_24,param_1,&local_44,&local_48);
    if (iVar4 == 0) {
      local_28 = uVar11 * 0x10;
      local_34 = (&DAT_0054aad8)[uVar11 * 4];
      if (((local_34 != 0) && (piVar3 = *(int **)(&DAT_0054aadc + local_28), piVar3 != (int *)0x0))
         && ((*(int *)(&DAT_0054aae0 + local_28) != 0 &&
             (local_3c = *(int **)(&DAT_0054aae4 + local_28), local_3c != (int *)0x0)))) {
        iVar7 = ftol();
        local_40 = ftol();
        iVar4 = ftol();
        local_48 = local_48 + iVar4;
        iVar4 = *piVar3;
        iVar8 = local_44 + iVar7;
        local_30 = (uint *)(local_48 - local_40);
        iVar9 = local_44 - iVar7;
        local_3c = (int *)((iVar7 + local_44) - *local_3c);
        puVar10 = (uint *)(((piVar3[1] << 3) >> 3) + local_40 + local_48);
        iVar7 = local_38 * 0xd0;
        draw_bitmap_context_or_textured_quad
                  (param_1,&DAT_0054a458 + local_38 * 0x34,iVar9,
                   (uint *)(((*(int *)(local_34 + 4) << 3) >> 3) + local_40 + local_48),0,0,
                   (uint *)0x1);
        draw_bitmap_context_or_textured_quad
                  (param_1,(int *)(&DAT_0054a48c + iVar7),iVar8 - iVar4,puVar10,0,0,(uint *)0x1);
        puVar10 = local_30;
        draw_bitmap_context_or_textured_quad
                  (param_1,(int *)(&DAT_0054a4c0 + iVar7),iVar9,local_30,0,0,(uint *)0x1);
        draw_bitmap_context_or_textured_quad
                  (param_1,(int *)(&DAT_0054a4f4 + iVar7),(int)local_3c,puVar10,0,0,(uint *)0x1);
        fVar12 = compute_world_object_damage_integrity_percent((int)local_2c);
        param_1 = (float *)(float)fVar12;
        if ((float10)_DAT_004bdfdc < fVar12) {
          param_1 = (float *)0x42c80000;
        }
        if ((float)param_1 < _DAT_004be02c) {
          param_1 = (float *)0x3dcccccd;
        }
        if ((float)param_1 == _DAT_004bdfdc) {
          iVar4 = 3;
        }
        else {
          fVar5 = _DAT_004bdfe8;
          fVar1 = _DAT_004be030;
          for (iVar4 = 0; (fVar1 < (float)param_1 && (iVar4 < 2)); iVar4 = iVar4 + 1) {
            fVar5 = fVar5 - _DAT_004be034;
            fVar1 = fVar5 - _DAT_004be034;
          }
        }
        if (*(int *)((int)pfVar2[0xf] + 8) == 0) {
          iVar8 = ftol();
          iVar9 = iVar8 + 0xf;
          iVar7 = ftol();
          iVar7 = -iVar7;
          if (((DAT_004f70fc != iVar9) || (DAT_004f7100 != iVar7 + 0xf)) ||
             (DAT_004f67f0 != *(int *)(&DAT_0054a440 + iVar4 * 4))) {
            DAT_004f67f0 = *(int *)(&DAT_0054a440 + iVar4 * 4);
            DAT_004f70fc = iVar9;
            DAT_004f7100 = iVar7 + 0xf;
            fill_bitmap_surface_context(&DAT_0054a378,0xff);
            set_bitmap_surface_clip_rect(&DAT_0054a378,iVar9,0,iVar7 + 0xe,4);
            bitmap_surface_clip_context_helper_00474f60(&DAT_0054a378,(uint)DAT_0054a450);
            set_bitmap_surface_clip_rect(&DAT_0054a378,iVar8 + 0x10,1,iVar7 + 0xd,3);
            bitmap_surface_clip_context_helper_00474f60
                      (&DAT_0054a378,*(uint *)(&DAT_0054a440 + iVar4 * 4));
            set_bitmap_surface_clip_rect(&DAT_0054a378,0,0,0x1d,4);
          }
          if (param_2 == 0) {
            puVar10 = (uint *)((local_48 - local_40) + -5);
          }
          else {
            puVar10 = (uint *)(((*(int *)(*(int *)(&DAT_0054aadc + local_28) + 4) << 3) >> 3) +
                               local_40 + 10 + local_48);
          }
          draw_bitmap_context_or_textured_quad
                    (pfVar2,&DAT_0054a378,local_44 - *DAT_0054a3c0 / 2,puVar10,0,0,(uint *)0x1);
          return;
        }
        iVar7 = ftol();
        iVar8 = local_48 - local_40;
        iVar9 = local_44 - (iVar7 >> 1);
        cockpit_gauge_render_context_helper_0045b8c0
                  (pfVar2,DAT_0054a450,iVar9,iVar8 + -5,iVar7 + -1,4);
        cockpit_gauge_render_context_helper_0045b8c0
                  (pfVar2,*(uint **)(&DAT_0054a440 + iVar4 * 4),iVar9 + 1,iVar8 + -4,iVar7 + -2,3);
      }
    }
    else if ((DAT_0054ab94 != (int *)0x0) && (param_2 == 0)) {
      draw_bitmap_context_or_textured_quad
                (param_1,&DAT_0054a2b0,local_44 - *DAT_0054ab94 / 2,
                 (uint *)(local_48 -
                         (((DAT_0054ab94[1] << 3) >> 3) - ((DAT_0054ab94[1] << 3) >> 0x1f) >> 1)),0,
                 0,(uint *)0x1);
      return;
    }
  }
  return;
}


